class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter,
                      int x1, int y1, int x2, int y2) {
        
        // Closest x-coordinate on rectangle to circle center
        int closestX = max(x1, min(xCenter, x2));
        
        // Closest y-coordinate on rectangle to circle center
        int closestY = max(y1, min(yCenter, y2));
        
        // Distance between circle center and closest point
        int dx = xCenter - closestX;
        int dy = yCenter - closestY;
        
        // Compare squared distances
        return dx * dx + dy * dy <= radius * radius;
    }
};