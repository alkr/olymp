template <typename T>
struct Complex {
	T real, im;
	Complex(T x = (T) 0, T y = (T) 0) : real(x), im(y) {}
	Complex inverse() { return Complex(real, -im); }
	Complex operator+ (const Complex& c) { return Complex(real + c.real, im + c.im); }
	Complex operator- (const Complex& c) { return Complex(real - c.real, im - c.im); }
	Complex operator* (const T& num) { return Complex(real * num, im * num); }
	Complex operator/ (const T& num) { return Complex(real / num, im / num); }
	Complex operator* (const Complex& c) {
		return Complex(real * c.real - im * c.im, real * c.im + im * c.real);
	}
	Complex operator/ (const Complex& c) {
		return *this * c.inverse() / (c.x * c.x + c.y * c.y);
	}
};

typedef Complex<double> cd;

int rev(int x, int p) {
	int ans = 0;
	for (int i = 0; i < p; i++, x >>= 1) 
		ans = (ans << 1) | (x & 1);
	re ans;
}

void fft (cd* a, int p, bool inv) {
	int n = 1 << p;
	for (int i = 0; i < n; i++) {
		int x = rev(i, p);
		if (x > i) swap(a[i], a[x]);
	}
	for (int len = 1; len < n; len *= 2) {
		double ang = pi / len * (inv ? -1 : 1);
		cd w = {cos(ang), sin(ang)};
		for (int i = 0; i < n; i += len * 2) {
			cd cur = 1;
			for (int j = i; j < i + len; j++){
				auto u = a[j];
				auto v = cur * a[j + len];
				a[j] = u + v;
				a[j + len] = u - v;
				cur = cur * w;
			}
		}
	}
	if (inv)
		for (int i = 0; i < n; i++) 
			a[i] = a[i] / n;
}
