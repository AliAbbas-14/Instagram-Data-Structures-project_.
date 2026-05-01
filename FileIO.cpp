#include "Instagram.h"
#include <fstream>

// Helper to manually tokenize strings split by a delimiter without using standard vectors
string parseToken(string& line, int& pos, char delimiter) {
    string token = "";
    while (pos < line.length() && line[pos] != delimiter) {
        token += line[pos];
        pos++;
    }
    pos++; // skip delimiter
    return token;
}

void saveData() {
    ofstream fUsers("users.txt");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        User* curr = userDirectory[i];
        while (curr != nullptr) {
            fUsers << curr->userName << "|" << curr->password << "|" << curr->email << "|" << curr->bio << "|" << curr->lastActive << endl;
            curr = curr->next;
        }
    }
    fUsers.close();

    ofstream fPosts("posts.txt");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        User* u = userDirectory[i];
        while (u != nullptr) {
            Post* p = u->postsHead;
            while (p != nullptr) {
                fPosts << p->postID << "|" << p->content << "|" << p->owner << "|" << p->likes << endl;
                p = p->next;
            }
            u = u->next;
        }
    }
    fPosts.close();

    ofstream fFriends("friends.txt");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        User* u = userDirectory[i];
        while (u != nullptr) {
            Edge* e = u->friendsHead;
            while (e != nullptr) {
                fFriends << u->userName << "|" << e->friendUserName << endl;
                e = e->next;
            }
            u = u->next;
        }
    }
    fFriends.close();

    ofstream fMsgs("messages.txt");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        User* u = userDirectory[i];
        while (u != nullptr) {
            Conversation* c = u->convHead;
            while (c != nullptr) {
                Message* m = c->messageStack;
                while (m != nullptr) {
                    fMsgs << m->fromUser << "|" << m->toUser << "|" << m->text << "|" << m->timestamp << endl;
                    m = m->next;
                }
                c = c->next;
            }
            u = u->next;
        }
    }
    fMsgs.close();

    ofstream fStories("stories.txt");
    if (storyHead != nullptr) {
        Story* s = storyHead;
        while (true) {
            fStories << s->userName << "|" << s->storyContent << endl;
            s = s->next;
            if (s == storyHead) break;
        }
    }
    fStories.close();

    ofstream fNotifs("notifications.txt");
    Notification* n = notifFront;
    while (n != nullptr) {
        fNotifs << n->message << "|" << n->userName << "|" << n->timestamp << endl;
        n = n->next;
    }
    fNotifs.close();
}

void loadData() {
    string line;

    ifstream fUsers("users.txt");
    if (fUsers.is_open()) {
        while (getline(fUsers, line)) {
            int pos = 0;
            string uName = parseToken(line, pos, '|');
            string pass = parseToken(line, pos, '|');
            string em = parseToken(line, pos, '|');
            string b = parseToken(line, pos, '|');
            string la = parseToken(line, pos, '|');

            if (uName == "") continue;

            User* nu = new User{ uName, pass, em, b, la, nullptr, nullptr, nullptr, nullptr };
            int idx = getHash(uName);
            nu->next = userDirectory[idx];
            userDirectory[idx] = nu;

            userActivityTree = insertAVL(userActivityTree, uName, 0);
        }
        fUsers.close();
    }

    ifstream fPosts("posts.txt");
    if (fPosts.is_open()) {
        while (getline(fPosts, line)) {
            int pos = 0;
            string id = parseToken(line, pos, '|');
            string content = parseToken(line, pos, '|');
            string owner = parseToken(line, pos, '|');
            string slikes = parseToken(line, pos, '|');

            if (id == "") continue;

            int likes = 0;
            if (slikes != "") likes = stoi(slikes);

            User* u = findUser(owner);
            if (u != nullptr) {
                Post* p = new Post{ id, content, owner, likes, nullptr, nullptr };
                if (u->postsHead != nullptr) {
                    u->postsHead->prev = p;
                    p->next = u->postsHead;
                }
                u->postsHead = p;

                int oldAct = findValueByKey(userActivityTree, owner);
                userActivityTree = deleteAVL(userActivityTree, owner, oldAct);
                userActivityTree = insertAVL(userActivityTree, owner, oldAct + 1);

                postLikesTree = insertAVL(postLikesTree, id, likes);
            }

            if (id.length() > 1) {
                int idNum = stoi(id.substr(1));
                if (idNum > postCounter) {
                    postCounter = idNum;
                }
            }
        }
        fPosts.close();
    }

    ifstream fFriends("friends.txt");
    if (fFriends.is_open()) {
        while (getline(fFriends, line)) {
            int pos = 0;
            string uName = parseToken(line, pos, '|');
            string fName = parseToken(line, pos, '|');

            if (uName == "") continue;

            User* u1 = findUser(uName);
            if (u1 != nullptr) {
                bool exists = false;
                Edge* curr = u1->friendsHead;
                while (curr != nullptr) {
                    if (curr->friendUserName == fName) { exists = true; break; }
                    curr = curr->next;
                }
                if (exists == false) {
                    Edge* e = new Edge{ fName, u1->friendsHead };
                    u1->friendsHead = e;
                }
            }
        }
        fFriends.close();
    }

    ifstream fMsgs("messages.txt");
    if (fMsgs.is_open()) {
        while (getline(fMsgs, line)) {
            int pos = 0;
            string fromU = parseToken(line, pos, '|');
            string toU = parseToken(line, pos, '|');
            string txt = parseToken(line, pos, '|');
            string ts = parseToken(line, pos, '|');

            if (fromU == "") continue;

            User* sender = findUser(fromU);
            if (sender != nullptr) {
                Conversation* c = getConversation(sender, toU);
                Message* m = new Message{ fromU, toU, txt, ts, c->messageStack };
                c->messageStack = m;
            }
        }
        fMsgs.close();
    }

    ifstream fStories("stories.txt");
    if (fStories.is_open()) {
        while (getline(fStories, line)) {
            int pos = 0;
            string uName = parseToken(line, pos, '|');
            string content = parseToken(line, pos, '|');

            if (uName == "") continue;

            Story* s = new Story{ uName, content, nullptr };
            if (storyHead == nullptr) {
                storyHead = s;
                storyTail = s;
                s->next = s;
            }
            else {
                storyTail->next = s;
                storyTail = s;
                storyTail->next = storyHead;
            }
        }
        fStories.close();
    }

    ifstream fNotifs("notifications.txt");
    if (fNotifs.is_open()) {
        while (getline(fNotifs, line)) {
            int pos = 0;
            string msg = parseToken(line, pos, '|');
            string uName = parseToken(line, pos, '|');
            string ts = parseToken(line, pos, '|');

            if (msg == "") continue;

            Notification* n = new Notification{ msg, uName, ts, nullptr };
            if (notifRear == nullptr) {
                notifFront = n;
                notifRear = n;
            }
            else {
                notifRear->next = n;
                notifRear = n;
            }
        }
        fNotifs.close();
    }
}
