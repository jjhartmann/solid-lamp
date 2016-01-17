#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <ctime>

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


    // Benchmarking for optimised
    clock_t begin = clock();
    EResolution resolve(fileListing, fileProduct);
    clock_t end = clock();
    double optimised = double(end - begin);


    // Benchmarking for bruteforce
    begin = clock();
    EResolution bruteF;
    bruteF.bruteForceProcedure(fileListing, fileProduct);
    end = clock();
    double bruteforce = double(end - begin);


    resolve.writeJSON(resultpath);

    cout << "~Benchmarking~" << endl;
    cout << "Optimized Run Time (seconds):\t" << optimised/1000 << endl;
    cout << "Brute force Run Time (seconds):\t" << bruteforce/1000 << endl;
    cout << "Oprtimized/Brute Percentage:\t" << optimised / bruteforce << endl;

    return 0;
}