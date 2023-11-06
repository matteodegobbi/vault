from PIL import Image
import os
import shutil 
i=0
for filename in os.listdir('animeFaces'):
    img = Image.open("animeFaces/"+filename)
    if i%5==0: #filename.endswith('.jpg'):
        shutil.copy2("animeFaces/"+filename,"testAnime")
    else:
        shutil.copy2("animeFaces/"+filename,"trainAnime")
    i+=1
print(f"we have deleted {i} files")
