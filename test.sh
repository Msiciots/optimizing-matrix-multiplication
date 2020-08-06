#!/bin/sh

i=100
while [ $i != 0 ]
do
    # ./tradition input_data/test_data_2
    ./tradition input_data/test_data_3
	i=$(($i-1))   # 每次 i 都會增加 1 
	echo $i
done