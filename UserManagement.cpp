#include "Instagram.h"

/**
 * Function: registerUser
 * Description: Inserts a novel User instance onto the Hash Table, addressing conflicts via Linked Chains.
 */
void registerUser() {
    string uName, pass, em, b;

    cout << "Enter UserName: ";
    cin >> ws;
    getline(cin, uName);

    if (findUser(uName)) {
        cout << "User already exists!" << endl;
        return;
    }

    cout << "Enter Password: ";
    cin >> ws;
    getline(cin, pass);

    cout << "Enter Email: ";
    cin >> ws;
    getline(cin, em);

    cout << "Enter Bio: ";
    cin >> ws;
    getline(cin, b);

    User* nu = new User{ uName, pass, em, b, "Online", nullptr, nullptr, nullptr, nullptr };
    int idx = getHash(uName);

    // Hash chain linkage
    nu->next = userDirectory[idx];
    userDirectory[idx] = nu;

    // Integrate: Insert into AVL Activity tree with 0 activity
    userActivityTree = insertAVL(userActivityTree, uName, 0);

    saveData();
    cout << "Instagram User '" << uName << "' registered successfully!" << endl;
}

/**
 * Function: loginUser
 * Description: Validates credentials and overrides the system's global currentUser.
 */
void loginUser() {
    string uName, pass;

    cout << "Enter UserName: ";
    cin >> ws;
    getline(cin, uName);

    cout << "Enter Password: ";
    cin >> ws;
    getline(cin, pass);

    User* u = findUser(uName);
    if (u != nullptr && u->password == pass) {
        currentUser = u;
        cout << "Logged in successfully to Instagram as " << uName << "!" << endl;
    }
    else {
        cout << "Invalid credentials provided." << endl;
    }
}

/**
 * Function: searchUser
 * Description: Executes an O(1) expected time operation via Username on the Hash Map.
 */
void searchUser() {
    string target;

    cout << "Enter username to search: ";
    cin >> ws;
    getline(cin, target);

    User* u = findUser(target);
    if (u != nullptr) {
        cout << "\n--- Instagram Profile ---" << endl;
        cout << "Username: " << u->userName << endl;
        cout << "Bio: " << u->bio << endl;
        cout << "Email: " << u->email << endl;
        cout << "Last Active: " << u->lastActive << endl;
    }
    else {
        cout << "User not found!" << endl;
    }
}

/**
 * Function: displayUsers
 * Description: Prints a brief catalogue of currently active users across the hash chains.
 */
void displayUsers() {
    cout << "\n--- Global Instagram Users ---" << endl;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        User* curr = userDirectory[i];
        while (curr != nullptr) {
            cout << "@" << curr->userName << " - " << curr->bio << endl;
            curr = curr->next;
        }
    }
}

/**
 * Function: deleteUser
 * Description: Systematically purges the current user's entity, inclusive of linked Post trees, networking properties, and associated hash placement.
 */
void deleteUser() {
    if (requireAuth() == false) {
        return;
    }

    string uName = currentUser->userName;

    Edge* f = currentUser->friendsHead;
    while (f != nullptr) {
        User* friendUser = findUser(f->friendUserName);
        if (friendUser != nullptr) {
            Edge* currEdge = friendUser->friendsHead;
            Edge* prevEdge = nullptr;

            while (currEdge != nullptr) {
                if (currEdge->friendUserName == uName) {
                    if (prevEdge != nullptr) {
                        prevEdge->next = currEdge->next;
                    }
                    else {
                        friendUser->friendsHead = currEdge->next;
                    }
                    delete currEdge;
                    break;
                }
                prevEdge = currEdge;
                currEdge = currEdge->next;
            }
        }
        f = f->next;
    }

    Post* p = currentUser->postsHead;
    while (p != nullptr) {
        postLikesTree = deleteAVL(postLikesTree, p->postID, p->likes);
        Post* temp = p;
        p = p->next;
        delete temp;
    }

    int act = findValueByKey(userActivityTree, uName);
    userActivityTree = deleteAVL(userActivityTree, uName, act);

    int idx = getHash(uName);
    User* curr = userDirectory[idx];
    User* prev = nullptr;

    while (curr != nullptr) {
        if (curr->userName == uName) {
            if (prev != nullptr) {
                prev->next = curr->next;
            }
            else {
                userDirectory[idx] = curr->next;
            }

            Conversation* cnv = curr->convHead;
            while (cnv != nullptr) {
                Message* msg = cnv->messageStack;
                while (msg != nullptr) {
                    Message* tmpM = msg;
                    msg = msg->next;
                    delete tmpM;
                }
                Conversation* tmpC = cnv;
                cnv = cnv->next;
                delete tmpC;
            }

            delete curr;
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    currentUser = nullptr;
    saveData();
    cout << "Instagram Account purged entirely. Goodbye." << endl;
}
