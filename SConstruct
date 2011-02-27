env = Environment(CCFLAGS = '-m32 -Wall -Wextra -O3 -g',
                  LINKFLAGS = '-m32')

jit = env.Program('jit', Glob('src/*.cc'))
