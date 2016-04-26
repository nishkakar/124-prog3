# averages for all 7 over the 50 trials
# each run is going to generate 7 numbers
# need to parse those 7 numbers and sum them for moving averages

>timings.txt
make kk
for i in {1..50}
do
    arr=($(./kk input_$i.txt | sed 's/[^0-9]//g'))
    echo ${arr[@]} >> timings.txt
done