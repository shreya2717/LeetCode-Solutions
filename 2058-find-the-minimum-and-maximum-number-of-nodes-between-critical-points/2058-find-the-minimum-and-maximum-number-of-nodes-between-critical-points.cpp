class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        
        int first = -1;       // first critical point
        int last = -1;        // most recent critical point
        int minDist = INT_MAX;
        
        int pos = 1;          // current node's position
        
        ListNode* prev = head;
        ListNode* curr = head->next;
        
        while (curr != nullptr && curr->next != nullptr) {
            
            ListNode* next = curr->next;
            
            // Check if curr is a critical point
            bool isCritical =
                (curr->val > prev->val && curr->val > next->val) ||
                (curr->val < prev->val && curr->val < next->val);
            
            if (isCritical) {
                
                if (first == -1) {
                    // First critical point
                    first = pos;
                } 
                else {
                    // Distance from previous critical point
                    minDist = min(minDist, pos - last);
                }
                
                last = pos;
            }
            
            prev = curr;
            curr = next;
            pos++;
        }
        
        // Fewer than two critical points
        if (first == -1 || first == last) {
            return {-1, -1};
        }
        
        int maxDist = last - first;
        
        return {minDist, maxDist};
    }
};