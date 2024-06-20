#pragma once
namespace CMS {
	vector<vector<int> > expand(vector<vector<int> > x, int N) {
		int n = x.size();
		int m = 0;
		for (int i = 0; i < n; i++)m = max((size_t)m, x[i].size());
		BMS::proc1(x);
		if (n == 0)return x;
		vector<vector<int> > fa = BMS::calcfa(x);
		int t = -1;
		for (int i = 0; i < m; i++)if (x[n - 1][i])t = i;
		if (t == -1) { x.pop_back(); return x; }
		int rt = fa[n - 1][t];
		vector<int> ac;
		vector<vector<int> > am;
		for (int i = 0; i < m; i++)ac.push_back(i < t ? x[n - 1][i] - x[rt][i] : 0);
		for (int i = rt; i < n; i++) {
			vector<int> v;
			for (int j = 0; j < m; j++)v.push_back((j < t) ? ((i == rt) || fa[i][j] >= rt && am[fa[i][j] - rt][j]) * ac[j] : 0);
			am.push_back(v);
		}
		vector<int> xl = x[n - 1];
		x.pop_back();
		fa.pop_back();
		for (int r = 1; r <= N; r++)for (int i = rt; i < n - 1; i++) {
			vector<int> v, v2;
			for (int j = 0; j < m; j++)v.push_back(x[i][j] + r * am[i - rt][j]), v2.push_back(fa[i][j] >= rt ? fa[i][j] + r * (n - rt - 1) : (i == rt && j < t ? rt + (r - 1) * (n - rt - 1) : fa[i][j]));
			x.push_back(v);
			fa.push_back(v2);
		}
		if (N == 0)return x;
		if (t == m - 1)return x;
		vector<int> sc;
		int cc = -1;
		for (int i = rt; i < n - 1; i++) {
			sc.push_back(i == rt ? 1 : fa[i][t + 1] >= rt ? sc[fa[i][t + 1] - rt] : 0);
			if (sc[i - rt] && i > rt)cc = i;
		}
		if (cc == -1)return x;
		{
			vector<int> v, v2;
			for (int j = 0; j < m; j++)v.push_back(xl[j] + N * ac[j]), v2.push_back(rt + N * (n - rt - 1));
			x.push_back(v);
			fa.push_back(v2);
		}
		vector<vector<int> > x2;
		for (int i = 0; i < cc + (n - rt - 1); i++)x2.push_back(x[i]);
		vector<vector<int> > vr, lp;
		for (int i = n - 1; i < n + N * (n - rt - 1); i++) {
			vector<int> v;
			for (int j = 0; j <= t; j++)v.push_back(0);
			vr.push_back(v);
		}
		for (int j = 0; j <= t; j++) {
			int p = n - 1 + N * (n - rt - 1);
			while (p >= n - 1)vr[p - n + 1][j] = 1, p = fa[p][j];
		}
		for (int i = n - 1; i < n - 1 + N * (n - rt - 1); i++) {
			vector<int> v;
			for (int j = 0; j <= t; j++)if (fa[i][j] < n - 1)v.push_back(i); else v.push_back(lp[fa[i][j] - n + 1][j]);
			lp.push_back(v);
		}
		for (int i = n - 1; i < n - 1 + N * (n - rt - 1); i++) {
			vector<int> v;
			for (int j = 0; j < m; j++) {
				if (j <= t && (j == 0 || vr[lp[i - n + 1][j] - n + 1][j - 1]))v.push_back(x[cc][j] + ac[j] - x[lp[i - n + 1][j]][j] + x[i][j]);
				else v.push_back(x[i][j]);
			}
			x2.push_back(v);
		}
		BMS::proc2(x2);
		return x2;
	}
	string expandstr(string str, int n) {
		return BMS::tostr(expand(BMS::parse(str), n));
	}
}
