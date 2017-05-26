from PIL import Image
from PIL import ImageFilter

img1 = Image.open("image.jpg")
img2 = img1.filter(ImageFilter.Mean)
img2.save("image_mean.jpg")
