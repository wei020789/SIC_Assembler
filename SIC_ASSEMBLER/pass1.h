#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "opcode.h"
#include <map>
using namespace std;

int index = 0;
vector<string> address, label, mnemonic, operand,opcode;
ofstream out;
map<string, string> lta;
string ad, lab, mne, ope, opc;
void table() {
	ifstream file("input.txt");
	string s, temp;
	if (file.is_open())
	{
		while (getline(file, s))
		{	
			bool foundop=0;
			if (s[0] == '.')continue;
			for (int i = 0; i < s.length(); i++)
			{
				address.push_back("\t");
				label.push_back("\t");
				mnemonic.push_back("\t");
				operand.push_back("\t");
				opcode.push_back("\t");
				while (i < s.size() && s[i] != '\t' && s[i] != '\n' && s[i] != ' ')
					temp += s[i++];
				if (getopcode(temp) == "-1" && (temp != "START" && temp != "END" && temp != "RESW" && temp != "RESB" && temp != "WORD" && temp != "BYTE"))
				{
					if (foundop) operand[index] = temp;
					else label[index] = temp;
				}
				else
				{
					mnemonic[index] = temp;
					foundop = 1;
				}
				temp.clear();
			}			
			index++;
		}
	}
	else
		cout << "open file error!" << endl;
	file.close();
}
string dth(int i)
{
	string s, ts;
	int temp;
	while (i != 0) {
		temp = i % 16;
		if (temp > 9) ts = temp - 10 + 'A';
		else ts = temp + '0';
		s.insert(0, ts);
		i /= 16;
	}
	return s;
}
int htd(string s)
{
	int sum = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] > '9') sum = sum*16 + s[i] - 'A' + 10;
		else sum = sum * 16 + s[i] - '0';
	}
	return sum;
}
string strAdd(string s1, string s2)
{
	int n1 = htd(s1), n2 = 0;
	for (int i = 0; i < s2.size(); i++)
	{
		n2 = n2 * 10 + s2[i]-'0';
	}
	return dth(n1 + n2);
}
string strAdd(string s1, string s2, bool mode)
{
	int n1 = htd(s1), n2 = 0;
	for (int i = 0; i < s2.size(); i++)
	{
		n2 = n2 * 10 + s2[i] - '0';
	}
	if(mode)
		return dth(n1 + 3*n2);
	return "-2";
}
void loc()
{
	out.open("loc.txt", ios::out, ios::trunc);
	int i = 1;
	address[0] = operand[0];
	while (mnemonic[i-1]!="END")
	{
		if (mnemonic[i - 1] == "START")
		{
			address[i] = address[i - 1];
		}
		else if (mnemonic[i - 1] == "BYTE")
		{
			if (operand[i - 1][0] == 'C')
			{
				int sum = operand[i-1].size()-3;
				address[i] = strAdd(address[i - 1], to_string(sum));
			}
			else
			{
				int sum = operand[i - 1].size() - 3;
				if(sum%2) address[i] = strAdd(address[i - 1], to_string(sum/2+1));
				else address[i] = strAdd(address[i - 1], to_string(sum/2));
			}
		}
		else if (mnemonic[i - 1] == "WORD")
		{
			address[i] = strAdd(address[i - 1], "3");
		}
		else if (mnemonic[i - 1] == "RESB")
		{
			address[i] = strAdd(address[i - 1], operand[i-1]);
		}
		else if (mnemonic[i - 1] == "RESW")
		{
			address[i] = strAdd(address[i - 1], operand[i - 1],1);
		}
		else
		{
			address[i] = strAdd(address[i - 1], "3");
		}
		if(label[i]!="\0") lta[label[i]] = address[i];
		i++;
	}
	for (int i = 0; i < index; i++)		out << address[i] << '\t' << label[i] << '\t' << mnemonic[i] << '\t' << operand[i] << endl;
	out.close();
}