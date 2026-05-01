#include "Instagram.h"

/**
 * Function: enqueueNotification
 * Description: Adds a new notification to the rear of the notification Queue.
 */
void enqueueNotification(string msg, string user) {
    Notification* n = new Notification{ msg, user, "Now", nullptr };

    if (notifRear == nullptr) {
        notifFront = n;
        notifRear = n;
    }
    else {
        notifRear->next = n;
        notifRear = n;
    }
    saveData();
}

/**
 * Function: viewNotifications
 * Description: Non-destructively presents the notifications for the current user.
 */
void viewNotifications() {
    if (requireAuth() == false) {
        return;
    }

    Notification* t = notifFront;
    bool found = false;

    cout << "\n--- Your Instagram Notifications ---" << endl;

    while (t != nullptr) {
        if (t->userName == currentUser->userName || t->userName == "All") {
            cout << "[Time: " << t->timestamp << "] " << t->message << endl;
            found = true;
        }
        t = t->next;
    }

    if (found == false) {
        cout << "No notifications at this time." << endl;
    }
}

/**
 * Function: processNotification
 * Description: Dequeues the first existing notification from the front of the queue entirely.
 */
void processNotification() {
    if (requireAuth() == false) {
        return;
    }

    if (notifFront == nullptr) {
        cout << "Notification queue is completely empty." << endl;
        return;
    }

    Notification* t = notifFront;
    notifFront = notifFront->next;

    if (notifFront == nullptr) {
        notifRear = nullptr; // Reset rear ptr if queue becomes empty
    }
    saveData();

    cout << "Processed & Deleted App Notification for " << t->userName << ": " << t->message << endl;
    delete t;
}
