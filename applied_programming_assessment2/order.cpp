//
//  order.cpp
//  applied_programming_assessment2
//
//  Created by Cole Crawley on 15/12/2023.
//

#include "order.hpp"
#include "utility.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

Order::Order() : itemsInOrder() {}

Order::~Order()
{
    for (auto& item : itemsInOrder)
    {
        delete item;
        item = nullptr;1
    }
}

void Order::add(Item* item)
{
    itemsInOrder.push_back(item);
    std::cout << item->getFoodName() << " has been added to your order!" << std::endl;
}

void Order::remove(int index)
{
    if (index > 0 && index <= static_cast<int>(itemsInOrder.size()))
    {
        std::cout << itemsInOrder[index - 1]->getFoodName() << " has been removed from your order!" << std::endl;
        delete itemsInOrder[index - 1];
        itemsInOrder.erase(itemsInOrder.begin() + index - 1);
    }
    else
    {
        std::cerr << "Invalid index for removal of item." << std::endl;
    }
}

double Order::calculateTotal() const
{
    double total_amount = 0.0;
    int eligible_twoForOne = 0;
    
    for (const auto& item : itemsInOrder)
    {
        total_amount += item->getFoodPrice();
        
        //check for twoforone eligibility
        if (item->getItemType() == 'a' && dynamic_cast<Appetiser*>(item)->getFoodTwoForOne())
        {
            eligible_twoForOne++;
        }
    }
    
    if (eligible_twoForOne >= 2)
    {
        double discount = 0.0;
        for (const auto& item : itemsInOrder)
        {
            if (item->getItemType() == 'a' && dynamic_cast<Appetiser*>(item)->getFoodTwoForOne())
            {
                discount = item->getFoodPrice();
                break;
            }
        }
        
        total_amount -= discount;
        
        std::cout << "2-4-1 discount has been applied! Your savings is: $" << std::fixed << std::setprecision(2) << discount << std::endl;
    }
    
    return total_amount;
}

std::string Order::toString() const
{
    std::stringstream result;
    result << "===== ORDER =====\n";
    
    int indexItem = 1; //starts the menu on 1 instead of 0
    
    double total = 0.0;
    double savings = 0.0;
    
    
    for (const auto& item: itemsInOrder)
    {
        result << "(" << indexItem << ")" << item->toString() << "\n";
        total += item->getFoodPrice();
        
        if (item->getItemType() == 'a' && dynamic_cast<Appetiser*>(item)->getFoodTwoForOne())
        {
            savings += item->getFoodPrice();
        }
        
        indexItem++;
    }
    
    result << "Total: $" << std::fixed << std::setprecision(2) << total << "\n";
    
    if (savings > 0)
    {
        result << "Savings: $" << std::fixed << std::setprecision(2) << savings << "\n";
    }
    else
    {
        result << "Savings: $0.00\n";
    }
    
    return result.str();
}

void Order::printReceipt(const std::string& filePath) const
{
    std::ofstream receiptFile(filePath); //receipt.txt file path
    if (receiptFile.is_open())
    {
        receiptFile << toString();
        receiptFile.close();
        std::cout << "Receipt has been written to the text file receipt.txt" << std::endl;
    }
    else
    {
        std::cout << "Error: Unable to open receipt.txt." << std::endl;
    }
}

int Order::getOrderSize() const
{
    return static_cast<int>(itemsInOrder.size());
}

const std::vector<Item*>& Order::getOrderedItems() const
{
    return itemsInOrder;
}
