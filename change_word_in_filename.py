import os
import sys

def rename_files(directory, current_word, new_word):
    for root, dirs, files in os.walk(directory):
        for file in files:
            if current_word in file:
                old_file_path = os.path.join(root, file)
                new_file_name = file.replace(current_word, new_word)
                new_file_path = os.path.join(root, new_file_name)
                os.rename(old_file_path, new_file_path)

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python change_word_in_filename.py directory_path current_word new_word (ALL ARGUMENTS ARE CASE SENSITIVE)")
        sys.exit(1)

    directory_path = sys.argv[1]
    current_word = sys.argv[2]
    new_word = sys.argv[3]
    if not os.path.isdir(directory_path):
        print("Error: Directory does not exist.")
        sys.exit(1)

    rename_files(directory_path, current_word, new_word)