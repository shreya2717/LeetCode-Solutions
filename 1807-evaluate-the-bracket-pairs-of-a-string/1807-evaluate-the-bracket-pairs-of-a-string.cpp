class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        // Store key-value pairs in a map
        unordered_map<string, string> mp;

        for (auto &pair : knowledge) {
            mp[pair[0]] = pair[1];
        }

        string ans;

        for (int i = 0; i < s.length(); i++) {

            // Start of a bracket pair
            if (s[i] == '(') {
                i++; // Move past '('

                string key;

                // Extract key until ')'
                while (s[i] != ')') {
                    key += s[i];
                    i++;
                }

                // Check if key exists
                if (mp.find(key) != mp.end()) {
                    ans += mp[key];
                } else {
                    ans += '?';
                }
            }
            else {
                // Normal character
                ans += s[i];
            }
        }

        return ans;
    }
};