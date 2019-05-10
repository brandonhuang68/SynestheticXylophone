from PIL import Image
import numpy as np
from matplotlib import pyplot as plt
from scipy import misc
import io
# img = Image.open('cat.bmp')
# arr = np.array(img)
# h,w,l = np.shape(arr)
# print(h,w,l)
# plt.imshow(arr)
# plt.show()

# ###################  OR  ############################
# arr = misc.imread('cat.bmp')
# h,w,l = np.shape(arr)
# print(h,w,l)
# plt.imshow(arr)
# plt.show()

fileIN = 'rainbow.jpg'
# pathSD = 'E:/'
fileOut = 'inter.txt'
numNotes2Play = 24

arr = misc.imread(fileIN)
arr = np.array(arr)
# h,w,l = np.shape(arr)
# print(h,w,l)
# plt.imshow(arr)
# plt.show()

notes = ['H','B','A','G','F','E','D','C']
n = int(256/len(notes))
#convert 0-255 to corresponding index in list notes
R = arr[:,:,0].flatten()
G = arr[:,:,1].flatten()
B = arr[:,:,2].flatten()

R_short = []
G_short = []
B_short = []

l = np.prod(np.shape(R))
stride = int(np.floor(l/numNotes2Play))
for i in range(numNotes2Play):
	if i == numNotes2Play:
		R_short.append(np.mean(R[stride*i:]))
		G_short.append(np.mean(G[stride*i:]))
		B_short.append(np.mean(B[stride*i:]))
	else:
		R_short.append(np.mean(R[stride*i:stride*(i+1)]))
		G_short.append(np.mean(G[stride*i:stride*(i+1)]))
		B_short.append(np.mean(B[stride*i:stride*(i+1)]))

R_short = np.array(R_short)//n
G_short = np.array(G_short)//n
B_short = np.array(B_short)//n

# turn index into actual string notes
def toNote(a):
	return [notes[int(i)] for i in a]

# turn each layer into column vectors
r = np.array(toNote(R_short)).flatten().reshape(-1,1)
g = np.array(toNote(G_short)).flatten().reshape(-1,1)
b = np.array(toNote(B_short)).flatten().reshape(-1,1)

# stack them so each row has 3 columns corresponding to r, g, b
# number of rows = total number of pixels in the image
T = np.hstack((np.hstack((r,g)),b))
# make matrix into a 1D array... rgbrgb...
t = T.flatten()

def writeSD(t, toSD):
	# content = ''
	if toSD:
		f = open(pathSD+fileOut,'w')
	else:
		f = open(fileOut,'w')

	for i in range(int(len(t)/3)):
		#overwrites contents
		f.write(t[3*i] + t[3*i+1] + t[3*i+2] +'\n')

	f.close()

writeSD(t, False)