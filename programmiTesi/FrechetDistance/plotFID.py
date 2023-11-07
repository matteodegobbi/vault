import os
import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict
dsizes=list()
FIDs=list()
labels=list()
colors=list()

colormap=plt.cm.get_cmap("hsv",10000)
for file in os.listdir(os.getcwd()):
    filename = os.fsdecode(file)
    if filename.endswith(".txt"): 
        infoPath=filename[0:-len(".txt")]
        f = open(f"../GAN_target/{infoPath}whitebox/infowhite.txt", "r")
        line = f.readline()
        infoEpochs = int(line[line.rindex(":")+1:])
        f.close()
        labels.append(infoEpochs)
        colors.append(colormap(infoEpochs))
        dsizes.append(float(filename[1:-len(".txt")]))
        FIDs.append(float(open(f'{filename}', "r").read()))
        #print(filename,": ",) 
print(dsizes)
#print(FIDs)
print(labels)
d = defaultdict(list)
for i, x in enumerate(labels):
    d[x].append(i)

print(list(d.values()))
print(len(dsizes))
fig=plt.subplot()
for indexlist in d:
    plt.scatter([dsizes[i] for i in d[indexlist]],[FIDs[i] for i in d[indexlist]],label=indexlist)
fig.legend(labels)
#for i, txt in enumerate(labels):
#    fig.annotate(txt, (dsizes[i], (FIDs[i])-0.2))
plt.title("Frechet's Inception Distance of generated datasets from original dataset")
plt.xlabel('dataset size')
plt.ylabel('FID')

handles,labels = plt.gca().get_legend_handles_labels()
labarray=(np.array(labels)).astype(int)
indexsorted=labarray.argsort()
plt.legend(np.array(handles)[indexsorted],labarray[indexsorted],loc='upper right', labelspacing=0.25, handlelength=0.4, handletextpad=0.7,title="epochs:")
plt.show()
plt.savefig("generated_original_FIDs.png")
