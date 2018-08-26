
#include"stdafx.h"
#include <algorithm>
#include "translation.h"
#include <sstream>
using std::istringstream;
using std::ios;
using std::hex;
using std::ios_base;

string instruct[39] = {"MOV", "LEA","IMM","JMP","CALL","JZ","JNZ","ENT","ADJ","LEV","LI","LC","SI","SC","PUSH","OR","XOR","AND","EQ","NE","LT","GT","LE","GE","SHL","SHR","ADD","SUB","MUL","DIV","MOD","OPEN","READ","CLOS","PRTF","MALC","MSET","MCMP","EXIT"};
int number = 39;
string GR_8[8] = { "AL","AH","BL","BH","CL","CH","DL","DH" };// General_register 8
string GR_16[8] = {"AX","BX","CX","DX","BP","SP","SI","DI" };// General_register 16
string GR_32[8] = {"EAX","EBX","ECX","EDX","EBP","ESP","ESI","EDI" };// General register 32
string SR[6] = {"ES","CS","SS","DS","FS","GS"};//Segment Register
string IP[2] = { "IP","EIP" };//16 32 Instruction Pointer
string FR[2] = { "Flags","EFlags" };//16 32 Flags Register

string ss;
string op;//开头
string EraseSpace(string &s);
int judge(string s);
char bytes_16[] = {0x0,0x0}; //写入数据
char bytes_16_2[] = { 0x0,0x0 };
int translation(int Type, string s);
int bit_type = 16;//默认16位 default 16bit

bool R_16 = false;


void read_code_first(string Filename,int bit)//第一次阅读代码并翻译 read code and translation
{
	if (bit != 16)
	{
		bit_type = bit;//change bit
	}
	
	int error_type = 0;
	
	//
	ofstream outfile;
	outfile.open(Filename , ios::trunc | ios::binary| ios_base::out);
	
	
	
	//准备进行写入
	//
	string file = "temp";
	ifstream infile;
	infile.open(file.data());   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 
	string s;




	if (bit_type == 16)
	{
		while (getline(infile, s))
		{
			error_type = translation(judge(s), s);
			error(error_type);
			if (R_16)
			{
				outfile.write(bytes_16, 2);
			}
		}
	}





	instruct->clear();
	outfile.close();
	infile.close();             //关闭文件输入流 
	remove("temp");//删除缓存  delete temp
}//结束 end





string EraseSpace(string &s)
{
	s.erase(s.find_last_not_of(" ") + 1);
	s.erase(0, s.find_first_not_of(" "));
	return s;
}

int judge(string s)
{
	int i;
	
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] != ' ')
		{
			op += s[i];
		}
		else
		{
			break;
		}

	}

	s = "";
	
	transform(op.begin(), op.end(), op.begin(), ::toupper);
	cout << op << endl;
	for(i = 0; i<number; ++i){
		if (op.compare(instruct[i]) == 0) { op = "";  return i; }
	}
	
	op = "";
	
	return -1;
	
		
}

