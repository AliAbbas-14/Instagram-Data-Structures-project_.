#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <fstream>

using namespace std;

// ==========================================
// FORWARD DECLARATIONS & STRUCTURES
// ==========================================

struct Post {
    string postID;
    string content;
    string owner;
    int likes;
    Post* next;
    Post* prev; // Doubly linked list requirement
};

struct Edge {
    string friendUserName;
    Edge* next; // Graph Adjacency representation
};

struct Message {
    string fromUser;
    string toUser;
    string text;
    string timestamp;
    Message* next; // Stack implementation
};

struct Conversation {
    string withUser;
    Message* messageStack; // LIFO order
    Conversation* next;
};

struct User {
    string userName;
    string password;
    string email;
    string bio;
    string lastActive;

    Post* postsHead;
    Edge* friendsHead;
    Conversation* convHead;

    User* next; // For Hash Table Chaining
};

struct Story {
    string userName;
    string storyContent;
    Story* next; // Circular list requirement
};

struct Notification {
    string message;
    string userName;
    string timestamp;
    Notification* next; // FIFO Queue requirement
};

struct AVLNode {
    string key;
    int value;
    AVLNode* left;
    AVLNode* right;
    int height;
};

struct StringNode {
    string val;
    StringNode* next;
};

// ==========================================
// GLOBALS DECLARATIONS
// ==========================================
extern const int HASH_TABLE_SIZE;
extern User** userDirectory;
extern User* currentUser;

extern Story* storyHead;
extern Story* storyTail;

extern Notification* notifFront;
extern Notification* notifRear;

extern AVLNode* userActivityTree;
extern AVLNode* postLikesTree;

extern int postCounter;

// ==========================================
// FUNCTION PROTOTYPES
// ==========================================

// Globals
bool requireAuth();
int getHash(string key);
User* findUser(string userName);
Post* getPostByID(string postID);

// Module A
void registerUser();
void loginUser();
void searchUser();
void displayUsers();
void deleteUser();

// Module B
void addFriend();
void removeFriend();
void viewFriends();
bool isVisited(StringNode* head, string val);
void addVisited(StringNode*& head, string val);
void BFS();
void dfsHelper(string curr, StringNode*& visited, string target, bool& found);
void DFS();

// Module C
void createPost();
void deletePost();
void viewMyPosts();
void viewFeed();
void likePost();

// Module D
void addStory();
void viewStories();

// Module E
void enqueueNotification(string msg, string user);
void viewNotifications();
void processNotification();

// Module F
int maxVal(int a, int b);
int height(AVLNode* N);
AVLNode* rightRotate(AVLNode* y);
AVLNode* leftRotate(AVLNode* x);
int getBalance(AVLNode* N);
bool isLess(int v1, string k1, int v2, string k2);
bool isGreater(int v1, string k1, int v2, string k2);
AVLNode* insertAVL(AVLNode* node, string key, int value);
AVLNode* minValueNode(AVLNode* node);
AVLNode* deleteAVL(AVLNode* root, string key, int value);
int findValueByKey(AVLNode* root, string key);
void reverseInorderTopK(AVLNode* root, int& K);
void rangeQuery(AVLNode* root, int min, int max);

// Module G
Conversation* getConversation(User* user, string withUser);
void sendMessage();
void viewLatestMessage();
void popMessage();
void viewConversation();

// File IO
void saveData();
void loadData();
