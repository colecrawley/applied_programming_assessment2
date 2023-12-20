//
//  main.cpp
//  applied_programming_assessment2
//
//  Created by Cole Crawley on 15/12/2023.
//

#include <stdio.h>
#include <iostream>
#include "menu.hpp"
#include "order.hpp"

/*std::string toLowerCase(const std::string& str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
    
}*/


int main() {
    
    Menu menu("/Users/colecrawley/Desktop/applied_programming_assessment2/applied_programming_assessment2/applied_programming_assessment2/menu.csv");
    
    Order order;
    
    while (true)
    {
        std::cout << "\n========== Welcome to Cole's Restaurant Menu! ==========\n";
        std::cout << "1. View Menu in ascending order\n";
        std::cout << "2. View Menu in descending order\n";
        std::cout << "3. Add food to Order\n";
        std::cout << "4. Remove food from order\n";
        std::cout << "5. View your Order\n";
        std::cout << "6. Print Receipt\n";
        std::cout << "7. View current orders\n";
        std::cout << "8. Exit Restaurant\n";
        std::cout << "=========================================================\n";
        
        int user_choice;
        
        while (true)
        {
            std::cout << "Enter a number: ";
            std::cin >> user_choice;
            
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid answer, please try again! " << std::endl;
            }
            else
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
        }
        
        //std::cin.clear();
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (user_choice)
        {
            case 1:
                menu.sortByMenuPriceAscending();
                std::cout << menu.toString() << std::endl;
                break;
                
            case 2:
                menu.sortByMenuDescending();
                std::cout << menu.toString() << std::endl;
                break;
                
            case 3:
            {
                std::string foodName;
                std::cout << "Enter the number of the item to add: ";
                int itemNumber;
                std::cin >> itemNumber;
                
                //Item* chosenItem = menu.findItemByName(foodName);
                if (itemNumber >= 1 && itemNumber <= menu.getMenuSize())
                {
                    //order.add(chosenItem);
                    Item* chosenItem = menu.getItemOnMenu(itemNumber - 1);
                    order.add(chosenItem);
                    //std::cout << chosenItem->getFoodName() << " has been added to your order!" << std::endl;
                    /*std::vector<int> itemIndices;
                    int itemIndex;
                    std::cout << "Enter the food numbers you want to add: [enter -1 to finish order]: ";
                    
                    while (std::cin >> itemIndex && itemIndex != -1)
                    {
                        itemIndices.push_back(itemIndex);
                    }
                    
                    menu.multipleItemsToOrder(orders[itemNumber - 1], itemIndices);*/
                }
                else
                {
                    std::cout << "Food or Beverage is not found on the menu!\n";
                }
                break;
            }
                
            case 4:
            {
                std::cout << "========== Your Order ==========\n";
                const std::vector<Item*>& orderedItems = order.getOrderedItems();
                
                for (int i = 0; i < orderedItems.size(); ++i)
                {
                    std::cout << i + 1 << ".) " << orderedItems[i]->toString() << "\n";
                }
                
                int removedItem;
                
                std::cout << "Enter the number of the food or beverage to remove: ";
                std::cin >> removedItem;
                
                if (removedItem > 0 && removedItem <= orderedItems.size())
                {
                    order.remove(removedItem);
                }
                else
                {
                    std::cout << "Entered number is not on the menu. No item has been removed.\n";
                }
                break;
            }
                
            case 5:
            {
                
                std::cout << "========== Your Order ==========\n";
                
                const std::vector<Item*>& orderedItems = order.getOrderedItems();
                
                for (int i = 0; i < order.getOrderSize(); ++i)
                {
                    std::cout << i + 1 << ".) " << orderedItems[i]->toString() << "\n";
                }
                
                std::cout << "Order Total: $" << order.calculateTotal() << std::endl;
                break;
            }
                
            case 6:
                order.printReceipt("/Users/colecrawley/Desktop/applied_programming_assessment2/applied_programming_assessment2/applied_programming_assessment2/receipt.txt");
                break;
                
            case 7:
                
            {
                std::vector<int> itemIndices;
                int itemIndex;
                
                std::cout << "Enter the numbers of the items on the menu you want to add to your order (separate your choices with spaces, finish with -1): ";
                
                while (std::cin >> itemIndex)
                {
                    if (itemIndex == -1)
                    {
                        break;
                    }
                    itemIndices.push_back(itemIndex);
                }
                
                for (int index : itemIndices)
                {
                    if (index >= 1 && index <= menu.getMenuSize())
                    {
                        Item* chosenItem = menu.getItemOnMenu(index - 1);
                        order.add(chosenItem);
                    }
                    else
                    {
                        std::cout << "Invalid item number " << index << ". Item skipped.";
                    }
                }
                break;
            }
                
            case 8:
                std::cout << "Exiting the Restaurant.\n";
                return 0;
                
            default:
                std::cout << "Invalid choice, please try again!";
        }
    }
    
    return 0;
}
