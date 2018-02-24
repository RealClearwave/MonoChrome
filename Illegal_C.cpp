#include <bits/stdc++.h>
#include <cstdlib>
#include <windows.h>

#define CL_RED system("color 4");
#define CL_GREEN system("color 2");
#define print cout<<
#define chr(x) x
#define dpsec 50
#define fdtkt(s) {fin.close();fin.open(s,ios_base::in|ios_base::out);}
using namespace std;

fstream fin;

struct acc {
	int stat,ful;
	string name,pswd;
} cacc;
int tc,st,ff[501];
string ch[501],txt[501],nm[501];
bool gone[501];

string vg[501];
int lg[501],vn;

int find_val(string s) {
	int i=1;//cout<<s<<endl;
	while(vg[i] != s) i++;
	return i;
}

void set_val(string s,int x) {
	int p = find_val(s);
	lg[p] = x;
}

void add_val(string s,int x) {
	int p = find_val(s);
	lg[p] += x;
}

void dp(string s) {
	CL_GREEN;
	int xal = 0;
	for (int i=0; i<s.length(); i++) {
		if (s[i] == '$') continue;
		if (s[i] == '*') {
			xal = i+1;
			while (s[xal] != '#') xal++;
			string ss = s.substr(i+1,xal-i-1);
			xal = 0;
			while (xal < ss.length()){
				xal ++;
				if (ss[xal] == '+' || ss[xal] == '=' || ss[xal] == '-'){
					string p;int q;
					p = ss.substr(0,xal);
					q = stoi(ss.substr(xal+1));
					if (ss[xal] == '+'){
						add_val(p,q);
					}else if (ss[xal] == '-'){
						add_val(p,-q);
					}else if (ss[xal] == '='){
						set_val(p,q);
					}
				}
			}
		} else if (s[i] == '%' ) {
			xal = i+1;
			while (s[xal] != '#')
				xal+=1;
			system(s.substr(i+2,xal-i-1).c_str());
			CL_RED;
			print "[SYSTEM]:Executing:\\";
			CL_GREEN;
		} else {
			if (chr(s[i]) != '#') {
				print chr(s[i]);
				Sleep(dpsec);
			} else
				cout<<endl;
		}
	}
}

void Login() {
	dp("Loading...\n");
	fdtkt("Save.cfg");
	fin>>cacc.name;

	fdtkt("Game.ini");
	fin>>cacc.ful;
	if (!cacc.ful) {
		cout<<"E:Game.ini Missing or Destoyed!";
		while(1);
	}


	string s;
	if (cacc.name == "") {
		while(fin>>s) {
			int p = s.find('=');
			vn ++;
			vg[vn] = s.substr(0,p);
			lg[vn] = stoi(s.substr(p+1));
		}
		
		fdtkt("Save.cfg");
		fin<<"admin"<<endl<<"alpine"<<endl<<1<<endl;
		for (int i=1;i<=vn;i++){
			fin<<vg[i]<<'='<<lg[i]<<endl;
		}
		cacc.name = "admin";
		cacc.pswd = "alpine";
		cacc.stat = 1;
		st = cacc.stat;
	}else{
		fdtkt("Save.cfg");
		fin>>cacc.name>>cacc.pswd>>cacc.stat;
		st = cacc.stat;
		while(fin>>s) {
			int p = s.find('=');
			vn ++;
			vg[vn] = s.substr(0,p);
			lg[vn] = stoi(s.substr(p+1));
		}
	}
	
	return;
}

bool PlayScript(int st) {
	string s,spath = "Scripts\\scr" + to_string(st) + ".log";
	fdtkt(spath);
	fin>>s;
	if (s != "@Characters_Start") {
		if (st < cacc.ful)
			cout<<"E:Scripts Has Been Damaged or Missing.";
		else {
			cout<<"It seems that you have found the True End.\n";
			cout<<"Have a Good Time or delete the Save.cfg to play again!\n";
		}
		return false;
	}

	memset(gone,false,sizeof(gone));
	while(s != "@Characters_End") {
		fin>>s;
		tc++;
		ch[tc] = s;
		//nm[tc] =nnm;
	}
	tc--;
	for (int i=1; i<=tc; i++) {
		fdtkt("Characters\\" + ch[i]);
		while (getline(fin,s)) {
			txt[i] += s;
		}
		//cout<<"Characters\\" + ch[i]<<endl;
	}

	//cout<<tc<<endl;
	int exit = 0;
	int i = 0,tff;
	bool prt;
	while (exit < tc) {
		i++;
		if (i > tc) i = 1;
		while (gone[i]) {
			i++;
			if (i > tc) i = 1;
		}


		tff = ff[i];
		ff[i] = txt[i].find('$',ff[i]+1);

		prt = false;
		if (ff[i] == -1) {
			exit++;
			gone[i] = true;
		} else if (txt[i].substr(tff,ff[i]-tff+1) != "") {
			cout<<'['<<ch[i].substr(0,ch[i].find('\\'))<<"]:";
			dp(txt[i].substr(tff,ff[i]-tff+1));
			prt = true;
		}

		if (prt) system("pause>nul");
	}

	int sel;
	dp("Play Next?(0 for No Or 1 for Yes)");
	cin>>sel;
	return (bool)sel;
}
int main() {
	Login();
	while (PlayScript(st)) st++;
	
	system("del Save.cfg>nul");
	system("copy Save.bak Save.cfg>nul");
	fdtkt("Save.cfg");
	fin<<cacc.name<<endl<<cacc.pswd<<endl;
	fin<<st+1<<endl;
	
	for (int i=1;i<=vn;i++){
		fin<<vg[i]<<'='<<lg[i]<<endl;
	}

	return 0;
}
