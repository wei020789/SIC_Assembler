#include "pass1.h"

void output()
{
	out.open("output.txt",ios::out,ios::trunc);
	for (int i = 0; i < index; i++)
	{
		ad = address[i], lab = label[i], mne = mnemonic[i], ope = operand[i];
		string code;
		if (mne == "START" || mne == "RESW" || mne == "RESB") opcode[i] = "\0";
		else if (mne == "RSUB")
		{
			operand[i] = "\0";
			opcode[i] = getopcode(mne) + "0000";
		}
		else if (mne == "BYTE")
		{
			string s;
			if (ope[0] == 'X')
			{
				for (int i = 2; i < ope.size() - 1; i++)
				{
					s += ope[i];
				}
				opcode[i] = s;
			}
			else
			{
				for (int i = 2;  i < ope.size() - 1; i++)
				{
					s += dth(ope[i]);
				}
				opcode[i] = s;
			}
		}
		else if (mne == "WORD")
		{
			int temp = 0;
			for (char c : ope)
				temp = temp * 10 + c - '0';
			opcode[i] = dth(temp);
			while (opcode[i].size() < 6)
			{
				opcode[i].insert(0, "0");
			}
		}
		else if (mne == "END") break;
		else
		{
			if (ope[ope.size() - 1] == 'X' && ope[ope.size() - 2 == ','])
			{
				string temp;
				for (int i = 0; i < ope.size() - 2; i++)
				{
					temp += ope[i];
				}
				code = strAdd(lta[temp], "32768");
				opcode[i] = getopcode(mne) + code;
			}
			else
				opcode[i] = getopcode(mne) + lta[ope];
		}
	}
	for (int i = 0; i < index; i++)		
		out << address[i] << '\t' << label[i] << '\t' << mnemonic[i] << "\t" << operand[i] << "\t" << opcode[i] << endl;
	out.close();
}

void cz()
{
	for (int i = 0; i < index; i++)
	{
		while (address[i].size() < 6)
			address[i].insert(0, "0");
	}
}
string len(string s1, string s2,int i)
{
	string re;
	re = dth(htd(s1) - htd(s2));
	while (re.size() < i)
		re.insert(0, "0");
	return re;
}
void object()
{
	out.open("objectcode.txt", ios::out, ios::trunc);
	string start, end, s;
	int count = 0;
	
	out << "H " << label[0] << ' ' << address[0] << ' ' << len(address[index - 1], address[0], 6) << endl;

	for (int i = 1; i < index; i++)
	{
		count++;

		if (opcode[i] == "\0")
		{
			if (start == "\0")
			{
				count = 0;
				start = "\0";
				end = "\0";
				continue;
			}
			else
			{
				out << "T " << start << ' ' << len(end, start, 2) << ' ' << s << endl;
				count = 0;
				start = "\0";
				end = "\0";
				s.clear();
				continue;
			}
		}
		if (count == 1)
		{
			start = address[i];
			s += opcode[i] + ' ';
		}
		else
		{
			s += opcode[i] + ' ';
			if (i != index - 1)
				end = address[i + 1];
			else
				end = address[i];
		}
		if (count == 10 || i == index-1)
		{
			out << "T " << start << ' ' << len(end, start, 2) << ' ' << s << endl;
			count = 0;
			start = "\0";
			end = "\0";
			s.clear();
		}
	}
	out << "E " << address[0];
	cout << "輸出成功!" << endl <<"檔案loc.txt、output.txt、objectcode.txt已建好" << endl;
}