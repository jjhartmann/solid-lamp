///////////////////////////////////////////////////////////////
// Created by Jeremy on 1/10/2016.
///////////////////////////////////////////////////////////////

#include "ListingManufacturer.h"

using namespace std;

ListingManufacturer::ListingManufacturer(string in_manName) :
    mItr(mListings.begin()),
    mManufacturerName(in_manName)
{

}

ListingManufacturer::~ListingManufacturer()
{
    for (rapidjson::Document *d : mListings)
    {
        if (d)
        {
            delete d;
        }
    }
}

// Add the json object to the manufacturer
//
// IN: *in_d        JSON object to add. OWN
void ListingManufacturer::add(rapidjson::Document *in_d)
{
    mListings.push_back(in_d);
}

// Retrieve the data from the current JSON object
//
// IN: in_memberName        THe name of the member to retrieve.
rapidjson::Value* ListingManufacturer::operator[](const string in_memberName)
{
    rapidjson::Document *d =  (*mItr);

    if (d->HasMember(in_memberName.c_str()))
    {
        return &(*d)[in_memberName.c_str()];
    }

    return nullptr;

}

// Reset the Document iterator to zero
void ListingManufacturer::resetDocumentItr()
{
    mItr = mListings.begin();
}

// Increment the Document iterator by one.
void ListingManufacturer::operator++()
{
    ++mItr;
}

// Get the name of this manufacturer
string ListingManufacturer::getName()
{
    return mManufacturerName;
}

// Check to see if iterator is valid
bool ListingManufacturer::isValid()
{
    if (mItr != mListings.end())
    {
        return true;
    }

    return false;
}
