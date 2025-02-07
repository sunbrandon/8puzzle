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

    return 0;
}