from PIL import Image
from PIL import ImageFilter

img1 = Image.open("image_noise.jpg")
img2 = img1.filter(ImageFilter.GaussianBlur(11))
img2.save("image_noise_gaussian11.jpg")
