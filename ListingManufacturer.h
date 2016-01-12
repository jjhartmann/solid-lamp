///////////////////////////////////////////////////////////////
// Created by Jeremy on 1/10/2016.
///////////////////////////////////////////////////////////////

#ifndef SORTABLECHALLENGEREPO_LISTINGMANUFACTURER_H
#define SORTABLECHALLENGEREPO_LISTINGMANUFACTURER_H

#include <string>
#include <vector>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

using namespace std;

class ListingManufacturer
{
public:
    ListingManufacturer(string in_manName);
    ~ListingManufacturer();

    // Add the json object to the manufacturer
    //
    // IN: *in_d        JSON object to add. OWN
    void add(rapidjson::Document *in_d);

    // Retrieve the data from the current JSON object
    //
    // IN: in_memberName        THe name of the member to retrieve.
    rapidjson::Value& operator[] (string in_memberName);

    // Reset the Document iterator to zero
    void resetDocumentItr();

    // Increment the Listings iterator by one.
    void operator++ ();

    // Get the name of this manufacturer
    string getName();

private:
    // Private Variables
    string mManufacturerName;
    vector<rapidjson::Document*> mListings; // OWN

};


#endif //SORTABLECHALLENGEREPO_LISTINGMANUFACTURER_H
