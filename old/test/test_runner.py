##
#	Author:		antikostya
#	Created:	2021-11-10 23:06:16
#	Modified:	2021-11-11 00:05:13
##

import os
import sys

x64coms = """
clang -Wall -Wextra -Werror -m64 -O3 -ffast-math {c_defs} -D TESTFUNC={def_num} -D BIT=64 test/{tester_name}.c src/TLU{fname}.c -o obj/test_{fname}64
./obj/test_{fname}64
rm ./obj/test_{fname}64
"""

x32coms = """
clang -Wall -Wextra -Werror -m32 -O3 -ffast-math {c_defs} -D TESTFUNC={def_num} -D BIT=32 test/{tester_name}.c src32/TLU{fname}32.c -o obj32/test_{fname}32
./obj32/test_{fname}32
rm ./obj32/test_{fname}32
"""

c_defs = sys.argv[2]
command = sys.argv[1].split('-')
if len(command) == 1:
	print('bad arguments: command command name need to test')
	exit(1)
fname = command[1]
if fname in ['memset', 'bzero']:
	def_num = {'memset': 1, 'bzero': 2}[fname]
	myx64coms = x64coms.format(c_defs=c_defs, def_num=def_num, fname=fname, tester_name='test_all_memset').split('\n')
	myx32coms = x32coms.format(c_defs=c_defs, def_num=def_num, fname=fname, tester_name='test_all_memset').split('\n')

elif fname in ['isdigit']:
	def_num = {'isdigit': 1}[fname]
	myx64coms = x64coms.format(c_defs=c_defs, def_num=def_num, fname=fname, tester_name='test_all_issmth').split('\n')
	myx32coms = x32coms.format(c_defs=c_defs, def_num=def_num, fname=fname, tester_name='test_all_issmth').split('\n')
	print (myx64coms)
else:
	print('function not implemented')
	exit(1)

if len(command) == 2:
	for cmd in myx64coms:
		os.system(cmd)
	for cmd in myx32coms:
		os.system(cmd)
elif command[2] == '64':
	for cmd in myx64coms:
		os.system(cmd)
elif command[2] == '32':
	for cmd in myx32coms:
		os.system(cmd)
else:
	printf(f'cannot run test for {command[2]} bit system')
