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
    static unordered_set<string> invalidWordMap;
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

    ////////////////////////////////////////////////////////////////////////////////
    // Process a string and perform normalization
    void processString(string &in_str, const bool in_removeInt = false)
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

            // Remove numbers. 
            if (in_removeInt && c <=57 & c >=48)
            {
                in_str.erase(i, 1);
                --i;
            }
        }
    }
};

class ParseString
{
public:
    ParseString() {}

    ////////////////////////////////////////////////////////////////////////////////
    // Find word in list.
    ParseString(string str)
    {
        mIndex = 0;
        mTmpStr = str;
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Reset values;
    void resetString(string str = "") 
    { 
        mIndex = 0; 
        if (!str.empty())
        {
             mTmpStr = str;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////
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

    ////////////////////////////////////////////////////////////////////////////////
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

private:
    string mTmpStr;
    int mIndex;

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

    bool match(string in_str1, string in_str2, string in_str3)
    {
        return mMatcher(in_str1, in_str2, in_str3);
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

    ////////////////////////////////////////////////////////////////////////////////
    // Using a KB, look up and match against known manufacturers.
    string operator()(string str, unordered_map<string, ListingManufacturer*> &map)
    {
        // Convert string to lower case
        norm.processString(str, true);
        mString.resetString(str);

        unordered_map<string, ListingManufacturer *>::iterator mIter = map.find(str);

        while (mIter == map.end() && !mString.isEnd())
        {
            // Try to find words in map
            string word = mString.nextWord();

            // Check for ambiguous words. ie Digital, camera etc...
            unordered_set<string>::iterator sitr = KB::ambiguousWordMap.find(word);
            if (sitr != KB::ambiguousWordMap.end())
            {
                // Close the gap.
                str = mString.eraseBeforeAtIndex(-1);
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

    ////////////////////////////////////////////////////////////////////////////////
    // Optimize the map with word look-up, deduplication.
    void operator()(unordered_map<string, ListingManufacturer*>::iterator &in_cIter, 
                    unordered_map<string, ListingManufacturer*> &map,
                    bool &isChanged)
    {
        string tmpName = in_cIter->first;

        // Valid String, can perform bulk move.
        mString.resetString(tmpName);

        // Iterate through each word
        unordered_map<string, ListingManufacturer *>::iterator itr = map.end();
        while (itr == map.end() && !mString.isEnd())
        {
            // Get next word and find in the map
            itr = map.find(mString.nextWord());
        }

        // If candidate is found. Transfer all data from in_cIter to itr.
        if (itr != map.end() && *itr != *in_cIter)
        {
            itr->second->merge(in_cIter->second);
            isChanged = true;
        }
    }


    ////////////////////////////////////////////////////////////////////////////////
    // Optimize For Invalid Words. 
    void removeInvalids(unordered_map<string, ListingManufacturer*>::iterator &in_cIter,
        unordered_map<string, ListingManufacturer*> &map,
        bool &isChanged)
    {
        string tmpName = in_cIter->first;

        // Unknown  manufacturer. Rehash all.
        in_cIter->second->resetDocumentItr();
        while (in_cIter->second->isValid())
        {
            tmpName = (*(in_cIter->second))["title"];
            norm.processString(tmpName);
            mString.resetString(tmpName);

            // Iterate through each word
            unordered_map<string, ListingManufacturer *>::iterator itr = map.end();

            string word;
            while (itr == map.end() && !mString.isEnd())
            {
                // Get next word and find in maps
                word = mString.nextWord();

                unordered_set<string>::iterator sitr = KB::ambiguousWordMap.find(word);
                if (sitr != KB::ambiguousWordMap.end())
                {
                    // Close the gap.
                    mString.eraseBeforeAtIndex(-1);
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
                mString.resetString();
                string newManu = mString.nextWord();

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

private:
    Normalize norm;
    ParseString mString;
};


///////////////////////////////////////////////////////////////
// Functor: Manufacturer Matching
///////////////////////////////////////////////////////////////
class ProductMatcher
{
public:
    bool operator()(string title, string model, string manufacturer)
    {
        // Find the vector in the manufacturer key map. 
        int index = title.find(model, 0);
        return index != string::npos;
    }
};

#endif //SORTABLECHALLENGEREPO_STRINGMATCHER_H
