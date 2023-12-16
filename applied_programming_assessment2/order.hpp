//
//  order.hpp
//  applied_programming_assessment2
//
//  Created by Cole Crawley on 15/12/2023.
//

#ifndef ORDER_HPP
#define ORDER_HPP

#include <stdio.h>
#include <vector>
#include "item.hpp"

 class Order
{
public:
    Order();
    ~Order();
    
    void add(Item* item);
    void remove(int index);
    double calculateTotal() const;
    std::string toString() const; //doesn't need to be virtual because no derived classes
    void printReceipt(const std::string& filePath) const;
    int getOrderSize() const;
    const std::vector<Item*>& getOrderedItems() const;
    
private:
    std::vector<Item*> itemsInOrder;
};

#endif /* ORDER_HPP */
