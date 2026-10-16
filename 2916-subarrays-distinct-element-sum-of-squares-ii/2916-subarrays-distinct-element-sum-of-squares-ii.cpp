class Solution {
public:
    static const int MOD = 1e9 + 7;

    struct Node {
        long long sum1 = 0, sum2 = 0, lazy = 0;
    };

    vector<Node> tree;
    int n;

    void apply(int node, int l, int r, long long x) {
        long long len = r - l + 1;
        x %= MOD;

        tree[node].sum2 =
            (tree[node].sum2 + 2 * x % MOD * tree[node].sum1 % MOD
             + len % MOD * x % MOD * x % MOD) % MOD;

        tree[node].sum1 =
            (tree[node].sum1 + len % MOD * x % MOD) % MOD;

        tree[node].lazy = (tree[node].lazy + x) % MOD;
    }

    void push(int node, int l, int r) {
        if (tree[node].lazy == 0 || l == r)
            return;

        int mid = (l + r) / 2;
        long long x = tree[node].lazy;

        apply(node * 2, l, mid, x);
        apply(node * 2 + 1, mid + 1, r, x);

        tree[node].lazy = 0;
    }

    void update(int node, int l, int r, int ql, int qr,
                long long x) {
        if (ql > r || qr < l)
            return;

        if (ql <= l && r <= qr) {
            apply(node, l, r, x);
            return;
        }

        push(node, l, r);

        int mid = (l + r) / 2;

        update(node * 2, l, mid, ql, qr, x);
        update(node * 2 + 1, mid + 1, r, ql, qr, x);

        tree[node].sum1 =
            (tree[node * 2].sum1 + tree[node * 2 + 1].sum1) % MOD;

        tree[node].sum2 =
            (tree[node * 2].sum2 + tree[node * 2 + 1].sum2) % MOD;
    }

    int sumCounts(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n, Node());

        vector<int> last(100001, -1);
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int prev = last[nums[i]];

            // Increase distinct counts for subarrays
            // ending at i by one.
            update(1, 0, n - 1, prev + 1, i, 1);

            // Sum of squared distinct counts for all
            // subarrays ending at i.
            ans = (ans + tree[1].sum2) % MOD;

            last[nums[i]] = i;
        }

        return ans;
    }
};