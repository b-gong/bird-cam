from PIL import Image
import numpy as np

# Open the BMP file
bmp_image = Image.open('f_sparrow.bmp')

# Convert the BMP image to a NumPy array
bmp_array = np.array(bmp_image)

# Check the data type of the array
if np.issubdtype(bmp_array.dtype, np.integer):
    print("The BMP image contains integer pixel values.")
else:
    print("The BMP image contains floating-point pixel values.")

# Close the BMP image
bmp_image.close()