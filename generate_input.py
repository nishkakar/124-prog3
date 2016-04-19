import random

def generate_inputs():
	num_ints = 100
	max_int = 10E12
	import argparse

	parser = argparse.ArgumentParser(description='Process some integers.')
	parser.add_argument('file_num', metavar='N', type=int,help='an integer for the accumulator')

	args = parser.parse_args()
	file_num = args.file_num

	f = open('input_' + str(file_num) + '.txt', 'w')
	
	for i in range(num_ints):
		r = random.randint(1,max_int)
		f.write(str(r) + '\n')

	f.close()



if __name__ == '__main__':
	generate_inputs()