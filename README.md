# Limit Order Book

A small C++ project I started to get more comfortable with the language by building the matching logic for a limit order book.

## What it does right now

Each order has an ID, a side, a price in cents, an arrival position, and a remaining quantity.

When an order comes in, it checks the opposite side of the book for a match. A sell checks the waiting buys, and a buy checks the waiting sells. If the buyer's price is at least the seller's price, both quantities decrease by the smaller of the two. This allows partial fills, with any unmatched quantity staying in the book.

Orders are sorted by price first, then arrival position. Buyers offering more go first, sellers asking less go first, and equal prices are ordered by who arrived earlier.

Prices are stored as integer cents to avoid floating-point rounding when comparing them.

## Decisions I made along the way

I started with two separate matching passes and couldn't shake the intuition that they should be one, since each match already updates both sides. I moved the processing into one function that takes an incoming order and branches based on whether it's a buy or sell. There are still loops for each direction, but each incoming order now goes through one matching process.

I'm using `std::vector` and `std::sort` for now. Sorting the relevant side again after processing an order isn't the most efficient approach, but I wanted to understand the matching logic and get it working before changing the data structures.

The incoming order is passed by value, so the function works on a copy. The two book vectors are passed by reference, so changes to the waiting orders persist. Any remaining quantity from the incoming order is added to its corresponding vector.

## What's left

- Add more test cases to check partial fills, price/time priority, and orders that cannot match.
- Record the trades, including the execution price and quantity.
- Add checks for invalid order inputs.
- Add order cancellation.
- Add a way to read orders from user input or a file. The processing function is there, but orders are currently created manually in `main`.
- Explore other data structures. Sorting a side containing n orders costs O(n log n). One option to investigate is a map of price levels with a queue at each level.