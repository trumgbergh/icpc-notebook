#include <bits/stdc++.h>
using namespace std;
void fft(vector<complex<double>>& a) {
    int n = a.size();
    int L = 31 - __builtin_clz(n);
    vector<complex<long double>> R(2, 1);
    vector<complex<double>> rt(2, 1);
    for (int k = 2; k < n; k *= 2) {
        R.resize(n);
        rt.resize(n);
        complex<long double> x = polar(1.0L, acos(-1.0L) / k);
        for (int i = k; i < 2 * k; i++) {
            if (i & 1)
                rt[i] = R[i] = R[i / 2] * x;
            else
                rt[i] = R[i] = R[i / 2];
        }
    }

    vector<int> rev(n);
    for (int i = 0; i < n; i++) {
        rev[i] = rev[i / 2];
        rev[i] |= (i & 1) << L;
        rev[i] /= 2;
    }

    for (int i = 0; i < n; i++) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }

    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                double* x = (double*)&rt[j + k];
                double* y = (double*)&a[i + j + k];

                complex<double> z(x[0] * y[0] - x[1] * y[1],
                                  x[0] * y[1] + x[1] * y[0]);
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
        }
    }
}

template <int M>
vector<int64_t> convMOD(const vector<int64_t>& a, vector<int64_t>& b) {
    if (a.empty() || b.empty()) return {};
    int sz = (int)a.size() + (int)b.size() - 1;
    vector<int64_t> res(sz);
    int B = 32 - __builtin_clz(sz), n = (1 << B), cut = int(sqrt(M));
    vector<complex<double>> L(n), R(n), outs(n), outl(n);
    for (int i = 0; i < (int)a.size(); i++) {
        L[i] = complex<double>((int)a[i] / cut, (int)a[i] % cut);
    }

    for (int i = 0; i < (int)b.size(); i++) {
        R[i] = complex<double>((int)b[i] / cut, (int)b[i] % cut);
    }
    fft(L);
    fft(R);

    for (int i = 0; i < n; i++) {
        int j = -i & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] =
            (L[i] - conj(L[j])) * R[i] / (2.0 * n) / complex<double>(0, 1);
    }

    fft(outl);
    fft(outs);
    for (int i = 0; i < sz; i++) {
        int64_t av = (int64_t)(real(outl[i]) + .5);
        int64_t cv = (int64_t)(imag(outs[i]) + .5);
        int64_t bv =
            (int64_t)(imag(outl[i]) + .5) + (int64_t)(real(outs[i]) + .5);
        res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
    }
    return res;
}
