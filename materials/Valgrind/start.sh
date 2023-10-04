#!/bin/bash

cd s21_cal
pwd
ls
make check_valg
#valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test