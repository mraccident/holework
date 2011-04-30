#
# scons script specifying just the sources and target for the project
#

Import('env')

sources = Glob('src/*.cpp') + Glob('src/*/*.cpp')
objects = env.Object(source = sources)
target = env.Program( target='server', source = objects)

# Copy to the build location all our python scripts
py = Dir('py')

Default(target, py)
