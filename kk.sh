# averages for all 7 over the 50 trials
# each run is going to generate 7 numbers
# need to parse those 7 numbers and sum them for moving averages

declare -a residues=(0 0 0 0 0 0 0)

>results.txt
make kk
for i in {1..500}
do
    python generate_input.py "$i"
    arr=($(./kk input_$i.txt | sed 's/[^0-9]//g'))
    echo ${arr[@]} >> results.txt
    for j in {0..6}
    do
        residues[$j]=$((${residues[$j]}+${arr[$j]}))
    done
done
for j in {0..6}
do
    residues[$j]=$(echo "scale=2; ${residues[$j]}/50" | bc)
done
echo ${residues[@]}