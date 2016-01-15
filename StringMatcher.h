///////////////////////////////////////////////////////////////
// Created by Jeremy on 1/10/2016.
///////////////////////////////////////////////////////////////

#ifndef SORTABLECHALLENGEREPO_STRINGMATCHER_H
#define SORTABLECHALLENGEREPO_STRINGMATCHER_H

#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "ListingManufacturer.h"


using namespace std;

///////////////////////////////////////////////////////////////
// KB for Companies
///////////////////////////////////////////////////////////////
class KB
{
public:
    static unordered_map< string, vector<string> > manufacturerMap;
    static unordered_set<char> invalidCharMap;
    static unordered_set<string> ambiguousWordMap;
};

///////////////////////////////////////////////////////////////
// TOLower Functor
///////////////////////////////////////////////////////////////
class Normalize
{
public:
    // For use in STD algorithms
    char operator() (char c)
    {
        c = tolower(c);
        unordered_set<char>::iterator itr =  KB::invalidCharMap.find(c);
        if (itr != KB::invalidCharMap.end())
        {
            c = ' ';
        }

        return c;
    }

    // Process a string and perform normalization
    void processString(string &in_str)
    {
        for (int i = 0; i < in_str.length(); ++i)
        {
            char c = in_str[i];
            in_str[i] = tolower(c);

            unordered_set<char>::iterator itr =  KB::invalidCharMap.find(in_str[i]);
            if (itr != KB::invalidCharMap.end() || (int) c < 32)
            {
                in_str.erase(i, 1);
                --i;
            }

        }
    }
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
    string operator()(string str, unordered_map<string, ListingManufacturer*> &map)
    {
        // Convert string to lower case
        norm.processString(str);
        initString(str);

        unordered_map<string, ListingManufacturer *>::iterator mIter = map.find(str);

        while (mIter == map.end() && !isEnd())
        {
            // Try to find words in map
            string word = nextWord();

            // Check for ambiguous words. ie Digital, camera etc...
            unordered_set<string>::iterator sitr = KB::ambiguousWordMap.find(word);
            if (sitr != KB::ambiguousWordMap.end())
            {
                // Close the gap.
                str = eraseBeforeAtIndex(-1);
            }
            else
            {
                mIter = map.find(word);
            }
        }

        // Add to map
        if (mIter != map.end())
        {
            str = mIter->first;
        }

        return str;
    }

    // Optimize the map with word look-up
    void operator()(unordered_map<string, ListingManufacturer*>::iterator &in_cIter, unordered_map<string, ListingManufacturer*> &map, bool &isChanged)
    {
        string tmpName = in_cIter->first;
        if (tmpName == "" || tmpName == "camera")
        {
            // Unknown  manufacturer. Rehash all.
            in_cIter->second->resetDocumentItr();
            while (in_cIter->second->isValid())
            {
                tmpName = (*(in_cIter->second))["title"]->GetString();
                norm.processString(tmpName);
                initString(tmpName);

                // Iterate through each word
                unordered_map<string, ListingManufacturer *>::iterator itr = map.end();

                string word;
                while (itr == map.end() && !isEnd())
                {
                    // TODO: REMOVE TEMP.
                    word = nextWord();

                    unordered_set<string>::iterator sitr = KB::ambiguousWordMap.find(word);
                    if (sitr != KB::ambiguousWordMap.end())
                    {
                        // Close the gap.
                        eraseBeforeAtIndex(-1);
                    }
                    else
                    {
                        itr = map.find(word);
                    }
                }

                // If match, move document to new location
                
                if (itr != map.end() && *itr != *in_cIter)
                {
                    // Move iterates by one
                    itr->second->add(in_cIter->second->move());
                }
                else
                {
                    // Create new listing based on first word.
                    resetString();
                    string newManu = nextWord();

                    ListingManufacturer *el = new ListingManufacturer(newManu);
                    el->add(in_cIter->second->move());
                    map[newManu] = el;
                }
            }

            // Delete manufacturer if empty listing.
            if(in_cIter->second->isEmpty())
            {
                isChanged = true;
            }
        }
        else
        {
            // Valid String, can perform bulk move.
            initString(tmpName);

            // Iterate through each word
            unordered_map<string, ListingManufacturer *>::iterator itr = map.end();
            while (itr == map.end() && !isEnd())
            {
                // TODO: REMOVE TEMP.
                string tmp2 = nextWord();
                itr = map.find(tmp2);
            }

            // If candidate is found. Transfer all data from in_cIter to itr.
            if (itr != map.end() && *itr != *in_cIter)
            {
                itr->second->merge(in_cIter->second);
                isChanged = true;
            }
        }
    }

private:
    string mTmpStr;
    int mIndex;
    Normalize norm;

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

    // erase at and before index " "
    string eraseBeforeAtIndex(int offset, int len = 1)
    {
        bool resetStr = false;

        // Don't erase last char. 
        if (mIndex + offset < mTmpStr.length() - 1)
        {
            mTmpStr.erase(mIndex + offset, len);  
            resetStr = true;
        }

        // Find previous " " and erase
        int i = mTmpStr.rfind(' ', mIndex);
        if (i != string::npos)
        {
            mTmpStr.erase(i, 1);
            resetStr = true;
        }

        if (resetStr)
        {
            mIndex = 0;
        }

        return mTmpStr;
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
