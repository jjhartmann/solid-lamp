///////////////////////////////////////////////////////////////
// Created by Jeremy on 1/10/2016.
///////////////////////////////////////////////////////////////

#ifndef SORTABLECHALLENGEREPO_LISTINGOBJECT_H
#define SORTABLECHALLENGEREPO_LISTINGOBJECT_H

#include <unordered_map>

#include "ListingManufacturer.h"
#include "StringMatcher.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

using namespace std;

template <class T>
class ListingObject
{
    // Constructor: Initialize the List Object
    //
    // IN: *in_matcher      Pointer to a matcher object for
    //                      discriminating against manufacturer
    //                      strings.
    ListingObject(StringMatcher<T> *in_matcher);
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
    unordered_map<ListingManufacturer*> mManufacturerList;
    StringMatcher<T> *mMMatcher; // OWN

};


#endif //SORTABLECHALLENGEREPO_LISTINGOBJECT_H
