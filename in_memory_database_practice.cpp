/*
In-Memory Database — Progressive Design Practice

Implement a simplified in-memory database. The problem consists of four levels.
Each level adds functionality while keeping all functionality from previous
levels working.

You do not need the most efficient implementation. Any implementation satisfying
the required behavior is acceptable.

===============================================================================
LEVEL 1 — BASIC OPERATIONS
===============================================================================

The database contains records.

Each record is identified by a unique string key.

Each record contains zero or more field-value pairs, where both the field and
value are strings.

Conceptually:

database
|
|-- "user1"
|    |-- "name" -> "Alice"
|    \-- "age"  -> "20"
|
\-- "user2"
     \-- "name" -> "Bob"


Implement:

void Set(
    const std::string& key,
    const std::string& field,
    const std::string& value
);

Set inserts a field-value pair into the record associated with key.

If the record does not exist, create it.

If the field already exists, replace its value.


Implement:

std::optional<std::string> Get(
    const std::string& key,
    const std::string& field
);

Return the value associated with field in the record identified by key.

If either the record or field does not exist, return std::nullopt.


Implement:

bool Delete(
    const std::string& key,
    const std::string& field
);

Delete field from the record associated with key.

Return true if the field existed and was successfully deleted.

Return false if the key or field did not exist.


Example:

Set("A", "B", "E");
Set("A", "C", "F");

Get("A", "B");     // "E"
Get("A", "D");     // nullopt

Delete("A", "B");  // true
Delete("A", "D");  // false


===============================================================================
LEVEL 2 — SCANNING AND FILTERING
===============================================================================

Implement:

std::vector<std::string> Scan(
    const std::string& key
);

Return all fields belonging to key.

Each element must have the format:

field(value)

Fields must be returned in lexicographical order by field name.

If the record does not exist, return an empty vector.


Example:

Set("A", "BC", "E");
Set("A", "BD", "F");
Set("A", "C", "G");

Scan("A");

returns:

{
    "BC(E)",
    "BD(F)",
    "C(G)"
}


Implement:

std::vector<std::string> ScanByPrefix(
    const std::string& key,
    const std::string& prefix
);

This behaves like Scan, except only fields whose names start with prefix are
included.

Results must still be lexicographically sorted.


Example:

ScanByPrefix("A", "B");

returns:

{
    "BC(E)",
    "BD(F)"
}


===============================================================================
LEVEL 3 — TIMESTAMPS AND TTL
===============================================================================

The database now supports timestamps and TTL (Time-To-Live).

Each operation from previous levels now has a timestamp-based alternative.

Timestamps are guaranteed to strictly increase as operations execute.

A test will use either timestamped operations or the original operations, not
both. However, your original Level 1 and Level 2 functions must continue
working.


SetAt:

void SetAt(
    const std::string& key,
    const std::string& field,
    const std::string& value,
    int timestamp
);

Behaves like Set.

The field does not expire.

If the field previously had a TTL, SetAt removes that TTL.


SetAtWithTtl:

void SetAtWithTtl(
    const std::string& key,
    const std::string& field,
    const std::string& value,
    int timestamp,
    int ttl
);

Insert or update the field and assign it a TTL.

The field exists during:

[timestamp, timestamp + ttl)

For example:

SetAtWithTtl("A", "B", "hello", 10, 5);

means "B" exists at timestamps 10 through 14 and is expired at timestamp 15.


GetAt:

std::optional<std::string> GetAt(
    const std::string& key,
    const std::string& field,
    int timestamp
);

Behaves like Get, but the field should only be returned if it exists and has not
expired at the given timestamp.


DeleteAt:

bool DeleteAt(
    const std::string& key,
    const std::string& field,
    int timestamp
);

Behaves like Delete.

Return true only if the field exists and has not expired at the given timestamp.

Otherwise return false.


ScanAt:

std::vector<std::string> ScanAt(
    const std::string& key,
    int timestamp
);

Behaves like Scan, but expired fields must not appear.


ScanByPrefixAt:

std::vector<std::string> ScanByPrefixAt(
    const std::string& key,
    const std::string& prefix,
    int timestamp
);

Behaves like ScanByPrefix, but expired fields must not appear.


TTL Example:

SetAtWithTtl("A", "BC", "E", 1, 9);
SetAtWithTtl("A", "BC", "E", 5, 10);
SetAt("A", "BD", "F", 5);

The second operation overwrites BC, so it now expires at timestamp 15.
BD has no expiration.

ScanByPrefixAt("A", "B", 14);

returns:

{
    "BC(E)",
    "BD(F)"
}

but:

ScanByPrefixAt("A", "B", 15);

returns:

{
    "BD(F)"
}


===============================================================================
LEVEL 4 — BACKUP AND RESTORE
===============================================================================

The database should support saving and restoring previous database states.

TTL values must be handled correctly when restoring.


Backup:

int Backup(int timestamp);

Save the database's current state at timestamp.

Only fields that are alive at this timestamp should be saved.

For fields with TTLs, save their remaining TTL.

For example, if a field expires at timestamp 30 and a backup occurs at
timestamp 20, its remaining TTL is 10.

Backup returns the number of non-empty, non-expired records in the database.

Remember: this is the number of records, not the number of fields.


Restore:

void Restore(
    int timestamp,
    int timestamp_to_restore
);

Find the latest backup whose timestamp is less than or equal to
timestamp_to_restore.

Restore the database to that backup's state.

A suitable backup is guaranteed to exist.

TTL expiration times must be recalculated relative to the timestamp at which
Restore occurs.

For example, if a backup contains a field with remaining TTL 10 and you perform:

Restore(100, 50);

then that field should now expire at timestamp 110.

Restoring the database does not delete backup history.

Backups created after timestamp_to_restore remain available for future Restore
operations.


===============================================================================
RETRY NOTES
===============================================================================

Try to reconstruct the design yourself:

Level 1:
key -> field -> value

Level 2:
iterate fields -> format -> sort

Level 3:
field -> expiration time

Level 4:
backup:
    save values
    save remaining TTL

restore:
    choose latest valid backup
    restore values
    new expiration = restore time + remaining TTL

No solution is included in this file on purpose.
*/

#include <optional>
#include <string>
#include <vector>

using namespace std;

class InMemoryDBPractice {
public:
    // Level 1
    void Set(const string& key, const string& field, const string& value);
    optional<string> Get(const string& key, const string& field);
    bool Delete(const string& key, const string& field);

    // Level 2
    vector<string> Scan(const string& key);
    vector<string> ScanByPrefix(const string& key, const string& prefix);

    // Level 3
    void SetAt(const string& key, const string& field,
               const string& value, int timestamp);

    void SetAtWithTtl(const string& key, const string& field,
                      const string& value, int timestamp, int ttl);

    bool DeleteAt(const string& key, const string& field, int timestamp);

    optional<string> GetAt(const string& key, const string& field,
                           int timestamp);

    vector<string> ScanAt(const string& key, int timestamp);

    vector<string> ScanByPrefixAt(const string& key, const string& prefix,
                                  int timestamp);

    // Level 4
    int Backup(int timestamp);

    void Restore(int timestamp, int timestamp_to_restore);

private:
    // Add your data structures here.
};

// Implement the methods below when you retry the problem.
