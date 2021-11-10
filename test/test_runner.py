##
#	Author:		antikostya
#	Created:	2021-11-10 23:06:16
#	Modified:	2021-11-10 23:31:58
##

import os
import sys

c_defs = sys.argv[2]
command = sys.argv[1].split('-')
if len(command) == 1:
	print('bad arguments: command command name need to test')
	exit(1)
fname = command[1]
if fname in ['memset', 'bzero']:
	def_num = {'memset': 1, 'bzero': 2}[fname]
	x64coms = [
		'clang -Wall -Wextra -Werror -m64 -O3 -ffast-math' +
			c_defs +
			' -D TESTFUNC={} -D BIT=64 '.format(def_num) +
			' test/test_all_memset.c src/TLU{}.c'.format(fname) +
			' -o obj/test_{}64'.format(fname),
		'./obj/test_{}64'.format(fname),
		'rm ./obj/test_{}64'.format(fname)
	]

	x32coms = [
		'clang -Wall -Wextra -Werror -m32 -O3 -ffast-math' +
			c_defs +
			' -D TESTFUNC={} -D BIT=32 '.format(def_num) +
			' test/test_all_memset.c src32/TLU{}32.c'.format(fname) +
			' -o obj32/test_{}'.format(fname),
		'./obj32/test_{}'.format(fname),
		'rm ./obj32/test_{}'.format(fname)
	]

	if len(command) == 2:
		for cmd in x64coms:
			os.system(cmd)
		for cmd in x32coms:
			os.system(cmd)
	elif command[2] == '64':
		for cmd in x64coms:
			os.system(cmd)
	elif command[2] == '32':
		for cmd in x32coms:
			os.system(cmd)
	else:
		printf(f'cannot run test for {command[2]} bit system')
