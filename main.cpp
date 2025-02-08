#include <iostream>
#include <vector>

using namespace std;

const vector<vector<int>> GOAL_STATE = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

// struct PuzzleState {
//     // Current state of the board
//     vector<vector<int>> board;
//     // Number of moves taken to reach this state
//     int cost;
//     string path;
// };

struct Node {
    vector<vector<int> > board;
    int cost;
    Node* parent;
    char move;
};

void printBoard(const vector<vector<int> >& board) {
    cout << board[0][0] << " " << board[0][1] << " " << board[0][2] << endl;
    cout << board[1][0] << " " << board[1][1] << " " << board[1][2] << endl;
    cout << board[2][0] << " " << board[2][1] << " " << board[2][2] << endl;
}

void printPath(Node* node) {
    if (node->parent != NULL) { 
        printPath(node->parent); 
        cout << node->move;
    }
}

void printSolution(Node* goal) {
    cout << "Goal state!" << endl;
    cout << "Solution found with cost (g(n)): " << goal->cost << endl;
    cout << "Path: ";
    printPath(goal);
    cout << endl;
}

bool isGoalState(const Node* node) {
    return (node->board == GOAL_STATE);
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

vector<Node*> generateMoves(Node* current) {
    // vector<PuzzleState> moves;
    vector<Node*> moves;
    int row;
    int col;
    findEmptyTile(current->board, row, col);
    Node* newNode = NULL;
    if (col > 0) { 
        newNode = new Node;
        newNode->board = current->board;
        newNode->board[row][col] = newNode->board[row][col - 1];
        newNode->board[row][col - 1] = 0;
        newNode->cost = current->cost + 1;
        newNode->parent = current;
        newNode->move = 'L';
        moves.push_back(newNode);
    }
    if (col < 2) { 
        newNode = new Node;
        newNode->board = current->board;
        newNode->board[row][col] = newNode->board[row][col + 1];
        newNode->board[row][col + 1] = 0;
        newNode->cost = current->cost + 1;
        newNode->parent = current;
        newNode->move = 'R';
        moves.push_back(newNode);
    }
    if (row > 0) { 
        newNode = new Node;
        newNode->board = current->board;
        newNode->board[row][col] = newNode->board[row - 1][col];
        newNode->board[row - 1][col] = 0;
        newNode->cost = current->cost + 1;
        newNode->parent = current;
        newNode->move = 'U';
        moves.push_back(newNode);
    }
    if (row < 2) { 
        newNode = new Node;
        newNode->board = current->board;
        newNode->board[row][col] = newNode->board[row + 1][col];
        newNode->board[row + 1][col] = 0;
        newNode->cost = current->cost + 1;
        newNode->parent = current;
        newNode->move = 'D';
        moves.push_back(newNode);
    }
    return moves;
}

// void uniformCostSearch(const PuzzleState& initialState) {
//     PuzzleState current = initialState;

//     // Check if the initial state is the goal state
//     if (isGoalState(current)) {
//         cout << "Solution found with cost: " << current.cost << endl;
//         cout << "Path: " << current.path << endl;
//         return;
//     }

//     // Generate all possible moves from the initial state
//     vector<PuzzleState> moves = generateMoves(current);

//     // Check each move individually
//     if (!moves.empty()) {
//         PuzzleState move1 = moves[0];
//         if (isGoalState(move1)) {
//             cout << "Solution found with cost: " << move1.cost << endl;
//             cout << "Path: " << move1.path << endl;
//             return;
//         }

//         PuzzleState move2 = moves[1];
//         if (isGoalState(move2)) {
//             cout << "Solution found with cost: " << move2.cost << endl;
//             cout << "Path: " << move2.path << endl;
//             return;
//         }

//         PuzzleState move3 = moves[2];
//         if (isGoalState(move3)) {
//             cout << "Solution found with cost: " << move3.cost << endl;
//             cout << "Path: " << move3.path << endl;
//             return;
//         }

//         PuzzleState move4 = moves[3];
//         if (isGoalState(move4)) {
//             cout << "Solution found with cost: " << move4.cost << endl;
//             cout << "Path: " << move4.path << endl;
//             return;
//         }
//     }

//     cout << "No solution found." << endl;
// }

int misplacedTileHeuristic(const vector<vector<int> >& board) {
    int count = 0;
    if ((board[0][0] != 0) && (board[0][0] != GOAL_STATE[0][0])) { 
        count++; 
    }
    if ((board[0][1] != 0) && (board[0][1] != GOAL_STATE[0][1])) { 
        count++;
    }
    if ((board[0][2] != 0) && (board[0][2] != GOAL_STATE[0][2])) { 
        count++;
    }
    if ((board[1][0] != 0) && (board[1][0] != GOAL_STATE[1][0])) { 
        count++;
    }
    if ((board[1][1] != 0) && (board[1][1] != GOAL_STATE[1][1])) { 
        count++;
    }
    if ((board[1][2] != 0) && (board[1][2] != GOAL_STATE[1][2])) { 
        count++;
    }
    if ((board[2][0] != 0) && (board[2][0] != GOAL_STATE[2][0])) { 
        count++;
    }
    if ((board[2][1] != 0) && (board[2][1] != GOAL_STATE[2][1])) { 
        count++;
    }
    if ((board[2][2] != 0) && (board[2][2] != GOAL_STATE[2][2])) { 
        count++;
    }
    return count;
}

// void aStarMisplacedTile(const PuzzleState& initialState) {
//     PuzzleState current = initialState;

//     // Check if the initial state equals goal state
//     if (isGoalState(current)) {
//         cout << "Solution found with cost: " << current.cost << endl;
//         cout << "Path: " << current.path << endl;
//         return;
//     }

//     vector<PuzzleState> moves = generateMoves(current);

//     if (!moves.empty()) {
//         PuzzleState move1 = moves[0];
//         if (isGoalState(move1)) {
//             cout << "Solution found with cost: " << move1.cost << endl;
//             cout << "Path: " << move1.path << endl;
//             return;
//         }

//         PuzzleState move2 = moves[1];
//         if (isGoalState(move2)) {
//             cout << "Solution found with cost: " << move2.cost << endl;
//             cout << "Path: " << move2.path << endl;
//             return;
//         }

//         PuzzleState move3 = moves[2];
//         if (isGoalState(move3)) {
//             cout << "Solution found with cost: " << move3.cost << endl;
//             cout << "Path: " << move3.path << endl;
//             return;
//         }

//         PuzzleState move4 = moves[3];
//         if (isGoalState(move4)) {
//             cout << "Solution found with cost: " << move4.cost << endl;
//             cout << "Path: " << move4.path << endl;
//             return;
//         }
//     }

//     // cout << "OUTPUT FLAG" << endl;
//     cout << "No solution found." << endl;
// }

struct CompareMisplacedTile {
    bool operator()(const Node* a, const Node* b) const {
        int g_a = a->cost;
        int h_a = misplacedTileHeuristic(a->board);
        int f_a = g_a + h_a;
        int g_b = b->cost;
        int h_b = misplacedTileHeuristic(b->board);
        int f_b = g_b + h_b;
        return (f_a > f_b);
    }
};

void generalSearch(Node* initialNode, int algorithmChoice) {
    int nodesExpanded = 0;
    int maxQueueSize = 0;
    if (algorithmChoice == 1) { 
        queue<Node*> frontier;
        frontier.push(initialNode);
        while (!frontier.empty()) {
            if (frontier.size() > maxQueueSize) { 
                maxQueueSize = frontier.size(); 
            }
            Node* current = frontier.front();
            frontier.pop();
            nodesExpanded = nodesExpanded + 1;
            cout << "Expanding state (Uniform Cost): g(n) = " << current->cost << ", f(n) = " << current->cost << endl;
            printBoard(current->board);
            cout << "---------------------" << endl;
            if (isGoalState(current)) { 
                printSolution(current); 
                cout << "Solution depth: " << current->cost << endl;
                cout << "Nodes expanded: " << nodesExpanded << endl;
                cout << "Max queue size: " << maxQueueSize << endl;
                return; 
            }
            vector<Node*> moves = generateMoves(current);
            if (moves.size() > 0) { 
                frontier.push(moves[0]); 
            }
            if (moves.size() > 1) { 
                frontier.push(moves[1]); 
            }
            if (moves.size() > 2) { 
                frontier.push(moves[2]); 
            }
            if (moves.size() > 3) { 
                frontier.push(moves[3]); 
            }
        }
    }
    else if (algorithmChoice == 2) { 
        priority_queue<Node*, vector<Node*>, CompareMisplacedTile> frontier;
        frontier.push(initialNode);
        while (!frontier.empty()) {
            if (frontier.size() > maxQueueSize) { 
                maxQueueSize = frontier.size(); 
            }
            Node* current = frontier.top();
            frontier.pop();
            nodesExpanded = nodesExpanded + 1;
            int g_val = current->cost;
            int h_val = misplacedTileHeuristic(current->board);
            int f_val = g_val + h_val;
            cout << "Expanding state (Misplaced Tile Heuristic): g(n) = " << g_val << ", h(n) = " << h_val << ", f(n) = " << f_val << endl;
            printBoard(current->board);
            cout << "---------------------" << endl;
            if (isGoalState(current)) { 
                printSolution(current); 
                cout << "Solution depth: " << current->cost << endl;
                cout << "Nodes expanded: " << nodesExpanded << endl;
                cout << "Max queue size: " << maxQueueSize << endl;
                return; 
            }
            vector<Node*> moves = generateMoves(current);
            if (moves.size() > 0) { 
                frontier.push(moves[0]); 
            }
            if (moves.size() > 1) { 
                frontier.push(moves[1]); 
            }
            if (moves.size() > 2) { 
                frontier.push(moves[2]); 
            }
            if (moves.size() > 3) { 
                frontier.push(moves[3]); 
            }
        }
    }
}

int main() {
    int userChoice;
    cout << "Welcome to 862384951 8-Puzzle Solver. Type '1' to use a default puzzle, or '2' to create your own." << endl;
    cin >> userChoice;
    Node* initialNode = new Node;
    initialNode->board.resize(3);
    initialNode->board[0].resize(3);
    initialNode->board[1].resize(3);
    initialNode->board[2].resize(3);
    if (userChoice == 1) { 
        initialNode->board[0][0] = 1;
        initialNode->board[0][1] = 2;
        initialNode->board[0][2] = 3;
        initialNode->board[1][0] = 0;
        initialNode->board[1][1] = 4;
        initialNode->board[1][2] = 6;
        initialNode->board[2][0] = 7;
        initialNode->board[2][1] = 5;
        initialNode->board[2][2] = 8;
    }
    else if (userChoice == 2) { 
        cout << "Enter your puzzle, using a zero to represent the blank. Please only enter valid 8-puzzles." << endl;
        cout << "Enter the puzzle delimiting the numbers with a space. Type RETURN only when finished." << endl;
        int first;
        int second;
        int third;
        cout << "Enter the first row: " << endl;
        cin >> first;
        cin >> second;
        cin >> third;
        initialNode->board[0][0] = first;
        initialNode->board[0][1] = second;
        initialNode->board[0][2] = third;
        cout << "Enter the second row: " << endl;
        cin >> first;
        cin >> second;
        cin >> third;
        initialNode->board[1][0] = first;
        initialNode->board[1][1] = second;
        initialNode->board[1][2] = third;
        cout << "Enter the third row: " << endl;
        cin >> first;
        cin >> second;
        cin >> third;
        initialNode->board[2][0] = first;
        initialNode->board[2][1] = second;
        initialNode->board[2][2] = third;
    }
    else { 
        cout << "Invalid choice. Exiting." << endl;
        return 1;
    }

    // PuzzleState initialState;
    // initialState.board = {
    //     {1, 2, 3},
    //     {4, 0, 6},
    //     {7, 5, 8}
    // };
    // initialState.cost = 0;
    // initialState.path = "";

    // cout << "Initial State:" << endl;
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         cout << initialState.board[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    initialNode->cost = 0;
    initialNode->parent = NULL;
    initialNode->move = ' ';

    // int row;
    // int col;
    // findEmptyTile(initialState.board, row, col);
    // cout << "Empty tile is at: (" << row << ", " << col << ")" << endl;

    // if (isGoalState(initialState)) {
    //     cout << "The initial state is already the goal state!" << endl;
    // } else {
    //     cout << "The initial state is not the goal state." << endl;
    // }

    cout << "Select algorithm. (1) for Uniform Cost Search, (2) for the Misplaced Tile Heuristic, or (3) for the Manhattan Distance Heuristic" << endl;
    int algoChoice;
    cin >> algoChoice;
    generalSearch(initialNode, algoChoice);
    return 0;

    // uniformCostSearch(initialState);

    // aStarMisplacedTile(initialState);

    // vector<PuzzleState> moves = generateMoves(initialState);
    // cout << "Possible moves: " << moves.size() << endl;

    return 0;
}