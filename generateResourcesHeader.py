import os

def generate_resource_header(images, output_header):
    with open(output_header, 'w') as header_file:
        for image in images:
            variable_name = os.path.splitext(os.path.basename(image))[0]
            header_file.write(f'unsigned char {variable_name}_data[] = {{\n')
            with open(image, 'rb') as img_file:
                data = img_file.read()
                byte_array = ', '.join([f'0x{byte:02x}' for byte in data])
                header_file.write(byte_array)
            header_file.write('};\n')
            header_file.write(f'unsigned int {variable_name}_size = sizeof({variable_name}_data);\n\n')

def find_images_in_folder(directory, extensions=['.png', '.jpg', '.jpeg', '.bmp', '.gif']):
    image_paths = []
    for root, dirs, files in os.walk(directory):
        for file in files:
            if any(file.endswith(ext) for ext in extensions):
                image_paths.append(os.path.join(root, file))
    return image_paths


directory = './Worms/Resources'
images = find_images_in_folder(directory)

filePath = "./Worms/Resources/"
filename = "Resources.h"
generate_resource_header(images, filePath + filename)
