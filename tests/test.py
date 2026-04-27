import os
import subprocess

from argparse import ArgumentParser

# parse command-line arguments
parser = ArgumentParser()

parser.add_argument('-b', '--binary-path', default='bin/compiler', type=str, help='binary path')
parser.add_argument('-e', '--example-dir', default='examples/simple_c_examples', type=str, help='examples path')

args = vars(parser.parse_args())

binary = args['binary_path']
examples_dir = args['example_dir']

# Run make when binary doesn't exist
if not os.path.isfile(binary):
    result = subprocess.run('make', capture_output=True)

# loop through all examples
test_count = 0
test_fail_count = 0
for path, dirs, files in os.walk(examples_dir):
    for file_name in sorted(files):

        test_code = path + '/' + file_name

        run_args = ['./' + binary, test_code]
        result = subprocess.run(run_args, capture_output=True, text=True)

        if result.returncode == 0:
            print(f'Test on file \'{test_code}\' passed!')
        else:
            print(f'Test on file \'{test_code}\' failed!')
            print(result.stderr)
            test_fail_count += 1
        
        test_count += 1

if (test_fail_count == 0):
    print('All tests were passed successfully!')
else:
    print(f'{test_fail_count}/{test_count} tests failed! Pass rate: {100*(test_count - test_fail_count)/test_count}%')