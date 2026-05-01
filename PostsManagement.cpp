#include "Instagram.h"
#include <cstdlib>

// Simple Custom Doubly Linked Node for the Feed Interface
struct FeedNode {
    Post* postPtr;
    FeedNode* next;
    FeedNode* prev;
};

void appendFeed(FeedNode*& head, FeedNode*& tail, Post* p) {
    FeedNode* fn = new FeedNode{ p, nullptr, nullptr };
    if (head == nullptr) {
        head = fn;
        tail = fn;
    }
    else {
        tail->next = fn;
        fn->prev = tail;
        tail = fn;
    }
}

/**
 * Function: createPost
 * Description: Synthesizes a new Doubly Linked List Node to assign as Post, tracks analytics.
 */
void createPost() {
    if (requireAuth() == false) {
        return;
    }

    string content;
    cout << "Enter Instagram Post Caption/Content: ";
    cin >> ws;
    getline(cin, content);

    string id = "P" + to_string(++postCounter);
    Post* p = new Post{ id, content, currentUser->userName, 0, nullptr, nullptr };

    if (currentUser->postsHead != nullptr) {
        currentUser->postsHead->prev = p;
        p->next = currentUser->postsHead;
    }
    currentUser->postsHead = p;

    int oldAct = findValueByKey(userActivityTree, currentUser->userName);
    userActivityTree = deleteAVL(userActivityTree, currentUser->userName, oldAct);
    userActivityTree = insertAVL(userActivityTree, currentUser->userName, oldAct + 1);

    postLikesTree = insertAVL(postLikesTree, id, 0);

    Edge* e = currentUser->friendsHead;
    while (e != nullptr) {
        enqueueNotification("New Instagram post (" + id + ") from " + currentUser->userName, e->friendUserName);
        e = e->next;
    }

    saveData();
    cout << "Post " << id << " published successfully!" << endl;
}

/**
 * Function: deletePost
 * Description: Bypasses doubly linked list sequences to sever a node correctly and releases its AVL state.
 */
void deletePost() {
    if (requireAuth() == false) {
        return;
    }

    string pID;
    cout << "Enter Post ID to delete: ";
    cin >> ws;
    getline(cin, pID);

    Post* curr = currentUser->postsHead;
    while (curr != nullptr) {
        if (curr->postID == pID) {
            if (curr->prev != nullptr) {
                curr->prev->next = curr->next;
            }
            else {
                currentUser->postsHead = curr->next;
            }

            if (curr->next != nullptr) {
                curr->next->prev = curr->prev;
            }

            postLikesTree = deleteAVL(postLikesTree, pID, curr->likes);
            delete curr;

            saveData();
            cout << "Post permanently deleted." << endl;
            return;
        }
        curr = curr->next;
    }
    cout << "You can only delete your own posts. Not found." << endl;
}

/**
 * Function: viewMyPosts
 * Description: Isolates user specific singly/doubly tracked data outputs.
 */
void viewMyPosts() {
    if (requireAuth() == false) {
        return;
    }

    Post* p = currentUser->postsHead;
    if (p == nullptr) {
        cout << "No posts created yet on your profile." << endl;
        return;
    }

    while (p != nullptr) {
        cout << "\n[Post ID: " << p->postID << "]" << endl;
        cout << "Likes: " << p->likes << endl;
        cout << "Caption: " << p->content << endl;
        p = p->next;
    }
}

/**
 * Function: viewFeed
 * Description: Congeals relative external Posts into an intuitive navigation panel rendering doubly properties.
 */
void viewFeed() {
    if (requireAuth() == false) {
        return;
    }

    FeedNode* head = nullptr;
    FeedNode* tail = nullptr;

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        User* u = userDirectory[i];
        while (u != nullptr) {
            bool isFriend = false;

            if (u->userName != currentUser->userName) {
                Edge* e = currentUser->friendsHead;
                while (e != nullptr) {
                    if (e->friendUserName == u->userName) {
                        isFriend = true;
                        break;
                    }
                    e = e->next;
                }
            }

            if (u->userName == currentUser->userName || isFriend == true) {
                Post* p = u->postsHead;
                while (p != nullptr) {
                    appendFeed(head, tail, p);
                    p = p->next;
                }
            }
            u = u->next;
        }
    }

    if (head == nullptr) {
        cout << "Your Instagram Feed is completely empty. Follow some users!" << endl;
        return;
    }

    FeedNode* currentUI = head;
    while (true) {
        system("CLS");

        cout << "\n========== INSTAGRAM FEED ==========" << endl;
        cout << "Author: @" << currentUI->postPtr->owner << " | ID: " << currentUI->postPtr->postID << endl;
        cout << "Likes (" << currentUI->postPtr->likes << ")" << endl;
        cout << "--- " << currentUI->postPtr->content << " ---" << endl;
        cout << "====================================" << endl;
        cout << "1. SCROLL NEXT" << endl;
        cout << "2. SCROLL PREV" << endl;
        cout << "3. EXIT APP VIEW" << endl;
        cout << "Choice: ";

        int nav;
        cin >> nav;

        switch (nav) {
        case 1:
            if (currentUI->next != nullptr) {
                currentUI = currentUI->next;
            }
            else {
                cout << "-> Notice: Reached End of Infinite Scroll." << endl;
                system("PAUSE");
            }
            break;
        case 2:
            if (currentUI->prev != nullptr) {
                currentUI = currentUI->prev;
            }
            else {
                cout << "-> Notice: Reached Top of the Feed." << endl;
                system("PAUSE");
            }
            break;
        case 3:
            while (head != nullptr) {
                FeedNode* t = head;
                head = head->next;
                delete t;
            }
            return;
        default:
            cout << "Invalid choice." << endl;
            system("PAUSE");
            break;
        }
    }
}

/**
 * Function: likePost
 * Description: Pinpoints a generic user's post to increment internal score metrics propagating onto ranking arrays.
 */
void likePost() {
    if (requireAuth() == false) {
        return;
    }

    string pID;
    cout << "Enter Post ID to drop a like: ";
    cin >> ws;
    getline(cin, pID);

    Post* target = getPostByID(pID);
    if (target != nullptr) {
        int oldLikes = target->likes;
        target->likes = target->likes + 1;

        postLikesTree = deleteAVL(postLikesTree, pID, oldLikes);
        postLikesTree = insertAVL(postLikesTree, pID, target->likes);

        if (target->owner != currentUser->userName) {
            enqueueNotification(currentUser->userName + " liked your post: " + pID, target->owner);
        }
        saveData();
        cout << "Successfully liked post " << pID << "!" << endl;
    }
    else {
        cout << "Invalid Post ID." << endl;
    }
}
