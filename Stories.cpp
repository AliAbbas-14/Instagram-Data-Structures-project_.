#include "Instagram.h"
#include <cstdlib>

/**
 * Function: addStory
 * Description: Establishes recursive tail->head pointer associations mirroring cyclical continuity.
 */
void addStory() {
    if (requireAuth() == false) {
        return;
    }

    string content;
    cout << "Record your 24h Story update: ";
    cin >> ws;
    getline(cin, content);

    Story* s = new Story{ currentUser->userName, content, nullptr };

    if (storyHead == nullptr) {
        storyHead = s;
        storyTail = s;
        s->next = s; // loops back identically to itself mapping a complete cycle.
    }
    else {
        storyTail->next = s;
        storyTail = s;
        storyTail->next = storyHead; // bridges newly aligned tail node securely traversing unto head
    }
    saveData();
    cout << "Instagram Story update active globally." << endl;
}

/**
 * Function: viewStories
 * Description: Executes unconstrained infinite traversal across the closed cyclic pathway nodes sequentially jumping links.
 */
void viewStories() {
    if (requireAuth() == false) {
        return;
    }

    if (storyHead == nullptr) {
        cout << "No stories exist currently in the network." << endl;
        return;
    }

    Story* curr = storyHead;
    while (true) {
        system("CLS");

        cout << "\n[INSTAGRAM HIGHLIGHT/STORY]" << endl;
        cout << "From: @" << curr->userName << endl;
        cout << "Update: " << curr->storyContent << endl;

        cout << "--------------------" << endl;
        cout << "1. NEXT STORY FRAME" << endl;
        cout << "2. LEAVE HIGHLIGHTS" << endl;
        cout << "Option: ";

        int action;
        cin >> action;

        switch (action) {
        case 1:
            curr = curr->next;
            if (curr == storyHead) {
                cout << ">> Alert: Resetting bounds... back to first user's story node." << endl;
                system("PAUSE");
            }
            break;
        case 2:
            return;
        default:
            cout << "Invalid Option!" << endl;
            system("PAUSE");
            break;
        }
    }
}
