from PIL import Image
import numpy as np

# Open the BMP file
bmp_image = Image.open('sparrow.bmp')

# Convert the BMP image to a NumPy array with float32 dtype
bmp_array = np.array(bmp_image, dtype=np.float32)

# Save the float32 array as a new BMP file
float_bmp_image = Image.fromarray(bmp_array.astype(np.uint8))
float_bmp_image.save('f_sparrow.bmp')

# Close the BMP image
bmp_image.close()