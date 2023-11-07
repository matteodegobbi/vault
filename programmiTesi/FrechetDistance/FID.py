import numpy as np
from numpy import cov
from numpy import trace
from numpy import iscomplexobj
from numpy import asarray
from numpy.random import randint
from scipy.linalg import sqrtm
from keras.applications.inception_v3 import InceptionV3
from keras.applications.inception_v3 import preprocess_input
import tensorflow as tf
import skimage.transform
import sys 

def calculate_fid(model, images1, images2):
    # calculate activations
    act1 = model.predict(images1)
    act2 = model.predict(images2)
    # calculate mean and covariance statistics
    mu1, sigma1 = act1.mean(axis=0), cov(act1, rowvar=False)
    mu2, sigma2 = act2.mean(axis=0), cov(act2, rowvar=False)
    # calculate sum squared difference between means
    ssdiff = np.sum((mu1 - mu2)**2.0)
    # calculate sqrt of product between cov
    covmean = sqrtm(sigma1.dot(sigma2))
    # check and correct imaginary numbers from sqrt
    if iscomplexobj(covmean):
        covmean = covmean.real
    # calculate score
    fid = ssdiff + trace(sigma1 + sigma2 - 2.0 * covmean)
    return fid


CODICE_RUN = sys.argv[1] 
generated_images_path = f"/home/fogliodicarta/Desktop/vault/programmiTesi/GAN_target/{CODICE_RUN}whitebox/generated"
ds=tf.keras.utils.image_dataset_from_directory(generated_images_path,color_mode="grayscale",label_mode=None,batch_size=1,image_size=(28,28))
iteratorDS=ds.as_numpy_iterator()
generated=np.fromiter(iteratorDS,np.dtype("(28,28,1)f4"))
#print(generated.shape)
(train_images, train_labels), (test_images, test_labels) = tf.keras.datasets.mnist.load_data()
train_images = train_images.reshape(-1, 28, 28, 1).astype('float32')
original=train_images[0:20000,:]
#print(original.shape)
originalScaled = np.ndarray(shape=(20000,75,75,1))
i=0
for im in original:
    kwargs = dict(output_shape=(75,75,1), mode='edge', order=1, preserve_range=True)
    originalScaled[i]= skimage.transform.resize(im, **kwargs).astype(im.dtype)
    #print(im.shape)
    i+=1

generatedScaled= np.ndarray(shape=(20000,75,75,1))
i=0
for im in generated:
    kwargs = dict(output_shape=(75,75,1), mode='edge', order=1, preserve_range=True)
    generatedScaled[i]= skimage.transform.resize(im, **kwargs).astype(im.dtype)
    #print(im.shape)
    i+=1
originalScaled=np.repeat(originalScaled[...], 3, -1)
generatedScaled=np.repeat(generatedScaled[...], 3, -1)
model = InceptionV3(include_top=False, pooling='avg', input_shape=(75,75,3))

#print(originalScaled.shape)
#print("######################################################")
fid_original_generated = calculate_fid(model,originalScaled,generatedScaled)

f = open(f"{CODICE_RUN}.txt", "w")
f.write(f"{fid_original_generated}")
f.close()
