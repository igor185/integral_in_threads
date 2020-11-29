#!/bin/bash

cd release

cmake -DCMAKE_BUILD_TYPE=Release ..
make

./integral --csv --file ../configs/config1.txt > ../results/result1.csv
./integral --csv --file ../configs/config2.txt > ../results/result2.csv
./integral --csv --file ../configs/config3.txt > ../results/result3.csv
./integral --csv --file ../configs/config4.txt > ../results/result4.csv

cd ..
python vizualize.py

