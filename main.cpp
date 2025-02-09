#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

const vector<vector<int>> GOAL_STATE = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

// different boards with depths 4, 8, 16, and 24 for easy testing
const vector<vector<int>> FOUR = {
    {1, 2, 3},
    {5, 0, 6},
    {4, 7, 8}
};

const vector<vector<int>> EIGHT = {
    {1, 3, 6},
    {5, 0, 2},
    {4, 7, 8}
};

const vector<vector<int>> SIXTEEN= {
    {1, 6, 7},
    {5, 0, 3},
    {4, 8, 2}
};

const vector<vector<int>> TWOFOUR = {
    {0, 7, 2},
    {4, 6, 1},
    {3, 5, 8}
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
    cout << "[ " << board[0][0] << ", " << board[0][1] << ", " << board[0][2] << " ]" << endl;
    cout << "[ " << board[1][0] << ", " << board[1][1] << ", " << board[1][2] << " ]" << endl;
    cout << "[ " << board[2][0] << ", " << board[2][1] << ", " << board[2][2] << " ]" << endl;
}

// recursively prints solution by reverse traversing
void printPath(Node* node) {
    if (node->parent != NULL) { 
        printPath(node->parent); 
        cout << node->move;
    }
}

void printSolution(Node* goal) {
    cout << endl;
    cout << "Goal state!" << endl;
    // cout << "Solution found with cost (g(n)): " << goal->cost << endl;
    // cout << "Path: ";
    // printPath(goal);
    cout << endl;
}

// checks the board of the current node to see if equal to goal state
bool isGoalState(const Node* node) {
    return (node->board == GOAL_STATE);
}

// go through each tile changing coordinates until empty tile is found
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
    // if no empty tile found board is invalid, return arbitrary val
    row = -1; 
    col = -1;
}

