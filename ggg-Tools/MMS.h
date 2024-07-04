#pragma once
#define col first
#define row second
namespace MMS {
	vector<vector<pair<int, int> > > parseP(string str) {
		vector<vector<pair<int, int> > > ans;
		int l = str.length(), c = 0, fl = 0, t = 0;
		for (int i = 0; i < l; i++) {
			if (str[i] == '(')ans.push_back(vector<pair<int, int> >()), ans[ans.size() - 1].push_back(make_pair(-1, -1)), c = i, fl = 0;
			if (str[i] == ',' || str[i] == ')') {
				if (fl == 0)t = readint(str.substr(c + 1, i - c - 1)), c = i, fl = 1;
				else ans[ans.size() - 1].push_back(make_pair(t, readint(str.substr(c + 1, i - c - 1)))), c = i, fl = 0;
			}
		}
		return ans;
	}
	string tostrP(vector<vector<pair<int,int> > > x) {
		string ans;
		int l = x.size();
		if (l == 0)return "/";
		for (int i = 0; i < l; i++) {
			ans += "(";
			int l2 = x[i].size();
			for (int j = 1; j < l2; j++) {
				ans += inttostr(x[i][j].col);
				ans += ",";
				ans += inttostr(x[i][j].row);
				if (j < l2 - 1)ans += ",";
			}
			ans += ")";
		}
		return ans;
	}
	void proc1(vector<vector<pair<int, int> > >& x) {
		int n = x.size();
		int m = 0;
		for (int i = 0; i < n; i++)m = max((size_t)m, x[i].size());
		for (int i = 0; i < n; i++)while (x[i].size() < m)x[i].push_back(make_pair(-1, -1));
	}
	void proc2(vector<vector<pair<int, int> > >& x) {
		int n = x.size();
		int m = 0;
		for (int i = 0; i < n; i++)for (int j = 0; j < x[i].size(); j++)if (x[i][j].col != -1)m = max(m, j + 1);
		for (int i = 0; i < n; i++) {
			while (x[i].size() < m)x[i].push_back(make_pair(-1, -1));
			while (x[i].size() > m)x[i].pop_back();
		}
	}
	vector<vector<pair<int, int> > > expand(vector<vector<pair<int, int> > > x, int N) {
		int n = x.size();
		int m = 0;
		for (int i = 0; i < n; i++)m = max((size_t)m, x[i].size());
		proc1(x);
		if (n == 0)return x;
		int t = -1;
		for (int i = 0; i < m; i++)if (x[n - 1][i].col != -1)t = i;
		if (t == -1) { x.pop_back(); return x; }
		auto getlvl = [&x](int a, int b) {
			if (x[a][b].col == -1)return 1;
			int ans = 1;
			for (int i = b - 1; i >= 1; i--)if (x[a][b] == x[a][i])ans++; else break;
			return ans;
			};
		int llvl = getlvl(n - 1, t);
		pair<int, int> br = x[n - 1][t];
		if (llvl > 1) {
			while (getlvl(br.col, br.row) >= llvl)br = x[br.col][br.row];
		}
		pair<int, int> lf = x[n - 1][t];
		x[n - 1][t] = make_pair(-1, -1);
		t--;
		for (int i = lf.row + 1; i < m; i++) if (x[lf.col][i].col == -1)break;
		else {
			pair<int, int> v = x[lf.col][i];
			if (i - lf.row + t >= x[n - 1].size())x[n - 1].push_back(make_pair(0, 0));
			x[n - 1][i - lf.row + t] = v;
		}
		for (int i = 0; i < n; i++)m = max((size_t)m, x[i].size());
		proc1(x);
		vector<vector<int> > mag;
		for (int i = br.col; i < n; i++) {
			vector<int> v;
			for (int j = 0; j < m; j++)v.push_back(0);
			mag.push_back(v);
		}
		mag[0][br.row] = 1;
		mag[n - 1 - br.col][t + 1] = 1;
		for (int i = br.col + 1; i < n; i++)for (int j = m - 1; j >= 0; j--)if ((x[i][j].col >= br.col && mag[x[i][j].col - br.col][x[i][j].row]) || (j < m - 1 && mag[i - br.col][j + 1]))mag[i - br.col][j] = 1;
		for (int M = 1; M <= N; M++)for (int i = br.col + 1; i <= n - 1; i++) {
			vector<pair<int, int> > v;
			int e = mag[i - br.col][br.row];
			for (int j = 0; j <= br.row; j++) {
				pair<int, int> y = x[i][j];
				if (y.col >= br.col) {
					y.col += M * (n - 1 - br.col);
				}
				v.push_back(y);
			}
			int h;
			if (e)for (int j = 1; j <= M * (t - br.row); j++) {
				pair<int, int> y = x[i][br.row + 1];
				if ((j - 1) % (t - br.row) == 0)h = j - 1;
				else {
					int p = (j - 1) % (t - br.row) + 1;
					if (x[n - 1][br.row + p - 1] != x[n - 1][br.row + p])h = j - 1;
					//不知道magma部分父项行填充对不对
				}
				if (y.col >= br.col) {
					y.col += M * (n - 1 - br.col);
					if (y.row >= br.row)y.row += h;
				}
				v.push_back(y);
			}
			for (int j = br.row + 1; j < m; j++) {
				pair<int, int> y = x[i][j];
				if (y.col >= br.col) {
					y.col += M * (n - 1 - br.col);
					if (e && y.row >= br.row)y.row += M * (t - br.row);
				}
				v.push_back(y);
			}
			x.push_back(v);
		}
		proc1(x);
		proc2(x);
		return x;
	}
	vector<vector<int> > toMMS(vector<vector<pair<int, int> > > x) {
		int n = x.size();
		int m = 0;
		for (int i = 0; i < n; i++)m = max((size_t)m, x[i].size());
		proc1(x);
		vector<vector<int> > ans;
		for (int i = 0; i < n; i++) {
			vector<int> v;
			for (int j = 0; j < m - 1; j++)if (x[i][j + 1].col == -1)v.push_back(0); else v.push_back(ans[x[i][j + 1].col][x[i][j + 1].row] + 1);
			ans.push_back(v);
		}
		BMS::proc2(ans);
		return ans;
	}
	vector<vector<pair<int, int> > > fromMMS(vector<vector<int> > x) {
		int n = x.size();
		int m = 0;
		for (int i = 0; i < n; i++)m = max((size_t)m, x[i].size());
		BMS::proc1(x);
		vector<vector<pair<int, int> > > ans, up;
		vector<vector<int> > t;
		int cn;
		if (n == 0)return ans;
		if (n == 1) {
			vector<pair<int, int> > v;
			ans.push_back(v);
			return ans;
		}
		int u = 0;
		for (int i = 0; i < x[1].size(); i++)if (x[1][i] > 0)u = i + 1; else break;
		vector<pair<int, int> > v;
		ans.push_back(v);
		up.push_back(v);
		v.push_back(make_pair(-1, -1));
		for (int i = 0; i < u; i++)v.push_back(make_pair(0, 0));
		ans.push_back(v);
		v.push_back(make_pair(0, 0));
		up.push_back(v);
		t = toMMS(ans);
		cn = 0;
		for (int i = 2; i < n; i++) {
			while (ans.size() < i + 1) {
				ans = expand(up, ++cn);
				t = toMMS(ans);
			}
		nxt:;
			for (int j = 0; j < t[i].size(); j++)if (ans[i][j + 1].col != -1 && t[i][j] != (x[i].size() <= j ? 0 : x[i][j])) {
				while (t[i].size() >= j + 2)t[i].pop_back();
				while (ans.size() > i + 1)ans.pop_back();
				up = ans;
				ans = expand(up, cn = 1);
				t = toMMS(ans);
				goto nxt;
			}
		}
		while (ans.size() > n)ans.pop_back();
		proc2(ans);
		return ans;
	}
	vector<vector<int> > toMMYM(vector<vector<pair<int, int> > > x) {
		int n = x.size();
		int m = 0;
		for (int i = 0; i < n; i++)m = max((size_t)m, x[i].size());
		proc1(x);
		vector<vector<int> > ans;
		for (int i = 0; i < n; i++) {
			vector<int> v;
			for (int j = 0; j < m; j++)v.push_back(0);
			ans.push_back(v);
		}
		for (int i = 0; i < n; i++) {
			int t = 0;
			while ((t == 0 && m > 1 && x[i][1].col != -1) || (t < m - 1 && x[i][t + 1].col != -1))t++;
			for (int j = t; j >= 0; j--)ans[i][j] = (j == t ? 1 : ans[i][j + 1] + ans[x[i][j + 1].col][x[i][j + 1].row]);
		}
		return ans;
	}
	vector<int> toMMY(vector<vector<pair<int, int> > > x) {
		int n = x.size();
		vector<vector<int> > ans = toMMYM(x);
		vector<int> res;
		for (int i = 0; i < n; i++)res.push_back(ans[i][0]);
		return res;
	}
	vector<vector<pair<int, int> > > fromMMY(vector<int> x) {
		int n = x.size();
		vector<vector<pair<int, int> > > ans, up;
		vector<vector<int> > t;
		int cn;
		if (n == 0)return ans;
		if (n == 1) {
			vector<pair<int, int> > v;
			ans.push_back(v);
			return ans;
		}
		int u = x[1] - 1;
		vector<pair<int, int> > v;
		ans.push_back(v);
		up.push_back(v);
		v.push_back(make_pair(-1, -1));
		for (int i = 0; i < u; i++)v.push_back(make_pair(0, 0));
		ans.push_back(v);
		v.push_back(make_pair(0, 0));
		up.push_back(v);
		t = toMMYM(ans);
		cn = 0;
		for (int i = 2; i < n; i++) {
			while (ans.size() < i + 1) {
				ans = expand(up, ++cn);
				t = toMMYM(ans);
			}
			while (t[i][0] > x[i]) {
			nxt:;
				for (int j = 0; j < t[i].size(); j++)if (t[i][j] > 1 && (t[i][j] - 1) < t[i][0] - x[i]) {
					for (int k = j + 1; k < ans[i].size(); k++)ans[i][k] = make_pair(-1, -1);
					up = ans;
					ans = expand(up, cn = 1);
					t = toMMYM(ans);
					goto nxt;
				}
				while (ans.size() < i + 1) {
					ans = expand(up, ++cn);
					t = toMMYM(ans);
				}
				if (t[i][0] <= x[i])break;
				up = ans;
				ans = expand(up, cn = 0);
				t = toMMYM(ans);
				while (ans.size() < i + 1) {
					ans = expand(up, ++cn);
					t = toMMYM(ans);
				}
			}
		}
		while (ans.size() > n)ans.pop_back();
		proc2(ans);
		return ans;
	}
}
#undef col
#undef row
