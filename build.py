from subprocess import call
import sys
f = sys.argv[1]
build = "g++ " + f + ".cpp -o bin/" + f
run = "./bin/" + f
# Builds And Run
call(build)