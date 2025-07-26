vector<int> s;
    for (int i = 0; i <= n; i++) {
        unsigned long long k = a / b;
        a -= b * k;
        a *= 10;
        s.push_back(k);
    }