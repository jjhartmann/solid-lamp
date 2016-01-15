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
    rapidjson::Value* operator[] (const string in_memberName);

    // Reset the Document iterator to zero
    void resetDocumentItr();

    // Increment the Document iterator by one.
    void operator++ ();

    // Check to see if iterator is valid
    bool isValid();

    // Get the name of this manufacturer
    string getName();

    // Merge a listings this this.
    void merge(ListingManufacturer *in_list);

    // Return a copy of the current docuement
    rapidjson::Document getCopy();

private:
    // Private Variables
    string mManufacturerName;
    vector<rapidjson::Document*> mListings; // OWN
    vector<rapidjson::Document*>::iterator mItr;

};


#endif //SORTABLECHALLENGEREPO_LISTINGMANUFACTURER_H
