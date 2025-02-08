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

vector<PuzzleState> generateMoves(const PuzzleState& state) {
    vector<PuzzleState> moves;
    int row, col;
    findEmptyTile(state.board, row, col);

    // Move Left
    if (col > 0) {
        PuzzleState newState = state;
        // Move tile to the right
        newState.board[row][col] = newState.board[row][col - 1];
        // Set the empty tile
        newState.board[row][col - 1] = 0; 
        newState.cost += 1;
        newState.path += "L";
        moves.push_back(newState);
    }

    // Move Right
    if (col < 2) {
        PuzzleState newState = state;
        // Move tile to the left
        newState.board[row][col] = newState.board[row][col + 1];
        // Set the empty tile
        newState.board[row][col + 1] = 0; 
        newState.cost += 1;
        newState.path += "R";
        moves.push_back(newState);
    }

    // Move Up
    if (row > 0) {
        PuzzleState newState = state;
        // Move tile down
        newState.board[row][col] = newState.board[row - 1][col];
        // Set the empty tile
        newState.board[row - 1][col] = 0; 
        newState.cost += 1;
        newState.path += "U";
        moves.push_back(newState);
    }

    // Move Down
    if (row < 2) {
        PuzzleState newState = state;
        // Move tile up
        newState.board[row][col] = newState.board[row + 1][col];
        // Set the empty tile
        newState.board[row + 1][col] = 0;
        newState.cost += 1;
        newState.path += "D";
        moves.push_back(newState);
    }

    return moves;
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

    int row;
    int col;
    findEmptyTile(initialState.board, row, col);
    cout << "Empty tile is at: (" << row << ", " << col << ")" << endl;

    if (isGoalState(initialState)) {
        cout << "The initial state is already the goal state!" << endl;
    } else {
        cout << "The initial state is not the goal state." << endl;
    }

    vector<PuzzleState> moves = generateMoves(initialState);
    cout << "Possible moves: " << moves.size() << endl;

    return 0;
}