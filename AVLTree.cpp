#include <iostream>

using namespace std;

struct Node {
    double value;
    int height;
    Node* left;
    Node* right;

    Node(double value) : value(value), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
    Node* root;

public:
    AVLTree() : root(nullptr) {}
    
    void printTree() {
        printNode(root, 0);
    }

    void insert(double value) {
        root = insertNode(root, value);
    }

    Node* insertNode(Node* node, double value) {
        // Обычная вставка узла в бинарное дерево поиска
        if (node == nullptr)
            return new Node(value);
        if (value < node->value)
            node->left = insertNode(node->left, value);
        else if (value > node->value)
            node->right = insertNode(node->right, value);
        else // Если значение уже присутствует в дереве, ничего не делаем
            return node;
        
        // Обновляем высоту текущего узла
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Проверяем балансировку текущего узла и балансируем его, если необходимо
        int balance = getBalance(node);

        if (balance > 1 && value < node->left->value)
            return rotateRight(node);
        
        if (balance < -1 && value > node->right->value)
            return rotateLeft(node);
        
        if (balance > 1 && value > node->left->value) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && value < node->right->value) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inOrderTraversal() {
        cout << "In-order traversal: ";
        inOrder(root);
        cout << endl;
    }

    void findLeafSum() {
        cout << "Sum of leaf values: " << getLeafSum(root) << endl;
    }

    void findAverage() {
        double sum = getSum(root);
        int count = getCount(root);
        double average = count != 0 ? sum / count : 0;
        cout << "Average: " << average << endl;
    }

private:

    void printNode(Node* nd, int indent) {
        if (nd == nullptr)
            return;
        printNode(nd->right, indent + 4);
        cout << string(indent, ' ') << nd->value << endl;
        printNode(nd->left, indent + 4);
    }
    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int getBalance(Node* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    void inOrder(Node* root) {
        if (root == nullptr)
            return;
        inOrder(root->left);
        cout << root->value << " ";
        inOrder(root->right);
    }

    double getLeafSum(Node* node) {
        if (node == nullptr)
            return 0;
        if (node->left == nullptr && node->right == nullptr) // Листовой узел
            return node->value;
        return getLeafSum(node->left) + getLeafSum(node->right);
    }

    double getSum(Node* node) {
        if (node == nullptr)
            return 0;
        return node->value + getSum(node->left) + getSum(node->right);
    }

    int getCount(Node* node) {
        if (node == nullptr)
            return 0;
        return 1 + getCount(node->left) + getCount(node->right);
    }
};

int main() {
    AVLTree tree;

    tree.insert(1.2);
    tree.insert(2.3);
    tree.insert(3.4);
    tree.insert(4.5);
    tree.insert(5.6);

    tree.inOrderTraversal();
    tree.findLeafSum();
    tree.findAverage();
    
    tree.printTree();

    return 0;
}