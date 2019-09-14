#pragma GCC optimize("O3")
#pragma GCC target("avx")

#include <bits/stdc++.h>
  
using namespace std;
  
#define fi first
#define se second
#define pb push_back
#define sz(x)  ((int)x.size ())
#define all(x) (x).begin(), (x).end()
#define re return
#define mp make_pair
#define sqrt(x) sqrt (abs(x))
#define y0 y3451
#define y1 y4562
#define makeunique(x) sort(all(x)), (x).resize (unique(all(x)) - (x).begin())
  
typedef pair <int, int> ii;
typedef long long ll;
typedef unsigned long long ull;
typedef double D;
typedef long double ld;
typedef unsigned int uint;
typedef vector <string> vs;
typedef vector <int> vi;
typedef vector <ii> vii;
typedef vector <vi> vvi;
typedef vector <ll> vll;
  
template <class T> T abs (T x) { re x > 0 ? x : -x; }
template <class T> T sqr (T x) { re x * x; }
template <class T> T gcd (T a, T b) { re (a != 0) ? gcd (b % a, a) : b; }
template <class T> int sgn (T x) { re x > 0 ? 1 : (x < 0 ? -1 : 0); }
  
#define filename ""
  
const ld pi = acos(-1.);
const int N = 2e5 + 100;
const int inf = 1e9 + 7;
const int base = 10;
  
int MAGIC = 2;
int cash = 18;
  
template <typename T>
struct Complex {
	T real, im;
	Complex(T x = (T) 0, T y = (T) 0) : real(x), im(y) {}
	Complex inverse() const { return Complex(real, -im); }
	Complex operator+ (const Complex& c) { return Complex(real + c.real, im + c.im); }
	Complex operator- (const Complex& c) { return Complex(real - c.real, im - c.im); }
	Complex operator* (const T& num) { return Complex(real * num, im * num); }
	Complex operator/ (const T& num) { return Complex(real / num, im / num); }
	Complex operator* (const Complex& c) {
		return Complex(real * c.real - im * c.im, real * c.im + im * c.real);
	}
	Complex operator/ (const Complex& c) {
		return *this * c.inverse() / (c.real * c.real + c.im * c.im);
	}
};

typedef Complex<double> cd;
typedef vector<cd> vc;
  
void fft (vector<cd>& a, int p, bool inv, vvi& rev) {
    int n = 1 << p;
	for (int i = 0; i < sz(rev); i++)
		for (int j = 0; j < sz(rev[i]); j++) {
			int x = i * sz(rev[i]) + j;
			if (x > rev[i][j]) swap(a[x], a[rev[i][j]]);
		}
    for (int len = 1; len < n; len <<= 1) {
        double ang = (inv) ? -pi / len : pi / len;
        cd w = {cos(ang), sin(ang)};
        for (int i = 0; i < n; i += len * 2) {
            cd cur = 1;
            for (int j = i; j < i + len; j++, cur = cur * w){
                auto u = a[j];
                auto v = cur * a[j + len];
                a[j] = u + v;
                a[j + len] = u - v;
            }
        }
    }
    if (inv)
        for (int i = 0; i < n; i++) 
            a[i] = a[i] / n;
}
  
class bigint {
    public :
        vector<int> ans;        
        bigint () { ans.pb(0); }
        bigint (const string& s) {
            ans.resize(sz(s));
            for (int i = 0; i < sz(s); i++)
                ans[i] = s[i] - '0';
            reverse(all(ans));
        }
          
        bigint (const vector<int>& x) { ans = x; }
          
        bigint (const int& p) {
            int x = p;
            if (x == 0) {
                ans.pb(0);
                re;
            }
            while (x) {
                ans.pb(x % 10);
                x /= 10;
            }
        }
  
        void normalize() {
            int cur = 0;
            for (int i = 0; i < sz(ans); i++) {
                cur += ans[i];
                ans[i] = cur % base;
                cur /= base;
            }
            while (cur) {
                ans.pb(cur % base);
                cur /= base;
            }
            while (sz(ans) > 1 && ans.back() == 0) ans.pop_back();
        }
  
        void up (int x) {
            ans.resize(sz(ans) + x);
            for (int i = sz(ans) - 1; i >= 0; i--)
                if (i < x) ans[i] = 0;
                else ans[i] = ans[i - x];
        }
  
        void print () const {
            for (int i = sz(ans) - 1; i >= 0; i--)
                cout << ans[i];
        }   
  
        friend ostream& operator << (ostream& out, const bigint& x);
        friend istream& operator >> (istream& in, bigint& x);
  
};
  
