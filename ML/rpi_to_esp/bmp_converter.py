from PIL import Image

# Open the JPG image using Pillow
jpg_image = Image.open('301807021-720px.jpg')

# Convert the JPG image to BMP format
bmp_image = jpg_image.convert('RGB')  # Convert to RGB mode if not already in RGB
bmp_image.save('sparrow.bmp')

# Close the images
jpg_image.close()
bmp_image.close()

print("JPG to BMP conversion complete.")