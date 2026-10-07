class Solution {
public:

    bool isValid(string s) {
        int balance = 0;

        for (char c : s) {
            if (c == '(') {
                balance++;
            }
            else if (c == ')') {
                balance--;

                // More closing brackets than opening brackets
                if (balance < 0)
                    return false;
            }
        }

        return balance == 0;
    }

    vector<string> removeInvalidParentheses(string s) {

        vector<string> ans;

        unordered_set<string> visited;
        queue<string> q;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while (!q.empty()) {

            int size = q.size();

            // Process one BFS level
            while (size--) {

                string current = q.front();
                q.pop();

                // If valid, this is the minimum-removal level
                if (isValid(current)) {
                    ans.push_back(current);
                    found = true;
                }

                // Don't generate the next level
                // once valid strings are found
                if (found)
                    continue;

                // Try removing every character
                for (int i = 0; i < current.size(); i++) {

                    // Only remove parentheses
                    if (current[i] != '(' && current[i] != ')')
                        continue;

                    string next = current.substr(0, i) +
                                  current.substr(i + 1);

                    if (!visited.count(next)) {
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }

            // First valid level = minimum removals
            if (found)
                break;
        }

        return ans;
    }
};