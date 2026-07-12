class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> sorted = arr;

        // Sort elements
        sort(sorted.begin(), sorted.end());

        // Store rank of each unique element
        unordered_map<int, int> rank;
        int currentRank = 1;

        for (int num : sorted) {
            if (rank.find(num) == rank.end()) {
                rank[num] = currentRank++;
            }
        }

        // Replace each element with its rank
        for (int& num : arr) {
            num = rank[num];
        }

        return arr;
    }
};