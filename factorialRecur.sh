echo "Enter a number"
read num
factorial=1
for((i=2;i<=num;i++)){
  factorial=$((factorial * i))
}
echo $factorial