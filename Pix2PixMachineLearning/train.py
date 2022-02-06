import os
import numpy as np
import matplotlib.pyplot as plt
import imageio
import shutil
import torchvision
import torch
from shutil import move
from pathlib import Path
from PIL import Image as PIL
import subprocess
import cv2

#Sets the current location as the root path.
root = Path(os.getcwd())
root = str(root)
os.chdir(root)

#Change these to determine whether or not to perform specific functions.
oversaturation_setting = True
oversaturation_threshold = 3500000
misorder_setting = True
misorder_threshold = 7000
automatic_histogram_setting = "Augmentation"
zero_check_setting = True
blur_type = False

#Creates a custom error.
class DtypeException(Exception):
    pass

#Takes the given source_folder and begins to send the tiff files to the ImageConvert() Function.    
def FolderConvert(source_folder):
    os.chdir(source_folder)
    source_folder_list = sorted(os.listdir(source_folder))
    source_folder_range = range(len(source_folder_list))
    for i in source_folder_range:
        unconverted_tiff = source_folder_list[i].rstrip('.tif')
        dtype = None        
        try:
            ImageConvert(unconverted_tiff)
        #Tries to locate the error if the conversion failed.
        except DtypeException as dtype:
            if dtype != None:
                print("Error: The file " + unconverted_tiff + " is in " + dtype + " dtype. The current version of this program only supports uint8 and uint16. It will be skipped.")
            else:            
                print("Error: The file "+ unconverted_tiff + " had an unknown error and may be corrupted. It will be skipped.")

#Converts the given tiff_file_name to png and separates the frames.
def ImageConvert(tiff_file_name):
    #Reads the tiff file from the source folder.
    imageio_tiff_file = imageio.volread(tiff_file_name + ".tif")    
    frame_range = range(imageio_tiff_file.shape[0])
    #Saves each frame of the tiff file.
    for i in frame_range:
        #Checks the frame as the program deals with two frames at a time
        if (i % 2) != 0:
            continue
        #Gets the needed frames for this loop.
        imageio_tiff_file_frame = FrameGet(imageio_tiff_file, i)
        imageio_tiff_file_frame_round = np.around(imageio_tiff_file_frame)
        imageio_tiff_file_frame_next = FrameGet(imageio_tiff_file, i + 1)
        imageio_tiff_file_frame_next_round = np.around(imageio_tiff_file_frame_next)
        #Runs an oversaturation check if needed. 
        if oversaturation_setting and (OversaturationCheck(imageio_tiff_file_frame_round.astype('uint8')) or OversaturationCheck(imageio_tiff_file_frame_next_round.astype('uint8'))):
            continue
        #Runs a misorder check if needed.
        if misorder_setting:
            A_misorder = imageio_tiff_file_frame_round.astype('uint8')
            A_misorder_sum = A_misorder.sum()
            B_misorder = imageio_tiff_file_frame_next_round.astype('uint8')
            B_misorder_sum = B_misorder.sum()
            AB_misorder = abs(A_misorder_sum - B_misorder_sum)
            #Subtracts the A and the B to find how close the sums are and if they need to be thrown out.
            if (AB_misorder <= misorder_threshold) or (A_misorder_sum <= B_misorder_sum):
                continue
        #Checks if the image is entirely zeros.
        if automatic_histogram_setting or automatic_histogram_setting == "Augmentation":
            if zero_check_setting and (ZeroCheck(imageio_tiff_file_frame) or ZeroCheck(imageio_tiff_file_frame_next)):
                continue
        else:
            if zero_check_setting and (ZeroCheck(imageio_tiff_file_frame_round.astype('uint8')) or ZeroCheck(imageio_tiff_file_frame_next_round.astype('uint8'))):
                continue
        #Runs a histogram adjustment if needed.
        if automatic_histogram_setting:
            if automatic_histogram_setting == "Augmentation":
                imageio.imwrite(Path(root + '/A/train/' + tiff_file_name + "_nonhistogram" + '-' + str(i) + ".png"), imageio_tiff_file_frame_round.astype('uint8'))
                imageio.imwrite(Path(root + '/B/train/' + tiff_file_name + "_nonhistogram" + '-' + str(i) + ".png"), imageio_tiff_file_frame_next_round.astype('uint8'))
            imageio_tiff_file_frame = HistogramAdjustment(imageio_tiff_file_frame)
            imageio_tiff_file_frame_round = np.around(imageio_tiff_file_frame)
            imageio_tiff_file_frame_next = HistogramAdjustment(imageio_tiff_file_frame_next)
            imageio_tiff_file_frame_next_round = np.around(imageio_tiff_file_frame_next)
        #Applies a Blur if needed.
        if blur_type != False:
            imageio_tiff_file_frame_round = Blur(imageio_tiff_file_frame_round, blur_type)
        #Writes each image to its proper folder.
        imageio.imwrite(Path(root + '/A/train/' + tiff_file_name + '-' + str(i) + ".png"), imageio_tiff_file_frame_round.astype('uint8'))
        imageio.imwrite(Path(root + '/B/train/' + tiff_file_name + '-' + str(i) + ".png"), imageio_tiff_file_frame_next_round.astype('uint8'))

