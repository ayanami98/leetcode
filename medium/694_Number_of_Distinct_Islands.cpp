/******************************************************************************
 * Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's
 * (representing land) connected 4-directionally (horizontal or vertical.) You
 * may assume all four edges of the grid are surrounded by water.
 *
 * Count the number of distinct islands. An island is considered to be the same
 * as another if and only if one island can be translated (and not rotated or
 * reflected) to equal the other.
 * 
 * Example 1:
 * 11000
 * 11000
 * 00011
 * 00011
 * Given the above grid map, return 1.
 *
 * Example 2:
 * 11011
 * 10000
 * 00001
 * 11011
 * Given the above grid map, return 3.
 * 
 * Notice that:
 * 11
 * 1
 * and
 *  1
 * 11
 * are considered different island shapes, because we do not consider reflection
 * / rotation. Note: The length of each dimension in the given grid does not
 * exceed 50. 
******************************************************************************/

// Clean recursive C++ solution by creating unique string based on turn taken
class Solution {
public:
    // we need the depth to differentiate between [[1,0],[1,1],[1,0]] (dddr) and [1,0],[1,0],[1,1] (dddr) 
    void colorIsland(vector<vector<int>>& grid, int i, int j, int color, string &x, int d) {
        if(!grid[i][j]) {
            return;
        }
        x += to_string(d);
        grid[i][j] = color;
        if(i < grid.size() - 1 && grid[i+1][j] == 1){
            x = x + "d";
            colorIsland(grid, i+1, j, color, x, d+1);
        }
        if(i > 0 && grid[i-1][j] == 1) {
            x = x + "u";
            colorIsland(grid, i-1, j, color, x, d+1);
        }
        if(j < grid[i].size() - 1 && grid[i][j+1] == 1){
            x = x + "r";
            colorIsland(grid, i, j+1, color, x, d+1);
        }
        if(j > 0 && grid[i][j-1] == 1) {
            x = x + "l";
            colorIsland(grid, i, j-1, color, x, d+1);
        }
    }

    int numDistinctIslands(vector<vector<int>>& grid) {
        int count = 0;
        unordered_set<string> shape;
        for(int i=0; i<grid.size(); i++) {
            for(int j=0; j<grid[i].size(); j++) {
                if(grid[i][j] == 1) {
                    string x;
                    colorIsland(grid, i, j, 2, x, 0);
                    if(shape.find(x) == shape.end()) {
                        shape.insert(x);
                        count++;
                    }
                }
            }
        }
        return count;
    }
};