int translation(int Type, string s)
//参数分别是指令的类型以及该指令 Parameter is the types of instruction and instruction
//返回的是错误类型的编号 Return error type serial number 
{
	string str[2] = { "","" };
	string comma = ",";
	string Space = " ";
	//
	int i_1;
	int i_2;
	bool reg8_1 = false;
	bool reg8_2 = false;
	bool reg16_1 = false;
	bool reg16_2 = false;
	bool reg32_1 = false;
	bool reg32_2 = false;
	bool segReg_1 = false;
	bool segReg_2 = false;
	bool mem8_1 = false;
	bool mem8_2 = false;
	bool mem16_1 = false;
	bool mem16_2 = false;
	bool mem32_1 = false;
	bool mem32_2 = false;
	R_16 = false;
	//
	
	if (Type == 0)
	{ 
		s.erase(0,3);//删除mov方便后面处理
		EraseSpace(s);//删除里面的空格
		s = s.replace(s.find(comma), comma.length(),Space);
		istringstream is(s);
		is >> str[0] >> str[1];
		transform(str[0].begin(), str[0].end(), str[0].begin(), ::toupper);//大写capital letters
		transform(str[1].begin(), str[1].end(), str[1].begin(), ::toupper);
		
		//开始处理可能情况Start processing (先确定两个参数的类型)(Determine the type of two parameters)
		for (int i = 0; i < 6; ++i)
		{
			if (str[0].compare(SR[i]) == 0) { segReg_1 = true; i_1 = i; break; }
			if (str[1].compare(SR[i]) == 0) { segReg_2 = true; i_2 = i; break; }
		}
		if (segReg_1 == false)
		{
			for (int i = 0; i < 8; ++i)
			{

				if (str[0].compare(GR_8[i]) == 0) { reg8_1 = true; i_1 = i; break; }//确定参数一是否是8位寄存器 reg8
				if (str[0].compare(GR_16[i]) == 0) { reg16_1 = true; i_1 = i; break; }
				if (str[0].compare(GR_32[i]) == 0) { reg32_1 = true; i_1 = i; break; }
			}
		}
		
			
		
		if (segReg_2 == false)
		{
			for (int i = 0; i < 8; ++i)
			{
				if (str[1].compare(GR_8[i]) == 0) { reg8_2 = true; i_2 = i; break; }//确定参数二是否是8位（后面不再说明）
				if (str[1].compare(GR_16[i]) == 0) { reg16_2 = true; i_2 = i; break; }
				if (str[1].compare(GR_32[i]) == 0) { reg32_2 = true; i_2 = i; break; }
			}
		}
		//判断结束  judge end
		//开始翻译 Start translating
		
		//8bit 暂时不管 unfinished
		
		//
		//16位
		if (reg16_1)//MOV reg16,reg16/mem16
		{
			bytes_16[0] = 0x89;
			if (reg16_2)//mov reg16,reg16 89
			{
				if (i_1 == i_2)
				{
					if (i_1 == 0) { bytes_16[1] = 0xC0; R_16 = true; return 0;};//mov ax,ax
					if (i_1 == 1) { bytes_16[1] = 0xDB; R_16 = true; return 0;};//bx,bx
					if (i_1 == 2) { bytes_16[1] = 0xC9; R_16 = true; return 0;}//cx,cx
					if (i_1 == 3) { bytes_16[1] = 0xD2; R_16 = true; return 0;};//dx,dx
				}
				else
				{
					if (i_1 == 0)
					{
						if (i_2 == 1){ bytes_16[1] = 0xD8; R_16 = true; return 0;}//ax,bx
						if (i_2 == 2) { bytes_16[1] = 0xC8; R_16 = true; return 0; }//ax,cx
						if (i_2 == 2) { bytes_16[1] = 0xD0; R_16 = true; return 0; }//ax,dx
					}
					else if (i_1 == 1) 
					{
						if(i_2 == 0) { bytes_16[1] = 0xC3; R_16 = true; return 0; }//bx,ax
						if (i_2 == 2) { bytes_16[1] = 0xCB; R_16 = true; return 0; }//bx,cx
						if (i_2 == 3) { bytes_16[1] = 0xD3; R_16 = true; return 0; }//bx,dx
					}
					else if (i_1 == 2)
					{
						if (i_2 == 0) { bytes_16[1] = 0xC1; R_16 = true; return 0; }//cx,ax
						if (i_2 == 1) { bytes_16[1] = 0xD9; R_16 = true; return 0; }//cx,bx
						if (i_2 == 3) { bytes_16[1] = 0xD1; R_16 = true; return 0; }//cx,dx
					}
					else if (i_1 == 3)
					{
						if (i_2 == 0) { bytes_16[1] = 0xC2; R_16 = true; return 0; }//dx,ax
						if (i_2 == 1) { bytes_16[1] = 0xDA; R_16 = true; return 0; }//dx,bx
						if (i_2 == 2) { bytes_16[1] = 0xCA; R_16 = true; return 0; }//dx,cx
					}
				}


				
			}
			else
			{
				
				if (str[1][str[1].size() - 1] != 'H') {  }//十进制立即数
				else {  }//十六进制立即数
			}


		}
		


	}//mov
	else if (Type == 1) {}//lea

	return 1;//未找到错误 return 0;是正常
}