#Takes the given tiff_volume and exports the needed frame
def FrameGet(tiff_volume, frame_num):
    tiff_volume_frame = tiff_volume[frame_num, :, :]
    #Checks that the dtype of the image is processed correctly.        
    if tiff_volume_frame.dtype == "uint16":
        tiff_volume_frame = tiff_volume_frame / 256
    elif tiff_volume_frame.dtype != "uint8":
        raise DtypeException(tiff_volume_frame.dtype)
    return tiff_volume_frame

#Checks if the provided image_saturation is oversaturated.
def OversaturationCheck(image_saturation):
    if image_saturation.sum() > oversaturation_threshold:        
        return True
    else:
        return False

#Checks if the provided tiff_zero_sum is entirely zeroes.
def ZeroCheck(tiff_zero_sum):
    if tiff_zero_sum.sum() == 0:
        return True
    else:
        return False

#Applies an automatic histogram adjustment.
def HistogramAdjustment(image, number_bins = 256):
    image_histogram, bins = np.histogram(image.flatten(), number_bins, density = True)
    cdf = image_histogram.cumsum()
    cdf = 255 * cdf / cdf[-1]
    image_equalized = np.interp(image.flatten(), bins[:-1], cdf)
    image_equalized = image_equalized.reshape(image.shape)
    imin = image_equalized.min()
    imax = image_equalized.max()
    a = 255 / (imax - imin)
    b = 255 - a * imax
    image_normalization = (a * image_equalized + b)
    return image_normalization

#Applies the chosen blue.
def Blur(image, blur_type):
    if blur_type == "gaussian":
        return cv2.GaussianBlur(image, (0, 0) , 1, 0)
    if blur_type == "median":
        return cv2.medianBlur(image.astype('uint8'), 5)
    if blur_type == "mean":
        return cv2.blur(image, (5, 5))

#Triggers the program to start.
FolderConvert(Path(root + '/source/'))
os.chdir(root)

#Sets the locations and file lists of each subset.
current_path = os.getcwd()
restored_path = Path(root + '/A/train/')
restored_files = sorted(os.listdir(restored_path))
unrestored_path = Path(root + '/B/train/')
unrestored_files = sorted(os.listdir(unrestored_path))
restored_files = [os.path.join(current_path, restored_path, item) for item in restored_files]
unrestored_files = [os.path.join(current_path, unrestored_path, item) for item in unrestored_files]

#Sets the files that will be moved to the validation set based on their position in the directory.
val_restored_inds = [i for i in range(len(restored_files)) if (i + 1)/len(restored_files) > 0.8]
val_unrestored_inds = [i for i in range(len(unrestored_files)) if (i + 1)/len(unrestored_files) > 0.8]
val_restored = [fname for i, fname in enumerate(restored_files) if i in val_restored_inds]
val_unrestored = [fname for i, fname in enumerate(unrestored_files) if i in val_unrestored_inds]

#Moves each indicated validation file to the correct directory.
for val_filename in val_restored:
    img_name = os.path.split(val_filename)[1]
    move(val_filename, os.path.join(Path(root + '/A/val/'), img_name))
    move(os.path.join(Path(root + '/B/train/', img_name)), Path(root + '/B/val/', img_name))

#Triggers the combination program that will combine the A and B subsets into one image.
commandAB = 'python3 "' + str(Path(root + '/pytorch-CycleGAN-and-pix2pix/datasets/combine_A_and_B.py/')) + '" --fold_A A --fold_B B --fold_AB .'
os.system(commandAB)

#Triggers the training program.
commandTRAIN = str(Path(root + '/pytorch-CycleGAN-and-pix2pix/train.py/'))
subprocess.call(['python3', commandTRAIN, '--dataroot=.', '--model=pix2pix', '--display_id=0', '--name=pix_2_pix_CARE', '--direction=BtoA', '--ndf=64', '--ngf=64', '--batch_size=8'])
#Delete the --gpu_ids=-1 parameter if you wish to use a CUDA enabled GPU or add it if you wish to only use the CPU.
