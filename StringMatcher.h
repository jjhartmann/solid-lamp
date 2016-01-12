///////////////////////////////////////////////////////////////
// Created by Jeremy on 1/10/2016.
///////////////////////////////////////////////////////////////

#ifndef SORTABLECHALLENGEREPO_STRINGMATCHER_H
#define SORTABLECHALLENGEREPO_STRINGMATCHER_H

#include <string>

using namespace std;

template <typename FuncType>
class StringMatcher
{
public:
    StringMatcher()
    {

    }

    bool match(string str1, string str2)
    {

    }

private:
    FuncType mMatcher;
};


///////////////////////////////////////////////////////////////
// Functor: Manufacturer Matching
///////////////////////////////////////////////////////////////
class ManufacturerMatcher
{
public:
    // Using a KB, look up and match against known manufacturers.
    string operator()(string str)
    {
        return str;
    }
};


///////////////////////////////////////////////////////////////
// Functor: Manufacturer Matching
///////////////////////////////////////////////////////////////
class ProductMatcher
{
public:
    bool operator()(string str1, string str2)
    {}
};

#endif //SORTABLECHALLENGEREPO_STRINGMATCHER_H
