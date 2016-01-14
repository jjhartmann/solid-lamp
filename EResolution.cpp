///////////////////////////////////////////////////////////////
// Created by Jeremy on 1/10/2016.
///////////////////////////////////////////////////////////////

#include "EResolution.h"

#include <fstream>
#include <iostream>

using namespace std;
using namespace rapidjson;

// Builds and parses the product file into a data structure
//
// IN: in_path      takes a path to the product data file.
// IN: in_path      takes a path to the listings data file.
//
EResolution::EResolution(string in_ListingPath, string in_ProductPath)
{
    cout << in_ListingPath << endl;

    // Get and load the files into a buffer stream.
    ifstream inListingFile(in_ListingPath.c_str(), ifstream::in);
    ifstream inProductFile(in_ProductPath.c_str(), ifstream::in);

    if (!inListingFile) return;
    if (!inProductFile) return;

    // Get json document and build store listings
    string jsonStr;
    while (getline(inListingFile, jsonStr))
    {
        Document *d = new Document(); // DON'T OWN
        d->Parse(jsonStr.c_str());

        mListing.add(d);
    }

    // invoke Store listings optimization

    // Get json document and build the product listings
    while (getline(inProductFile, jsonStr))
    {
        Document *d = new Document(); // DON'T OWN
        d->Parse(jsonStr.c_str());

        mProduct.add(d);
    }

    // Initiate Entity Resolution.
    StringMatcher<ProductMatcher> matcher;

    mListing.resetManufacturerItr();
    mProduct.resetManufacturerItr();

    while (mProduct.isValid())
    {
        // Compare against the listings.
        if (mListing.findManufacturer(mProduct.getManufacturerName()))
        {
            do
            {
                // Collect information from json object
                Value *pName = mProduct["product_name"];
                Value *model = mProduct["model"];
                Value *family = mProduct["family"];

                // Document to be used to build listing for product
                Document d;
                d.SetObject();

                Value v(kStringType);
                v.SetString(pName->GetString(), pName->GetStringLength());

                d.AddMember("product_name", v, d.GetAllocator());

                Value a(kArrayType);

                // Iterator throught the product listing for matches.
                do
                {
                    // Get the title from each listing and compare with product.
                    Value *title = mListing["title"];
                    bool res = matcher.match(title->GetString(), model->GetString());

                    // If match, add to resolved
                    if(res)
                    {
                        a.PushBack(mListing.getCopy(), d.GetAllocator());
                    }
                }
                while (++mListing); // Next listing in manufacturer group
            }
            while (++mProduct); // next product in manufacturer group
        }

        // Go to the next manufacturer
        mProduct.nextManufacturer();
    }
}


// Deconstructor
EResolution::~EResolution()
{
    for (Document *d : mResolved)
    {
        if (d)
        {
            delete d;
        }
    }
}

// Write the entity resolution result to JSON format.
//
// IN: in_FileName      the filename of the docuemtn to write.
void EResolution::writeJSON()
{

}