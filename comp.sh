#!/bin/bash

gcc main.c libftprintf.a -g
./resources/filler_vm -f resources/maps/map00 -p1 resources/players/abanlin.filler -p2 ~/filler/a.out
