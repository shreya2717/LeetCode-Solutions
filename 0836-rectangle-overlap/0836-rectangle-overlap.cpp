class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        // Check overlap along X-axis
        bool xOverlap = rec1[0] < rec2[2] && rec2[0] < rec1[2];

        // Check overlap along Y-axis
        bool yOverlap = rec1[1] < rec2[3] && rec2[1] < rec1[3];

        return xOverlap && yOverlap;
    }
};