ostream& operator << (ostream& out, const bigint& x) {
    for (int i = sz(x.ans) - 1; i >= 0; i--)
        out << x.ans[i];
    re out;
}
  
istream& operator >> (istream& in, bigint& x) {
    string s;
    in >> s; 
    bigint tmp(s);  
    x = tmp;
    return in;
}
  
bigint operator * (const bigint& a, const bigint& b) {
    int p = 0;
    while ((1 << p) < sz(a.ans) + sz(b.ans) - 1) p++;
    int n = 1 << p;
    vector<cd> f(n);
    vector<cd> x(n);
    vector<cd> y(n);
    for (int i = 0; i < sz(a.ans); i++) f[i].real = a.ans[i];
    for (int i = 0; i < sz(b.ans); i++) f[i].im = b.ans[i];

	int s, k;
	if (p <= cash) s = 1 << p, k = 1;
	else s = 1 << cash, k = 1 << (p - cash); 
	vector <vi> rev (k, vi(s));
	int l = 0, r = 0;
	for (int i = 0; i < k; i++)
		for (int j = 0; j < s; j++) {
			rev[i][j] = (rev[l][r] >> 1) + (((i * s + j) & 1) << (p - 1));				
			if (j & 1) {
				r++;
				if (r >= s) { l++; r = 0; }	
			}
		}

    fft(f, p, 0, rev);
    cd z(0, 2);
    x[0] = (f[0] + f[0].inverse()) / 2;
    y[0] = (f[0] - f[0].inverse()) / z;    
    for (int i = 1; i < n; i++) {
	    x[i] = (f[i] + f[n - i].inverse()) / 2;
	    y[i] = (f[i] - f[n - i].inverse()) / z;
    }
	for (int i = 0; i < n; i++) f[i] = x[i] * y[i];   
    fft(f, p, 1, rev);
    vi ans(1 << p);
    for (int i = 0; i < (1 << p); i++)
        ans[i] = (int) (f[i].real + 0.5);
    bigint res = ans;
    res.normalize();
    re res;                                     
}
  
bigint operator * (const bigint& a, int x) {
    bigint z = x;
    re a * z;
}
  
bigint operator + (const bigint& a, const bigint& b) {
    vi ans(max(sz(a.ans), sz(b.ans)));
    int cur = 0;
    for (int i = 0; i < sz(ans); i++) {
        cur += (i < sz(b.ans) ? b.ans[i] : 0);
        cur += (i < sz(a.ans) ? a.ans[i] : 0);       
        ans[i] = cur % base;
        cur /= base;
    }
    while (cur) {
        ans.pb(cur % base);
        cur /= base;
    }
    re ans;
}
  
bigint operator + (const bigint& a, int x) {
    re a + bigint(x);
}
  
bigint operator - (const bigint& a, const bigint& b) {
    bigint ans = a.ans;
    int cur = 0;
    for (int i = 0; i < sz(ans.ans) || cur; i++) {
        ans.ans[i] = ans.ans[i] - cur - (i < sz(b.ans) ? b.ans[i] : 0);
        if (ans.ans[i] < 0) {
            cur = 1;
            ans.ans[i] += base;
        } else cur = 0;                     
    }
    while (sz(ans.ans) > 1 && ans.ans.back() == 0) ans.ans.pop_back();
    re ans;
}
  
bool operator < (const bigint& a, const bigint& b) {
    if (sz(a.ans) != sz(b.ans)) re sz(a.ans) < sz(b.ans);
    for (int i = sz(a.ans) - 1; i >= 0; i--)
        if (a.ans[i] != b.ans[i]) re a.ans[i] < b.ans[i];
    re false;
}
  
bool operator > (const bigint& a, const bigint& b) { re b < a; }
bool operator == (const bigint& a, const bigint& b) { re !(b < a) && !(a < b); }
bool operator != (const bigint& a, const bigint& b) { re (b < a || a < b); }
bool operator >= (const bigint& a, const bigint& b) { re !(b > a); }
bool operator <= (const bigint& a, const bigint& b) { re !(a > b); }
  
class bigd {
    public :
        bigint p;
        int deg;
        bigd (const bigint& x = 0, int d = 0) {
            p = x;
            deg = d;
        }
        void normalize() {
            p.normalize();
            if (p.ans[0] == 0 && deg) {
                reverse(all(p.ans));
                while (deg && p.ans.back() == 0) {
                    deg--;
                    p.ans.pop_back();
                }
                reverse(all(p.ans));
            }       
        }
        void up (int x) {
            deg += x;
            p.up(x);
        }
  
