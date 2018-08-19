
#include"stdafx.h"
#include <algorithm>
#include "translation.h"
string instruct[39] = {"MOV", "LEA","IMM","JMP","CALL","JZ","JNZ","ENT","ADJ","LEV","LI","LC","SI","SC","PUSH","OR","XOR","AND","EQ","NE","LT","GT","LE","GE","SHL","SHR","ADD","SUB","MUL","DIV","MOD","OPEN","READ","CLOS","PRTF","MALC","MSET","MCMP","EXIT"};



string ss;
string op;//开头
void cprintf(char* str, WORD color, ...);
void read_code();
string EraseSpace(string &s);
int judge(string s);



void read_code_first()//第一次阅读代码并翻译
{
	string file = "one";
	ifstream infile;
	infile.open(file.data());   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

	string s;
	while (getline(infile, s))
	{
		judge(s);
		//cout << s << endl;
	}
	infile.close();             //关闭文件输入流 
}


void cprintf(char* str, WORD color, ...) {
	WORD colorOld;
	HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	colorOld = csbi.wAttributes;
	SetConsoleTextAttribute(handle, color);
	std::cout << str;
	SetConsoleTextAttribute(handle, colorOld);
}


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
	for(i = 0; i<39; ++i){
		if (op.compare(instruct[i]) == 0) { break; }
		


		
	}
	
	
	op = "";
	return i;
	
		
}