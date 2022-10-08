import argparse
import os
import subprocess
import sys
from pathlib import Path

parser = argparse.ArgumentParser()
parser.add_argument("lovci_path", type=Path)
parser.add_argument("test_case")
args = parser.parse_args()
lovci_path = args.lovci_path.resolve()
assert lovci_path.exists()

ncpus = subprocess.check_output("echo ${OMP_NUM_THREADS}", shell=True).decode("utf-8").strip()
if not ncpus:
    ncpus = "1"

os.chdir(args.test_case)
zpe = ""
cmd = f"{lovci_path} -n {ncpus} -i input -o Spect.txt > Log.txt"
print(cmd)
ret = subprocess.run(cmd, shell=True, check=True)
if ret.returncode != 0:
    sys.exit(ret.returncode)
data = Path("Log.txt").read_text().splitlines()
ref = Path("ref").read_text().strip()
for line in data:
    line = line.strip().split()
    if len(line) > 3:
        if line[0] == "Zero-point":
            zpe = line[2]
rv = 0
if zpe != ref:
    sys.exit(1)
