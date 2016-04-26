import numpy as np

names = ['KK', 'RR1', 'HC1', 'SA1', 'RR2', 'HC2', 'SA2']
f = open('results.txt')
lines = f.readlines()
arr = [[],[],[],[],[],[],[]]
for line in lines:
	new_arr = line.split(' ')
	new_arr = [int(a.replace('\n', '')) for a in new_arr]
	for i in range(len(new_arr)):
		arr[i].append(new_arr[i])
means = []
for arr1 in arr:
	means.append(np.mean(arr1))
for ix,mean in enumerate(means):
	print "%s:%d" % (names[ix], int(mean))

# import matplotlib.pyplot as plt
# %matplotlib inline

# plt.boxplot(arr)
# plt.xticks([1,2,3,4,5,6,7], names)
# plt.show()

# new_means = [a for a in means if means.index(a) != 2]
# new_names = ['KK', 'RR1', 'SA1', 'RR2', 'HC2', 'SA2']
# plt.bar([1,2,3,4,5,6], new_means, align='center')
# plt.xticks([1,2,3,4,5,6], new_names)
# plt.show()