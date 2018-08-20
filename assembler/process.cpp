#include"stdafx.h"
#include "translation.h"
#include <algorithm>
#include<fstream>


void process(string file)
{
	//Erase space and annotation
	ifstream in;
	in.open(file.data());   
	assert(in.is_open());   
	assert(in.is_open());
	ofstream out("temp");
	string s = "";
	string str = "";
	string data = "";
	bool validity = false;
	int i = 0;
	while (getline(in, s))
	{
		
		for (i = 0; i < s.length(); i++)//情况：注释“#”，前头有空格的，前头没空格的，空行。
		{									//单引号是char类型，双引号是字符串类型。
			if (s[i] != ' ')
			{
				if (s[i] == '#') 
				{
					validity = false;
					break;
				}//注释，跳过
				else 
				{
					validity = true;
					break;
				}
				

			}
			

		}

		if (validity)
		{
			for (;i < s.length(); i++)
			{
				str += s[i];

			}

		}
		if (str != "")//空行，跳过
		{
			data += (str += '\n');

		}
		
		str = "";

	}
	

	out << data << endl;
	cout << data << endl;
	data = "";
	str = "";
	in.close();
	out.close();
		//逐行读取数据并存于data中，直至数据全部读取
	//设置obj路径 Set the path of obj
	file = file.substr(0, file.rfind("."));//去掉后缀名
	string new_file = file + (string)".obj";
	cout << new_file << endl;
	//
	read_code_first(new_file);//第一次阅读代码
	

	//


}