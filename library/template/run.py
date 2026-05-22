import subprocess
import sys

def compile():
	subprocess.run("g++ -std=c++20 -O2 -Wall -Wextra -pedantic -Wshadow main.cpp -o main -g".split(), check=True)
	subprocess.run("g++ -std=c++20 -O2 -Wall -Wextra -pedantic -Wshadow stupid.cpp -o stupid -g".split(), check=True)

def stress():
	compile()
	NTEST = 10000
	for i in range(1, NTEST + 1):
		print(f"TEST #{i}")
		with open("inp", "w") as inp:
			subprocess.run("python3 gen.py".split(), stdout = inp, check=True)
		with open("inp", "r") as inp, open("out", "w") as out:
			subprocess.run("./main", stdin=inp, stdout=out, check=True)
		with open("inp", "r") as inp, open("ans", "w") as ans:
			subprocess.run("./stupid", stdin=inp, stdout=ans, check=True)
		subprocess.run("diff -w out ans".split(), check = True)

if len(sys.argv) == 1:
	print("lol")
elif sys.argv[1] == "c":
	compile()
elif sys.argv[1] == "s":
	stress()
