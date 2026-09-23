/*
SIMPLIFIED BANKING SYSTEM — PROGRESSIVE DESIGN PRACTICE

Implement a simplified banking system. The problem has four levels.
Each level adds new behavior while preserving the previous levels.

Timestamps are unique, strictly increasing millisecond values.

===============================================================================
LEVEL 1 — ACCOUNTS AND BASIC TRANSACTIONS
===============================================================================

Implement:

bool CreateAccount(int timestamp, const string& accountId)

Creates an account with balance 0.
Return false if the account already exists. Otherwise return true.

optional<int> Deposit(int timestamp, const string& accountId, int amount)

Add amount to the account.
Return the resulting balance.
Return nullopt if the account does not exist.

optional<int> Pay(int timestamp, const string& accountId, int amount)

Withdraw amount from the account.
If the account does not exist or has insufficient funds, return nullopt.
Otherwise return the resulting balance.

Example:

CreateAccount(1, "account1")      // true
CreateAccount(2, "account1")      // false
Deposit(3, "account1", 2000)      // 2000
Pay(4, "account1", 500)           // 1500
Pay(5, "missing", 100)            // nullopt


===============================================================================
LEVEL 2 — ACCOUNT ACTIVITY
===============================================================================

Track the total value of successful transactions for every account.

Deposits and successful payments both contribute their amount to activity.

Implement:

vector<string> TopActivity(int timestamp, int n)

Return up to n accounts with the highest total transaction value.

Format each result as:

accountId(totalTransactionValue)

Sort by:
1. total transaction value descending
2. accountId lexicographically ascending when totals tie


===============================================================================
LEVEL 3 — TRANSFERS
===============================================================================

Implement scheduled transfers between accounts.

optional<string> Transfer(
    int timestamp,
    const string& sourceAccountId,
    const string& targetAccountId,
    int amount
)

Rules:
- Both accounts must exist.
- Source and target must be different.
- Source must have enough money.
- On success, immediately withhold amount from the source account.
- Return a unique transfer id such as "transfer1", "transfer2", ...
- Invalid transfers return nullopt.

A transfer expires after 24 hours:

86400000 milliseconds

If it expires before being accepted, the withheld money is returned to the
source account.

Implement:

bool AcceptTransfer(
    int timestamp,
    const string& accountId,
    const string& transferId
)

Rules:
- The transfer must exist.
- It must not already be accepted or expired.
- accountId must be the intended target.
- If accepted, the target receives the money.
- The transferred amount contributes to the transaction totals of BOTH source
  and target accounts.
- Return true only when acceptance succeeds.


===============================================================================
LEVEL 4 — MERGING ACCOUNTS AND BALANCE HISTORY
===============================================================================

Implement:

bool MergeAccounts(
    int timestamp,
    const string& accountId1,
    const string& accountId2
)

Merge accountId2 into accountId1.

Return false if:
- the accounts are the same
- either account does not exist

On success:
- Add accountId2's current balance to accountId1.
- Combine their transaction totals.
- Remove accountId2.
- Cancel outgoing pending transfers from accountId2 and refund them as required.
- Cancel pending transfers from accountId1 to accountId2.
- Redirect other valid incoming transfers intended for accountId2 so that they
  now target accountId1.
- Preserve enough history for historical balance queries.

Implement:

optional<int> GetBalance(
    int timestamp,
    const string& accountId,
    int timeAt
)

Return the account's balance at timeAt, based on the state after the operation
processed at that timestamp.

Return nullopt if the account did not yet exist at timeAt or had already been
removed by a merge at that time.

Historical balance behavior must remain correct after account merges.


===============================================================================
RETRY NOTES
===============================================================================

Think about the data model before implementing.

Level 1:
account -> balance

Level 2:
account -> total transaction value

Level 3:
transfer id -> source, target, amount, status, expiration

Level 4:
account merges + historical balances

Try this from scratch before looking at an old solution.
*/

#include <optional>
#include <string>
#include <vector>

using namespace std;

class BankingSystemPractice {
public:
    // Level 1
    bool CreateAccount(int timestamp, const string& accountId);
    optional<int> Deposit(int timestamp, const string& accountId, int amount);
    optional<int> Pay(int timestamp, const string& accountId, int amount);

    // Level 2
    vector<string> TopActivity(int timestamp, int n);

    // Level 3
    optional<string> Transfer(int timestamp,
                              const string& sourceAccountId,
                              const string& targetAccountId,
                              int amount);

    bool AcceptTransfer(int timestamp,
                        const string& accountId,
                        const string& transferId);

    // Level 4
    bool MergeAccounts(int timestamp,
                       const string& accountId1,
                       const string& accountId2);

    optional<int> GetBalance(int timestamp,
                             const string& accountId,
                             int timeAt);

private:
    // Add your data structures here.
};

// Implement the methods below when you retry the problem.
