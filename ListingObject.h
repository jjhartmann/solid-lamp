///////////////////////////////////////////////////////////////
// Created by Jeremy on 1/10/2016.
///////////////////////////////////////////////////////////////

#ifndef SORTABLECHALLENGEREPO_LISTINGOBJECT_H
#define SORTABLECHALLENGEREPO_LISTINGOBJECT_H

#include <unordered_set>

#include "ListingManufacturer.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

using namespace std;

class ListingObject
{
    ListingObject();
    ~ListingObject();


    // Add a document file to the listings object.
    //
    // IN: in_d         The json object to be added.
    void add(rapidjson::Document in_d);

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
    unordered_set<ListingManufacturer*> mManufacturerList;


};


#endif //SORTABLECHALLENGEREPO_LISTINGOBJECT_H
