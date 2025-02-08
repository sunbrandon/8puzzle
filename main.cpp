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

void uniformCostSearch(const PuzzleState& initialState) {
    PuzzleState current = initialState;

    // Check if the initial state is the goal state
    if (isGoalState(current)) {
        cout << "Solution found with cost: " << current.cost << endl;
        cout << "Path: " << current.path << endl;
        return;
    }

    // Generate all possible moves from the initial state
    vector<PuzzleState> moves = generateMoves(current);

    // Check each move individually
    if (!moves.empty()) {
        PuzzleState move1 = moves[0];
        if (isGoalState(move1)) {
            cout << "Solution found with cost: " << move1.cost << endl;
            cout << "Path: " << move1.path << endl;
            return;
        }

        PuzzleState move2 = moves[1];
        if (isGoalState(move2)) {
            cout << "Solution found with cost: " << move2.cost << endl;
            cout << "Path: " << move2.path << endl;
            return;
        }

        PuzzleState move3 = moves[2];
        if (isGoalState(move3)) {
            cout << "Solution found with cost: " << move3.cost << endl;
            cout << "Path: " << move3.path << endl;
            return;
        }

        PuzzleState move4 = moves[3];
        if (isGoalState(move4)) {
            cout << "Solution found with cost: " << move4.cost << endl;
            cout << "Path: " << move4.path << endl;
            return;
        }
    }

    cout << "No solution found." << endl;
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

    // int row;
    // int col;
    // findEmptyTile(initialState.board, row, col);
    // cout << "Empty tile is at: (" << row << ", " << col << ")" << endl;

    // if (isGoalState(initialState)) {
    //     cout << "The initial state is already the goal state!" << endl;
    // } else {
    //     cout << "The initial state is not the goal state." << endl;
    // }

    uniformCostSearch(initialState);

    // vector<PuzzleState> moves = generateMoves(initialState);
    // cout << "Possible moves: " << moves.size() << endl;

    return 0;
}