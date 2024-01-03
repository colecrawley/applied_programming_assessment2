//
//  Itemlist.hpp
//  applied_programming_assessment2
//
//  Created by Cole Crawley on 05/12/2023.
//

#ifndef ITEMLIST_HPP
#define ITEMLIST_HPP

#include <stdio.h>
#include <string>

class ItemList
{
public:
    
    //pure virtual destructor. I want the derived classes to use their own specific destructors
    virtual ~ItemList() = default;
    
    //forces the derived classes to use their own toString fucntions
    virtual std::string toString() const = 0; //abstract class, meant to be overriden
};

#endif
