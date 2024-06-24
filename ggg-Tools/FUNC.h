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
int readint(string str) {
	int ans = 0, fl = 0;
	int l = str.length();
	for (int i = 0; i < l; i++)if (str[i] == '-')fl = 1 - fl; else ans = ans * 10 + (str[i] - 48);
	return (fl ? -ans : ans);
}
string inttostr(int x) {
	if (x == -2147483648)return "-2147483648";
	if (x < 0)return string("-") + inttostr(-x);
	string ans,ans2;
	do ans.append(1, 48 + x % 10), x /= 10; while (x);
	int l = ans.length();
	for (int i = l - 1; i >= 0; i--)ans2.append(1, ans[i]);
	return ans2;
}
vector<vector<int> > expand(int tp, vector<vector<int> > x, int n);
#ifdef REMOTE
#include "C:\Users\CF\Desktop\C(Us)\REPOS\ggg-Tools\ggg-Tools\BMS.h"
#include "C:\Users\CF\Desktop\C(Us)\REPOS\ggg-Tools\ggg-Tools\Y0.h"
#include "C:\Users\CF\Desktop\C(Us)\REPOS\ggg-Tools\ggg-Tools\CMS.h"
#include "C:\Users\CF\Desktop\C(Us)\REPOS\ggg-Tools\ggg-Tools\HSMS.h"
#include "C:\Users\CF\Desktop\C(Us)\REPOS\ggg-Tools\ggg-Tools\MMS.h"
#else
#include "BMS.h"
#include "Y0.h"
#include "CMS.h"
#include "HSMS.h"
#include "MMS.h"
#endif
string expand(int tp, string str, int n) {
	if (tp == 1)return BMS::expandstr(str, n, 0);
	if (tp == 2)return Y0::tostr(Y0::fromBMS(BMS::expand(Y0::toBMS(Y0::parse(str)), n, 0)));
	if (tp == 3)return CMS::expandstr(str, n);
	if (tp == 4)return HSMS::expandstr(str, n, 0);
	if (tp == 5)return HSMS::expandstr(str, n, 1);
	if (tp == 6)return BMS::expandstr(str, n, 1);
	if (tp == 7)return MMS::tostrP(MMS::expand(MMS::parseP(str), n));
	if (tp == 8)return BMS::tostr(MMS::toMMS(MMS::expand(MMS::fromMMS(BMS::parse(str)), n)));
	if (tp == 9)return Y0::tostr(MMS::toMMY(MMS::expand(MMS::fromMMY(Y0::parse(str)), n)));
	return "";
}
vector<vector<int> > expand(int tp, vector<vector<int> > x, int n) {
	if (tp == 1)return BMS::expand(x, n, 0);
	if (tp == 3)return CMS::expand(x, n);
	if (tp == 4)return HSMS::expand(x, n, 0);
	if (tp == 5)return HSMS::expand(x, n, 1);
	if (tp == 6)return BMS::expand(x, n, 1);
}
string cvt(int tp1, int tp2, string str) {
	if (tp1 == tp2)return str;
	if (tp1 == 1 && tp2 == 2)return Y0::tostr(Y0::fromBMS(BMS::parse(str)));
	if (tp1 == 2 && tp2 == 1)return BMS::tostr(Y0::toBMS(Y0::parse(str)));
	if (tp1 == 7 && tp2 == 8)return BMS::tostr(MMS::toMMS(MMS::parseP(str)));
	if (tp1 == 8 && tp2 == 7)return MMS::tostrP(MMS::fromMMS(BMS::parse(str)));
	if (tp1 == 7 && tp2 == 9)return Y0::tostr(MMS::toMMY(MMS::parseP(str)));
	if (tp1 == 8 && tp2 == 9)return Y0::tostr(MMS::toMMY(MMS::fromMMS(BMS::parse(str))));
	if (tp1 == 9 && tp2 == 7)return MMS::tostrP(MMS::fromMMY(Y0::parse(str)));
	if (tp1 == 9 && tp2 == 8)return BMS::tostr(MMS::toMMS(MMS::fromMMY(Y0::parse(str))));
	return "Not Supported";
}
int chkstd(int tp, string str) {
	if (tp == 1)return BMS::chkstd(BMS::parse(str), 1);
	if (tp == 2)return BMS::chkstd(Y0::toBMS(Y0::parse(str)), 1);
	if (tp == 3)return BMS::chkstd(BMS::parse(str), 3);
	if (tp == 4)return BMS::chkstd(BMS::parse(str), 4);
	if (tp == 5)return BMS::chkstd(BMS::parse(str), 5);
	if (tp == 6)return BMS::chkstd(BMS::parse(str), 6);
	return -1;
}
void init() {
	cout << "CF ggg Tools Build5: MMS" << endl << "input H to get help" << endl;
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
	TRIE::add("IBMS", 2, 6);
	TRIE::add("PMMS", 2, 7);
	TRIE::add("MMS", 2, 8);
	TRIE::add("MMY", 2, 9);
}
string cstrs[110];
int cscnt;
int stt;
string loop(string str) {
	cscnt = 1;
	cstrs[1].clear();
	int l = str.length();
	for (int i = 0; i < l; i++)if (str[i] != ' ')cstrs[cscnt].append(1, str[i]); else cscnt++, cstrs[cscnt].clear();
	int cmd = TRIE::q(cstrs[1], 1);
	if (cmd == 0)return "Unknown Command";
	if (cmd == 1) {
		stt = 1;
		return "";
	}
	if (cmd == 2)return "Q:quit\nH:help\nE:expand\nE [Notation] [To Expand] [#FS]\nCV:convert\nCV [From Notation] [To Notation] [To Convert]\nCH:check standard\nCH:check standard\nCH [Notation] [To Check]\nNotations: B:BMS 0:0Y C:CMS H:HMS S:SMS I:IBMS P:PMMS M:MMS";
	if (cmd == 3) {
		int tp = TRIE::q(cstrs[2], 2);
		if (tp == 0)return "Unknown Type";
		else return expand(tp, cstrs[3], readint(cstrs[4]));
	}
	if (cmd == 4) {
		int tp1 = TRIE::q(cstrs[2], 2), tp2 = TRIE::q(cstrs[3], 2);
		if (tp1 == 0 || tp2 == 0)return "Unknown Type";
		else return cvt(tp1, tp2, cstrs[4]);
	}
	if (cmd == 5) {
		int tp = TRIE::q(cstrs[2], 2);
		if (tp == 0)return "Unknown Type";
		else {
			int res = chkstd(tp, cstrs[3]);
			if (res == 0)return "NOT STD";
			if (res == 1)return "STD";
			if (res == 2)return "INVALID";
			if (res == -1)return "Not Supported";
		}
	}
	return "";
}
