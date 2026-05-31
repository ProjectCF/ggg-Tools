#pragma once
namespace MN {
	struct mctt {
		vector<pair<unique_ptr<mctt>, int> > x;
	};
	typedef unique_ptr<mctt> mct;
	mct gt() {
		return make_unique<mctt>();
	}
	mct cp(const mct& b) {
		if (!b)return mct();
		mct a = gt();
		for (int i = 0; i < b->x.size(); i++)a->x.push_back(Q(cp(b->x[i].A), b->x[i].B));
		return a;
	}
	vector<mct> cp(const vector<mct>& b) {
		vector<mct> a;
		for (int i = 0; i < b.size(); i++)a.push_back(cp(b[i]));
		return a;
	}
	template<class T>
	struct CP {
		T x;
		CP() :x() {}
		CP(const CP<T>& b) :x(cp(b.x)) {}
		CP(CP<T>&& b) :x(exchange(b.x, T())) {}
		CP<T>& operator=(const CP<T>& b) {
			x = cp(b.x);
			return *this;
		}
		CP<T>& operator=(CP<T>&& b) {
			x = exchange(b.x, T());
			return *this;
		}
		CP(const T& b) :x(cp(b)) {}
		CP(T&& b) :x(exchange(b, T())) {}
		CP<T>& operator=(const T& b) {
			x = cp(b);
			return *this;
		}
		CP<T>& operator=(T&& b) {
			x = exchange(b, T());
			return *this;
		}
		operator const T& () {
			return x;
		}
		T lek() {
			return move(x);
		}
	};
	struct ct {
		mct x;
		ct() :x() {}
		ct(const ct& b) :x(cp(b.x)) {}
		ct(ct&& b)noexcept :x(exchange(b.x, mct())) {}
		ct& operator=(const ct& b) {
			x = cp(b.x);
			return *this;
		}
		ct& operator=(ct&& b)noexcept {
			x = exchange(b.x, mct());
			return *this;
		}
		ct(const mct& b) :x(cp(b)) {}
		ct(mct&& b) :x(exchange(b, mct())) {}
		ct& operator=(const mct& b) {
			x = cp(b);
			return *this;
		}
		ct& operator=(mct&& b) {
			x = exchange(b, mct());
			return *this;
		}
		operator const mct& () const {
			return x;
		}
		mctt* operator->() const {
			return x.get();
		}
		mct lek() {
			return move(x);
		}
	};
	template<class T>
	auto lek(T x) {
		return exchange(x, T()).lek();
	}
	int cmp(const ct& a, const ct& b) {
		int as = a->x.size(), bs = b->x.size();
		int cs = min(as, bs);
		for (int i = 0; i < cs; i++) {
			int c = cmp(a->x[i].A, b->x[i].A);
			if (c != 0)return c;
			if (a->x[i].B != b->x[i].B)return (a->x[i].B < b->x[i].B) ? -1 : 1;
		}
		if (as == bs)return 0;
		else if (as < bs)return -1;
		else return 1;
	}
	ct add(const ct& a, const ct& b) {
		if (b->x.empty())return cp(a);
		ct c = gt();
		int fl = 0;
		for (int i = 0; i < a->x.size(); i++) {
			int d = cmp(a->x[i].A, b->x[0].A);
			if (d == -1)break;
			else {
				c->x.push_back(Q(cp(a->x[i].A), a->x[i].B));
				if (d == 0) {
					fl = 1;
					break;
				}
			}
		}
		for (int i = 0; i < b->x.size(); i++)if (fl && i == 0)c->x[c->x.size() - 1].B += b->x[i].B; else c->x.push_back(Q(cp(b->x[i].A), b->x[i].B));
		return c;
	}
	ct sub(const ct& a, const ct& b) {
		ct c = gt();
		for (int i = 0; i < a->x.size(); i++) {
			if (i >= b->x.size()) {
				for (int j = i; j < a->x.size(); j++)c->x.push_back(Q(cp(a->x[j].A), a->x[j].B));
				return c;
			}
			int d = cmp(a->x[i].A, b->x[i].A);
			if (d == -1) {
				cout << "ERROR" << endl;
				return c;
			}
			else if (d == 1) {
				for (int j = i; j < a->x.size(); j++)c->x.push_back(Q(cp(a->x[j].A), a->x[j].B));
				return c;
			}
			else if (a->x[i].B < b->x[i].B) {
				cout << "ERROR" << endl;
				return c;
			}
			else if (a->x[i].B > b->x[i].B) {
				c->x.push_back(Q(cp(a->x[i].A), a->x[i].B - b->x[i].B));
				for (int j = i + 1; j < a->x.size(); j++)c->x.push_back(Q(cp(a->x[j].A), a->x[j].B));
				return c;
			}
		}
		if (a->x.size() < b->x.size()) {
			cout << "ERROR" << endl;
			return c;
		}
		return c;
	}
	ct p1(const ct& a) {
		ct b = gt();
		if (a->x.size())b->x.push_back(Q(cp(a->x[0].A), 1));
		return b;
	}
	ct lg(const ct& a) {
		ct b = gt();
		if (a->x.size())b = a->x[0].A;
		return b;
	}
	ct wp(const ct& a) {
		ct b = gt();
		b->x.push_back(Q(cp(a), 1));
		return b;
	}
	ct ifll(const ct& a) {
		ct b = lg(a);
		if (cmp(b, gt()) == 0)return gt();
		else return wp(sub(b, wp(gt())));
	}
	ct ifl(const ct& x, const ct& y, const ct& z, const ct& w) {
		return add(w, sub(z, x));
	}
	ct toct(int x) {
		ct a = gt();
		a->x.push_back(Q(gt(), x));
		return a;
	}
	ct parsect(string s) {
		ct a = gt(), b = gt();
		int l = s.length(), c = 0, k = 0;
		for (int i = 0; i < l; i++) {
			if ((s[i] == '[' || s[i] == '(') && k == 0)c = i + 1;
			else if ((s[i] == ']' || s[i] == ')') && k == 2) {
				b = parsect(s.substr(c, i - c + 1));
				c = i + 1;
			}
			else if ((s[i] == ',' || s[i] == ']' || s[i] == ')') && k == 1 && i != 1) {
				int d = parseint(s.substr(c, i - c));
				a->x.push_back(Q(lek(b), d));
				c = i + 1;
			}
			if (s[i] == '[' || s[i] == '(')k++; else if (s[i] == ']' || s[i] == ')')k--;
		}
		return a;
	}
	string cttostr(const ct& a, int v) {
		string s;
		s += (v ? '(' : '[');
		for (int i = 0; i < a->x.size(); i++) {
			s += cttostr(a->x[i].A, 0);
			s += inttostr(a->x[i].B);
			if (i < a->x.size() - 1)s += ',';
		}
		s += (v ? ')' : ']');
		return s;
	}
	vector<ct> parse(string s) {
		vector<ct> x;
		x.push_back(ct());
		int l = s.length(), c = 0;
		for (int i = 0; i < l; i++) {
			if (s[i] == '(')c = i;
			if (s[i] == ')')x.push_back(parsect(s.substr(c, i - c + 1)));
		}
		return x;
	}
	string tostr(vector<ct> x) {
		if (x.size() == 1)return "/";
		string s;
		for (int i = 1; i < x.size(); i++)s += cttostr(x[i], 1);
		return s;
	}
	vector<ct> cpl(vector<ct> x) {
		for (int i = 1; i < x.size(); i++) {
			ct y = gt(), c = gt();
			for (int j = 0; j < x[i]->x.size(); j++) {
				int k = x[i]->x[j].B;
				const ct& d = x[i]->x[j].A;
				for (int l = 0; l < x[k]->x.size(); l++)if (cmp(x[k]->x[l].A, c) == 1 && cmp(x[k]->x[l].A, d) <= 0)y->x.push_back(Q(cp(x[k]->x[l].A), k)), c = x[k]->x[l].A;
				if (cmp(c, d) == -1)y->x.push_back(Q(cp(d), k)), c = d;
			}
			c = gt();
			x[i] = gt();
			for (int j = 0; j < y->x.size(); j++)while (cmp(c, y->x[j].A) == -1) {
				ct d = p1(sub(y->x[j].A, c));
				c = add(c, d);
				x[i]->x.push_back(Q(cp(c), y->x[j].B));
			}
		}
		return x;
	}
	vector<ct> expand2(vector<ct> x, int N) {
		int n = x.size() - 1;
		if (n == 0)return x;
		if (x[n]->x.empty()) {
			x.pop_back();
			return x;
		}
		ct a, b, c;//a=row(LNZ) b=row(LNZ.lt) c=row(LNZ.rt)
		int r = x[n]->x[x[n]->x.size() - 1].B;
		a = x[n]->x[x[n]->x.size() - 1].A;
		b = gt();
		for (int i = 0; i < x[r]->x.size(); i++)if (cmp(x[r]->x[i].A, a) == -1)b = x[r]->x[i].A;
		c = gt();
		for (int i = 0; i < x[n]->x.size(); i++)if (cmp(x[n]->x[i].A, a) == -1)c = x[n]->x[i].A;
		vector<ct> xl, yl;//(xl,zl,yl)
		for (int i = 0; i < x[r]->x.size(); i++)if (cmp(x[r]->x[i].A, a) == -1)xl.push_back(i == 0 ? gt() : cp(x[r]->x[i - 1].A)), yl.push_back(cp(x[r]->x[i].A));
		xl.push_back(cp(b)), yl.push_back(cp(a));
		ct d = add(b, ifll(sub(a, b)));
		x[n]->x.pop_back();
		if (cmp(c, d) == -1)x[n]->x.push_back(Q(cp(d), r));
		vector<ct> zl;
		for (int i = 0; i < xl.size(); i++)zl.push_back(xl[i]);
		int cl = 0;
		for (int i = 0; i < x[n]->x.size(); i++) {
			while (cl < xl.size() && cmp(yl[cl], x[n]->x[i].A) <= 0)cl++;
			if (cl < xl.size() && cmp(zl[cl], x[n]->x[i].A) == -1)zl[cl] = x[n]->x[i].A;
		}
		for (int i = 0; i < x[r]->x.size(); i++)if (cmp(x[r]->x[i].A, b) == 1)x[n]->x.push_back(Q(cp(x[r]->x[i].A), x[r]->x[i].B));
		int kr = r, k1 = r + 1, k2 = n;
		for (int I = 1; I <= N; I++) {
			for (int i = k1; i <= k2; i++) {
				x.push_back(gt());
				for (int j = 0; j < x[i]->x.size(); j++) {
					ct y = x[i]->x[j].A, z;
					int k = x[i]->x[j].B;
					int fl = 0;
					for (int l = 0; l < xl.size(); l++)if (!fl && cmp(xl[l], y) == -1 && cmp(y, yl[l]) == -1) { fl = 1; z = ifl(xl[l], yl[l], zl[l], y); }
					if (fl == 0)z = y;
					int l = (k >= kr ? k2 - kr + k : k);
					x[k2 - kr + i]->x.push_back(Q(lek(z), l));
				}
			}
			int d = k2 - kr;
			kr += d, k1 += d, k2 += d;
		}
		return x;
	}
	vector<ct> expand(vector<ct> x, int N) {
		x = cpl(x);
		x = expand2(x, N);
		x = cpl(x);
		return x;
	}
	string expandstr(string str, int n) {
		return tostr(expand(parse(str), n));
	}
	vector<ct> parsew(string s) {
		vector<ct> x;
		x.push_back(gt());
		int k = 0;
		string t;
		ct c = gt();
		auto ht = [&]() {c = add(c, wp(toct(k - 1)).lek()), x[x.size() - 1]->x.push_back(Q(cp(c), parseint(t))), k = 0, t = ""; };
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '(')x.push_back(gt()), c = gt();
			if ('0' <= s[i] && s[i] <= '9')t += s[i];
			else if (s[i] == ',') {
				if (t.length())ht();
				k++;
			}
			else if (s[i] == ')')if (t.length())ht();
		}
		return x;
	}
	string wtostr(vector<ct> x) {
		if (x.size() == 1)return "/";
		string s;
		for (int i = 1; i < x.size(); i++) {
			s += '(';
			ct c = gt();
			for (int j = 0; j < x[i]->x.size(); j++) {
				ct d = lg(sub(x[i]->x[j].A, c));
				c = x[i]->x[j].A;
				int k = 0;
				if (d->x.size())k = d->x[0].B;
				for (int l = 0; l <= k; l++)s += ',';
				s += inttostr(x[i]->x[j].B);
			}
			s += ')';
		}
		return s;
	}
	string expandstrw(string str, int n) {
		return wtostr(expand(parsew(str), n));
	}
}