#include "Instagram.h"

// Helper function instead of lambda for simple understanding
bool unlinkEdge(User* u, string target) {
    Edge* curr = u->friendsHead;
    Edge* prev = nullptr;
    while (curr != nullptr) {
        if (curr->friendUserName == target) {
            if (prev != nullptr) {
                prev->next = curr->next;
            }
            else {
                u->friendsHead = curr->next;
            }
            delete curr;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

/**
 * Function: addFriend
 * Description: Manifests twin direction 'Edge' pointers on two authenticated instances.
 */
void addFriend() {
    if (requireAuth() == false) {
        return;
    }

    string fName;
    cout << "Enter username to follow/friend: ";
    cin >> ws;
    getline(cin, fName);

    User* u2 = findUser(fName);
    if (u2 == nullptr) {
        cout << "User not found." << endl;
        return;
    }
    if (fName == currentUser->userName) {
        cout << "Cannot friend yourself!" << endl;
        return;
    }

    Edge* check = currentUser->friendsHead;
    while (check != nullptr) {
        if (check->friendUserName == fName) {
            cout << "Already connected!" << endl;
            return;
        }
        check = check->next;
    }

    Edge* e1 = new Edge{ fName, currentUser->friendsHead };
    currentUser->friendsHead = e1;

    Edge* e2 = new Edge{ currentUser->userName, u2->friendsHead };
    u2->friendsHead = e2;

    saveData();
    cout << "Successfully connected with " << fName << "!" << endl;
}

/**
 * Function: removeFriend
 * Description: Splices edges simultaneously preventing subsequent relationship visibility.
 */
void removeFriend() {
    if (requireAuth() == false) {
        return;
    }

    string fName;
    cout << "Enter friend's username to Unfollow: ";
    cin >> ws;
    getline(cin, fName);

    User* f = findUser(fName);
    if (f != nullptr) {
        bool b1 = unlinkEdge(currentUser, fName);
        bool b2 = unlinkEdge(f, currentUser->userName);
        if (b1 == true || b2 == true) {
            saveData();
            cout << "Connection removed." << endl;
        }
        else {
            cout << "You were not connected to " << fName << "." << endl;
        }
    }
    else {
        cout << "User doesn't exist!" << endl;
    }
}

/**
 * Function: viewFriends
 * Description: Sequentially enumerates locally anchored Edge instances.
 */
void viewFriends() {
    if (requireAuth() == false) {
        return;
    }

    Edge* e = currentUser->friendsHead;
    if (e == nullptr) {
        cout << "Your network is empty." << endl;
        return;
    }

    cout << "\n--- Instagram Connections ---" << endl;
    while (e != nullptr) {
        cout << "- " << e->friendUserName << endl;
        e = e->next;
    }
}

/**
 * Function: isVisited
 * Description: Determines if a given node was already traversed during search.
 */
bool isVisited(StringNode* head, string val) {
    while (head != nullptr) {
        if (head->val == val) {
            return true;
        }
        head = head->next;
    }
    return false;
}

/**
 * Function: addVisited
 * Description: Logs a traversal node into our custom visited marker linked list.
 */
void addVisited(StringNode*& head, string val) {
    StringNode* n = new StringNode{ val, head };
    head = n;
}

// Simple Custom Queue logic for BFS
struct QNode {
    string val;
    QNode* next;
};

void pushQ(QNode*& front, QNode*& rear, string s) {
    QNode* n = new QNode{ s, nullptr };
    if (rear == nullptr) {
        front = n;
        rear = n;
    }
    else {
        rear->next = n;
        rear = n;
    }
}

string popQ(QNode*& front, QNode*& rear) {
    if (front == nullptr) {
        return "";
    }
    string s = front->val;
    QNode* t = front;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    delete t;
    return s;
}

/**
 * Function: BFS
 * Description: Dissects social degrees systematically via an implicit procedural Queue.
 */
void BFS() {
    if (requireAuth() == false) {
        return;
    }

    cout << "Performing Social BFS from {" << currentUser->userName << "}..." << endl;

    QNode* front = nullptr;
    QNode* rear = nullptr;
    StringNode* visited = nullptr;

    string st = currentUser->userName;
    pushQ(front, rear, st);
    addVisited(visited, st);

    cout << "Network Trace: ";
    while (front != nullptr) {
        string curr = popQ(front, rear);
        cout << curr << " -> ";

        User* u = findUser(curr);
        if (u != nullptr) {
            Edge* e = u->friendsHead;
            while (e != nullptr) {
                if (isVisited(visited, e->friendUserName) == false) {
                    addVisited(visited, e->friendUserName);
                    pushQ(front, rear, e->friendUserName);
                }
                e = e->next;
            }
        }
    }
    cout << "[END]" << endl;

    // Free the linked list memory safely
    while (visited != nullptr) {
        StringNode* t = visited;
        visited = visited->next;
        delete t;
    }
}

/**
 * Function: dfsHelper
 * Description: Implements intrinsic Stack behavior to recursively seek tree depth targets.
 */
void dfsHelper(string curr, StringNode*& visited, string target, bool& found) {
    if (found == true) {
        return;
    }

    cout << curr << " -> ";
    addVisited(visited, curr);

    if (curr == target) {
        found = true;
        return;
    }

    User* u = findUser(curr);
    if (u != nullptr) {
        Edge* e = u->friendsHead;
        while (e != nullptr) {
            if (isVisited(visited, e->friendUserName) == false) {
                dfsHelper(e->friendUserName, visited, target, found);
            }
            e = e->next;
        }
    }
}

/**
 * Function: DFS
 * Description: Explores potential connection depths towards a distinct end-user identifier.
 */
void DFS() {
    if (requireAuth() == false) {
        return;
    }

    string endUser;
    cout << "Enter target endUser for Deep Search: ";
    cin >> ws;
    getline(cin, endUser);

    StringNode* visited = nullptr;
    bool found = false;

    cout << "DFS Discovery Path: ";
    dfsHelper(currentUser->userName, visited, endUser, found);

    if (found == true) {
        cout << "[FOUND CONNECTION!]" << endl;
    }
    else {
        cout << "[DEAD END! User unreachable based on depth relationships]" << endl;
    }

    // Free memory
    while (visited != nullptr) {
        StringNode* t = visited;
        visited = visited->next;
        delete t;
    }
}
