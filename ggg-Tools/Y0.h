#pragma once
namespace Y0 {
	vector<int> parse(string str) {
		vector<int> ans;
		int l = str.length(), c = -1;
		for (int i = 0; i <= l; i++) if (i == l || str[i] == ',')ans.push_back(readint(str.substr(c + 1, i - c - 1))), c = i;
		return ans;
	}
	string tostr(vector<int> x) {
		string ans;
		int l = x.size();
		if (l == 0)return "/";
		for (int i = 0; i < l; i++) {
			ans += inttostr(x[i]);
			if (i < l - 1)ans += ",";
		}
		return ans;
	}
	vector<int> fromBMS(vector<vector<int> > x) {
		BMS::proc1(x);
		vector<vector<int> > fa = BMS::calcfa(x);
		int n = x.size();
		int m = 0;
		for (int i = 0; i < n; i++)m = max((size_t)m, x[i].size());
		vector<vector<int> > tmp;
		for (int i = 0; i < n; i++) {
			vector<int> v;
			for (int j = 0; j < m; j++)v.push_back(1);
			tmp.push_back(v);
		}
		for (int j = m - 1; j >= 0; j--)for (int i = 0; i < n; i++)if (fa[i][j] != -1) {
			if (j == m - 1)tmp[i][j] = tmp[fa[i][j]][j] + 1;
			else tmp[i][j] = tmp[fa[i][j]][j] + tmp[i][j + 1];
		}
		vector<int> ans;
		for (int i = 0; i < n; i++)ans.push_back(tmp[i][0]);
		return ans;
	}
	vector<vector<int> > toBMS(vector<int> x) {
		int n = x.size();
		vector<vector<int> > y, fa, ans;
		if (n == 0)return ans;
		for (int i = 0; i < n; i++) {
			vector<int> v;
			v.push_back(x[i]);
			y.push_back(v);
			vector<int> v2;
			fa.push_back(v2);
		}
		int t = 0;
		while (1) {
			int fl = 0;
			for (int i = 0; i < n; i++) {
				int f = -1;
				if (t == 0)for (int j = i - 1; j >= 0; j--)if (y[j][t] < y[i][t]) { f = j; break; }
				if (t != 0)for (int j = fa[i][t - 1]; j >= 0; j = fa[j][t - 1])if (y[j][t] < y[i][t]) { f = j; break; }
				fa[i].push_back(f);
				if (f != -1)fl = 1;
			}
			if (!fl)break;
			for (int i = 0; i < n; i++)if (fa[i][t] == -1)y[i].push_back(1); else y[i].push_back(y[i][t] - y[fa[i][t]][t]);
			t++;
		}
		int m = y[0].size() - 1;
		if (m == 0)m = 1;
		for (int i = 0; i < n; i++) {
			vector<int> v;
			for (int j = 0; j < m; j++)v.push_back(fa[i][j] == -1 ? 0 : ans[fa[i][j]][j] + 1);
			ans.push_back(v);
		}
		return ans;
	}
}
