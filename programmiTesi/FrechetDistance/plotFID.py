import os
import numpy as np
import matplotlib.pyplot as plt
    
dsizes=list()
FIDs=list()
labels=list()
for file in os.listdir(os.getcwd()):
     filename = os.fsdecode(file)
     if filename.endswith(".txt"): 
         labels.append(filename[0])
         dsizes.append(float(filename[1:-len(".txt")]))
         FIDs.append(float(open(f'{filename}', "r").read()))
         #print(filename,": ",) 

print(dsizes)
print(FIDs)

fig=plt.subplot()
plt.scatter(dsizes,np.log(FIDs))
for i, txt in enumerate(labels):
    fig.annotate(txt, (dsizes[i], np.log(FIDs[i])))

plt.show()
