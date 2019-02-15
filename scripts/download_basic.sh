#! /bin/bash

if [ $# -eq 0 ]
then

  echo "2Cap parametre introduit"

  exit
fi
#grep -m 1 "yt-lockup-content" | tr ">" "\n" |
SEARCH=$(echo $@ | tr " " "+")
#echo $SEARCH grep -m 1 "yt-lockup-content"
wget -O html --no-check-certificate "https://www.youtube.com/results?search_query=$SEARCH"

awk '/yt-lockup-content/{i++}i==1' html | tr ">" "\n" | grep  "/watch?" | tr '"' "\n" | grep -m 2 -A 1 -e "title" -e "href" | grep -v -e "--" -e "title" -e "href"  > current

TITLE=$(cat current | tail -n 1)
#  LINK="https://www.easy-youtube-mp3.com/download.php?v=$(cat current | grep "/watch?" | tr "=" "\n" | tail -n 1)"


echo "2TITLE: $TITLE"




wget -O html --no-check-certificate "https://www.easy-youtube-mp3.com/download.php?v=$(cat current | grep "/watch?" | tr "=" "\n" | tail -n 1)"

echo "2SONG: $(cat html | grep "youtubemp3api.com/@download/" | tr "\"" "\n" | grep ".mp3")"




rm current html
