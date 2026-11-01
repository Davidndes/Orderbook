// Limit orderbook 

#include <iostream>
#include <vector>
#include <algorithm>


struct Order { // struct creates a new data type that allows for combining related information 
    // there fore this creates "order" datatype that stores the follwoing info 
    // each member of "Order" is accessed via using a dot
    int ID;
    char side;
    int priceCents;
    int arrivalPos;
    int quantity; 
};

bool buyComesFirst(const Order& a, const Order& b) { // creating a fucntion that allows for sorting buy higher price first and then oldest position second

    if (a.priceCents != b.priceCents) {
        return a.priceCents > b.priceCents; // returns true is a's price is higher, false if not
    }
    return a.arrivalPos < b.arrivalPos; // if the prices are the same it returns true if a arrived earlier, false if not
}

bool sellComesFirst(const Order& a, const Order& b){

    if (a.priceCents != b.priceCents){
        return a.priceCents < b.priceCents;
    }
    return a.arrivalPos < b.arrivalPos;
}


void processIncomingOrder( // void means no return value
    Order newOrder,
    std::vector<Order>& buy_orders,
    std::vector<Order>& sell_orders){

        if (newOrder.side == 'S'){
            for (Order& buy_order : buy_orders){
                if (newOrder.quantity == 0){
                    break;
                }
                if (buy_order.quantity == 0){
                    continue;
                }
                if (newOrder.priceCents <= buy_order.priceCents){
                    int matched_quantity = std::min(newOrder.quantity, buy_order.quantity); 
                    newOrder.quantity -= matched_quantity;
                    buy_order.quantity -= matched_quantity;
                } 
            }

            buy_orders.erase(
            std::remove_if(
                buy_orders.begin(),
                buy_orders.end(),
                [](const Order& order) {
                    return order.quantity == 0;
                }
            ),
            buy_orders.end()
        );
            
            if (newOrder.quantity > 0) {
                sell_orders.push_back(newOrder);
            }
            
            std::sort(
                sell_orders.begin(),
                sell_orders.end(),
                sellComesFirst);
        
        } else {

        for (Order& sell_order: sell_orders){
            if (newOrder.quantity == 0){
                break;
            }
            if (sell_order.quantity == 0){
                continue;
            }
            if (newOrder.priceCents >= sell_order.priceCents){
                int matched_quantity = std::min(newOrder.quantity, sell_order.quantity);
                newOrder.quantity -= matched_quantity;
                sell_order.quantity -= matched_quantity;
            }
        }

        sell_orders.erase(// deletes everything from start up to but not including finish
            std::remove_if( // moves retained orders to the front
                sell_orders.begin(),
                sell_orders.end(),
                // create a function that the algorithm can run itself to decide what to remove
                [](const Order& order) { // this "[]" is a lambda - a function without a name used directly where needed, empty brackets mean it doesnt use outside variables
                    return order.quantity == 0; // returns true if the order quantity finishes 
                }
            ),
            sell_orders.end()
        );

        if (newOrder.quantity > 0) {
            buy_orders.push_back(newOrder);
        }

        std::sort(
            buy_orders.begin(),
            buy_orders.end(),
            buyComesFirst);
        }
    }

int main() {

    std::vector<Order> incoming_buy_orders;
    std::vector<Order> incoming_sell_orders;

//    Order firstSell{ 1, 'S', 10000, 1 ,5};
//    Order firstBuy{2, 'B', 10000, 2, 7};
    
    int nextPosition = 1;

    char again;

    while (true) { // loop allows user to enter their order into the terminal and  

    Order newOrder{}; 

    std::cout << "Enter Order ID, side, price in cents and quantity: \n";

    std::cin >> newOrder.ID
            >> newOrder.side
            >> newOrder.priceCents
            >> newOrder.quantity;

    if (newOrder.side != 'S' && newOrder.side != 'B'){
        std::cout << "enter correct side" << std::endl;
        continue; 
    }

    if (newOrder.priceCents <= 0 || newOrder.quantity <= 0){
        std::cout << "enter valid price and quantity" << std::endl;
        continue;
    }

    newOrder.arrivalPos = nextPosition;
    nextPosition++;

    processIncomingOrder(
        newOrder,
        incoming_buy_orders,
        incoming_sell_orders);

    std::cout << "Continue? (y/n): ";
    std::cin >> again;

    if (again != 'y' && again != 'Y') {
        break;
    };

    }

   // std::cout << incoming_buy_orders[0].arrivalPos << std::endl;

return 0;

}
