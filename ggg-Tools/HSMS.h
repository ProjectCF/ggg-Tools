#pragma once
namespace HSMS {
	vector<vector<int> > expand(vector<vector<int> > x, int N, int T) {
		int n = x.size();
		int m = 0;
		for (int i = 0; i < n; i++)m = max((size_t)m, x[i].size());
		BMS::proc1(x);
		if (n == 0)return x;
		vector<vector<int> > fa = BMS::calcfa(x);
		int t = -1;
		for (int i = 0; i < m; i++)if (x[n - 1][i])t = i;
		if (t == -1) { x.pop_back(); return x; }
		vector<int> antp, ant;
		for (int i = 0; i < n; i++)antp.push_back(0), ant.push_back(0);
		if (t == 0)for (int i = 0; i < n; i++)antp[i] = 1;
		else {
			int k = n - 1;
			while (k != -1) {
				antp[k] = 1;
				k = fa[k][t - 1];
			}
		}
		{
			int k = fa[n - 1][t];
			if (k != -1)k = fa[k][t];
			while (k != -1) {
				ant[k] = 1;
				k = fa[k][t];
			}
		}
		int rt = fa[n - 1][t];
		if (rt == -1) { x.pop_back(); return x; }
		vector<int> R;
		for (int i = n - 2; i >= 0; i--)if (antp[i] && (T ? (fa[i][t] == -1 || ant[fa[i][t]]) : fa[i][t] == fa[rt][t]))R.push_back(i);
		int e = -1;
		vector<vector<int> > rtp, rp;
		for (int p = 0; p < R.size(); p++) {
			rp.clear();
			int r = R[p];
			vector<int> ac;
			vector<vector<int> > am;
			for (int i = 0; i < m; i++)ac.push_back(i <= t ? x[n - 1][i] - x[r][i] - (i == t) : 0);
			for (int i = r; i < n; i++) {
				vector<int> v;
				for (int j = 0; j < m; j++)v.push_back((j <= t) ? ((i == r) || fa[i][j] >= r && am[fa[i][j] - r][j]) * ac[j] : 0);
				am.push_back(v);
			}
			for (int i = r; i < n; i++) {
				vector<int> v;
				for (int j = 0; j < m; j++)v.push_back(x[i][j] + am[i - r][j]);
				rp.push_back(v);
			}
			if (p == 0)rtp = rp;
			if (BMS::matcmp(rp, rtp) < 0) {
				e = p;
				break;
			}
		}
		if (e == -1)rt = R[R.size() - 1];
		else rt = R[e - 1];
		vector<int> ac;
		vector<vector<int> > am;
		for (int i = 0; i < m; i++)ac.push_back(i <= t ? x[n - 1][i] - x[rt][i] - (i == t) : 0);
		for (int i = rt; i < n; i++) {
			vector<int> v;
			for (int j = 0; j < m; j++)v.push_back((j <= t) ? ((i == rt) || fa[i][j] >= rt && am[fa[i][j] - rt][j]) * ac[j] : 0);
			am.push_back(v);
		}
		x.pop_back();
		for (int r = 1; r <= N; r++)for (int i = rt; i < n - 1; i++) {
			vector<int> v;
			for (int j = 0; j < m; j++)v.push_back(x[i][j] + r * am[i - rt][j]);
			x.push_back(v);
		}
		BMS::proc2(x);
		return x;
	}
	string expandstr(string str, int n, int t) {
		return BMS::tostr(expand(BMS::parse(str), n, t));
	}
}