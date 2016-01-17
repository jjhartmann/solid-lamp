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

    // Get JSON document and build store listings
    string jsonStr;
    Document d;
    while (getline(inListingFile, jsonStr))
    {
        d.Parse(jsonStr.c_str());
        mListing.add(d);
    }

    // invoke Store listings optimization and deduplication.
    mListing.optimize();

    // Get JSON document and build the product listings
    while (getline(inProductFile, jsonStr))
    {
        d.Parse(jsonStr.c_str());
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
                // Collect information from JSON object
                string pName = mProduct["product_name"];
                string model = mProduct["model"];
                string family = mProduct["family"];
                string manufacturer = mProduct.getManufacturerName();

                // Document to be used to build listing for product
                rapidjson::Document *d;
                rapidjson::Value a(kArrayType);

                // Iterator through the product listing for matches.
                do
                {
                    // Get the title from each listing and compare with product.
                    string title = mListing["title"];
                    bool res = matcher.match(title, model, manufacturer);

                    // If match, add to resolved
                    if(res)
                    {
                        // Allocate the document if not alread done so.
                        if (!d)
                        {
                            d = new Document();
                            d->SetObject();                               
                        }

                        a.PushBack(mListing.getJSONCopy(), d->GetAllocator());
                    }
                }
                while (++mListing); // Next listing in manufacturer group

                // Store documents in result vector
                if (!a.Empty()) 
                {
                    rapidjson::Value v(kStringType);
                    v = StringRef(pName.c_str(), pName.length());

                    d->AddMember("product_name", v, d->GetAllocator());
                    d->AddMember("listings", a, d->GetAllocator());

                    mResolved.push_back(d);

                }
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
    for (rapidjson::Document *d : mResolved)
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