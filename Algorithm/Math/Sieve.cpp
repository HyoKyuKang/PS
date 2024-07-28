//출처 https://cologne.tistory.com/46
//1억 약 0.25초 12.5mb / 10억 약 3.6초 125mb
vector<bool> p(N + 1);
p[2] = true;
for (uint64_t i = 3; i <= N; i += 2)
    p[i] = true;
for (uint64_t i = 3; i * i <= N; i += 2)
    if (p[i])
        for (uint64_t j = i * i; j <= N; j += 2 * i)
            p[j] = false;
