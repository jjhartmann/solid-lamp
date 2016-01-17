#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

#include "EResolution.h"

using namespace rapidjson;
using namespace std;

int main() {
    string fileProduct = "./data/products.txt";
    string fileListing = "./data/listings.txt";


    EResolution resolve(fileListing, fileProduct);

    resolve.writeJSON();

    return 0;
}