#include <bits/stdc++.h>
using namespace std;

struct Sqrt {
    int block_size;
    vector<int> nums;
    vector<long long> blocks;

    Sqrt(int sqrtn, vector<int> &arr) : block_size(sqrtn), blocks(sqrtn, 0) {
        nums = arr;
        //TODO 0-Based
        for (int i = 0; i < nums.size(); i++) {
            //TODO
            blocks[i / block_size] += nums[i];
        }
    }

    // O(1) update to set nums[i] to v
    void update(int i, int v) {
        //TODO
        blocks[i / block_size] -= nums[i];
        nums[i] = v;
        blocks[i / block_size] += nums[i];
    }

    // O(sqrt(n)) query for sum of [0, r)
    long long query(int r) {
        //TODO
        long long ret = 0;
        for (int i = 0; i < r / block_size; i++) {
            ret += blocks[i];
        }
        for (int i = (r / block_size) * block_size; i < r; i++) {
            ret += nums[i];
        }
        return ret;
    }

    // O(sqrt(n)) query for sum of [l, r)
    long long query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    Sqrt sq((int) ceil(sqrt(n)), arr);

    // l, r 1-Based
    sq.update(l - 1, r);
    cout << sq.query(l, r);
}
