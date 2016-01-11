///////////////////////////////////////////////////////////////
// Created by Jeremy on 1/10/2016.
///////////////////////////////////////////////////////////////

#ifndef SORTABLECHALLENGEREPO_ERESOLUTION_H
#define SORTABLECHALLENGEREPO_ERESOLUTION_H

#include <string>

class Document;
class ListingObject;
class StringMatcher;

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

    // Write the entity resolution result to JSON format.
    //
    // IN: in_FileName      the filename of the docuemtn to write.
    void writeJSON();

private:
    Document *mResolved; // OWN
    ListingObject *mListing; // OWN
    ListingObject *mProduct; // OWN
    StringMatcher *mMatcher; // OWN
};


#endif //SORTABLECHALLENGEREPO_ERESOLUTION_H
