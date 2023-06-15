import os

output_file = "merged_result.txt"
file_prefix = "outFiles/result"
file_extension = ".txt"
file_range = range(1000)  # Numbers from 0 to 999

with open(output_file, "w") as outfile:
    for number in file_range:
        filename = file_prefix + str(number).zfill(3) + file_extension
        if os.path.exists(filename):
            with open(filename, "r") as infile:
                outfile.write(infile.read())
