#!/usr/bin/env bash

sed -n 's/^.*handler="\([^"]\{1,\}\)".*$/ITEM(\1)/p' $1/data/geany.glade | sort | uniq > $1/src/signallist.i