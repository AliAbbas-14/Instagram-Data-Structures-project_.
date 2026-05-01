#include "Instagram.h"
#include <windows.h>
#include <cstdlib>

// ==========================================
// STARTUP ANIMATION
// ==========================================

void startupAnimation() {
    string colors[] = { "0A", "0B", "0C", "0D", "0E", "0F", "09", "03" };
    int numColors = 8;

    // 10 iterations * 500ms = 5 Seconds exactly
    for (int i = 0; i < 10; i++) {
        system("CLS");

        string colorCmd = "COLOR " + colors[i % numColors];
        system(colorCmd.c_str());

        // Push further down the screen (vertical centering)
        cout << "\n\n\n\n\n\n\n\n\n";

        // Push further right (horizontal centering)
        cout << "\t\t   _____  _   _  _____  _______    _     _____  _____            __  __ " << endl;
        cout << "\t\t  |_   _|| \\ | |/ ____||__   __|  / \\   / ____||  __ \\    /\\    |  \\/  |" << endl;
        cout << "\t\t    | |  |  \\| | (___     | |    /  \\  | |  __ | |__) |  /  \\   | \\  / |" << endl;
        cout << "\t\t    | |  | . ` |\\___ \\    | |   / /\\ \\ | | |_ ||  _  /  / /\\ \\  | |\\/| |" << endl;
        cout << "\t\t   _| |_ | |\\  |____) |   | |  / ____ \\| |__| || | \\ \\ / ____ \\ | |  | |" << endl;
        cout << "\t\t  |_____||_| \\_|_____/    |_| /_/    \\_\\\\_____||_|  \\_/_/    \\_\\|_|  |_|" << endl;
        cout << "\n\t\t\t========================================================" << endl;

        Sleep(500);
    }

    system("COLOR 0F");
    system("CLS");
}

// ==========================================
// SUBMENUS WRAPPER INVOCATIONS
// ==========================================

void subUserTree() {
    while (true) {
        system("COLOR 0B"); // Light Aqua
        system("CLS");

        cout << "\n--- Account/User Management ---" << endl;
        cout << "1. Register User" << endl;
        cout << "2. Login" << endl;
        cout << "3. Delete Account" << endl;
        cout << "4. Search Profile" << endl;
        cout << "5. Display All Database Users" << endl;
        cout << "6. Back" << endl;
        cout << "Choice: ";

        int ch;
        cin >> ch;

        switch (ch) {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        case 3:
            deleteUser();
            break;
        case 4:
            searchUser();
            break;
        case 5:
            displayUsers();
            break;
        case 6:
            return;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }

        cout << endl;
        system("PAUSE");
    }
}

void subGraphTree() {
    while (true) {
        system("COLOR 0E"); // Light Yellow
        system("CLS");

        cout << "\n--- Followings & Network ---" << endl;
        cout << "1. Follow User (Add Friend)" << endl;
        cout << "2. Unfollow User (Remove)" << endl;
        cout << "3. View Followings" << endl;
        cout << "4. Network BFS Traversal" << endl;
        cout << "5. Network DFS Traversal" << endl;
        cout << "6. Back" << endl;
        cout << "Choice: ";

        int ch;
        cin >> ch;

        switch (ch) {
        case 1:
            addFriend();
            break;
        case 2:
            removeFriend();
            break;
        case 3:
            viewFriends();
            break;
        case 4:
            BFS();
            break;
        case 5:
            DFS();
            break;
        case 6:
            return;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }

        cout << endl;
        system("PAUSE");
    }
}

void subListTree() {
    while (true) {
        system("COLOR 0D"); // Light Purple
        system("CLS");

        cout << "\n--- Instagram Posts ---" << endl;
        cout << "1. Create Post" << endl;
        cout << "2. Delete Post" << endl;
        cout << "3. View My Profile Grid" << endl;
        cout << "4. View Home Feed (Scroll)" << endl;
        cout << "5. Like Post" << endl;
        cout << "6. Back" << endl;
        cout << "Choice: ";

        int ch;
        cin >> ch;

        switch (ch) {
        case 1:
            createPost();
            break;
        case 2:
            deletePost();
            break;
        case 3:
            viewMyPosts();
            break;
        case 4:
            viewFeed();
            break;
        case 5:
            likePost();
            break;
        case 6:
            return;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }

        cout << endl;
        system("PAUSE");
    }
}

void subStoryTree() {
    while (true) {
        system("COLOR 0A"); // Light Green
        system("CLS");

        cout << "\n--- Instagram Stories ---" << endl;
        cout << "1. Add Story" << endl;
        cout << "2. Watch Stories" << endl;
        cout << "3. Back" << endl;
        cout << "Choice: ";

        int ch;
        cin >> ch;

        switch (ch) {
        case 1:
            addStory();
            break;
        case 2:
            viewStories();
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }

        cout << endl;
        system("PAUSE");
    }
}

