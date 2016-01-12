///////////////////////////////////////////////////////////////
// Created by Jeremy on 1/10/2016.
///////////////////////////////////////////////////////////////

#include "EResolution.h"

// Builds and parses the product file into a data structure
//
// IN: in_path      takes a path to the product data file.
// IN: in_path      takes a path to the listings data file.
//
EResolution::EResolution(string in_ListingPath, string in_ProductPath) :
    mListing(new StringMatcher<ManufacturerMatcher>()),
    mProduct(new StringMatcher<ManufacturerMatcher>())
{

}


// Write the entity resolution result to JSON format.
//
// IN: in_FileName      the filename of the docuemtn to write.
void EResolution::writeJSON()
{

}