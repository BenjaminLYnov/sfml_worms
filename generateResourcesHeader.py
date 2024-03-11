import os
import re

def generate_resource_files(images, fonts, sounds, output_dir, header_filename, source_filename):
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
        
        for font in fonts:
            # Extraire le nom de base sans l'extension
            variable_name = os.path.splitext(os.path.basename(font))[0]
            variable_name = clean_filename(variable_name)

            # Écrire dans le fichier d'en-tête
            header_file.write(f'extern unsigned char {variable_name}_data[];\n')
            header_file.write(f'extern unsigned int {variable_name}_size;\n\n')
            
            # Écrire dans le fichier source
            source_file.write(f'unsigned char {variable_name}_data[] = {{\n')
            with open(font, 'rb') as font_file:
                data = font_file.read()
                byte_array = ', '.join([f'0x{byte:02x}' for byte in data])
                source_file.write(byte_array)
            source_file.write('\n};\n')
            source_file.write(f'unsigned int {variable_name}_size = sizeof({variable_name}_data);\n\n')
        
        for sound in sounds:
            # Extraire le nom de base sans l'extension
            variable_name = os.path.splitext(os.path.basename(sound))[0]
            variable_name = clean_filename(variable_name)

            # Écrire dans le fichier d'en-tête
            header_file.write(f'extern unsigned char {variable_name}_data[];\n')
            header_file.write(f'extern unsigned int {variable_name}_size;\n\n')
            
            # Écrire dans le fichier source
            source_file.write(f'unsigned char {variable_name}_data[] = {{\n')
            with open(sound, 'rb') as sound_file:
                data = sound_file.read()
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

def find_files_in_folder(directory, extensions):
    file_paths = []
    for root, dirs, files in os.walk(directory):
        for file in files:
            if any(file.endswith(ext) for ext in extensions):
                file_paths.append(os.path.join(root, file))
    return file_paths

directory = './Worms/Resources'
output_dir = "./Worms/Resources/"
header_filename = "Resources.h"
source_filename = "Resources.cpp"
image_extensions = ['.png', '.jpg', '.jpeg', '.bmp', '.gif']
font_extensions = ['.ttf']
sound_extensions = ['.wav', '.mp3']  # Ajoutez d'autres extensions de fichiers sonores au besoin
images = find_files_in_folder(directory, image_extensions)
fonts = find_files_in_folder(os.path.join(directory, 'Fonts'), font_extensions)
sounds = find_files_in_folder(os.path.join(directory, 'Sounds'), sound_extensions)
generate_resource_files(images, fonts, sounds, output_dir, header_filename, source_filename)
