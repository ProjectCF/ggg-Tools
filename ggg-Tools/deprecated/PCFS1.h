#pragma once
namespace PCFS1 {
	struct node {
		int tp;//0=0 1=+ 2=p 3=a
		shared_ptr<node> a, b;
		node() :tp(0), a(0), b(0) {}
	};
	typedef shared_ptr<node> np;
	np parse(string str) {
		stack<np> st;
		int n = str.size();
		for (int i = 0; i < n; i++) {
			if (str[i] == '0')st.push(np(new node));
			if (str[i] == '+') {
				np b = st.top();
				st.pop();
				np a = st.top();
				st.pop();
				np c = np(new node);
				c->tp = 1;
				c->a = a;
				c->b = b;
				st.push(c);
			}
			if (str[i] == 'p') {
				np b = st.top();
				st.pop();
				np a = st.top();
				st.pop();
				np c = np(new node);
				c->tp = 2;
				c->a = a;
				c->b = b;
				st.push(c);
			}
			if (str[i] == 'a') {
				np a = st.top();
				st.pop();
				np c = np(new node);
				c->tp = 3;
				c->a = a;
				st.push(c);
			}
		}
		return st.top();
	}
	string tostr(np x) {
		if (x->tp == 0)return "0";
		if (x->tp == 1)return tostr(x->a) + tostr(x->b) + "+";
		if (x->tp == 2)return tostr(x->a) + tostr(x->b) + "p";
		if (x->tp == 3)return tostr(x->a) + "a";
	}
	int lvl(np x) {
		if (x->tp == 0)return -1;
		if (x->tp == 1)return lvl(x->b);
		if (x->tp == 2)return lvl(x->b) - 1;
		if (x->tp == 3)return (x->a->tp == 0 ? -1 : 2);
	}
	int lvl2(np x) {
		if (x->tp == 0)return -1;
		if (x->tp == 1)return lvl(x->b);
		if (x->tp == 2)return lvl(x->b) - 1;
		if (x->tp == 3)return 2;
	}
	int cmp(np a, np b) {
		if (a->tp == 0)return (b->tp) != 0;
		if (b->tp == 0)return -((a->tp) != 0);
		if (a->tp == 1 && b->tp != 1) {
			int r = cmp(a->a, b);
			if (r < 0)return -1;
			if (r >= 0)return 1;
		}
		if (a->tp != 1 && b->tp == 1) {
			int r = cmp(a, b->a);
			if (r <= 0)return -1;
			if (r > 0)return 1;
		}
		if (a->tp == 1 && b->tp == 1) {
			int r = cmp(a->a, b->a);
			if (r)return r;
			return cmp(a->b, b->b);
		}
		int la = lvl2(a), lb = lvl2(b);
		if (la < lb) {
			int r = cmp(a->b, b);
			if (r <= 0)return -1;
			if (r > 0)return 1;
		}
		if (la > lb) {
			int r = cmp(a, b->b);
			if (r < 0)return -1;
			if (r >= 0)return 1;
		}
		if (la < 2) {
			int r = cmp(a->b, b->b);
			if (r)return r;
			return cmp(a->a, b->a);
		}
		return cmp(a->a, b->a);
	}
	np mk(int tp, np a, np b) {
		np x = np(new node);
		x->tp = tp;
		x->a = a;
		x->b = b;
		return x;
	}
	np cof(np x) {
		if (x->tp == 0)return x;
		if (x->tp == 1)return cof(x->b);
		int lx = lvl2(x);
		if (lx == 2) {
			if (lvl(x->a) == -1)return x;
			return cof(x->a);
		}
		if (lx == 1) {
			np ca = cof(x->a);
			int la = lvl(ca);
			if (la == -1)return x;
			if (cmp(ca, x->b) < 0)return ca;
			if (la == 2)return parse("000aapp");
			return x;
		}
		if (lx == 0) {
			np ca = cof(x->a);
			int la = lvl(ca);
			if (la == -1)return parse("000aapp");
			if (cmp(ca, x->b) >= 0)return parse("000aapp");
			return ca;
		}
	}
	np tonp(int i) {
		if (i == 0)return np(new node);
		np x = parse("0a");
		for (int j = 2; j <= i; j++)x = mk(1, parse("0a"), x);
		return x;
	}
	int frnp(np x) {
		if (x->tp == 0)return 0;
		if (x->tp == 3)return 1;
		return frnp(x->a) + frnp(x->b);
	}
	np fs(np x, np n) {
		if (x->tp == 0 || (x->tp == 3 && x->a->tp == 0))return parse("0");
		if (x->tp == 1 && x->b->tp == 3 && x->b->a->tp == 0)return x->a;
		if (x->tp == 1)return mk(1, x->a, fs(x->b, n));
		int lx = lvl2(x);
		if (lx == 2) {
			np cx = cof(x);
			if (cmp(cx, x) < 0)return mk(3, fs(x->a, n), nullptr);
			else return n;
		}
		if (lx == 1) {
			np cx = cof(x);
			if (cmp(cx, x) == 0)return n;
			np ca = cof(ca);
			if (cmp(ca, x->b) < 0)return mk(2, fs(x->a, n), x->b);
			int N = frnp(n);
			np y = 0;
			for (int i = 1; i <= N; i++)y = fs(x->a, mk(2, y, ca));
			return mk(2, y, x->b);
		}
		if (lx == 0) {
			np ca = cof(x->a);
		}
	}
}
