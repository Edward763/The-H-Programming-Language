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

	ofstream out("one");
	string s = "";
	string str = "";
	string data = "";
	bool validity = false;
	int i = 0;
	while (getline(in, s))
	{
		
		for (i = 0; i < s.length(); i++)//�����ע�͡�#����ǰͷ�пո�ģ�ǰͷû�ո�ģ����С�
		{									//��������char���ͣ�˫�������ַ������͡�
			if (s[i] != ' ')
			{
				if (s[i] == '#') 
				{
					validity = false;
					break;
				}//ע�ͣ�����
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
		if (str != "")//���У�����
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
		//���ж�ȡ���ݲ�����data�У�ֱ������ȫ����ȡ

	read_code_first();//��һ���Ķ�����
	

	//


}