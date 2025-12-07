//
// Created by Manju Muralidharan on 11/22/25.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Directions for DFS (students must use these)
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

// ----------------------------------------------------------
// DO NOT MODIFY: Maze generation
// ----------------------------------------------------------
void generateMaze(vector<vector<int>>& maze, int N, int M) {
    srand(time(0));

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            int roll = rand() % 100;
            maze[r][c] = (roll < 70) ? 0 : 1;   // 0 = open, 1 = wall
        }
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Choose a random boundary cell that is open
// ----------------------------------------------------------
pair<int,int> chooseBoundaryCell(const vector<vector<int>>& maze) {
    int N = maze.size();
    int M = maze[0].size();

    while (true) {
        int side = rand() % 4;
        int r, c;

        if (side == 0) {          // top row
            r = 0;
            c = rand() % M;
        } else if (side == 1) {   // bottom row
            r = N - 1;
            c = rand() % M;
        } else if (side == 2) {   // left column
            r = rand() % N;
            c = 0;
        } else {                  // right column
            r = rand() % N;
            c = M - 1;
        }

        if (maze[r][c] == 0) {
            return {r, c};
        }
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Print the maze with S and E markers
// ----------------------------------------------------------
void printMaze(const vector<vector<int>>& maze,
               int ent_r, int ent_c,
               int exit_r, int exit_c)
{
    int N = maze.size();
    int M = maze[0].size();

    cout << "\nMaze:\n";
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (r == ent_r && c == ent_c) {
                cout << "S ";
            } else if (r == exit_r && c == exit_c) {
                cout << "E ";
            } else {
                cout << maze[r][c] << " ";
            }
        }
        cout << "\n";
    }
}

// ----------------------------------------------------------
// DO NOT MODIFY: Print the reconstructed path
// Students must fill parent[][] correctly during DFS
// ----------------------------------------------------------
void printPath(pair<int,int> exitcell,
               const vector<vector<int>>& parent_r,
               const vector<vector<int>>& parent_c,
               int ent_r, int ent_c)
{
    int r = exitcell.first;
    int c = exitcell.second;

    vector<pair<int,int>> path;

    // Walk backward from exit to entrance
    while (!(r == ent_r && c == ent_c)) {
        path.push_back({r, c});
        int pr = parent_r[r][c];
        int pc = parent_c[r][c];
        r = pr;
        c = pc;
    }
    path.push_back({ent_r, ent_c});

    cout << "\nPath from entrance to exit:\n";
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << "(" << path[i].first << ", " << path[i].second << ")\n";
    }
}

// ----------------------------------------------------------
// STUDENTS IMPLEMENT DFS HERE
// Add arguments, return type, and logic
// ----------------------------------------------------------
bool dfs(int r, int c,
        const vector<vector<int>>& maze,
        vector<vector<bool>>& visited,
        vector<vector<int>>& parent_r,
        vector<vector<int>>& parent_c,
        int exit_r, int exit_c) {
   // Your code here:
   // int next_r ; //r + dr[i]; //next row(neighboor for yout path)
   //   int next_c ; //c + dc[i];
   //next column when moving


   int N = maze.size();  // size dimension of the generated maze
   int M = maze[0].size();




   //Out-of-bounds checks:
   if (r <0 || r >= N) {
       return false;
   } else if (c <0 || c >= M) {
       return false;
       //base case -> if coordinates lesss than 0 but greater/equal to given dimesnions
   }




   //Wall checks:
   if (maze[r][c] == 1) {
       return false;
       //base case-> if you hit a wall(1) it stops
   }


   //Visited checks:
   if (visited[r][c] == true) {
       return false;
       //base case -> if the currecunt coordinates is already vistited stop recusrion
   } else {
       //Marking the current cell as visited:


       // if its visted mark it true
       visited[r][c] = true;
   }


   //Returning true when the exit is found:
   if (r == exit_r && c == exit_c) {
       return true;
   }






   //Checking if (r, c) is the exit:
   if (r == exit_r && c == exit_c) {
       return true;
       //  base case: if r and c coordinates does equal the exit
   }


   else {
       //  for (int i = 0; i < 4; i++) { // all of i possible outcomes
       //   next_r = r + dr[i]; // the currect coord will equal the necxt follwoing direct depending on i
       //   next_c = c + dc[i];
       //  dfs (maze[r][c] = maze[next_r][next_c]);
       //   }
       // Recursive case = check the next position in the path to see if its the exit
       //  }


       //Exploring neighbors using dr and dc:
   //    for (int i = 0; i < 4; i++) {
           //next_r = r + dr[i];
           // next_c = c + dc[i];
           //make sure before recusrion you check if tis ouot of bound, a wall , or visited






        //   if (r == exit_r && c == exit_c) {
         //      return true ; // if the neigboors equal the exit cell
        //   }else if (visited[r][c] == 1) {
        //       return true;
        //   } else {
               // dfs(next_r,next_c);
       //    }
     //  }


       visited[r][c] = true; // this is for marking the cell you are in curretnly as vsited so the dfs cn move on to the next


       //Assigning the parent before recursing:
       //main recursive function code after main checks are completed
       for (int i = 0; i < 4; i++) {
           int next_r = r + dr[i];
           int next_c = c + dc[i];


           //make a base case for the neightboor rc (nextrc)
           if (next_r <0 || next_r >= N) {
               continue ;
           }else if (next_c <0 || next_c >= M) {
               continue;
           } else if (maze[next_r][next_c] == 1) {
               continue;
           } else if (visited[next_r][next_c] == true) {
               continue ;
           }


           parent_r[next_r][next_c] = r;
           parent_c[next_r][next_c] = c;
           // your ecurse call should use all variables in the function
           if (dfs(next_r, next_c, maze, visited, parent_r, parent_c, exit_r, exit_c))
               return true;
       }
       return false;
   }
}



// ----------------------------------------------------------
// MAIN PROGRAM (students add DFS calls and logic)
// ----------------------------------------------------------
int main() {
    int N, M;

    cout << "Enter maze dimensions N M: ";
    cin >> N >> M;

    vector<vector<int>> maze(N, vector<int>(M));
    generateMaze(maze, N, M);

    // Pick entrance and exit
    pair<int,int> entrance = chooseBoundaryCell(maze);
    pair<int,int> exitcell = chooseBoundaryCell(maze);

    while (exitcell == entrance) {
        exitcell = chooseBoundaryCell(maze);
    }

    int ent_r = entrance.first;
    int ent_c = entrance.second;
    int exit_r = exitcell.first;
    int exit_c = exitcell.second;

    // Display the maze
    printMaze(maze, ent_r, ent_c, exit_r, exit_c);

    // Students must use these
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    vector<vector<int>> parent_r(N, vector<int>(M, -1));
    vector<vector<int>> parent_c(N, vector<int>(M, -1));

    // ------------------------------------------------------
    // STUDENT WORK:
    // Call your DFS, track visited, and fill parent_r and parent_c
    // ------------------------------------------------------
     bool found = dfs(ent_r, ent_c, maze, visited, parent_r, parent_c, exit_r, exit_c);

    // ------------------------------------------------------
    // STUDENT WORK:
    // If found, print the path
    // ------------------------------------------------------
     if (found) {
        printPath(exitcell, parent_r, parent_c, ent_r, ent_c);
    } else {
        cout << "\nNo path exists.\n";
     }

    return 0;
}