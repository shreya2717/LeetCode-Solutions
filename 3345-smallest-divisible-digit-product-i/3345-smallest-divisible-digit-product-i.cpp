class Solution {
public:
    int digitProduct(int x) {
        int prod = 1;
        while (x > 0) {
            prod *= (x % 10);
            x /= 10;
        }
        return prod;
    }

    int smallestNumber(int n, int t) {
        int x = n;
        while (true) {
            if (digitProduct(x) % t == 0)
                return x;
            x++;
        }
    }
};