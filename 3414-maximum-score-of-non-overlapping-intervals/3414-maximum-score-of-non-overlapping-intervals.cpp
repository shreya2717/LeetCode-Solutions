class Solution {
public:
    struct State {
        long long score = 0;
        vector<int> ids;
    };

    bool better(const State& a, const State& b) {
        if (a.score != b.score)
            return a.score > b.score;

        return a.ids < b.ids;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {

        int n = intervals.size();

        // {left, right, weight, original index}
        vector<array<long long, 4>> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = {
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            };
        }

        // Sort by left endpoint
        sort(a.begin(), a.end(),
            [](const auto& x, const auto& y) {
                if (x[0] != y[0])
                    return x[0] < y[0];

                if (x[1] != y[1])
                    return x[1] < y[1];

                return x[3] < y[3];
            });

        /*
            next[i] =
            first interval whose left > current right.
        */
        vector<long long> lefts(n);

        for (int i = 0; i < n; i++)
            lefts[i] = a[i][0];

        vector<int> nxt(n);

        for (int i = 0; i < n; i++) {

            nxt[i] = upper_bound(
                lefts.begin(),
                lefts.end(),
                a[i][1]
            ) - lefts.begin();
        }

        /*
            dp[i][k] =
            best answer from i onward,
            choosing at most k intervals.
        */
        vector<vector<State>> dp(
            n + 1,
            vector<State>(5)
        );

        for (int i = n - 1; i >= 0; i--) {

            for (int k = 1; k <= 4; k++) {

                // Skip
                State skip = dp[i + 1][k];

                // Take
                State take = dp[nxt[i]][k - 1];

                take.score += a[i][2];

                take.ids.push_back(
                    (int)a[i][3]
                );

                sort(
                    take.ids.begin(),
                    take.ids.end()
                );

                dp[i][k] =
                    better(take, skip) ? take : skip;
            }
        }

        return dp[0][4].ids;
    }
};