        friend ostream& operator << (ostream& out, const bigd& x);
};
  
ostream& operator << (ostream& out, const bigd& x) {
    if (x.deg >= sz(x.p.ans)) {
        out << "0.";
        for (int i = 0; i < x.deg - sz(x.p.ans); i++)
            out << '0';
        out << x.p;
    } else { 
        if (x.deg <= 0) {
            out << x.p;
            for (int i = 0; i < abs(x.deg); i++)
                out << '0';
        } else { 
            int p = sz(x.p.ans) - x.deg;
            int j = sz(x.p.ans) - 1;
            for (int i = 0; i < p; i++, j--)
                cout << x.p.ans[j];
            out << ".";
            for (; j >= 0; j--) out << x.p.ans[j];
        }
    }
    re out;
}
  
bigd operator * (const bigd& a, const bigd& b) {
    auto ans = bigd (a.p * b.p, a.deg + b.deg);
    re ans;
}
  
bigd operator * (const bigd& a, const bigint& b) {
    auto ans = bigd (a.p * b, a.deg);
    re ans;
}
  
bigd operator - (bigd& a, bigd& b) {
    int p = max(a.deg, b.deg);
    if (a.deg != p) a.up(p - a.deg);
    if (b.deg != p) b.up(p - b.deg);
    assert (a.p >= b.p);
    auto ans = bigd (a.p - b.p, p);
    re ans;
}

bigd operator + (bigd& a, bigd& b) {
    int p = max(a.deg, b.deg);
	if (a.deg != p) a.up(p - a.deg);
	if (b.deg != p) b.up(p - b.deg);
    auto ans = bigd (a.p + b.p, p);
    re ans;
}

bigd inv (const bigint& a, int need) {
    int deg = 0, cur = 0;
    if (sz(a.ans) > 4) {
        deg = sz(a.ans) - 4;
        for (int i = sz(a.ans) - 1; i >= sz(a.ans) - 4; i--)
            cur *= base, cur += a.ans[i];
        cur++;
    } else {
        for (int i = sz(a.ans) - 1; i >= 0; i--)
            cur *= base, cur += a.ans[i];
    }
    double x = 1. / cur;
    while (x < 10) {
        deg++;
        x *= 10;
    }
    bigd z (2, 0);
    bigd w ((int) x, deg);
    int it = (need > 1000) ? MAGIC : 4;
    for (int p = 2; (1 << p) < it * need; p++) {
        int len = 1 << p;
        vc f (2 * len);
        vc tmp (2 * len);
        vc cur (2 * len);
        vi fi (2 * len);
        bool ok = false;
        if (len > sz(a.ans)) {
            ok = true;
            for (int i = 0; i < sz(a.ans); i++)
                f[i].real = a.ans[i];
        } else {
            for (int i = sz(a.ans) - len, j = 0; i < sz(a.ans); i++, j++)
                f[j].real = a.ans[i];
        }
        for (int i = 0; i < sz(w.p.ans); i++)
            f[i].im = w.p.ans[i];
        int l = (ok ? 0 : len - sz(a.ans)) + w.deg;
		int s, k;
		if (p + 1 <= cash) s = 1 << (p + 1), k = 1;
		else s = 1 << cash, k = 1 << (p + 1 - cash); 
		vector <vi> rev (k, vi(s));
		int c = 0, r = 0;
		for (int i = 0; i < k; i++)
			for (int j = 0; j < s; j++) {
				rev[i][j] = (rev[c][r] >> 1) + (((i * s + j) & 1) << (p));				
				if (j & 1) {
					r++;
					if (r >= s) { c++; r = 0; }	
				}
			}
		fft (f, p + 1, 0, rev);
	    cd z(0, 2);
   		tmp[0] = (f[0] + f[0].inverse()) / 2;
   	 	cur[0] = (f[0] - f[0].inverse()) / z;    
    	for (int i = 1; i < 2 * len; i++) {
	    	tmp[i] = (f[i] + f[2 * len - i].inverse()) / 2;
	    	cur[i] = (f[i] - f[2 * len - i].inverse()) / z;
    	}
        double ang = (pi * l) / len;
        cd root = {cos(ang), sin(ang)};
        cd ww = 2;
        for (int i = 0; i < 2 * len; i++, ww = ww * root) {
            tmp[i] = ww - cur[i] * tmp[i];
        }
        fft (tmp, p + 1, 1, rev);
        ll last = 0;
        for (int i = 0; i < 2 * len; i++) {
            if (tmp[i].real > 0)
                last += (ll) (tmp[i].real + 0.5);
            else last += (ll) (tmp[i].real - 0.5);
            fi[i] = last % base;
            if (fi[i] < 0) { last -= base; fi[i] += base; }
            last /= base;
            tmp[i] = 0;
        }
        while (last) { fi.pb(last % base); last /= base; }
        while (sz(fi) > 1 && fi.back() == 0) fi.pop_back();
		if (sz(fi) > len) {
			l += len - sz(fi);
            for (int i = sz(fi) - len, j = 0; i < sz(fi); i++, j++)
            	tmp[j] = fi[i];
        } else {
        	for (int i = 0; i < sz(fi); i++)
        		tmp[i] = fi[i];
		}
		fft (tmp, p + 1, 0, rev);
		for (int i = 0; i < 2 * len; i++) tmp[i] = tmp[i] * cur[i];
		fft (tmp, p + 1, 1, rev);
        fi.assign(2 * len, 0);
        last = 0;
        for (int i = 0; i < 2 * len; i++) {
            last += (ll) (tmp[i].real + 0.5);
            fi[i] = last % base;
            last /= base;
        }
        while (last) { fi.pb(last % base); last /= base; }
        while (sz(fi) > 1 && fi.back() == 0) fi.pop_back();
        w.deg += l;
        if (sz(fi) > len) {
            w.deg += len - sz(fi);
            w.p.ans.resize(len);
            for (int i = sz(fi) - len, j = 0; i < sz(fi); i++, j++)
            	w.p.ans[j] = fi[i];
        } else w.p.ans = fi;
    }
    re w;
}

