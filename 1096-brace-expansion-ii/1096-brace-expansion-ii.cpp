class Solution {
public:

    set<string> parse(string &s, int &i) {

        set<string> res;
        set<string> cur = {""};

        while (i < s.size() && s[i] != '}') {

            if (s[i] == ',') {
                // Union
                for (auto &x : cur)
                    res.insert(x);

                cur = {""};
                i++;
            }
            else {
                set<string> next;

                if (s[i] == '{') {
                    i++; // skip {

                    next = parse(s, i);

                    i++; // skip }
                }
                else {
                    next.insert(string(1, s[i]));
                    i++;
                }

                // Cartesian product = concatenation
                set<string> temp;

                for (auto &a : cur) {
                    for (auto &b : next) {
                        temp.insert(a + b);
                    }
                }

                cur = temp;
            }
        }

        // Add final part
        for (auto &x : cur)
            res.insert(x);

        return res;
    }

    vector<string> braceExpansionII(string expression) {

        int i = 0;

        set<string> ans = parse(expression, i);

        return vector<string>(ans.begin(), ans.end());
    }
};