#!/bin/sh
echo "enter max no."
read n
#taking input from user
echo "enter the elements in array:"
for ((i = 0; i<$n; i++))
do
read nos[$i]
done
#printing the no. before sorting
echo "Numbers in array are: "
for ((i = 0; i<$n; i++))
do
echo ${nos[$i]}
done
#now do the sorting of numbers
for ((i=0; i<$n; i++))
do
for ((j = $i; j<$n; j++))
do
if [ ${nos[$i]} -gt ${nos[$j]} ]; then
t=${nos[$i]}
nos[$i]=${nos[$j]}
nos[$j]=$t
fi
done
done
#printing the sorted array
echo -e "\n Sorted Numbers "
for ((i = 0; i<$n; i++))
do
echo ${nos[$i]}
done