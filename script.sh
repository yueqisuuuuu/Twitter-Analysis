#!/bin/bash

# remove tweet.txt if exists before starting
if test -r tweet.txt
  then rm tweet.txt
fi

# running tweeter hashtag
python tweetering.py $1  > log.txt &

# if user inputs "Time to Die", wait and kill
if [ $# -eq 2 ]
then
(sleep $(( $2 + 1 )); echo Program Terminated!; ./kill.sh;) &
fi

# checking new tweets per minute
count=1

while [ 1 -eq 1 ]
do
  sleep 10
  temp=$(cat log.txt | grep -Ev "^RT" | wc -l)
  new=$(($temp-$count))
  count=$temp
  echo $new >> tweet.txt
  if [ $new -ge 100 -a $new -lt 200 ]
    then
    echo Warning: High number of tweets being observed
  fi
  if [ $new -ge 200 ]
    then
    echo Attention: Very high number of tweets being observed!!!
  fi
done

