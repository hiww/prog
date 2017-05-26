from PIL import Image
from itertools import product
from random import random

class Noise:
    def __init__(self, input_image):
        self.input_image = input_image
        self.input_pix = self.input_image.load()
        self.w, self.h = self.input_image.size

    def saltpepper(self, salt=0.05, pepper=0.05):
        output_image = Image.new("RGB", input_image.size)
        output_pix = output_image.load()

        for x, y in product(*map(range, (self.w, self.h))):
            r = random()
            if r < salt:
                output_pix[x, y] = (255, 255, 255)
            elif r > 1 - pepper:
                output_pix[x, y] = (  0,   0,   0)
            else:
                output_pix[x, y] = self.input_pix[x, y]
        return output_image

input_img = Image.open("input.jpg")
filterInstance = Filter(input_img)
output_img = filterInstance.median()
output_img.save("output_goma.jpg","JPEG")
