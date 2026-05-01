#include "Instagram.h"

// Define array storage privately, export through pointer dynamically to maintain memory map smoothly
User* rawUserDirectory[101] = { nullptr };
const int HASH_TABLE_SIZE = 101;
User** userDirectory = rawUserDirectory;

User* currentUser = nullptr;

Story* storyHead = nullptr;
Story* storyTail = nullptr;

Notification* notifFront = nullptr;
Notification* notifRear = nullptr;

AVLNode* userActivityTree = nullptr;
AVLNode* postLikesTree = nullptr;

int postCounter = 0;

/**
 * Function: requireAuth
 * Description: Checks whether a user is currently logged into the system.
 */
bool requireAuth() {
    if (currentUser == nullptr) {
        cout << "Error: No user is currently logged in! Please login first." << endl;
        return false;
    }
    return true;
}

/**
 * Function: getHash
 * Description: Hashes a string key to find its index in the Hash Table.
 */
int getHash(string key) {
    long long hashVal = 0;
    for (char c : key) {
        hashVal = (hashVal * 31 + c) % HASH_TABLE_SIZE;
    }
    return hashVal;
}

/**
 * Function: findUser
 * Description: Searches for a user in the hash table by username.
 */
User* findUser(string userName) {
    int idx = getHash(userName);
    User* curr = userDirectory[idx];
    while (curr) {
        if (curr->userName == userName) return curr;
        curr = curr->next;
    }
    return nullptr;
}

/**
 * Function: getPostByID
 * Description: Searches globally across all users to find a specific post by its ID.
 */
Post* getPostByID(string postID) {
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        User* cur = userDirectory[i];
        while (cur) {
            Post* p = cur->postsHead;
            while (p) {
                if (p->postID == postID) return p;
                p = p->next;
            }
            cur = cur->next;
        }
    }
    return nullptr;
}
