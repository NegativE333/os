echo "Enter 1st string: "
read s

echo "Enter 2nd string: "
read t

count=0
l=${#s}
let l--
for i in $(seq 0 $l)
do
    v=$i
    for j in $(seq $v $l)
    do
        c=$c${s:$j:1}

        if [ $c = "" ];
        then
            break
        fi
        if [ $c = $t ];
        then

            let count++

        fi
    done
    c=""
done

echo $count