void subQueueTree() {
    while (true) {
        system("COLOR 0C"); // Light Red
        system("CLS");

        cout << "\n--- Live Notifications ---" << endl;
        cout << "1. View Alert Log" << endl;
        cout << "2. Process Next Alert" << endl;
        cout << "3. Back" << endl;
        cout << "Choice: ";

        int ch;
        cin >> ch;

        switch (ch) {
        case 1:
            viewNotifications();
            break;
        case 2:
            processNotification();
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }

        cout << endl;
        system("PAUSE");
    }
}

void subRankingTree() {
    while (true) {
        system("COLOR 09"); // Light Blue
        system("CLS");

        cout << "\n--- Explore & Analytics ---" << endl;
        cout << "1. Show Trending/Active Users" << endl;
        cout << "2. Show Top Liked Posts" << endl;
        cout << "3. Display Range Constraints" << endl;
        cout << "4. Back" << endl;
        cout << "Choice: ";

        int ch;
        cin >> ch;

        switch (ch) {
        case 1: {
            cout << "Fetch Top K Amount: ";
            int k;
            while (!(cin >> k)) { cin.clear(); cin.ignore(10000, '\n'); cout << "Enter a number: "; }
            reverseInorderTopK(userActivityTree, k);
            break;
        }
        case 2: {
            cout << "Fetch Top K Amount: ";
            int k;
            while (!(cin >> k)) { cin.clear(); cin.ignore(10000, '\n'); cout << "Enter a number: "; }
            reverseInorderTopK(postLikesTree, k);
            break;
        }
        case 3: {
            cout << "1. Filter Influencers" << endl;
            cout << "2. Filter Viral Posts" << endl;
            cout << "Type: ";
            int ty;
            while (!(cin >> ty)) { cin.clear(); cin.ignore(10000, '\n'); cout << "Enter a number: "; }

            cout << "Minimum Range limit: ";
            int mi;
            while (!(cin >> mi)) { cin.clear(); cin.ignore(10000, '\n'); cout << "Enter a number: "; }

            cout << "Maximum Range limit: ";
            int ma;
            while (!(cin >> ma)) { cin.clear(); cin.ignore(10000, '\n'); cout << "Enter a number: "; }

            if (ty == 1) {
                rangeQuery(userActivityTree, mi, ma);
            }
            else {
                rangeQuery(postLikesTree, mi, ma);
            }
            break;
        }
        case 4:
            return;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }

        cout << endl;
        system("PAUSE");
    }
}

void subStackTree() {
    while (true) {
        system("COLOR 03"); // Aqua
        system("CLS");

        cout << "\n--- Direct Messaging (DMs) ---" << endl;
        cout << "1. Send DM" << endl;
        cout << "2. Peak Last DM" << endl;
        cout << "3. Unsend Latest Message (Pop)" << endl;
        cout << "4. Open Chat History" << endl;
        cout << "5. Back" << endl;
        cout << "Choice: ";

        int ch;
        cin >> ch;

        switch (ch) {
        case 1:
            sendMessage();
            break;
        case 2:
            viewLatestMessage();
            break;
        case 3:
            popMessage();
            break;
        case 4:
            viewConversation();
            break;
        case 5:
            return;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }

        cout << endl;
        system("PAUSE");
    }
}

// ==========================================
// CORE SYSTEM INIT (MAIN)
// ==========================================

int main() {
    startupAnimation();
    loadData(); // Load persistence files

    while (true) {
        system("COLOR 0F"); // Bright White
        system("CLS");

        cout << "\n================ INSTAGRAM =================" << endl;

        if (currentUser != nullptr) {
            cout << "Logged in as: @" << currentUser->userName << endl;
        }
        else {
            cout << "Guest View - Please login." << endl;
        }

        cout << "1. User Management (Hash)" << endl;
        cout << "2. Network & Followings (Graph)" << endl;
        cout << "3. Profile & Feed (Linked Lists)" << endl;
        cout << "4. 24h Stories (Circular List)" << endl;
        cout << "5. Live Notifications (Queue)" << endl;
        cout << "6. Explore & Analytics (AVL Tree)" << endl;
        cout << "7. Direct Messaging (Stack)" << endl;
        cout << "8. Close Application" << endl;
        cout << "============================================" << endl;
        cout << "Choice: ";

        int mainChoice;
        if (!(cin >> mainChoice)) {
            break;
        }

        switch (mainChoice) {
        case 1:
            subUserTree();
            break;
        case 2:
            subGraphTree();
            break;
        case 3:
            subListTree();
            break;
        case 4:
            subStoryTree();
            break;
        case 5:
            subQueueTree();
            break;
        case 6:
            subRankingTree();
            break;
        case 7:
            subStackTree();
            break;
        case 8:
            cout << "Saving Data to disk..." << endl;
            saveData();
            cout << "Closing Instagram securely..." << endl;
            return 0;
        default:
            cout << "Invalid input mapping path selection discarded iteratively." << endl;
            system("PAUSE");
            break;
        }
    }
    return 0;
}
