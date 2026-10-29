// Limit orderbook 

#include <iostream>
#include <vector>
#include <algorithm>


struct Order { // struct creates a new data type that allows for combining related information 
    // there fore this creates "order" datatype that stores the follwoing info 
    int ID;
    char side;
    int priceCents;
    int arrivalPos;
    int quantity; 
};

Order firstOrder {1, 'S' , 4400, 1, 5}; // each member of "Order" is accessed via using a dot
Order secondOrder {2, 'S', 10100, 2, 4};


int main() {

    std::vector<Order> sellOrders;

    sellOrders.push_back(firstOrder);
    sellOrders.push_back(secondOrder);

    Order buyOrder {4, 'B', 10000, 3, 7};

    for (Order& order : sellOrders){ // this is a range based for loop looping over the items directly when the postions are not needed
        // order here refers to the current element in the iteration

        if (buyOrder.quantity == 0){ // this checks if they are any buy orders remaining
            break;
        }

        if (order.priceCents <= buyOrder.priceCents){          
            // order.quantity -= buyOrder.quantity;
            // std::cout << order.ID << " can match\n";

            int quantityMatch = std::min(buyOrder.quantity, order.quantity); // this selects the lower of the two quantities to decrease btoh quantities by

            buyOrder.quantity -= quantityMatch;
            order.quantity -= quantityMatch; 
         };

         // checking how much is remaining for each of the buys and sells 
    std::cout << "Buyer remaining: " << buyOrder.quantity << '\n';

    for (const Order& order : sellOrders){
        std::cout << "Sell " << order.ID << " remaining " << order.quantity << '\n';
    }
       
    }
    
    return 0;

}


