#!/bin/env sh
for asdf in $(find _store/LabelEx/)
do
	printf "%s\n" $asdf
	hxconv $asdf /dev/null -o obj >$asdf.txt
done
