#!/bin/bash

c=./main
mkdir hello{1..3}
$c add hello1
$c add hello2
$c add hello3
$c commit maBranche 