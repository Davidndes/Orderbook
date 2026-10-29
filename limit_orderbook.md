limit order book

This project will be a C++ limit order book 

Five things necerssay per order - an ID, side of the market, price, remaining quantity and timeof arrival




















###########

C++ Limit Order Book — Project Scope and Working Agreement
Version 1 • October 28, 2026 • Owner: David Deslandes
Status: Planning complete; implementation not started.
Purpose
Build a small, single-instrument limit order book and matching engine to strengthen C++ fundamentals and produce a demonstrable SWE / quant-development project. Success means you can explain the code, justify its data structures, and show that its behaviour is correct.

Target: a focused weekend project, with a short preparation session tonight. The milestones determine completion; the calendar is a target, not a reason to skip understanding or correctness.
Version 1 scope
- One instrument; one process; events handled sequentially.
- Add buy and sell limit orders with unique IDs, integer prices, and positive integer quantities.
- Match compatible orders using price–time priority.
- Handle full fills, partial fills, and matching across multiple orders or prices.
- Cancel the remaining quantity of an active order by its ID.
- Display best bid/ask and total remaining quantity at each price.
- Produce trade records showing buy ID, sell ID, execution price, and quantity.
- Run a deterministic demonstration, correctness tests, and documented build instructions.
A hardcoded sequence is sufficient for the first demonstration. A text-command interface is optional after the core is complete.
Behaviour contract
These are the rules for our simplified engine, not a claim to reproduce every exchange.
1. A buy limit is the highest acceptable purchase price; a sell limit is the lowest acceptable sale price.
2. An incoming buy matches the lowest resting sell price when that price is at or below its limit. An incoming sell matches the highest resting buy price when that price is at or above its limit.
3. At the same price, the order that arrived first fills first. Sequential processing establishes arrival order; wall-clock timestamps are unnecessary.
4. Each trade executes at the resting order's price. Its quantity is the smaller of the two orders' remaining quantities.
5. Continue matching while compatible orders and incoming quantity remain. Any unfilled incoming quantity then rests in the book.
6. Remove filled orders and empty price levels. Cancellation removes only an order's unfilled remainder.
7. Reject nonpositive prices or quantities and any previously accepted order ID reused during the run. Cancelling an unknown, filled, or already cancelled ID returns a clear failure without changing the book.
8. Store prices in integer ticks; for this project one tick is $0.01. Store 10025 for $100.25.
9. After each event, quantities must be positive for resting orders; if both sides exist, the best bid must be below the best ask.
Milestones and evidence
Milestone	Work	Done when
M0 — Understand the behaviour	Trace orders by hand; agree on the rules above	You can explain the trades and remaining book for the preparation example
M1 — Represent and store orders	Define order data; choose containers from required operations; compile a minimal executable	Noncrossing orders can be stored and displayed in correct price and arrival order
M2 — Match orders	Implement crossing checks, trade generation, partial fills, and repeated matching	Examples for both incoming sides produce the expected trades and remainder
M3 — Cancel and validate	Find orders by ID, remove their remainder, reject invalid inputs, clean empty levels	Cancelling first/middle/last orders and invalid requests preserves a consistent book
M4 — Verify and demonstrate	Add focused tests, a reproducible demo, and README	A clean build runs all tests and the documented demo; you can explain the design


Suggested pacing: tonight M0; first weekend session M1–M2; second session M3–M4. If progress is slower, finish the current milestone before adding anything.
Required correctness checks
- Noncrossing orders remain on the book.
- Exact full fill removes both quantities as appropriate.
- Partial fill works with either incoming or resting quantity left over.
- Better prices fill before worse prices, even if they arrived later.
- Equal-price orders fill in arrival order.
- One incoming order can consume several orders and price levels.
- Any unmatched remainder rests at its own limit price.
- Buy and sell incoming paths both work.
- Cancellation works at the front, middle, and end of a same-price queue.
- Filled orders and empty levels disappear; an empty side displays sensibly.
- Duplicate IDs, invalid prices/quantities, and unknown cancellations leave state unchanged.
- Submitted quantities can be accounted for by executed, cancelled, and remaining quantities.
Use small examples with explicit expected outcomes. A simple assertion-based test executable is enough; choosing a test framework is not a milestone.
C++ learning objectives
Introduce each concept when the implementation needs it: structs/classes for related data and behaviour; enums for order side; standard-library containers for prices and queues; references and const correctness for access; iterators and object lifetime for safe removal.

Choose containers after identifying the operations we need. Record the reason for each choice and the actual complexity of add, match, and cancel. A simple correct implementation is acceptable even if a later design could cancel faster.
Explicitly outside version 1
Market/stop orders, amendments, multiple instruments, live feeds, real trading, networking, GUI, persistence, concurrency, custom memory allocation, and exchange-specific rules.

Benchmarks and optimizations belong to a later version. Do not describe the project as low latency or high performance without measurements. Record new ideas in the parking lot instead of expanding the active milestone.
How we will work
- You write the implementation. I explain the next concept, help you choose a step, and review your attempt.
- One conceptual step at a time; no complete implementation dumps unless you request one.
- Explain why a variable, container, or abstraction is needed before introducing it.
- Review your code and notation; identify the first incorrect or unsupported step before suggesting a replacement.
- Begin each session with the current milestone and one concrete next task.
- End each session with what passed, what remains uncertain, and the next task.
- Change the scope explicitly before adding features. Do not silently turn this into a production trading system.
Tonight: M0 only
Preparation exercise, with orders arriving in this order:
Event	ID	Side	Quantity	Limit price
1	S1	Sell	5	$100.00
2	S2	Sell	4	$100.00
3	S3	Sell	3	$101.00
4	B1	Buy	7	$100.00


First task: determine which sell orders B1 trades with, at what price, and what remains. Explain why S3 can or cannot participate. We will review your answer before choosing data structures.
Progress log
Milestone	Status	Evidence / blocker
M0	Next	Hand trace not yet attempted
M1	Not started	
M2	Not started	
M3	Not started	
M4	Not started	


Parking lot: optional command input; measured performance comparisons; faster cancellation if the initial design needs it.