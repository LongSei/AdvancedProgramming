from PIL import Image

# Open an image file
image = Image.open("./images/map.png")

# Resize the image
width, height = image.size
new_width = 1000
new_height = 1000  # New height (50% of original)
resized_image = image.resize((new_width, new_height))

# Save the resized image
resized_image.save("./images/map.png")

# Display the resized image
resized_image.show()
