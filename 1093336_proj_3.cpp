#include<bits/stdc++.h>
//#define cout fout //debug
using namespace std;
const int RsCycle[4] = { 2,2,4,8 };//add,sub,mul,div
const string instType[4] = { "+", "-", "*", "/" }, rsType[6] = { "", "RS1", "RS2", "RS3", "RS4", "RS5" };
bool RSOut[6] = { false, false, false, false, false, false }, RSStart[6] = { false, false, false, false, false, false }, RSing[6] = { false, false, false, false, false, false };
string RS[6][3] = { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" }, RAT[6] = { "", "", "", "", "", "" };
int RF[6] = { 0,0,2,4,6,8 }, RScyced[6] = { 0,0,0,0,0,0 };
map< string, int > basic;
vector< vector< string > >  code;
//ofstream fout("cout.txt");
void build() {
	basic["ADDI"] = 0, basic["ADD"] = 0;
	basic["SUB"]  = 1, basic["MUL"] = 2;
	basic["DIV"]  = 3, basic["RS1"] = 1;
	basic["RS2"]  = 2, basic["RS3"] = 3;
	basic["RS4"]  = 4, basic["RS5"] = 5;
	basic["+"]    = 0, basic["-"]   = 1;
	basic["*"]    = 2, basic["/"]   = 3;
}
void print() {
	cout << "   _ RF __\n";
	for (int i = 1; i < 6; i++) 
		cout << "F" << i << " |" << setw(4) << RF[i] << " |\n";	
	cout << "   -------\n\n";
	cout << "   _ RAT __\n";
	for (int i = 1; i < 6; i++) 
		cout << "F" << i << " |" << setw(5) << RAT[i] << " |\n";	
	cout << "   --------\n\n";
	cout << "    _ RS _________________\n";
	for (int i = 1; i < 4; i++) 
		cout << "RS" << i << " |" << setw(5) << RS[i][0] << " |" << setw(5) << RS[i][1] << " |" << setw(5) << RS[i][2] << " |\n";	
	cout << "    ----------------------\n";
	bool out = false;
	for (int i = 1; i < 4; i++) {
		if (RSOut[i]) {
			cout << "BUFFER: (RS" + to_string(i) << " Dispatch Done)" << RS[i][1] << " " << RS[i][0] << " " << RS[i][2] << " Next Cycle Can Write Result\n\n";
			RSOut[i] = false;
			break;
		}
		if (RS[i][1].find("RS") == string::npos && RS[i][2].find("RS") == string::npos && RScyced[i] == 0 && !RSStart[i] && RS[i][1] != "" && RS[i][2] != "" && !RSing[i]) {
			for (int j = 1; j < 4; j++) {
				if (RSing[j] == true) 
					out = true;				
			}
			if (out) {
				cout << "BUFFER: empty\n\n";
				break;
			}
			cout << "BUFFER: (RS" + to_string(i) << " Dispatch)" << RS[i][1] << " " << RS[i][0] << " " << RS[i][2] << " \n\n";
			RScyced[i] = RsCycle[basic[RS[i][0]]];
			RSing[i] = true;
			break;
		}
		else 
			if (i == 3) 
				cout << "BUFFER: empty\n\n";					
	}
	cout << "    ______________________\n";
	for (int i = 4; i < 6; i++) 
		cout << "RS" << i << " |" << setw(5) << RS[i][0] << " |" << setw(5) << RS[i][1] << " |" << setw(5) << RS[i][2] << " |\n";
	cout << "    ----------------------\n";
	out = false;
	for (int i = 4; i < 6; i++) {
		if (RSOut[i]) {
			cout << "BUFFER: (RS" + to_string(i) << " Dispatch Done)" << RS[i][1] << " " << RS[i][0] << " " << RS[i][2] << " Next Cycle Can Write Result\n\n";
			RSOut[i] = false;
			break;
		}
		if (RS[i][1].find("RS") == string::npos && RS[i][2].find("RS") == string::npos && RScyced[i] == 0 && !RSStart[i] && RS[i][1] != "" && RS[i][2] != "" && !RSing[i]) {
			for (int j = 4; j < 6; j++) {
				if (RSing[j] == true) 
					out = true;
			}
			if (out) {
				cout << "BUFFER: empty\n\n";
				break;
			}
			cout << "BUFFER: (RS" + to_string(i) << " Dispatch)" << RS[i][1] << " " << RS[i][0] << " " << RS[i][2] << " \n\n";
			RScyced[i] = RsCycle[basic[RS[i][0]]];
			RSing[i] = true;
			break;
		}
		else 
			if (i == 5) 
				cout << "BUFFER: empty\n\n";
	}	
}
int main() {
	build();
	ifstream fin("test.txt", ios::in);
	string s, buf;
	cout << "----------IN File----------\n";
	while (getline(fin, s)) {
		cout << s << endl;
		if (s.empty())
			continue;
		for (int i = 0; i < s.size(); i++)
			if (s[i] == ',')
				s[i] = ' ';
		stringstream ss(s);
		vector< string > tmp;
		while (ss >> buf)
			tmp.push_back(buf);
		code.push_back(tmp);		
	}
	cout << "---------------------------\n";
	int cycle = 1,nowRsNum = 0;;
	bool endCode = false, change = false;
	while (true) {
		change = false, nowRsNum = 0;
		for (int i = 1; i < 6; i++)RSStart[i] = false;
		vector< string > buf;
		if (!code.empty()) {
			buf = *code.begin();						
			if (buf[0] == "ADD" || buf[0] == "ADDI" || buf[0] == "SUB") {
				for (int i = 1; i <= 3; i++) {
					if (RS[i][0] == "" && RS[i][1] == "" && RS[i][2] == "") {
						nowRsNum = i;
						break;
					}
				}
				if (buf[0] == "SUB" && nowRsNum) {
					RS[nowRsNum][0] = "-";
					int first = buf[1][1] - '0', sec = buf[2][1] - '0', num = buf[3][1] - '0';					
					if (RAT[sec] != "")
						RS[nowRsNum][1] = RAT[sec];
					else
						RS[nowRsNum][1] = to_string(RF[sec]);
					if (RAT[num] != "")
						RS[nowRsNum][2] = RAT[num];
					else
						RS[nowRsNum][2] = to_string(RF[num]);
					RAT[first] = "RS" + to_string(nowRsNum);
					change = true;
					code.erase(code.begin());
				}
				else if ((buf[0] == "ADD" || buf[0] == "ADDI") && nowRsNum) {
					RS[nowRsNum][0] = "+";
					int first = 0, sec = 0, num = 0;
					if (buf[0] == "ADD") {
						first = buf[1][1] - '0', sec = buf[2][1] - '0', num = buf[3][1] - '0';
						if (RAT[num] != "")
							RS[nowRsNum][2] = RAT[num];
						else
							RS[nowRsNum][2] = to_string(RF[num]);
					}
					else {
						first = buf[1][1] - '0', sec = buf[2][1] - '0', num = buf[3][0] - '0';
						RS[nowRsNum][2] = to_string(num);
					}					
					if (RAT[sec] != "")
						RS[nowRsNum][1] = RAT[sec];
					else
						RS[nowRsNum][1] = to_string(RF[sec]);
					RAT[first] = "RS" + to_string(nowRsNum);
					change = true;
					code.erase(code.begin());
				}
			}
			if (buf[0] == "MUL" || buf[0] == "DIV") {
				for (int i = 4; i <= 5; i++) {
					if (RS[i][0] == "" && RS[i][1] == "" && RS[i][2] == "") {
						nowRsNum = i;
						break;
					}
				}
				if (buf[0] == "DIV" && nowRsNum) {
					RS[nowRsNum][0] = "/";
					int first = buf[1][1] - '0', sec = buf[2][1] - '0', num = buf[3][1] - '0';					
					if (RAT[sec] != "")
						RS[nowRsNum][1] = RAT[sec];
					else
						RS[nowRsNum][1] = to_string(RF[sec]);
					if (RAT[num] != "")
						RS[nowRsNum][2] = RAT[num];
					else
						RS[nowRsNum][2] = to_string(RF[num]);
					RAT[first] = "RS" + to_string(nowRsNum);
					change = true;
					code.erase(code.begin());
				}
				else if (buf[0] == "MUL" && nowRsNum) {
					RS[nowRsNum][0] = "*";
					int first = buf[1][1] - '0', sec = buf[2][1] - '0', num = buf[3][1] - '0';					
					if (RAT[sec] != "")
						RS[nowRsNum][1] = RAT[sec];
					else
						RS[nowRsNum][1] = to_string(RF[sec]);

					if (RAT[num] != "")
						RS[nowRsNum][2] = RAT[num];
					else
						RS[nowRsNum][2] = to_string(RF[num]);
					RAT[first] = "RS" + to_string(nowRsNum);
					change = true;
					code.erase(code.begin());
				}
			}
		}
		RSStart[nowRsNum] = true;
		for (int i = 1; i < 6; i++) {
			if (RScyced[i] > 0) {
				RScyced[i]--; 
				if (RScyced[i] == 0) RSOut[i] = true;
			}
			else {
				//WR
				if (RScyced[i] == 0 && RS[i][0] != "" && !RSStart[i] && RSing[i]) {
					string tmp = "RS" + to_string(i);
					int ans = 0;
					if (basic[RS[i][0]] == 0)
						ans = atoi(RS[i][1].c_str()) + atoi(RS[i][2].c_str());
					if (basic[RS[i][0]] == 1)
						ans = atoi(RS[i][1].c_str()) - atoi(RS[i][2].c_str());
					if (basic[RS[i][0]] == 2)
						ans = atoi(RS[i][1].c_str()) * atoi(RS[i][2].c_str());
					if (basic[RS[i][0]] == 3)
						ans = atoi(RS[i][1].c_str()) / atoi(RS[i][2].c_str());
					for (int k = 1; k < 6; k++) {
						if (RAT[k] == tmp) 
							RAT[k] = "", RF[k] = ans;
						
						for (int j = 0; j < 3; j++) {
							if (RS[k][j] == tmp) {
								RS[k][j] = to_string(ans);								
							}
						}
					}					
					RS[i][0] = RS[i][1] = RS[i][2] = "";
					RSing[i] = false;
					change = true;
				}
			}
		}
		if (change) {
			cout << "Cycle: " << cycle << endl;
			print();
		}
		cycle++;
		bool flag = false;
		if (code.empty()) 
			for (int i = 1; i < 6; i++) {
				if (RAT[i] != "" || RScyced[i] != 0 || RSing[i]) 
					break;
				else
					if (i==5) 
						flag = true;									
			}		
		if (flag)
			break;			
	}	
	return 0;
}