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
    string resultpath = "./data/results.txt";
    char answer = 'y';
    cout << "Entity Resolution Algorithm (v1.0)" << endl;
    cout << "Would you like to use the default file paths? (Y/n) : ";
    cin >> answer;

    answer = towlower(answer);
    if (answer != 'y')
    {
        cout << "Enter product reference path (.txt):\t";
        cin >> fileProduct;

        cout << "Enter store listings path (.txt):\t";
        cin >> fileListing;

        cout << "Enter the desired output result path (.txt):\t";
        cin >> resultpath;
    }

    cout << "Product list input path:\t" << fileProduct << endl;
    cout << "Store listings input path:\t" << fileListing << endl;
    cout << "Output file path:\t" << resultpath << endl;
    cout << "Begin..." << endl;

    EResolution resolve(fileListing, fileProduct);

    cout << "Writing output file." << endl;
    resolve.writeJSON(resultpath);

    cout << "...End." << endl;
    return 0;
}