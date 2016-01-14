///////////////////////////////////////////////////////////////
// Created by Jeremy on 1/10/2016.
///////////////////////////////////////////////////////////////

#ifndef SORTABLECHALLENGEREPO_STRINGMATCHER_H
#define SORTABLECHALLENGEREPO_STRINGMATCHER_H

#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>

#include "ListingManufacturer.h"


using namespace std;

///////////////////////////////////////////////////////////////
// KB for Companies
///////////////////////////////////////////////////////////////
class KB
{
public:
    static bool ManufacturerCheck(string str)
    {

    }

private:
    static unordered_map< string, vector<string> > map;
};


///////////////////////////////////////////////////////////////
// Class String Matcher
///////////////////////////////////////////////////////////////
template <typename FuncType>
class StringMatcher
{
public:
    StringMatcher()
    {
        ;
    }

    bool match(string str1, string str2)
    {
        return mMatcher(str1, str2);
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
    string operator()(string str, unordered_map<string, ListingManufacturer*> &map, bool opt = false)
    {
        // bool opt: reverses the look up, Single word first and whole phrase last.

        // Convert string to lower case
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        initString(str);

        unordered_map<string, ListingManufacturer *>::iterator mIter = map.end();

        if (!opt)
        {
            mIter = map.find(str);
        }

        while (mIter == map.end() && !isEnd())
        {
            // Try to find words in map
            string word = nextWord();
            mIter = map.find(word);
        }

        // Add to map
        if (mIter != map.end())
        {
            str = mIter->first;

            // Delete whole word match if single
            if (opt)
            {

            }
        }

        return str;
    }

private:
    string mTmpStr;
    int mIndex;

    // Find word in list.
    void initString(string str)
    {
        mIndex = 0;
        mTmpStr = str;
    }

    // Reset values;
    void resetString() { mIndex =0;}

    // Find next word;
    string nextWord()
    {
        int i = 0;
        string word = "";
        if (mIndex < mTmpStr.length())
        {
            i = mTmpStr.find(' ', mIndex);

            if (i == string::npos)
            {
                i = mTmpStr.length();
            }

            word = mTmpStr.substr(mIndex, i - mIndex);
            mIndex = i + 1;
        }

        return word;
    }

    // Check if end of string
    bool isEnd()
    {
        return mIndex >= mTmpStr.length();
    }

};


///////////////////////////////////////////////////////////////
// Functor: Manufacturer Matching
///////////////////////////////////////////////////////////////
class ProductMatcher
{
public:
    bool operator()(string str1, string str2)
    {
        return str1 == str2;
    }
};

#endif //SORTABLECHALLENGEREPO_STRINGMATCHER_H
