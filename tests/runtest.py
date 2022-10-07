################################################################
#                                                              #
# LOVCI: Ladder Operator Vibrational Configuration Interaction #
#                                                              #
################################################################

# LOVCI semi-automated test suite

# Modules
import subprocess
import sys
import os
from pathlib import Path
import argparse

class ClrSet:
    # Unicode colors
    Norm = "\033[0m"
    Red = "\033[91m"
    Bold = "\033[1m"
    Green = "\033[92m"
    Blue = "\033[94m"
    Cyan = "\033[36m"
    # Set colors
    TFail = Bold + Red  # Highlight failed tests
    TPass = Bold + Green  # Highlight passed tests
    Reset = Norm  # Reset to defaults


# Print title
line = "\n"
line += "****************************************************************"
line += "\n"
line += "*                                                              *"
line += "\n"
line += "* LOVCI: Ladder Operator Vibrational Configuration Interaction *"
line += "\n"
line += "*                                                              *"
line += "\n"
line += "****************************************************************"
line += "\n"
print(line)

parser = argparse.ArgumentParser()
parser.add_argument("lovci_path", type=Path)
parser.add_argument("test_case")
args = parser.parse_args()
lovci_path = args.lovci_path.resolve()
assert lovci_path.exists()

Ncpus = subprocess.check_output("echo ${OMP_NUM_THREADS}", shell=True).decode("utf-8").strip()
if not Ncpus:
    Ncpus = "1"

# Print output
result = "Running tests with "
result += Ncpus
result += " CPUs..."
result += "\n"
result += "\n"
result += "Test results:"
print(result)

rv = 0

os.chdir(args.test_case)
result = ""
ZPE = ""
RunTime = ""
ret = subprocess.run(f"{lovci_path} -n {Ncpus} -i input -o Spect.txt > Log.txt", shell=True)
data = Path("Log.txt").read_text().splitlines()
ref = Path("ref").read_text().strip()
for line in data:
    line = line.strip()
    line = line.split()
    if len(line) > 3:
        if line[0] == "Zero-point":
            ZPE = line[2]
        if (line[0] == "Run") and (line[1] == "time:"):
            RunTime = line[2] + " " + line[3]
result += f"{args.test_case}: "
if ZPE == ref:
    result += ClrSet.TPass + "Pass" + ClrSet.Reset + ", "
else:
    result += ClrSet.TFail + "Fail" + ClrSet.Reset + ", "
    rv += 1
result += RunTime
print(result)
# cmd = "rm -f Spect.txt Log.txt"
# ret = subprocess.run(cmd,shell=True)
sys.exit(rv)
