import subprocess

proc  = subprocess.Popen("ps -ef", shell=True, stdout=subprocess.PIPE)
subprocess_return = proc.stdout.read()
print(subprocess_return)
