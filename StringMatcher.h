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
    StringMatcher(FuncType in_matcher);
    bool match(string str1, string str2);

private:
    FuncType mMatcher;
};


#endif //SORTABLECHALLENGEREPO_STRINGMATCHER_H


///////////////////////////////////////////////////////////////
// Functor: Manufacturer Matching
///////////////////////////////////////////////////////////////
class ManufacturerMatcher
{
public:
    bool operator()(string str1, string str2);
};


///////////////////////////////////////////////////////////////
// Functor: Manufacturer Matching
///////////////////////////////////////////////////////////////
class ProductMatcher
{
public:
    bool operator()(string str1, string str2);
};