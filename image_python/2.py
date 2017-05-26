from PIL import Image
from PIL import ImageFilter

img1 = Image.open("image_salt.jpg")
img2 = img1.filter(ImageFilter.MedianFilter(3))
img2.save("image_salt_median3.jpg")

