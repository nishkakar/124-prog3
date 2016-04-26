# generates 50 random inputs and passes them in as paramaters to the main() in kk.c, and outputs results to results.txt

>results.txt
make kk
for i in {1..50}
do
    python generate_input.py "$i"
    arr=($(./kk input_$i.txt | sed 's/[^0-9]//g'))
    echo ${arr[@]} >> results.txt
done