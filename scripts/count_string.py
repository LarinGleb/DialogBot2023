import os

count_strings = 0
import os
import os.path

for dirpath, dirnames, filenames in os.walk(".."):
    for filename in [f for f in filenames if f.endswith(".cpp") or f.endswith(".h") or f.endswith(".txt")]:
        with open(os.path.join(dirpath, filename), "r") as file:
            if("build" not in dirpath):
                count_strings += len(file.readlines())
                print(os.path.join(dirpath, filename))
print("Количество строк в проекте:", count_strings)