#!/bin/bash
[ -f stepnumbers.dat ] || wget https://pages.scinet.utoronto.ca/~rzon/stepnumbers.dat
[ -f morestepnumbers.dat ] || wget https://pages.scinet.utoronto.ca/~rzon/morestepnumbers.dat
touch stepnumbers.dat
touch morestepnumbers.dat
