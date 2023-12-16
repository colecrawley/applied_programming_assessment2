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
    virtual ~ItemList() = default;
    virtual std::string toString() const = 0; //abstract class, meant to be overriden
};

#endif /* ITEMLIST_HPP */
