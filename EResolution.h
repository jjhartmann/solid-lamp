///////////////////////////////////////////////////////////////
// Created by Jeremy on 1/10/2016.
///////////////////////////////////////////////////////////////

#ifndef SORTABLECHALLENGEREPO_ERESOLUTION_H
#define SORTABLECHALLENGEREPO_ERESOLUTION_H

#include <string>
#include <vector>

#include "ListingObject.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

#include "StringMatcher.h"
#include "ListingObject.h"

using namespace std;

class EResolution
{
public:
    // Builds and parses the product file into a data structure
    //
    // IN: in_path      takes a path to the product data file.
    // IN: in_path      takes a path to the listings data file.
    //
    EResolution(string in_ListingPath, string in_ProductPath);

    ~EResolution();

    // Write the entity resolution result to JSON format.
    //
    // IN: in_FileName      the filename of the document to write.
    void writeJSON(string in_path = "./data/results.txt");

private:
    vector<rapidjson::Document*> mResolved; // OWN
    ListingObject<ManufacturerMatcher> mListing;
    ListingObject<ManufacturerMatcher> mProduct;
};


#endif //SORTABLECHALLENGEREPO_ERESOLUTION_H
