# Information retrieval with NYC Yellow Taxi 2019 Trip Data
In this project we explore how a Binary Search Tree can be used as the underlying data structure for storing and retrieving information about New York City Yellow Taxi Trip Data, i.e. a dictionary. 

The data is provided by the New York City Taxi & Limousine Commission and can be found at: https://www1.nyc.gov/site/tlc/about/tlc-trip-record-data.page

`nyc_datafile_nh.txt` contains an abridged version of the December 2019 trip data, which is an example of a data file that may be used as input.

This implementation supports the following operations: `makedict` a new dictionary; `insert` a new item (key, value pair) into a dictionary; `search` for a key in the dictionary, and return the associated value.

The `tpep_pickup_datetime` field serves as the dictionary key, and the associated value is the data in the remaining fields. Hence, keys are not guaranteed to be unique - there are instances where multiple taxis pick up passengers at exactly the same day and time. Duplicate keys are handled by having a linked list for the associated items that share the same key.
## Programs 
This project is split into two separate programs:
* Dict1
* Dict2

Dict1 looks up records by their key, which the user of the program provides via `stdin`, retrieves the data/value and outputs the results to an output file specified as a command line argument.

Dict2 looks up records by their `PULocationID` value, which the user again provides via `stdin`, retrieves the associated key(s) that possess this field value and outputs the results to an output file specified as a command line argument.

Dict1 and Dict2 each take the following command line arguments:
* the name of the data file containing an unspecified number of taxi trip records, from which we build the dictionary
* the name of the output file, containing the data located in the searches

Dict1 and Dict2 each output the number of comparisons they make in their respective searches to `stdout`.
# Usage
To compile Dict1 and Dict2:
```bash
make
```
## Dict1 
To execute Dict1:
```bash
./dict1 datafile outputfile < keyfile
```

An example, which you can try with the example data provided in the repo, is:
```bash
./dict1 nyc_datafile_nh.txt outputfile < example_keyfile
```
## Dict2
To execute Dict2:
```bash
./dict2 datafile outputfile < idsfile
```

An example, which you can try with the example data provided in the repo, is:
```bash
./dict2 nyc_datafile_nh.txt outputfile < example_idsfile
```
## Cleaning
When you are finished, you can clean your directory of its ``.o`` files and executables, dict1 and dict2, with the following:
```bash
make clean
```
# License
[MIT](https://choosealicense.com/licenses/mit/)
