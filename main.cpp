#include <iostream>
#include <vector>

using namespace std;

const vector<vector<int>> GOAL_STATE = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

struct PuzzleState {
    // Current state of the board
    vector<vector<int>> board;
     // Number of moves taken to reach this state
    int cost;
    string path;
};

bool isGoalState(const PuzzleState& state) {
    return state.board == GOAL_STATE;
}

void findEmptyTile(const vector<vector<int>>& board, int& row, int& col) {
    if (board[0][0] == 0) { 
        row = 0; 
        col = 0; 
        return; 
    }
    if (board[0][1] == 0) { 
        row = 0; 
        col = 1; 
        return; 
    }
    if (board[0][2] == 0) { 
        row = 0; 
        col = 2; 
        return; 
    }
    if (board[1][0] == 0) { 
        row = 1; 
        col = 0; 
        return; 
    }
    if (board[1][1] == 0) { 
        row = 1; 
        col = 1; 
        return; 
    }
    if (board[1][2] == 0) { 
        row = 1; 
        col = 2; 
        return; 
    }
    if (board[2][0] == 0) { 
        row = 2; 
        col = 0; 
        return; 
    }
    if (board[2][1] == 0) { 
        row = 2; 
        col = 1; 
        return; 
    }
    if (board[2][2] == 0) { 
        row = 2; 
        col = 2; 
        return; 
    }
    // If board is invalid return non possible values
    row = -1; 
    col = -1;
}

int main() {
    PuzzleState initialState;
    initialState.board = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}
    };
    initialState.cost = 0;
    initialState.path = "";

    cout << "Initial State:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << initialState.board[i][j] << " ";
        }
        cout << endl;
    }

int row, col;
    findEmptyTile(initialState.board, row, col);
    cout << "Empty tile is at: (" << row << ", " << col << ")" << endl;

    if (isGoalState(initialState)) {
        cout << "The initial state is already the goal state!" << endl;
    } else {
        cout << "The initial state is not the goal state." << endl;
    }

    return 0;
}