# solid-lamp
A brute force implementation of an entity resolution algorithm for Sortable.
Fun to compare the optimized versus the brute force. 

Results: 
Input: products.txt
* ~800 json objects. 
Input: listings.txt
* ~20,000 json objects. 

OS: Ubuntu
* Optimized Version:    ~1000ms
* Brute Force Version:  ~15000ms

Percentage: Opt/Brute
* 6.6%
* 15 times more effiecent!

To build:
```
* cd to/the/head/dir/of/solid-lamp
* cmake .
* make
```
Then just run the executable file SortableChallengeRepo. 
The result file will be in the ./data/ directory. 

