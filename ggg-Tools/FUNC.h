#pragma once
namespace TRIE {
	struct TRIE {
		int x, ch[256];
	}trie[1000010];
	int cnt;
	void add(string str, int rt, int id) {
		int l = str.length(), c = rt;
		for (int i = 0; i < l; i++)if (trie[c].ch[str[i]])c = trie[c].ch[str[i]], trie[c].x = 0;
		else {
			trie[++cnt].x = id;
			trie[c].ch[str[i]] = cnt;
			c = cnt;
		}
	}
	int q(string str, int rt) {
		int l = str.length(), c = rt;
		for (int i = 0; i < l; i++)if (trie[c].ch[str[i]])c = trie[c].ch[str[i]]; else return 0;
		return trie[c].x;
	}
}
int parseint(string str) {
	int ans = 0, fl = 0;
	int l = str.length();
	for (int i = 0; i < l; i++)if (str[i] == '-')fl = 1 - fl; else ans = ans * 10 + (str[i] - 48);
	return (fl ? -ans : ans);
}
string inttostr(int x) {
	if (x == -2147483648)return "-2147483648";
	if (x < 0)return string("-") + inttostr(-x);
	string ans, ans2;
	do ans.append(1, 48 + x % 10), x /= 10; while (x);
	int l = ans.length();
	for (int i = l - 1; i >= 0; i--)ans2.append(1, ans[i]);
	return ans2;
}
vector<vector<int> > expand(int tp, vector<vector<int> > x, int n);
#ifdef REMOTE
#include "C:\Users\CF\Desktop\FD\REPOS\ggg-Tools\ggg-Tools\BMS.h"
#include "C:\Users\CF\Desktop\FD\REPOS\ggg-Tools\ggg-Tools\Y0.h"
#include "C:\Users\CF\Desktop\FD\REPOS\ggg-Tools\ggg-Tools\CMS.h"
#include "C:\Users\CF\Desktop\FD\REPOS\ggg-Tools\ggg-Tools\HSMS.h"
#include "C:\Users\CF\Desktop\FD\REPOS\ggg-Tools\ggg-Tools\MN.h"
#else
#include "BMS.h"
#include "Y0.h"
#include "CMS.h"
#include "HSMS.h"
#include "MN.h"
#endif
string expand(int tp, string str, int n) {
	if (tp == 1)return BMS::expandstr(str, n);
	if (tp == 2)return Y0::tostr(Y0::fromBMS(BMS::expand(Y0::toBMS(Y0::parse(str)), n)));
	if (tp == 3)return CMS::expandstr(str, n);
	if (tp == 4)return HSMS::expandstr(str, n, 0);
	if (tp == 5)return HSMS::expandstr(str, n, 1);
	if (tp == 6)return MN::expandstr(str, n);
	if (tp == 7)return MN::expandstrw(str, n);
	return "";
}
vector<vector<int> > expand(int tp, vector<vector<int> > x, int n) {
	if (tp == 1)return BMS::expand(x, n);
	if (tp == 3)return CMS::expand(x, n);
	if (tp == 4)return HSMS::expand(x, n, 0);
	if (tp == 5)return HSMS::expand(x, n, 1);
	return vector<vector<int> >();
}
string cvt(int tp1, int tp2, string str) {
	if (tp1 == tp2)return str;
	if (tp1 == 1 && tp2 == 2)return Y0::tostr(Y0::fromBMS(BMS::parse(str)));
	if (tp1 == 2 && tp2 == 1)return BMS::tostr(Y0::toBMS(Y0::parse(str)));
	return "Not Supported";
}
int chkstd(int tp, string str) {
	if (tp == 1)return BMS::chkstd(BMS::parse(str), 1);
	if (tp == 2)return BMS::chkstd(Y0::toBMS(Y0::parse(str)), 1);
	if (tp == 3)return BMS::chkstd(BMS::parse(str), 3);
	if (tp == 4)return BMS::chkstd(BMS::parse(str), 4);
	if (tp == 5)return BMS::chkstd(BMS::parse(str), 5);
	return -1;
}
void init() {
	cout << "CF ggg Tools Build7: wMN test" << endl << "input H to get help" << endl;
	TRIE::cnt = 2;
	TRIE::add("QUIT", 1, 1);
	TRIE::add("HELP", 1, 2);
	TRIE::add("EXP", 1, 3);
	TRIE::add("CVT", 1, 4);
	TRIE::add("CHKSTD", 1, 5);
	TRIE::add("BMS", 2, 1);
	TRIE::add("0Y", 2, 2);
	TRIE::add("CMS", 2, 3);
	TRIE::add("HMS", 2, 4);
	TRIE::add("SMS", 2, 5);
	TRIE::add("MNKM", 2, 6);
	TRIE::add("MNw", 2, 7);
}
string spstr[110];
int spcnt;
int stt;
string loop(string str) {
	spcnt = 1;
	spstr[1].clear();
	int l = str.length();
	for (int i = 0; i < l; i++)if (str[i] != ' ')spstr[spcnt].append(1, str[i]); else spcnt++, spstr[spcnt].clear();
	int cmd = TRIE::q(spstr[1], 1);
	if (cmd == 0)return "Unknown Command";
	if (cmd == 1) {
		stt = 1;
		return "";
	}
	if (cmd == 2)return "Q:quit\nH:help\nE:expand\nE [Notation] [To Expand] [#FS]\nCV:convert\nCV [From Notation] [To Notation] [To Convert]\nCH:check standard\nCH [Notation] [To Check]\nNotations: B:BMS 0:0Y C:CMS H:HMS S:SMS MNw:wMN";
	if (cmd == 3) {
		int tp = TRIE::q(spstr[2], 2);
		if (tp == 0)return "Unknown Type";
		else return expand(tp, spstr[3], parseint(spstr[4]));
	}
	if (cmd == 4) {
		int tp1 = TRIE::q(spstr[2], 2), tp2 = TRIE::q(spstr[3], 2);
		if (tp1 == 0 || tp2 == 0)return "Unknown Type";
		else return cvt(tp1, tp2, spstr[4]);
	}
	if (cmd == 5) {
		int tp = TRIE::q(spstr[2], 2);
		if (tp == 0)return "Unknown Type";
		else {
			int res = chkstd(tp, spstr[3]);
			if (res == 0)return "NOT STD";
			if (res == 1)return "STD";
			if (res == 2)return "INVALID";
			if (res == -1)return "Not Supported";
		}
	}
	return "";
}
