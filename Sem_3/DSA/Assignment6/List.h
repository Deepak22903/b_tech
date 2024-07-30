typedef struct Node {
    int row;
    int col;
    int value;
    struct Node* next;
} Node;

Node* createNode(int row, int col, int value);
Node* readMatrix(const char* filename, int* numRows, int* numCols);
void printMatrix(Node* result, int numRows, int numCols);
Node* addMatrices(Node* matrix1, Node* matrix2, int numRows, int numCols);
Node* subtractMatrices(Node* matrix1, Node* matrix2, int numRows, int numCols);
void writeMatrixToFile(const char* filename, Node* matrix, int numRows, int numCols);
