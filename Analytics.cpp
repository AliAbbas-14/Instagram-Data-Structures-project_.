#include "Instagram.h"

/**
 * Function: maxVal
 * Description: Helper to return the mathematical maximum of two integers.
 */
int maxVal(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

/**
 * Function: height
 * Description: Gets the stored height of an AVL Node to calculate balance.
 */
int height(AVLNode* N) {
    if (N == nullptr) {
        return 0;
    }
    return N->height;
}

/**
 * Function: rightRotate
 * Description: Performs a Right Rotation on a subtree to restore AVL properties.
 */
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = maxVal(height(y->left), height(y->right)) + 1;
    x->height = maxVal(height(x->left), height(x->right)) + 1;

    return x;
}

/**
 * Function: leftRotate
 * Description: Performs a Left Rotation on a subtree to restore AVL properties.
 */
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = maxVal(height(x->left), height(x->right)) + 1;
    y->height = maxVal(height(y->left), height(y->right)) + 1;

    return y;
}

/**
 * Function: getBalance
 * Description: Calculates the height difference between left and right subtrees.
 */
int getBalance(AVLNode* N) {
    if (N == nullptr) {
        return 0;
    }
    return height(N->left) - height(N->right);
}

/**
 * Function: isLess
 * Description: Comparator function to sort strictly based on value, breaking ties with keys.
 */
bool isLess(int v1, string k1, int v2, string k2) {
    if (v1 != v2) {
        return v1 < v2;
    }
    return k1 < k2;
}

/**
 * Function: isGreater
 * Description: Comparator function to sort strictly based on value, breaking ties with keys.
 */
bool isGreater(int v1, string k1, int v2, string k2) {
    if (v1 != v2) {
        return v1 > v2;
    }
    return k1 > k2;
}

/**
 * Function: insertAVL
 * Description: Recursively inserts a key-value pair as an AVLNode, then balances the tree utilizing rotations.
 */
AVLNode* insertAVL(AVLNode* node, string key, int value) {
    if (node == nullptr) {
        AVLNode* newNode = new AVLNode();
        newNode->key = key;
        newNode->value = value;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 1;
        return newNode;
    }

    if (isLess(value, key, node->value, node->key) == true) {
        node->left = insertAVL(node->left, key, value);
    }
    else if (isGreater(value, key, node->value, node->key) == true) {
        node->right = insertAVL(node->right, key, value);
    }
    else {
        return node;
    }

    node->height = 1 + maxVal(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && isLess(value, key, node->left->value, node->left->key) == true) {
        return rightRotate(node);
    }
    if (balance < -1 && isGreater(value, key, node->right->value, node->right->key) == true) {
        return leftRotate(node);
    }
    if (balance > 1 && isGreater(value, key, node->left->value, node->left->key) == true) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && isLess(value, key, node->right->value, node->right->key) == true) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

/**
 * Function: minValueNode
 * Description: Finds the leftmost leaf within an AVL tree structure (minimum value).
 */
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

/**
 * Function: deleteAVL
 * Description: Deletes a specific node by its key and tracked value, re-balancing the tree upwards.
 */
AVLNode* deleteAVL(AVLNode* root, string key, int value) {
    if (root == nullptr) {
        return root;
    }

    if (isLess(value, key, root->value, root->key) == true) {
        root->left = deleteAVL(root->left, key, value);
    }
    else if (isGreater(value, key, root->value, root->key) == true) {
        root->right = deleteAVL(root->right, key, value);
    }
    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else {
                *root = *temp;
            }
            delete temp;
        }
        else {
            AVLNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->value = temp->value;
            root->right = deleteAVL(root->right, temp->key, temp->value);
        }
    }

    if (root == nullptr) {
        return root;
    }

    root->height = 1 + maxVal(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

/**
 * Function: findValueByKey
 * Description: Recursively searches the tree strictly by its 'key' field regardless of tree order.
 */
int findValueByKey(AVLNode* root, string key) {
    if (root == nullptr) {
        return -1;
    }
    if (root->key == key) {
        return root->value;
    }

    int leftRes = findValueByKey(root->left, key);
    if (leftRes != -1) {
        return leftRes;
    }

    return findValueByKey(root->right, key);
}

/**
 * Function: reverseInorderTopK
 * Description: Traverses the AVL tree right->node->left effectively descending from highest value to lowest.
 */
void reverseInorderTopK(AVLNode* root, int& K) {
    if (root == nullptr || K <= 0) {
        return;
    }

    reverseInorderTopK(root->right, K);

    if (K > 0) {
        cout << "- " << root->key << " (Metric: " << root->value << ")" << endl;
        K = K - 1;
    }

    reverseInorderTopK(root->left, K);
}

/**
 * Function: rangeQuery
 * Description: Retrieves all AVL Nodes whose value fits within the inclusive span [min, max].
 */
void rangeQuery(AVLNode* root, int min, int max) {
    if (root == nullptr) {
        return;
    }

    if (root->value >= min) {
        rangeQuery(root->left, min, max);
    }

    if (root->value >= min && root->value <= max) {
        cout << "- " << root->key << " | Value: " << root->value << endl;
    }

    if (root->value <= max) {
        rangeQuery(root->right, min, max);
    }
}
