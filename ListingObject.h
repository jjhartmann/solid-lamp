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
    void add(rapidjson::Document *in_d);

    // Reset the counter for the Manufacturer to start at zero.
    void resetManufacturerItr();

    // Iterate to the next manufacturer in the list.
    void nextManufacturer();

    // Iterate to the next listing;
    void operator++ ();

    // Get the name of the current manufacturer.
    string getManufacturerName();

    // Returns the number of Manufacturers.
    int getManufacturerCount();

    // Get the value of a Member in the document
    //
    // IN: in_str           The name of the member to get.
    rapidjson::Value& operator[] (string str);


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
}


///////////////////////////////////////////////////////////////////////
template <class T>
void ListingObject<T>::add(rapidjson::Document *in_d)
{
    // Determine what manufacturer the document is and place in container
    Value& v = (*in_d)["manufacturer"];
    string res = (*mMMatcher)(v.GetString());

    ListingManufacturer *manufacturer = mManufacturerList[res];

    if (!manufacturer)
    {
        manufacturer = new ListingManufacturer(res);
        mManufacturerList[res] = manufacturer;
    }

    manufacturer->add(in_d);
}


///////////////////////////////////////////////////////////////////////
template <class T>
void ListingObject<T>::resetManufacturerItr()
{
    mItr = mManufacturerList.begin();
}


///////////////////////////////////////////////////////////////////////
template <class T>
void ListingObject<T>::nextManufacturer()
{
    mItr++;
}


///////////////////////////////////////////////////////////////////////
template <class T>
void ListingObject<T>::operator++ ()
{
    mItr->second++;
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
rapidjson::Value& ListingObject<T>::operator[] (string str)
{
    return (*(mItr->second))[str];
}

#endif //SORTABLECHALLENGEREPO_LISTINGOBJECT_H
