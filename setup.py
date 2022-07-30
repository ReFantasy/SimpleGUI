import os
os.system("mkdir build")
os.system("mkdir build/lib_build")
os.system("cmake -S third -B build/lib_build")
os.system("make --directory build/lib_build")
os.system("make install --directory build/lib_build")

#os.system("cmake ../../third")
#os.system("make")
#os.system("make install")