bigd operator / (const bigd& b, const bigd& a) {
	auto x = inv(a.p, max(100, sz(b.p.ans)));
	x.deg += a.deg;
	x = x * b;
	re x;
}

bigint operator / (const bigint& b, const bigint& a) {
    bigd w = inv (a, sz(b.ans));
    w.normalize();
	w = w * b;
	bigint ans = 0;
	if (sz(w.p.ans) > w.deg) {
		ans.ans.clear();
		for (int i = w.deg; i < sz(w.p.ans); i++)
			ans.ans.pb(w.p.ans[i]);
	}
	auto s = ans * a;
	auto r = b - s;
	if (r >= a) {		
		r = r - a;
		ans = ans + 1;
	}
	re ans;
}

bigint operator / (const bigint& b, const int& a) {
   	ll k = 0;
   	vi ans;
    for (int i = sz(b.ans) - 1; i >= 0; i--) {
    	k = k * base + b.ans[i];
    	ans.pb(k / a);
    	k %= a;
    }
	reverse(all(ans));
	while (sz(ans) > 1 && ans.back() == 0) ans.pop_back();
	re ans;    
}

bigd operator / (const bigd& b, const int& a) {
	bigint q = b.p / a;
	int deg = b.deg;
	if (a == 2 && q.ans[0] % 2) {
		deg++;
		q.ans.insert(q.ans.begin(), 5);	
   	}
   	re bigd(q, deg);
}

bigint operator % (const bigint& b, const bigint& a) {
    bigd w = inv (a, sz(b.ans));
    w.normalize();
    w = w * b;
    bigint ans = 0;
    if (sz(w.p.ans) > w.deg) {
        ans.ans.clear();
        for (int i = w.deg; i < sz(w.p.ans); i++)
            ans.ans.pb(w.p.ans[i]);
    }
    auto s = ans * a;
    auto r = b - s;
    if (r >= a) {       
        r = r - a;
        ans = ans + 1;
    }
    re r;
}

