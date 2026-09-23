/*
PAYMENT LEDGER — PROGRESSIVE DESIGN PRACTICE

Build a small transaction ledger that supports account funding through multiple
payment rails. Each level adds additional behavior.

===============================================================================
LEVEL 1 — ACCOUNTS AND FUNDING
===============================================================================

Support operations conceptually equivalent to:

INIT <timestamp> <account>
FUND <timestamp> <account> <method> <amount>
BALANCE <timestamp> <account>

INIT creates an account.

FUND submits money to the account using a payment method.

BALANCE returns the amount that has actually settled into the account by the
requested time.

Start with immediate funding behavior, then extend settlement rules in the
later levels.


===============================================================================
LEVEL 2 — MULTIPLE PAYMENT METHODS
===============================================================================

Support these funding methods:

STABLECOIN
- Settles immediately.
- Can settle on weekdays or weekends.

WIRE
- Normally settles on the submission day.
- If submitted on a weekend, settlement moves to Monday.

ACH
- Settles one business day after submission.
- Weekends are skipped.
- A submission whose next business-day settlement crosses a weekend should
  settle on the appropriate following weekday.

Only settled funds count toward BALANCE.


Example idea:

An account begins with 5000.

At timestamp/day 6:
FUND ... STABLECOIN 1000
FUND ... ACH 2000

The stablecoin funding can affect the balance immediately while the ACH funding
must wait for its settlement day.


===============================================================================
LEVEL 3 — PENDING TRANSACTIONS
===============================================================================

Represent submitted funding separately from settled balance.

Each transaction should contain enough information to determine:
- account
- amount
- payment method
- submission time/day
- settlement time/day
- whether it has already settled

When BALANCE is requested, process transactions that should have settled by
that time exactly once.

Avoid double-crediting a transaction when BALANCE is queried repeatedly.


===============================================================================
LEVEL 4 — EXTENSIONS
===============================================================================

Extend the ledger so the implementation can cleanly support additional payment
methods or settlement rules without rewriting the basic account logic.

Consider:
- separating settlement-date calculation from balance updates
- keeping pending transactions in a dedicated structure
- making each payment method's settlement rule easy to change
- preserving transaction history after settlement


===============================================================================
RETRY NOTES
===============================================================================

The important design split is:

account balances
        versus
submitted/pending transactions

A FUND operation does not necessarily mean the balance changes immediately.

For each payment method, ask:

1. When was it submitted?
2. What is its settlement date?
3. Has it already settled?
4. At the requested BALANCE time, should it now be applied?

No solution is included in this file.
*/

#include <string>
#include <vector>

using namespace std;

class PaymentLedgerPractice {
public:
    // Design the interface/data structures based on the specification above.

private:
    // Add your account and transaction state here.
};
