class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        
        unordered_map<int, set<int>> reserved;

        for (auto &seat : reservedSeats) {
            reserved[seat[0]].insert(seat[1]);
        }

        int ans = (n - reserved.size()) * 2;

        for (auto &row : reserved) {
            int r = row.first;
            set<int> seats = row.second;

            bool left = true;   // 2,3,4,5
            bool middle = true; // 4,5,6,7
            bool right = true;  // 6,7,8,9

            for (int s : seats) {
                if (s >= 2 && s <= 5)
                    left = false;

                if (s >= 4 && s <= 7)
                    middle = false;

                if (s >= 6 && s <= 9)
                    right = false;
            }

            if (left && right) {
                ans += 2;
            }
            else if (left || middle || right) {
                ans += 1;
            }
        }

        return ans;
    }
};