#include <iostream>
#include <string>
#include <limits>
using namespace std;

// ---------- Node of the doubly linked list ----------
struct Node {
    string songTitle;
    string artist;
    Node* prev;
    Node* next;
};

// ---------- Global pointers ----------
Node* head = nullptr;     // first song
Node* current = nullptr;  // currently selected/playing song
Node* p = nullptr;        // used for creating / deleting a node
Node* q = nullptr;        // used for traversal

// ---------- Function declarations ----------
void addSong();
void deleteSong();
void displayPlaylist();
void displayReverse();
void playCurrentSong();
void playNextSong();
void playPreviousSong();
void playCompletePlaylist();
void repeatAll();
void showCurrentSong();
void freePlaylist();

// ---------- Add song at the END ----------
void addSong() {
    string title, artist;
    cout << "Enter song title: ";
    getline(cin, title);
    cout << "Enter artist name: ";
    getline(cin, artist);

    if (title.empty()) {
        cout << "Song title cannot be empty. Song not added.\n";
        return;
    }

    // Create the new node
    p = new Node;
    p->songTitle = title;
    p->artist = artist;
    p->prev = nullptr;
    p->next = nullptr;

    if (head == nullptr) {
        // Empty playlist: new node is both head and current
        head = p;
        current = p;
    } else {
        // Walk to the last node
        q = head;
        while (q->next != nullptr) {
            q = q->next;
        }
        // Link last node <-> new node
        q->next = p;   // old last points forward to new node
        p->prev = q;   // new node points back to old last
    }
    cout << "Added: \"" << title << "\" by " << artist << "\n";
}

// ---------- Delete song by title ----------
void deleteSong() {
    if (head == nullptr) {
        cout << "Playlist is empty. Nothing to delete.\n";
        return;
    }

    string title;
    cout << "Enter title of the song to delete: ";
    getline(cin, title);

    // Search for the first matching song
    q = head;
    while (q != nullptr && q->songTitle != title) {
        q = q->next;
    }

    if (q == nullptr) {
        cout << "Song \"" << title << "\" not found.\n";
        return;
    }

    // If we are deleting the current song, move current first:
    // prefer next song, otherwise previous (may become nullptr if only song)
    if (q == current) {
        if (q->next != nullptr)
            current = q->next;
        else
            current = q->prev;
    }

    // Unlink q from the list
    if (q->prev != nullptr)
        q->prev->next = q->next;   // middle/last: previous skips over q
    else
        head = q->next;            // first node: head moves forward

    if (q->next != nullptr)
        q->next->prev = q->prev;   // middle/first: next skips back over q

    // Delete the node using p
    p = q;
    q = nullptr;
    cout << "Deleted: \"" << p->songTitle << "\" by " << p->artist << "\n";
    delete p;
    p = nullptr;

    // If list is now empty, head is already nullptr; make sure current is too
    if (head == nullptr) {
        current = nullptr;
    }
}

// ---------- Display forward ----------
void displayPlaylist() {
    if (head == nullptr) {
        cout << "Playlist is empty.\n";
        return;
    }
    cout << "\n--- Playlist ---\n";
    int count = 1;
    for (q = head; q != nullptr; q = q->next) {
        cout << count++ << ". " << q->songTitle << " - " << q->artist << "\n";
    }
}

// ---------- Display reverse ----------
void displayReverse() {
    if (head == nullptr) {
        cout << "Playlist is empty.\n";
        return;
    }
    // Go to the last node
    q = head;
    while (q->next != nullptr) {
        q = q->next;
    }
    cout << "\n--- Playlist (Reverse) ---\n";
    int count = 1;
    while (q != nullptr) {
        cout << count++ << ". " << q->songTitle << " - " << q->artist << "\n";
        q = q->prev;
    }
}

