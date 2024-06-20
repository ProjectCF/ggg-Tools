#pragma once
namespace BMS {
	vector<vector<int> > parse(string str) {
		vector<vector<int> > ans;
		int l = str.length(), c = 0;
		for (int i = 0; i < l; i++) {
			if (str[i] == '(')ans.push_back(vector<int>()), c = i;
			if (str[i] == ',' || str[i] == ')')ans[ans.size() - 1].push_back(readint(str.substr(c + 1, i - c - 1))), c = i;
		}
		return ans;
	}
	string tostr(vector<vector<int> > x) {
		string ans;
		int l = x.size();
		if (l == 0)return "/";
		for (int i = 0; i < l; i++) {
			ans += "(";
			int l2 = x[i].size();
			for (int j = 0; j < l2; j++) {
				ans += inttostr(x[i][j]);
				if (j < l2-1)ans += ",";
			}
			ans += ")";
		}
		return ans;
	}
	void proc1(vector<vector<int> >& x) {
		int n = x.size();
		int m = 0;
		for (int i = 0; i < n; i++)m = max((size_t)m, x[i].size());
		for (int i = 0; i < n; i++)while (x[i].size() < m)x[i].push_back(0);
	}
	void proc2(vector<vector<int> >& x) {
		int n = x.size();
		int m = 0;
		for (int i = 0; i < n; i++)for (int j = 0; j < x[i].size(); j++)if (x[i][j])m = max(m, j + 1);
		for (int i = 0; i < n; i++) {
			while (x[i].size() < m)x[i].push_back(0);
			while (x[i].size() > m)x[i].pop_back();
		}
	}
	vector<vector<int> > calcfa(vector<vector<int> > x) {
		vector<vector<int> > fa;
		int n = x.size();
		int m = 0;
		for (int i = 0; i < n; i++)m = max((size_t)m, x[i].size());
		for (int i = 0; i < n; i++) {
			vector<int> v;
			for (int j = 0; j < m; j++)v.push_back(-(i == 0));
			fa.push_back(v);
		}
		for (int i = 1; i < n; i++)for (int j = 0; j < m; j++)if (j == 0) {
			int k = i - 1;
			while (k != -1 && x[k][j] >= x[i][j])k--;
			fa[i][j] = k;
		}
		else {
			int k = fa[i][j - 1];
			while (k != -1 && x[k][j] >= x[i][j])k = fa[k][j - 1];
			fa[i][j] = k;
		}
		return fa;
	}
	vector<vector<int> > expand(vector<vector<int> > x, int N, int T) {
		int n = x.size();
		int m = 0;
		for (int i = 0; i < n; i++)m = max((size_t)m, x[i].size());
		proc1(x);
		if (n == 0)return x;
		vector<vector<int> > fa = calcfa(x);
		int t = -1;
		for (int i = 0; i < m; i++)if (x[n - 1][i])t = i;
		if (t == -1){x.pop_back(); return x;}
		int rt = fa[n - 1][t];
		/*IBMS*/vector<int> Ila;
		/*IBMS*/if (T == 1)for (int i = rt; i < n; i++)Ila.push_back(i == rt ? 1 : fa[i][t] >= rt && Ila[fa[i][t] - rt]);
		vector<int> ac;
		vector<vector<int> > am;
		for (int i = 0; i < m; i++)ac.push_back(i < t ? x[n - 1][i] - x[rt][i] : 0);
		for (int i = rt; i < n; i++) {
			vector<int> v;
			if (T == 0)for (int j = 0; j < m; j++)v.push_back((j < t) ? ((i == rt) || fa[i][j] >= rt && am[fa[i][j] - rt][j]) * ac[j] : 0);
			if (T == 1)for (int j = 0; j < m; j++)v.push_back((j < t) ? ((i == rt) || fa[i][j] == rt && Ila[i - rt] || fa[i][j] > rt && am[fa[i][j] - rt][j]) * ac[j] : 0);
			am.push_back(v);
		}
		x.pop_back();
		for (int r = 1; r <= N; r++)for (int i = rt; i < n - 1; i++) {
			vector<int> v;
			for (int j = 0; j < m; j++)v.push_back(x[i][j] + r * am[i - rt][j]);
			x.push_back(v);
		}
		proc2(x);
		return x;
	}
	string expandstr(string str, int n, int t) {
		return tostr(expand(parse(str), n, t));
	}
	int seqcmp(vector<int> x, vector<int> y) {
		int n = x.size(), m = y.size();
		for (int i = 0; i < max(n, m); i++) {
			int a = 0, b = 0;
			if (i < n)a = x[i];
			if (i < m)b = y[i];
			if (a < b)return -1;
			if (a > b)return 1;
		}
		return 0;
	}
	int matcmp(vector<vector<int> > x, vector<vector<int> > y) {
		int n = x.size(), m = y.size();
		for (int i = 0; i < max(n, m); i++) {
			vector<int> a, b;
			if (i < n)a = x[i];
			if (i >= n)return -1;
			if (i < m)b = y[i];
			if (i >= m)return 1;
			if (seqcmp(a, b) < 0)return -1;
			if (seqcmp(a, b) > 0)return 1;
		}
		return 0;
	}
	int chkstd(vector<vector<int> > x, int tp) {
		if (x.empty())return 1;
		if (seqcmp(vector<int>(), x[0]) < 0)return 0;
		vector<vector<int> > y;
		y.push_back(vector<int>());
		y.push_back(vector<int>());
		int n = x.size();
		int m = 0;
		for (int i = 0; i < n; i++)m = max((size_t)m, x[i].size());
		int k = 0;
		while (matcmp(y, x) < 0 && k <= m)y[1].push_back(1);
		if (k == m + 1)return 0;
		vector<vector<int> > z;
		while (matcmp(y, x) > 0) {
			if (y.size() == 0)return 0;
			int k = 0;
			while (1) {
				z = ::expand(tp, y, k);
				int res = matcmp(z, x);
				if (res == 0)return 1;
				if (res > 0) {
					y = z;
					goto re;
				}
				if (z.size() > n)return 0;
				k++;
			}
		re:;
		}
		return matcmp(y, x) == 0;
	}
}
