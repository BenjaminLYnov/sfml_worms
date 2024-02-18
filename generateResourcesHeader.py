import os
import re

def generate_resource_files(images, output_dir, header_filename, source_filename):
    header_path = os.path.join(output_dir, header_filename)
    source_path = os.path.join(output_dir, source_filename)
    
    with open(header_path, 'w') as header_file, open(source_path, 'w') as source_file:
        header_file.write("#ifndef RESOURCES_H\n#define RESOURCES_H\n\n")
        source_file.write(f'#include "{header_filename}"\n\n')
        
        for image in images:
            # Extraire le nom de base sans l'extension
            variable_name = os.path.splitext(os.path.basename(image))[0]
            variable_name = clean_filename(variable_name)
            
            # Écrire dans le fichier d'en-tête
            header_file.write(f'extern unsigned char {variable_name}_data[];\n')
            header_file.write(f'extern unsigned int {variable_name}_size;\n\n')
            
            # Écrire dans le fichier source
            source_file.write(f'unsigned char {variable_name}_data[] = {{\n')
            with open(image, 'rb') as img_file:
                data = img_file.read()
                byte_array = ', '.join([f'0x{byte:02x}' for byte in data])
                source_file.write(byte_array)
            source_file.write('\n};\n')
            source_file.write(f'unsigned int {variable_name}_size = sizeof({variable_name}_data);\n\n')
        
        header_file.write("#endif // RESOURCES_H\n")

def clean_filename(filename):
    filename = filename.replace('-', '_')
    filename = re.sub(r'[^\w_]', '', filename)
    filename = re.sub(r'__+', '_', filename)
    return filename

def find_images_in_folder(directory, extensions=['.png', '.jpg', '.jpeg', '.bmp', '.gif']):
    image_paths = []
    for root, dirs, files in os.walk(directory):
        for file in files:
            if any(file.endswith(ext) for ext in extensions):
                image_paths.append(os.path.join(root, file))
    return image_paths

directory = './Worms/Resources'
output_dir = "./Worms/Resources/"
header_filename = "Resources.h"
source_filename = "Resources.cpp"
images = find_images_in_folder(directory)
generate_resource_files(images, output_dir, header_filename, source_filename)
