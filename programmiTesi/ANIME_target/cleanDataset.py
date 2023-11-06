from PIL import Image
import os


i=0
for filename in os.listdir('animeFaces'):
    img = Image.open("animeFaces/"+filename)
    if img.size[0] < 64: #filename.endswith('.jpg'):
        print((img.size))
        os.remove("animeFaces/"+filename)
        i+=1
print(f"we have deleted {i} files")

'''
filename = os.path.join('')
img = Image.open(filename)
print img.size'''
