#!/bin/bash
grep '\(INFO\|elapsed\)' "${1:--}" |awk '{print $1, $8, $6}' | tr '\n' ' ' | sed 's/INFO: /\n/g' | sed 's/ "/   \t/' | sed  's/" /\t/'
