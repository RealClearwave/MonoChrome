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

int cmp_val(string s,int x) {
	int p = find_val(s);
	if (lg[p] < x) return 0;
	if (lg[p] == x) return 1;
	if (lg[p] > x) return 2;
}


void calc(string p,char x,int q) {
	if (x == '+') {
		add_val(p,q);
	} else if (x == '-') {
		add_val(p,-q);
	} else if (x == '=') {
		set_val(p,q);
	}
}

void dp(string s);
void calc0(string s) {
	string a;
	char x;
	int b;
	int p=0;
	while (!(s[p] == '+' || s[p] == '=' || s[p] == '-') && p < s.length()) p++;//cout<<p<<endl;
	//cout<<s<<' '<<p<<endl;
	if (p < s.length()){
	a = s.substr(0,p);
	x = s[p];
	b = stoi(s.substr(p+1));
	//cout<<a<<' '<<x<<' '<<b<<endl;
	calc(a,x,b);
	}else{
		//cout<<p<<endl;
		dp(s);
	}
}
bool dec_cmp(string s) {
	string a;
	char x;
	int b;
	int p = 0;
	while (!(s[p] == '<' || s[p] == '=' || s[p] == '>')) p++;
	a = s.substr(0,p);
	x = s[p];
	b = stoi(s.substr(p+1));
	//cout<<a<<' '<<x<<' '<<b<<endl;
	int r = cmp_val(a,b);//cout<<r<<endl;
	if (x == '<' && r == 0) return true;
	if (x == '=' && r == 1) return true;
	if (x == '>' && r == 2) return true;
	return false;
}
void decode_if(string s) {
	//Like A=B?1=2:3=4
	int pe = s.find('?');
	int ps = s.find(':');

	//cout<<pe<<' '<<ps<<endl;
	string sg1 = s.substr(0,pe);
	string sg2 = s.substr(pe+1,ps-pe-1);
	string sg3 = s.substr(ps+1);
	//cout<<sg1<<' '<<sg2<<' '<<sg3<<endl;

	bool bol = dec_cmp(sg1);
	if (bol)
		calc0(sg2);
	else
		calc0(sg3);
}

string ag_e[501],ats;
void agent(string s) {
	int lp = s.find('[');
	int rp = s.find(']');
	int p1 = s.find(',');
	int p2 = s.find(',',p1+1);
	string ask = s.substr(lp+1,rp-1);
	int np = rp+1,tp;
	cout<<"Q:"<<ask<<endl;
	int comp = 0;
	while (np != -1) {
		tp = np;
		while (s[tp] == ';') tp ++;
		np = s.find(';',np+1);
		ats = s.substr(tp,np-1-tp);
		if (ats[0] == '@') break;
		//cout<<ts<<endl;
		int fp = ats.find(',');
		string k,l;
		k = ats.substr(0,fp);
		l = ats.substr(fp+1);
		//cout<<k<<' '<<l;
		comp++;
		cout<<k<<"....."<<comp<<endl;
		ag_e[comp] = l;
	}
	int sel = 2147483;
	
	while(sel > comp){
		cout<<"Your Choise:";
		cin>>sel;
	}
	calc0(ag_e[sel]);
}

int g_i;
bool PlayScript(int st);
bool exe(string s,int i){
	string v;
	int p = s.find(' ');
	v = s.substr(0,p);
	//cout<<s.substr(p+1)<<endl;
	//cout<<v<<endl;
	if (v == "jump"){
		fdtkt("Characters\\"+s.substr(p+1));
		string ss;
		txt[g_i] = "";ff[i] = 0;
		while (getline(fin,ss)) {
			txt[g_i] += ss;
		}
		cout<<"..."<<endl;
		return true;
		//cout<<g_i<<' '<<txt[g_i];
	}else if (v == "jmpscr"){
		PlayScript(stoi(s.substr(p+1)));
		cout<<"..."<<endl;
		return true;
	}else if (v == "echo"){
		cout<<endl<<s.substr(p+1)<<endl;
	}
	return false;
}
void dp(string s) {
	CL_GREEN;
	int xal = 0;
	for (int i=0; i<s.length(); i++) {
		if (s[i] == '$') continue;
		if (s[i] == '\\') {
			i++;
			cout<<s[i];
			continue;
		}
		if (s[i] == '{'){
			xal = i+1;
			while (s[xal] != '}') xal++;
			string ss = s.substr(i+1,xal-i-1);
			
			if (exe(ss,i)) //Running Jump;
				return;
			i = xal;
		}else if (s[i] == '[') {
			xal = i+1;
			while (s[xal] != '@') xal++;
			string ss = s.substr(i+1,xal-i-1);
			agent(s);
			i = xal;
		} else if (s[i] == '\'') {
			xal = i+1;
			while (s[xal] != '\'') xal++;
			int fp = xal+1;
			while (s[fp] != ';') fp++;
			string ss = s.substr(i+1,xal-i-1);
			//cout<<"***"<<ss<<"***"<<endl;
			string se = s.substr(xal+1,fp-xal-1);
			//cout<<ss<<' '<<se<<endl;
			while(dec_cmp(ss)) {
				//cout<<1<<endl;
				calc0(se);
			}
			i = fp;
			//cout<<lg[find_val("IQ")]<<endl;
		} else if (s[i] == '^') {
			xal = i+1;
			while (s[xal] != '^') xal++;
			string ss = s.substr(i+1,xal-i-1);
			decode_if(ss);
			i = xal;
		} else if (s[i] == '~') {
			//cout<<i<<endl;
			xal = i+1;
			while (s[xal] != '~') xal++;
			//cout<<"***"<<xal<<"***"<<endl;
			string ss = s.substr(i+1,xal-i-1);
			//cout<<ss<<endl;
			//cout<<ss<<' '<<find_val(ss)<<endl;
			cout<<lg[find_val(ss)];
			i = xal;
		} else if (s[i] == '*') {
			xal = i+1;
			while (s[xal] != '#') xal++;
			string ss = s.substr(i+1,xal-i-1);
			xal = 0;
			while (xal < ss.length()) {
				xal ++;
				if (ss[xal] == '+' || ss[xal] == '=' || ss[xal] == '-') {
					string p;
					int q;
					p = ss.substr(0,xal);
					q = stoi(ss.substr(xal+1));
					calc(p,ss[xal],q);
				}
			}
			i = xal+2;
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
		for (int i=1; i<=vn; i++) {
			fin<<vg[i]<<'='<<lg[i]<<endl;
		}
		cacc.name = "admin";
		cacc.pswd = "alpine";
		cacc.stat = 1;
		st = cacc.stat;
	} else {
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
	}
	tc--;

	while(fin>>s) {
		int p = 1,q;
		while (s[p] != '+' && s[p] != '-' && s[p] != '=') p++;
		string r;
		r = s.substr(0,p);
		q = stoi(s.substr(p+1));
		calc(r,s[p],q);
	}
	for (int i=1; i<=tc; i++) {
		fdtkt("Characters\\" + ch[i]);
		while (getline(fin,s)) {
			txt[i] += s;
		}
	}

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

		g_i = i; //Global I;
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

	system("del Save.cfg>nul"); // linux users replace this to 'rm Save.cfg'
	system("copy Save.bak Save.cfg>nul");
	fdtkt("Save.cfg");
	fin<<cacc.name<<endl<<cacc.pswd<<endl;
	fin<<st+1<<endl;

	for (int i=1; i<=vn; i++) {
		fin<<vg[i]<<'='<<lg[i]<<endl;
	}

	return 0;
}
