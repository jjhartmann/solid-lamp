///////////////////////////////////////////////////////////////
// Created by Jeremy on 1/10/2016.
///////////////////////////////////////////////////////////////

#ifndef SORTABLECHALLENGEREPO_LISTINGOBJECT_H
#define SORTABLECHALLENGEREPO_LISTINGOBJECT_H

#include <unordered_map>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

#include "ListingManufacturer.h"
#include "StringMatcher.h"


using namespace std;
using namespace rapidjson;

template <class T>
class ListingObject
{
public:
    // Constructor: Initialize the List Object
    ListingObject();
    ~ListingObject();


    // Add a document file to the listings object.
    //
    // IN: *in_d         The json object to be added. DON'T OWN
    void add(const rapidjson::Document &in_d);

    // Invokes a rehashing of the list, performing deduplication.
    void optimize();

    // Reset the counter for the Manufacturer to start at zero.
    void resetManufacturerItr();

    // Iterate to the next manufacturer in the list.
    void nextManufacturer();

    // It returns true if mItr is at end.
    bool isValid();

    // Iterate to the next listing in the manufacturer;
    bool operator++ ();

    // Find the manufacturer and set iterator to point to it.
    bool findManufacturer(string in_mName);

    // Get the name of the current manufacturer.
    string getManufacturerName();

    // Returns the number of Manufacturers.
    int getManufacturerCount();

    // Get the value of a Member in the document
    //
    // IN: in_str           The name of the member to get.
    string operator[] (string str);

    // Get a copy of the current document
    DocumentMap getCopy();

    // Get a copy of the current document and convert to JSON format. 
    rapidjson::Document getJSONCopy(rapidjson::Document* in_d);


private:
    // Private Variables
    unordered_map<string, ListingManufacturer*> mManufacturerList;
    unordered_map<string, ListingManufacturer*>::iterator mItr;
    T *mMMatcher; // OWN
};

///////////////////////////////////////////////////////////////////////
// Impl: ListObject
///////////////////////////////////////////////////////////////////////
template <class T>
ListingObject<T>::ListingObject() :
        mMMatcher(new T()),
        mItr(mManufacturerList.begin())
{ }


///////////////////////////////////////////////////////////////////////
template <class T>
ListingObject<T>::~ListingObject()
{
    if (mMMatcher)
    {
        delete mMMatcher;
    }

    for (auto &itr : mManufacturerList)
    {
        delete itr.second;
    }
}


///////////////////////////////////////////////////////////////////////
template <class T>
void ListingObject<T>::add(const rapidjson::Document &in_d)
{
    // Determine what manufacturer the document is and place in container
    const Value& v = in_d["manufacturer"];
    string res = (*mMMatcher)(v.GetString(), mManufacturerList);

    ListingManufacturer *manufacturer = mManufacturerList[res];

    if (res == "" || res == "camera")
    {
        int x = 0;
        x += 5;
    }

    if (!manufacturer)
    {
        manufacturer = new ListingManufacturer(res);
        mManufacturerList[res] = manufacturer;
    }

    manufacturer->add(in_d);
}


///////////////////////////////////////////////////////////////////////
template <class T>
void ListingObject<T>::optimize()
{
    // Iterator through the entire mManufacturerList and perform deduplication.
    unordered_map<string, ListingManufacturer*>::iterator itr = mManufacturerList.begin();
    while (itr != mManufacturerList.end())
    {
        bool del = false;
        (*mMMatcher)(itr, mManufacturerList, del);

        if (del)
        {
            // If the manufacturer List is empty or moved. Delete.
            delete itr->second;
            itr = mManufacturerList.erase(itr);
        }
        else
        {
            ++itr;
        }
    }

    unordered_set<string>::iterator kbitr = KB::invalidWordMap.begin();
    while (kbitr != KB::invalidWordMap.end())
    {
        bool del = false;

        itr = mManufacturerList.find(*kbitr);
        
        if (itr != mManufacturerList.end())
            mMMatcher->removeInvalids(itr, mManufacturerList, del);

        if (del)
        {
            // If the manufacturer List is empty or moved. Delete.
            delete itr->second;
            mManufacturerList.erase(itr);
        }


        ++kbitr;
    }
}


///////////////////////////////////////////////////////////////////////
template <class T>
void ListingObject<T>::resetManufacturerItr()
{
    mItr = mManufacturerList.begin();

    if (mItr != mManufacturerList.end())
    {
        mItr->second->resetDocumentItr();
    }
}


///////////////////////////////////////////////////////////////////////
template <class T>
bool ListingObject<T>::isValid()
{
    return mItr != mManufacturerList.end();
}


///////////////////////////////////////////////////////////////////////
template <class T>
void ListingObject<T>::nextManufacturer()
{
    mItr++;

    if (mItr != mManufacturerList.end())
    {
        mItr->second->resetDocumentItr();
    }
}


///////////////////////////////////////////////////////////////////////
template <class T>
bool ListingObject<T>::operator++ ()
{
    ++(*(mItr->second));

    if ((mItr->second)->isValid())
    {
        return true;
    }

    // If Listing Manufacturer is in invalid state, reset.
    (mItr->second)->resetDocumentItr();
    return false;
}


///////////////////////////////////////////////////////////////////////
template <class T>
bool ListingObject<T>::findManufacturer(string in_mName)
{
    mItr = mManufacturerList.find(in_mName);

    if (mItr != mManufacturerList.end())
    {
        (mItr->second)->resetDocumentItr();
        return true;
    }

    return false;
}


///////////////////////////////////////////////////////////////////////
template <class T>
string ListingObject<T>::getManufacturerName()
{
    return mItr->first;
}


///////////////////////////////////////////////////////////////////////
template <class T>
int ListingObject<T>::getManufacturerCount()
{
    return mManufacturerList.size();
}


///////////////////////////////////////////////////////////////////////
template <class T>
string ListingObject<T>::operator[] (string str)
{
    return (*(mItr->second))[str];
}


///////////////////////////////////////////////////////////////////////
template <class T>
DocumentMap ListingObject<T>::getCopy()
{
    return (mItr->second)->getCopy();
}

///////////////////////////////////////////////////////////////////////
template <class T>
rapidjson::Document ListingObject<T>::getJSONCopy(rapidjson::Document* in_d)
{
    // JSON Container
    rapidjson::Document out_d;
    out_d.SetObject();

    DocumentMap d = mItr->second->getCopy();
    for (DocumentMap::iterator itr = d.begin(); itr != d.end(); ++itr)
    {
        string key = itr->first;
        string val = itr->second;

        // Only want the const_title, unaltered. 
        if (key == "title")
            continue;

        // Change const_title, back to title.
        if (key == "const_title")
            key = "title";

        Value v(val.c_str(), in_d->GetAllocator());
        Value k(key.c_str(), in_d->GetAllocator());
        out_d.AddMember(k, v, in_d->GetAllocator());
    }

    return out_d;
}


#endif //SORTABLECHALLENGEREPO_LISTINGOBJECT_H
