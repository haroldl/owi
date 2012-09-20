#!/bin/bash

cd $(dirname $0)
make && (setxkbmap us ; ./owi ; setxkbmap dvorak)
