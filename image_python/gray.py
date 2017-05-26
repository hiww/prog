from PIL import Image
from PIL import ImageOps

if __name__ == "__main__":
    input_image = Image.open("image.jpg")
    output_image = ImageOps.grayscale(input_image)
    output_image.save("im_g.jpg")
