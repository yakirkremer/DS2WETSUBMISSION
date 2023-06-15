import subprocess
import os

min = 11
max = 99

input_files = [f"inFiles/test{i}.in" for i in range(min, max)]

# Get the full path to the mainWet2 executable
executable_path = os.path.abspath(r"C:\Users\yakir\Documents\TechnionHW\Matam\DS2WET_NEW\submission\prog.exe")

for i, input_file in enumerate(input_files, min):
    output_file = f"outFiles/test{i}.res"
    command = f"{executable_path} < {input_file} > {output_file}"
    subprocess.run(command, shell=True)


import os

def compare_files(out_file, result_file):
    with open(out_file, 'r') as out_f, open(result_file, 'r') as result_f:
        out_lines = out_f.readlines()
        result_lines = result_f.readlines()

    mismatched_lines = []
    for line_num, out_line in enumerate(out_lines):
        if line_num >= len(result_lines):
            mismatched_lines.append((line_num + 1, out_line.strip(), None))
        else:
            result_line = result_lines[line_num]
            if out_line != result_line:
                mismatched_lines.append((line_num + 1, out_line.strip(), result_line.strip()))

    return mismatched_lines


def colorize_line(line, color):
    # ANSI escape sequences for text color
    color_codes = {
        'red': '\033[91m',
        'green': '\033[92m',
        'reset': '\033[0m'
    }

    return f"{line}"


directory = r"C:\Users\yakir\Documents\TechnionHW\Matam\DS2WET_NEW\submission\outFiles"
summary_file = os.path.join(directory, 'summary.txt')

with open(summary_file, 'w') as summary:
    for i in range(min, max):
        out_file = os.path.join(directory, f'test{i}.out')
        result_file = os.path.join(directory, f'test{i}.res')

        mismatched_lines = compare_files(out_file, result_file)

        result_filename = os.path.join(directory, f'result{i}.txt')
        with open(result_filename, 'w') as file:
            file.write(f'Result for test{i}:\n')

            for line_num, out_line, result_line in mismatched_lines:
                if result_line is None:
                    file.write(f'Line {line_num} - out: {colorize_line(out_line, "green")}\n')
                else:
                    file.write(f'Line {line_num} - out: {colorize_line(out_line, "red")}\n')
                    file.write(f'Line {line_num} - result: {colorize_line(result_line, "red")}\n')

        mismatch_count = len(mismatched_lines)
        if mismatch_count > 0:
            summary.write(f'Result file for test{i}: {mismatch_count} line(s) mismatched\n')
        else:
            summary.write(f'Result file for test{i}: Lines match\n')

        print(f'Result file {result_filename} created.')

print(f'Summary file {summary_file} created.')

