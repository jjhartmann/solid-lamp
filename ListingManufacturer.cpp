///////////////////////////////////////////////////////////////
// Created by Jeremy on 1/10/2016.
///////////////////////////////////////////////////////////////

#include "ListingManufacturer.h"
#include "StringMatcher.h"

using namespace std;

ListingManufacturer::ListingManufacturer(string in_manName) :
    mMapItr(mMapListings.begin()),
    mManufacturerName(in_manName)
{

}

ListingManufacturer::~ListingManufacturer()
{

    for (unordered_map<string, string> *itm : mMapListings)
    {
        if (itm)
        {
            delete itm;
            itm = nullptr;
        }
    }
}

// Add the JSON object to the manufacturer
//
// IN: *in_d        JSON object to add. OWN
void ListingManufacturer::add(const rapidjson::Document &in_d)
{
    Normalize norm;
    unordered_map<string, string> *item = new unordered_map<string, string>(); // OWN
    for (rapidjson::Value::ConstMemberIterator itr = in_d.MemberBegin(); itr != in_d.MemberEnd(); itr++)
    {
        string key = itr->name.GetString();
        string val = itr->value.GetString();
        
        // Normalize the value. 
        if (key == "title" || key == "model" || key == "family")
            norm.processString(val);

        (*item)[key] = val;
    }

    mMapListings.push_back(item);
}


// Add a DocumentMap object to the manufacturer
//
// IN: *in_d        The parsed hash table. OWN.
void ListingManufacturer::add(DocumentMap *in_d)
{
    if (!in_d) return;
    mMapListings.push_back(in_d);
}

// Retrieve the data from the current JSON object
//
// IN: in_memberName        THe name of the member to retrieve.
string ListingManufacturer::operator[](const string in_memberName)
{
    unordered_map<string, string> item = **mMapItr;
    return item[in_memberName];
}

// Reset the Document iterator to zero
void ListingManufacturer::resetDocumentItr()
{
    mMapItr = mMapListings.begin();
}

// Increment the Document iterator by one.
void ListingManufacturer::operator++()
{
    ++mMapItr;
}

// Get the name of this manufacturer
string ListingManufacturer::getName()
{
    return mManufacturerName;
}

// Merge a listings with this
void ListingManufacturer::merge(ListingManufacturer *in_list)
{
    mMapListings.insert(mMapListings.end(), in_list->mMapListings.begin(), in_list->mMapListings.end());
    in_list->mMapListings.clear();
}


// Check to see if iterator is valid
bool ListingManufacturer::isValid()
{

    if (mMapItr != mMapListings.end())
    {
        return true;
    }

    return false;
}

// Get a copy of the current document;
DocumentMap ListingManufacturer::getCopy()
{
    return **mMapItr;
}

// Move the document pointer and delete location. Moves Iterator to next.
DocumentMap* ListingManufacturer::move()
{
    DocumentMap *tmp = *mMapItr;
    mMapItr = mMapListings.erase(mMapItr);
    return tmp;
}

bool ListingManufacturer::isEmpty()
{
    return mMapListings.empty();
}