bigd rootd (const bigint& a, int need = 0) {
    int n = sz(a.ans) + need;
    int deg = 0, cur = 0;
    if (n % 2) {
        if (sz(a.ans) > 5) {
            deg = (5 - sz(a.ans)) / 2;
            for (int i = sz(a.ans) - 1; i >= sz(a.ans) - 5; i--)
                cur *= base, cur += a.ans[i];
        } else {
            for (int i = sz(a.ans) - 1; i >= 0; i--)
                cur *= base, cur += a.ans[i];
        }
    } else {
        if (sz(a.ans) > 4) {
            deg = (4 - sz(a.ans)) / 2;
            for (int i = sz(a.ans) - 1; i >= sz(a.ans) - 4; i--)
                cur *= base, cur += a.ans[i];
        } else {
            for (int i = sz(a.ans) - 1; i >= 0; i--)
                cur *= base, cur += a.ans[i];
        }
    }       
    double x = sqrt((D)cur);
    while (x < 10) {
        deg++;
        x *= 10;
    }
    bigd w ((int) x, deg);
    for (int p = 2; (1 << p) <= 2 * n; p++) {
        int len = 1 << p;
    	auto r = inv(w.p.ans, len);
    	deg = r.deg - w.deg;
    	vc f (2 * len);
    	vc cur (2 * len);
    	vc tmp (2 * len);
    	vi fi (2 * len);
        if (len > sz(a.ans)) {
            for (int i = 0; i < sz(a.ans); i++)
                f[i].real = a.ans[i];
        } else {
        	deg += len - sz(a.ans);
            for (int i = sz(a.ans) - len, j = 0; i < sz(a.ans); i++, j++)
                f[j].real = a.ans[i];
        }
        if (len > sz(r.p.ans)) {
            for (int i = 0; i < sz(r.p.ans); i++)
                f[i].im = r.p.ans[i];
        } else {
        	deg += len - sz(r.p.ans);
            for (int i = sz(r.p.ans) - len, j = 0; i < sz(r.p.ans); i++, j++)
                f[j].im = r.p.ans[i];
        }
		int s, k;
		if (p + 1 <= cash) s = 1 << (p + 1), k = 1;
		else s = 1 << cash, k = 1 << (p + 1 - cash); 
		vector <vi> rev (k, vi(s));
		int c = 0, d = 0;
		for (int i = 0; i < k; i++)
			for (int j = 0; j < s; j++) {
				rev[i][j] = (rev[c][d] >> 1) + (((i * s + j) & 1) << (p));				
				if (j & 1) {
					d++;
					if (d >= s) { c++; d = 0; }	
				}
			}
        fft (f, p + 1, 0, rev);
        cd z(0, 2);
    	tmp[0] = (f[0] + f[0].inverse()) / 2;
   	 	cur[0] = (f[0] - f[0].inverse()) / z;    
    	for (int i = 1; i < 2 * len; i++) {
	   		tmp[i] = (f[i] + f[2 * len - i].inverse()) / 2;
	    	cur[i] = (f[i] - f[2 * len - i].inverse()) / z;
    	}
        for (int i = 0; i < 2 * len; i++) {
            tmp[i] = cur[i] * tmp[i];
        }
        fft (tmp, p + 1, 1, rev);
        ll last = 0;
        for (int i = 0; i < 2 * len; i++) {
            last += (ll) (tmp[i].real + 0.5);
            fi[i] = last % base;
            last /= base;
        }
        while (last) { fi.pb(last % base); last /= base; }
        while (sz(fi) > 1 && fi.back() == 0) fi.pop_back();
		bigd nxt;
		nxt.deg = deg;
        if (sz(fi) > len) {
            nxt.deg += len - sz(fi);
            nxt.p.ans.resize(len);
            for (int i = sz(fi) - len, j = 0; i < sz(fi); i++, j++)
            	nxt.p.ans[j] = fi[i];
        } else nxt.p.ans = fi;
        w = w + nxt;
        w = w / 2;
        if (sz(w.p.ans) > len) {
            w.deg += len - sz(w.p.ans);
            for (int i = sz(w.p.ans) - len, j = 0; i < sz(w.p.ans); i++, j++)
            	w.p.ans[j] = w.p.ans[i];
            w.p.ans.resize(len);        
        } 
    }
    re w;
}

bigint root (const bigint& a) {
	if (a == 0) re 0;
	bigd w = rootd (a);
	vi ans;
	if (w.deg >= 0) {
		for (int i = w.deg; i < sz(w.p.ans); i++)
			ans.pb(w.p.ans[i]);
		if (!sz(ans)) ans.pb(0);
	} else {
		if (w.p == 0) re 0;
		ans = w.p.ans;
		reverse(all(ans));
		ans.resize(sz(ans) + abs(w.deg));
		reverse(all(ans));		
	}
	bigint res = ans;	
	if ((res + 1) * (res + 1) <= a) re res + 1;
	re res;
}                                             

bigint operator += (bigint& a, const bigint& x) { re a = a + x; }
bigint operator -= (bigint& a, const bigint& x) { re a = a - x; }
bigint operator *= (bigint& a, const bigint& x) { re a = a * x; }
bigint operator /= (bigint& a, const bigint& x) { re a = a / x; }
bigint operator %= (bigint& a, const bigint& x) { re a = a % x; }
bigint operator ++ (bigint& a) { re a = a + 1; }
bigint operator -- (bigint& a) { re a = a - 1; }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	bigint x, y;
	cin >> x >> y;
	x = root(x);
	cerr << clock() << endl;
}