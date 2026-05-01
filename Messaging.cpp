#include "Instagram.h"

/**
 * Function: getConversation
 * Description: Derives explicit shared Stack node roots connecting distinct individual conversation hubs dynamically linking dependencies.
 */
Conversation* getConversation(User* user, string withUser) {
    if (user == nullptr) {
        return nullptr;
    }

    Conversation* curr = user->convHead;
    while (curr != nullptr) {
        if (curr->withUser == withUser) {
            return curr;
        }
        curr = curr->next;
    }

    Conversation* nc = new Conversation{ withUser, nullptr, user->convHead };
    user->convHead = nc;
    return nc;
}

/**
 * Function: sendMessage
 * Description: Emits distinct mirrored packets cascading toward mutual communication targets simultaneously generating logical notifications.
 */
void sendMessage() {
    if (requireAuth() == false) {
        return;
    }

    string target;
    string text;

    cout << "Recipient Instagram Username (DM target): ";
    cin >> ws;
    getline(cin, target);

    User* toUser = findUser(target);
    if (toUser == nullptr) {
        cout << "Invalid target!" << endl;
        return;
    }

    cout << "Direct Message body: ";
    cin >> ws;
    getline(cin, text);

    Message* msgA = new Message{ currentUser->userName, target, text, "Now", nullptr };
    Conversation* convA = getConversation(currentUser, target);
    msgA->next = convA->messageStack;
    convA->messageStack = msgA;

    Message* msgB = new Message{ currentUser->userName, target, text, "Now", nullptr };
    Conversation* convB = getConversation(toUser, currentUser->userName);
    msgB->next = convB->messageStack;
    convB->messageStack = msgB;

    enqueueNotification("New Instagram DM from @" + currentUser->userName, target);
    saveData();
    cout << "DM successfully sent!" << endl;
}

/**
 * Function: viewLatestMessage
 * Description: Peaks abstract layer indices evaluating current underlying Stack logic states exposing single newest frame.
 */
void viewLatestMessage() {
    if (requireAuth() == false) {
        return;
    }

    string target;
    cout << "Specify conversation bound (Friend Username): ";
    cin >> ws;
    getline(cin, target);

    Conversation* c = getConversation(currentUser, target);

    if (c->messageStack != nullptr) {
        cout << "[LATEST DM] From: " << c->messageStack->fromUser << " => " << c->messageStack->text << endl;
    }
    else {
        cout << "Blank state: No prior message traces identified locating target inbox." << endl;
    }
}

/**
 * Function: popMessage
 * Description: Unspools and unlinks sequentially topmost stored frame LIFO destroying pointer integrity forcefully recovering logical memory paths physically tracking.
 */
void popMessage() {
    if (requireAuth() == false) {
        return;
    }

    string target;
    cout << "Username context to unsent message upon (Remove latest): ";
    cin >> ws;
    getline(cin, target);

    Conversation* c = getConversation(currentUser, target);

    if (c->messageStack != nullptr) {
        Message* t = c->messageStack;
        c->messageStack = c->messageStack->next;
        saveData();
        cout << "Discarding Message -> '" << t->text << "'" << endl;
        delete t;
    }
    else {
        cout << "System stack lacks requisite elements attempting popped sequences." << endl;
    }
}

/**
 * Function: viewConversation
 * Description: Analyzes hierarchical tree depth unrolling cascading links manifesting sequentially reversed structural visual representations of history buffers directly iterating linear pointer sequences backward referencing temporal order intrinsically derived.
 */
void viewConversation() {
    if (requireAuth() == false) {
        return;
    }

    string target;
    cout << "Load chronological DM history referencing user: ";
    cin >> ws;
    getline(cin, target);

    Conversation* c = getConversation(currentUser, target);
    Message* m = c->messageStack;

    if (m == nullptr) {
        cout << "Barren inbox session." << endl;
        return;
    }

    cout << "\n=== DIRECT MESSAGE HISTORY (LATEST FIRST) ===" << endl;
    while (m != nullptr) {
        cout << "[" << m->timestamp << "] " << m->fromUser << " : " << m->text << endl;
        m = m->next;
    }
}
