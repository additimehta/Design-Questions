/*
LRU CACHE — DESIGN PRACTICE

Design and implement a Least Recently Used (LRU) cache.

The cache stores integer key-value pairs and has a fixed positive capacity.

The goal is for both Get and Put to run in average O(1) time.

===============================================================================
REQUIREMENTS
===============================================================================

Implement:

LRUCache(int capacity)

Creates an LRU cache that can hold at most capacity entries.


int Get(int key)

If key exists:
- Return its value.
- Mark this key as the MOST recently used entry.

If key does not exist:
- Return -1.


void Put(int key, int value)

If key already exists:
- Update its value.
- Mark it as the MOST recently used entry.

If key does not exist:
- Insert the new key-value pair.
- Mark it as the MOST recently used entry.

If inserting causes the cache to exceed capacity:
- Remove the LEAST recently used entry.


===============================================================================
EXAMPLE
===============================================================================

LRUCache cache(2);

cache.Put(1, 1);
// cache: [1]

cache.Put(2, 2);
// cache: [2, 1]
// 2 is most recently used.

cache.Get(1);
// returns 1
// cache: [1, 2]

cache.Put(3, 3);
// capacity would be exceeded.
// key 2 is least recently used, so remove it.
// cache: [3, 1]

cache.Get(2);
// returns -1

cache.Put(4, 4);
// key 1 is least recently used.
// cache: [4, 3]

cache.Get(1);
// returns -1

cache.Get(3);
// returns 3
// cache: [3, 4]

cache.Get(4);
// returns 4
// cache: [4, 3]


===============================================================================
CONSTRAINT / DESIGN GOAL
===============================================================================

Get and Put should both run in average:

O(1)

Before coding, think about why these approaches alone are not enough:

1. vector / list only
   - Easy to track usage order.
   - But finding a key can take O(n).

2. unordered_map only
   - Easy to find a key in average O(1).
   - But it does not naturally track least-recently-used order.

Try to find a design that gives you BOTH:

O(1) lookup
+
O(1) removal/movement of entries


===============================================================================
QUESTIONS TO THINK ABOUT
===============================================================================

1. What information needs to change whenever Get succeeds?

2. What needs to happen when Put updates an existing key?

3. How can you quickly identify the least recently used entry?

4. If you know a key, how can you quickly move its corresponding entry?

5. What should happen when the cache reaches capacity?


===============================================================================
OPTIONAL FOLLOW-UP
===============================================================================

Once the basic LRU cache works, try extending it with:

bool Contains(int key)

int Size()

void Remove(int key)

Then consider how you would modify the design if entries could also expire
after a TTL.


===============================================================================
RETRY NOTES
===============================================================================

Do not start by memorizing a standard LRU implementation.

First identify the two separate jobs your data structures need to perform:

1. Fast key lookup.
2. Maintaining usage order.

Then decide which data structure should handle each job.

No solution is included in this file.
*/

class LRUCache {
public:
    LRUCache(int capacity) {
        // TODO
    }

    int Get(int key) {
        // TODO
        return -1;
    }

    void Put(int key, int value) {
        // TODO
    }

private:
    // Add your data structures here.
};
