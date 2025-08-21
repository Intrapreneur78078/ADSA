#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    
    Node(int val) : key(val), left(nullptr), right(nullptr), height(1) {}
};
int getHeight(Node* node) {
    return node ? node->height : 0;
}
int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}
void updateHeight(Node* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// Right rotation
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Left rotation
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* insert(Node* root, int key) {
    // 1. Perform normal BST insertion
    if (!root)
        return new Node(key);
    
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else // no duplicacy 
        return root;

    // 2. Update height of this ancestor node
    updateHeight(root);

    // 3. Get the balance factor
    int balance = getBalance(root);

    // 4. Balance the tree

    // LL
    if (balance > 1 && key < root->left->key)
        return rotateRight(root);

    // RR
    if (balance < -1 && key > root->right->key)
        return rotateLeft(root);

    // LR
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // RL
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    // if no rotation happens
    return root;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

int main() {
    Node* root = nullptr;

    int keys[] = { 10, 20, 30, 40, 50, 25 };

    for (int key : keys)
        root = insert(root, key);

    cout << "Inorder traversal of AVL Tree: ";
    inorder(root);
    cout << endl;

    return 0;
}
