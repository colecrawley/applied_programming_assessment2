//
//  order.cpp
//  applied_programming_assessment2
//
//  Created by Cole Crawley on 15/12/2023.
//

#include "order.hpp"
#include "utility.hpp"
#include "menu.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

Order::Order() : itemsInOrder() {}

Order::~Order() //don't want to delete items in order because it would be double deletion with items in the menu. we want menu to stay constant and items in order to be pointers to the menu that we can delete and add
{
    /*for (auto& item : itemsInOrder)
    {
        delete item;
        item = nullptr;
    }*/
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
        //std::cout << itemsInOrder[index - 1]->getFoodName() << " has been removed from your order!" << std::endl;
        
        Item* removedItem = itemsInOrder[index - 1];
        if (removedItem)
        {
            std::cout << itemsInOrder[index - 1]->getFoodName() << " has been removed from your order!" << std::endl;
            
            itemsInOrder.erase(itemsInOrder.begin() + index - 1);
        }
        //delete itemsInOrder[index - 1];
        //itemsInOrder.erase(itemsInOrder.begin() + index - 1);
    }
    else
    {
        std::cerr << "Invalid index for removal of item." << std::endl;
    }
}

double Order::calculateTotal() const
{
    double total_amount = 0.0;
    double total_discount = 0.0;
    int eligible_twoForOne = 0;
    
    for (const auto& item : itemsInOrder)
    {
        total_amount += item->getFoodPrice();
        
        //check for twoforone eligibility
        if (item->getItemType() == 'a' && dynamic_cast<Appetiser*>(item)->getFoodTwoForOne())
        {
            //eligible_twoForOne++;
            //total_discount += item->getFoodPrice(); //to keep adding the discounts for total
            
            eligible_twoForOne++;
            if (eligible_twoForOne % 2 == 0)
            {
                total_discount += item->getFoodPrice();
            }
        }
    }
    
    if (eligible_twoForOne >= 2)
    {
        //double discount = 0.0;
        
        total_amount -= total_discount;
        
        std::cout << "2-4-1 discount has been applied! Your savings is: $" << std::fixed << std::setprecision(2) << total_discount << std::endl;
    }
    
    return total_amount;
}

std::string Order::toString() const
{
    std::stringstream result;
    result << "===== ORDER =====\n";
    
    int indexItem = 1; //starts the menu on 1 instead of 0
    
    double total = 0.0; //total
    double savings = 0.0; // discount
    int eligible_twoForOne = 0;
    
    
    
    
    for (const auto& item: itemsInOrder)
    {
        result << "(" << indexItem << ")" << item->toString() << "\n";
        total += item->getFoodPrice();
        
        if (item->getItemType() == 'a' && dynamic_cast<Appetiser*>(item)->getFoodTwoForOne())
        {
            eligible_twoForOne++;
            if (eligible_twoForOne % 2 == 0)
            {
                savings += item->getFoodPrice();
            }
            
            //savings += item->getFoodPrice();
        }
        
        indexItem++;
    }
    
    if (eligible_twoForOne >= 2)
    {
        total -= savings;
        
        result << "Total: $" << std::fixed << std::setprecision(2) << total << "\n";
    }
    
    //result << "Total: $" << std::fixed << std::setprecision(2) << total << "\n";
    
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
