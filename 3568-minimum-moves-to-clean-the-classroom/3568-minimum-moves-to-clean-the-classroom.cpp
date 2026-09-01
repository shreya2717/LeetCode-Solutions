class Solution {
public:
    struct State {
        int r;
        int c;
        int mask;
        int energy;
        int dist;
    };

    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        // Find starting position and number every litter cell
        int sr = -1, sc = -1;
        int litterCount = 0;

        vector<vector<int>> litterId(m, vector<int>(n, -1));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }

                if (classroom[i][j] == 'L') {
                    litterId[i][j] = litterCount++;
                }
            }
        }

        // If there is no litter, already done.
        if (litterCount == 0)
            return 0;

        int totalMasks = 1 << litterCount;

        /*
            best[r][c][mask] = maximum energy with which
            we have reached this state.

            If we reach the same (r,c,mask) later with
            less or equal energy, that state is useless.
        */
        vector<vector<vector<int>>> best(
            m,
            vector<vector<int>>(n, vector<int>(totalMasks, -1))
        );

        queue<State> q;

        best[sr][sc][0] = energy;
        q.push({sr, sc, 0, energy, 0});

        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};

        int finalMask = (1 << litterCount) - 1;

        while (!q.empty()) {

            State cur = q.front();
            q.pop();

            // All litter collected
            if (cur.mask == finalMask) {
                return cur.dist;
            }

            // If energy is 0, we cannot move anymore.
            if (cur.energy == 0) {
                continue;
            }

            for (int d = 0; d < 4; d++) {

                int nr = cur.r + dr[d];
                int nc = cur.c + dc[d];

                // Outside grid
                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;

                // Obstacle
                if (classroom[nr][nc] == 'X')
                    continue;

                // Moving costs 1 energy
                int newEnergy = cur.energy - 1;

                // Collect litter if this cell contains one
                int newMask = cur.mask;

                if (classroom[nr][nc] == 'L') {
                    int id = litterId[nr][nc];
                    newMask |= (1 << id);
                }

                // Reset energy if we reach R
                if (classroom[nr][nc] == 'R') {
                    newEnergy = energy;
                }

                /*
                    If we've already reached the same position
                    with the same collected litter and MORE energy,
                    this state isn't useful.
                */
                if (newEnergy <= best[nr][nc][newMask]) {
                    continue;
                }

                best[nr][nc][newMask] = newEnergy;

                q.push({
                    nr,
                    nc,
                    newMask,
                    newEnergy,
                    cur.dist + 1
                });
            }
        }

        return -1;
    }
};