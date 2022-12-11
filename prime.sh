echo "Enter the no. :"
read number
i=2
f=0
num=0

while test $i -le `expr $number / 2`
do

if test `expr $number % $i` -eq 0
then
f=1
fi

i=`expr $i + 1`
done
if test $f -eq 1
then
echo "Not prime"
else
echo "Prime"
fi

while [ $number -gt 0 ]
do
num=$(expr $num \* 10)
k=$(expr $number % 10)
num=$(expr $num + $k)
number=$(expr $number / 10)
done
echo number is $num