// generate all possible moves from the current node
vector<Node*> generateMoves(Node* current) {
    // vector<PuzzleState> moves;
    vector<Node*> moves;
    int row;
    int col;
    findEmptyTile(current->board, row, col);
    Node* newNode = NULL;
    // check if left move is possible
    if (col > 0) { 
        newNode = new Node;
        newNode->board = current->board;
        // if left move is possible swap with empty tile
        newNode->board[row][col] = newNode->board[row][col - 1];
        newNode->board[row][col - 1] = 0;
        newNode->cost = current->cost + 1;
        newNode->parent = current;
        newNode->move = 'L';
        moves.push_back(newNode);
    }
    // check if right move is possible
    if (col < 2) { 
        newNode = new Node;
        newNode->board = current->board;
        // if right move is possible swap with empty tile
        newNode->board[row][col] = newNode->board[row][col + 1];
        newNode->board[row][col + 1] = 0;
        newNode->cost = current->cost + 1;
        newNode->parent = current;
        newNode->move = 'R';
        moves.push_back(newNode);
    }
    // check if possible to move up
    if (row > 0) { 
        newNode = new Node;
        newNode->board = current->board;
        // if possible to move up swap with empty tile
        newNode->board[row][col] = newNode->board[row - 1][col];
        newNode->board[row - 1][col] = 0;
        newNode->cost = current->cost + 1;
        newNode->parent = current;
        newNode->move = 'U';
        moves.push_back(newNode);
    }
    // check if possible to move down
    if (row < 2) { 
        newNode = new Node;
        newNode->board = current->board;
        // if possible to move down swap with empty tile
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

// goes through each tile on the board and increments a count of misplaced tiles
int misplacedTileHeuristic(const vector<vector<int> >& board) {
    int count = 0;
    // compare tile on current board to goal board, if not match increment
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

// 
int manhattanDistanceHeuristic(const vector<vector<int> >& board) {
    int distance = 0;
    int goalRow = 0;
    int goalCol = 0;
    // check each tile position if not empty and calculate the goal row and column
    if (board[0][0] != 0) { 
        goalRow = (board[0][0] - 1) / 3; 
        goalCol = (board[0][0] - 1) % 3; 
        // add the manhattan distance to the goal position from current position
        distance = distance + abs(0 - goalRow) + abs(0 - goalCol); 
    }
    if (board[0][1] != 0) { 
        goalRow = (board[0][1] - 1) / 3; 
        goalCol = (board[0][1] - 1) % 3; 
        distance = distance + abs(0 - goalRow) + abs(1 - goalCol); 
    }
    if (board[0][2] != 0) { 
        goalRow = (board[0][2] - 1) / 3; 
        goalCol = (board[0][2] - 1) % 3; 
        distance = distance + abs(0 - goalRow) + abs(2 - goalCol); 
    }
    if (board[1][0] != 0) { 
        goalRow = (board[1][0] - 1) / 3; 
        goalCol = (board[1][0] - 1) % 3; 
        distance = distance + abs(1 - goalRow) + abs(0 - goalCol); 
    }
    if (board[1][1] != 0) { 
        goalRow = (board[1][1] - 1) / 3; 
        goalCol = (board[1][1] - 1) % 3; 
        distance = distance + abs(1 - goalRow) + abs(1 - goalCol); 
    }
    if (board[1][2] != 0) { 
        goalRow = (board[1][2] - 1) / 3; 
        goalCol = (board[1][2] - 1) % 3; 
        distance = distance + abs(1 - goalRow) + abs(2 - goalCol); 
    }
    if (board[2][0] != 0) { 
        goalRow = (board[2][0] - 1) / 3; 
        goalCol = (board[2][0] - 1) % 3; 
        distance = distance + abs(2 - goalRow) + abs(0 - goalCol); 
    }
    if (board[2][1] != 0) { 
        goalRow = (board[2][1] - 1) / 3; 
        goalCol = (board[2][1] - 1) % 3; 
        distance = distance + abs(2 - goalRow) + abs(1 - goalCol); 
    }
    if (board[2][2] != 0) { 
        goalRow = (board[2][2] - 1) / 3; 
        goalCol = (board[2][2] - 1) % 3; 
        distance = distance + abs(2 - goalRow) + abs(2 - goalCol); 
    }
    return distance;
}

// function used by priority queue to determine where to expand
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

// function used by priority queue to determine where to expand
struct CompareManhattanDistance {
    bool operator()(const Node* a, const Node* b) const {
        int g_a = a->cost;
        int h_a = manhattanDistanceHeuristic(a->board);
        int f_a = g_a + h_a;
        int g_b = b->cost;
        int h_b = manhattanDistanceHeuristic(b->board);
        int f_b = g_b + h_b;
        return (f_a > f_b);
    }
};

// function implementing each search algorithm and choosing based of user choice parameter
void generalSearch(Node* initialNode, int algorithmChoice) {
    int nodesExpanded = 0;
    int maxQueueSize = 0;
    if (algorithmChoice == 1) { 
        queue<Node*> frontier;
        frontier.push(initialNode);
        // continue searching while the queue is populated
        while (!frontier.empty()) {
            // keep track of max queue size by updating value if queue is greater than current max size
            if (frontier.size() > maxQueueSize) { 
                maxQueueSize = frontier.size(); 
            }
            // queue is first in first out so remove next node from queue
            Node* current = frontier.front();
            frontier.pop();
            nodesExpanded = nodesExpanded + 1;
            // expand node
            cout << "The best state to expand with a g(n) = " << current->cost << " is..." << endl;
            printBoard(current->board);
            cout << endl;
            // cout << "---------------------" << endl;
            if (isGoalState(current)) { 
                printSolution(current); 
                cout << "Solution depth: " << current->cost << endl;
                cout << "Nodes expanded: " << nodesExpanded << endl;
                cout << "Max queue size: " << maxQueueSize << endl;
                return; 
            }
            // generate valid moves from current state and expanded node
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
            // remove node with lowest cost
            Node* current = frontier.top();
            frontier.pop();
            nodesExpanded = nodesExpanded + 1;
            // compute g(n) and h(n) to display expansion
            int g_val = current->cost;
            int h_val = misplacedTileHeuristic(current->board);
            int f_val = g_val + h_val;
            cout << "The best state to expand with a g(n) = " << g_val << " and h(n) = " << h_val << " is..." << endl;
            printBoard(current->board);
            // cout << "---------------------" << endl;
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
    else if (algorithmChoice == 3) { 
        priority_queue<Node*, vector<Node*>, CompareManhattanDistance> frontier;
        frontier.push(initialNode);
        while (!frontier.empty()) {
            if (frontier.size() > maxQueueSize) { 
                maxQueueSize = frontier.size(); 
            }
            // get node with lowest cost
            Node* current = frontier.top();
            frontier.pop();
            nodesExpanded = nodesExpanded + 1;
            int g_val = current->cost;
            int h_val = manhattanDistanceHeuristic(current->board);
            int f_val = g_val + h_val;
            cout << "The best state to expand with a g(n) = " << g_val << " and h(n) = " << h_val << " is..." << endl;
            printBoard(current->board);
            // cout << "---------------------" << endl;
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
    // 
    else { 
        cout << "Invalid algorithm choice." << endl;
        return;
    }
    cout << "No solution found." << endl;
}

int main() {
    int userChoice = 0;
    cout << "Welcome to 862384951 8-Puzzle Solver. ";
    while (userChoice != 1 && userChoice != 2) {
        cout << "Type '1' to use a default puzzle, or '2' to create your own." << endl;
        cin >> userChoice;
    }
    Node* initialNode = new Node;
    initialNode->board.resize(3);
    initialNode->board[0].resize(3);
    initialNode->board[1].resize(3);
    initialNode->board[2].resize(3);
    if (userChoice == 1) { 
        // int test_board = rand() % 1;
        // if (test_board == 0) {
        //     initialNode->board[0][0] = FOUR[0][0];
        //     initialNode->board[0][1] = FOUR[0][1];
        //     initialNode->board[0][2] = FOUR[0][2];
        //     initialNode->board[1][0] = FOUR[1][0];
        //     initialNode->board[1][1] = FOUR[1][1];
        //     initialNode->board[1][2] = FOUR[1][2];
        //     initialNode->board[2][0] = FOUR[2][0];
        //     initialNode->board[2][1] = FOUR[2][1];
        //     initialNode->board[2][2] = FOUR[2][2];
        // }
        // if (test_board == 0) {
        //     initialNode->board[0][0] = EIGHT[0][0];
        //     initialNode->board[0][1] = EIGHT[0][1];
        //     initialNode->board[0][2] = EIGHT[0][2];
        //     initialNode->board[1][0] = EIGHT[1][0];
        //     initialNode->board[1][1] = EIGHT[1][1];
        //     initialNode->board[1][2] = EIGHT[1][2];
        //     initialNode->board[2][0] = EIGHT[2][0];
        //     initialNode->board[2][1] = EIGHT[2][1];
        //     initialNode->board[2][2] = EIGHT[2][2];
        // }
        // if (test_board == 2) {
        //     initialNode->board[0][0] = SIXTEEN[0][0];
        //     initialNode->board[0][1] = SIXTEEN[0][1];
        //     initialNode->board[0][2] = SIXTEEN[0][2];
        //     initialNode->board[1][0] = SIXTEEN[1][0];
        //     initialNode->board[1][1] = SIXTEEN[1][1];
        //     initialNode->board[1][2] = SIXTEEN[1][2];
        //     initialNode->board[2][0] = SIXTEEN[2][0];
        //     initialNode->board[2][1] = SIXTEEN[2][1];
        //     initialNode->board[2][2] = SIXTEEN[2][2];
        // }
        // if (test_board == 3) {
        //     initialNode->board[0][0] = TWOFOUR[0][0];
        //     initialNode->board[0][1] = TWOFOUR[0][1];
        //     initialNode->board[0][2] = TWOFOUR[0][2];
        //     initialNode->board[1][0] = TWOFOUR[1][0];
        //     initialNode->board[1][1] = TWOFOUR[1][1];
        //     initialNode->board[1][2] = TWOFOUR[1][2];
        //     initialNode->board[2][0] = TWOFOUR[2][0];
        //     initialNode->board[2][1] = TWOFOUR[2][1];
        //     initialNode->board[2][2] = TWOFOUR[2][2];
        // }
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
        cout << "Enter your puzzle, using a zero to represent the blank. Please only enter valid 8-puzzles. Enter the puzzle delimiting the numbers with a space. Type RETURN only when finished." << endl;
        cout << endl;
        int first;
        int second;
        int third;
        cout << "Enter the first row: ";
        cin >> first;
        cin >> second;
        cin >> third;
        initialNode->board[0][0] = first;
        initialNode->board[0][1] = second;
        initialNode->board[0][2] = third;
        cout << "Enter the second row: ";
        cin >> first;
        cin >> second;
        cin >> third;
        initialNode->board[1][0] = first;
        initialNode->board[1][1] = second;
        initialNode->board[1][2] = third;
        cout << "Enter the third row: ";
        cin >> first;
        cin >> second;
        cin >> third;
        initialNode->board[2][0] = first;
        initialNode->board[2][1] = second;
        initialNode->board[2][2] = third;
        cout << endl;
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

    int algoChoice = 0;
    while (algoChoice != 1 && algoChoice != 2 && algoChoice !=3) {
        cout << "Select algorithm. (1) for Uniform Cost Search, (2) for the Misplaced Tile Heuristic, or (3) for the Manhattan Distance Heuristic" << endl;
        cin >> algoChoice;
    }
    cout << endl;
    generalSearch(initialNode, algoChoice);
    return 0;

    // uniformCostSearch(initialState);

    // aStarMisplacedTile(initialState);

    // vector<PuzzleState> moves = generateMoves(initialState);
    // cout << "Possible moves: " << moves.size() << endl;

    return 0;
}