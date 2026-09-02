# mini_Redis

An optimized, zero-dependency, in-memory key-value database and graph processing engine implemented entirely from scratch in C++. 

Designed as a simplified clone of Redis, this project enforces a strict no-standard-library data structures rule. Every dynamic array, hash map, doubly linked list, balanced search tree, and graph dynamic connectivity structure (Link-Cut Tree) is written manually using foundational memory management.

---

## Technical Highlights & Constraints

* **Zero External Dependencies:** Built without `std::vector`, `std::unordered_map`, `std::map`, or any generic containers/algorithms from standard libraries.
* **High Efficiency:** Core key-value and list operations execute in average $O(1)$ time complexity.
* **Advanced Data Structures:** Employs self-balancing search trees for sorted sets and dynamic link-cut trees for graph connectivity and Minimum Spanning Trees (MST).
* **CLI Interface:** Interactive command-line parser operating over standard input/output streams.

---

## Supported Commands & Time Complexities

### 1. Basic Key-Value Operations
| Command | Description | Expected Complexity |
| :--- | :--- | :--- |
| `SET <key> <value>` | Stores or updates a key-value pair. | $O(1)$ avg |
| `GET <key>` | Retrieves the value associated with `<key>`. | $O(1)$ avg |
| `DEL <key>` | Removes `<key>` and its associated value. | $O(1)$ avg |
| `EXISTS <key>` | Checks key existence (`1` if found, `0` otherwise). | $O(1)$ avg |

### 2. Key Expiration & Lifespan (TTL)
| Command | Description | Expected Complexity |
| :--- | :--- | :--- |
| `EXPIRE <key> <seconds>` | Sets a lifetime in seconds for a target key. | $O(1)$ |
| `TTL <key>` | Returns remaining time-to-live (`-1` if no expiration, `-2` if missing). | $O(1)$ |

### 3. Double-Ended List Operations
| Command | Description | Expected Complexity |
| :--- | :--- | :--- |
| `LPUSH <key> <value>` | Prepends an element to the start of the list. | $O(1)$ |
| `RPUSH <key> <value>` | Appends an element to the end of the list. | $O(1)$ |
| `LPOP <key>` | Removes and returns the first element of the list. | $O(1)$ |
| `RPOP <key>` | Removes and returns the last element of the list. | $O(1)$ |
| `LRANGE <key> <start> <end>` | Displays list elements within inclusive zero-based index bounds. | $O(N)$ |

### 4. Sorted Sets (Z-Sets)
| Command | Description | Expected Complexity |
| :--- | :--- | :--- |
| `ZADD <key> <score> <member>` | Adds or updates a member with a numeric score. | $O(\log N)$ |
| `ZREM <key> <member>` | Removes a member from the sorted set. | $O(\log N)$ |
| `ZSCORE <key> <member>` | Retrieves the score of a specific member. | $O(1)$ avg |
| `ZRANK <key> <member>` | Computes the 0-based rank of a member in ascending score order. | $O(\log N)$ |

### 5. In-Memory Graph Engine & Dynamic Spanning Tree
| Command | Description | Expected Complexity |
| :--- | :--- | :--- |
| `GCREATE <graph_name>` | Initializes a new named dynamic undirected graph. | $O(1)$ |
| `GADDNODE <graph_name> <node>` | Adds a node to the designated graph. | $O(1)$ amortized |
| `GADDEDGE <graph_name> <u> <v> <w>` | Adds an undirected weighted edge between `u` and `v`. | $O(1)$ amortized |
| `GCONNECTED <graph_name> <u> <v>` | Checks connectivity path existence between `u` and `v` (`1` / `0`). | $O(\log N)$ amortized |
| `GMST <graph_name>` | Computes Minimum Spanning Tree weight using Link-Cut Trees. | $O(\log N)$ amortized |

---

## Example Usage

```bash
# Basic KV
SET name Armin
GET name
> Armin

# Expiration
EXPIRE name 60
TTL name
> 59

# Lists
RPUSH numbers 10
LPUSH numbers 20
RPUSH numbers 30
LRANGE numbers 0 2
> 20 10 30

# Sorted Sets
ZADD leaderboard 120 Ali
ZADD leaderboard 90 Sara
ZADD leaderboard 150 Reza
ZRANK leaderboard Ali
> 1

# Graph & MST
GCREATE roads
GADDNODE roads Tehran
GADDNODE roads Karaj
GADDEDGE roads Tehran Karaj 35
GCONNECTED roads Tehran Karaj
> 1
GMST roads
> 35
```

---

## Build & Execution

### Prerequisites
* `g++` compiler supporting C++17 or higher.

### Building from Source

```bash
# Clone the repository
git clone [https://github.com/MParsa-ES/mini_Redis.git](https://github.com/MParsa-ES/mini_Redis.git)
cd mini_Redis

# Compile using g++
g++ -std=c++17 src/main.cpp src/HashMap.cpp src/ListHashMap.cpp src/LinkedList.cpp src/ZTree.cpp src/ZSet.cpp src/ZSetHashMap.cpp src/Graph.cpp src/GraphHashMap.cpp src/LinkCutTree.cpp  -I include -o mini_redis

# Run the interactive CLI executable
./mini_redis
```

---

## Architecture & Data Structures Implemented

* **Custom Hash Map:** Separate chaining hash table built manually to achieve average $O(1)$ lookup for `GET`, `SET`, `DEL`, `EXISTS`, and `ZSCORE`.
* **Doubly Linked List / Deque:** Hand-crafted pointers supporting $O(1)$ head/tail insertions and deletions for list data types.
* **Balanced Search Trees (Red-Black / Treap):** Ordered indexing structure powering $O(\log N)$ operations for `ZADD`, `ZREM`, and `ZRANK`.
* **Link-Cut Trees (LCT):** Advanced logarithmic data structure enabling dynamic tree connectivity and dynamic MST maintenance (`GCONNECTED`, `GMST`).