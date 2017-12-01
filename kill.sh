#!/bin/bash

# kill script.sh & tweetering.py

for pid in $(ps | awk '{if(($4~/\/bin\/bash/) || ($4~/python/)) print $1}')
do
  kill -9 $pid
done

