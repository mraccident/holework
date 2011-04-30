#
# Simple scons build file
#

# TODO: avoid hard-coding python include path
flags = '-Wall -Wno-unused-function -I/usr/include/python2.6'
libs = 'boost_system boost_iostreams boost_python python2.6'

# Set up environment
env = Environment()
env.Append(CPPFLAGS = flags)
env.Append(LIBS = Split(libs))

# Export environment and run script to compile everything into the build/ dir
Export('env')
SConscript('SConscript', variant_dir='build')
