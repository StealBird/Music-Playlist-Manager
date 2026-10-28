# 🎵 Music Playlist Manager

A console-based music playlist manager written in **C++**, built on a **doubly linked list**. Add and delete songs, move forward and backward through the playlist, and simulate playback from the terminal.

## Features

- Add a song (title and artist) at the end of the playlist
- Delete a song by title
- Display the playlist in forward or reverse order
- Play the current, next, or previous song
- Play the complete playlist
- Repeat all (plays the full playlist twice)
- Show the currently selected song
- Frees all memory on exit

## How It Works

Each song is a node in a doubly linked list:

```cpp
struct Node {
    string songTitle;
    string artist;
    Node* prev;
    Node* next;
};
```

- `head` points to the first song.
- `current` points to the selected or playing song.
- Because every node has both `prev` and `next` pointers, you can move in either direction and print the list in reverse.
- If you delete the current song, `current` moves to the next song, or to the previous one if it was the last.

## Menu

```
===== Music Playlist Manager =====
 1. Add Song
 2. Delete Song
 3. Display Playlist
 4. Display Playlist in Reverse
 5. Play Current Song
 6. Play Next Song
 7. Play Previous Song
 8. Play Complete Playlist
 9. Repeat All
10. Show Current Song
11. Exit
```

## Getting Started

### Requirements
- A C++ compiler (g++, MinGW, or MSVC)

### Compile and Run

```bash
g++ Music-Playlist-Manager.cpp -o Music-Playlist-Manager
./Music-Playlist-Manager
```

On Windows you can also run the prebuilt `Music-Playlist-Manager.exe`.

## Example

```
Enter your choice: 1
Enter song title: Believer
Enter artist name: Imagine Dragons
Added: "Believer" by Imagine Dragons
```

A sample run is in `Code&Output.txt`.

## Project Structure

```
Music-Playlist-Manager/
├── Music-Playlist-Manager.cpp   # Source code
├── Music-Playlist-Manager.exe   # Windows executable
├── Code&Output.txt              # Code and sample output
└── README.md
```

## Concepts Used

- Doubly linked list (insert at end, delete by value, forward and backward traversal)
- Dynamic memory allocation (`new` / `delete`)
- Input validation with `cin` and `getline`
- Menu-driven program using `switch`

## Complexity

| Operation | Time |
|---|---|
| Add song (at end) | O(n) |
| Delete song | O(n) |
| Display / Reverse | O(n) |
| Next / Previous / Current | O(1) |

## Possible Improvements

- Keep a `tail` pointer to make adding a song O(1)
- Save and load the playlist from a file
- Search for songs by title or artist
- Shuffle mode
- Use a class instead of global pointers

## Author

[StealBird](https://github.com/StealBird)