// ---------- Play current ----------
void playCurrentSong() {
    if (current == nullptr) {
        cout << "Playlist is empty. No song to play.\n";
        return;
    }
    cout << "Now playing: " << current->songTitle << " - " << current->artist << "\n";
}

// ---------- Play next ----------
void playNextSong() {
    if (current == nullptr) {
        cout << "Playlist is empty. No song to play.\n";
        return;
    }
    if (current->next == nullptr) {
        cout << "This is the last song. No next song.\n";
        return;
    }
    current = current->next;
    cout << "Now playing: " << current->songTitle << " - " << current->artist << "\n";
}

// ---------- Play previous ----------
void playPreviousSong() {
    if (current == nullptr) {
        cout << "Playlist is empty. No song to play.\n";
        return;
    }
    if (current->prev == nullptr) {
        cout << "This is the first song. No previous song.\n";
        return;
    }
    current = current->prev;
    cout << "Now playing: " << current->songTitle << " - " << current->artist << "\n";
}

// ---------- Play complete playlist (does not change current) ----------
void playCompletePlaylist() {
    if (head == nullptr) {
        cout << "Playlist is empty. Nothing to play.\n";
        return;
    }
    cout << "\n--- Playing Complete Playlist ---\n";
    for (q = head; q != nullptr; q = q->next) {
        cout << "Playing: " << q->songTitle << " - " << q->artist << "\n";
    }
    cout << "--- End of Playlist ---\n";
}

// ---------- Repeat all (two passes) ----------
void repeatAll() {
    if (head == nullptr) {
        cout << "Playlist is empty. Nothing to repeat.\n";
        return;
    }
    for (int pass = 1; pass <= 2; pass++) {
        cout << "\n--- Repeat All: Pass " << pass << " of 2 ---\n";
        for (q = head; q != nullptr; q = q->next) {
            cout << "Playing: " << q->songTitle << " - " << q->artist << "\n";
        }
    }
    cout << "--- Repeat All finished ---\n";
}

// ---------- Show current ----------
void showCurrentSong() {
    if (current == nullptr) {
        cout << "No song selected (playlist is empty).\n";
        return;
    }
    cout << "Current song: " << current->songTitle << " - " << current->artist << "\n";
}

// ---------- Free all nodes ----------
void freePlaylist() {
    while (head != nullptr) {
        p = head;
        head = head->next;   // move head first, then delete old head
        delete p;
    }
    p = nullptr;
    q = nullptr;
    current = nullptr;
}

// ---------- Menu ----------
void showMenu() {
    cout << "\n===== Music Playlist Manager =====\n"
         << " 1. Add Song\n"
         << " 2. Delete Song\n"
         << " 3. Display Playlist\n"
         << " 4. Display Playlist in Reverse\n"
         << " 5. Play Current Song\n"
         << " 6. Play Next Song\n"
         << " 7. Play Previous Song\n"
         << " 8. Play Complete Playlist\n"
         << " 9. Repeat All\n"
         << "10. Show Current Song\n"
         << "11. Exit\n"
         << "Enter your choice: ";
}

int main() {
    int choice = 0;

    while (true) {
        showMenu();

        if (!(cin >> choice)) {
            if (cin.eof()) break;                 // input closed
            cin.clear();                          // reset error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number from 1 to 11.\n";
            continue;
        }
        // Remove leftover newline so getline() works later
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:  addSong();             break;
            case 2:  deleteSong();          break;
            case 3:  displayPlaylist();     break;
            case 4:  displayReverse();      break;
            case 5:  playCurrentSong();     break;
            case 6:  playNextSong();        break;
            case 7:  playPreviousSong();    break;
            case 8:  playCompletePlaylist();break;
            case 9:  repeatAll();           break;
            case 10: showCurrentSong();     break;
            case 11:
                freePlaylist();
                cout << "Playlist memory released. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice! Please enter a number from 1 to 11.\n";
        }
    }

    freePlaylist();  // reached only if input ends (EOF)
    return 0;
}