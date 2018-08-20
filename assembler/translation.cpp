
#include"stdafx.h"
#include <algorithm>
#include "translation.h"
#include <sstream>
using std::istringstream;

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
string data; //写入数据
int translation(int Type, string s);
int bit_type = 16;//默认16位 default 16bit


void read_code_first(string Filename,int bit)//第一次阅读代码并翻译 read code and translation
{
	if (bit != 16)
	{
		bit_type = bit;//change bit
	}
	
	int error_type = 0;
	data = "";
	ofstream outfile(Filename);
	string file = "temp";
	ifstream infile;
	infile.open(file.data());   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 
	string s;
	while (getline(infile, s))
	{
		 error_type = translation(judge(s), s);
		 error(error_type);
	}
	instruct->clear();
	outfile << data << endl;
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
	string str[2];
	string comma = ",";
	string Space = " ";
	//
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
	//
	if (Type = 0) { 
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
			if (str[0].compare(SR[i]) == 0) { segReg_1 = true; break; }
			if (str[1].compare(SR[i]) == 0) { segReg_2 = true; break; }
		}
		for (int i = 0; i < 8; ++i)
		{
			
			if (str[0].compare(GR_8[i]) == 0) { reg8_1 = true; break; }//确定参数一是否是8位寄存器 reg8
			if (str[1].compare(GR_8[i]) == 0) { reg8_2 = true; break; }//确定参数二是否是8位（后面不再说明）
			if (str[0].compare(GR_16[i]) == 0) { reg16_1 = true; break; }
			if (str[1].compare(GR_16[i]) == 0) { reg16_2 = true; break; }
			if (str[0].compare(GR_32[i]) == 0) { reg32_1 = true; break; }
			if (str[1].compare(GR_32[i]) == 0) { reg32_2 = true; break; }
		}
		//判断结束  judge end
		//开始翻译 Start translating

		
	}//mov
	else if (Type = 1) {}//lea

	return 0;
}