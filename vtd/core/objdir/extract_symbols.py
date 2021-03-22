#!/usr/bin/python3
import sys

def generate_symbol_list(undefined_symbol_list,SystemMap):
	#for each symbol in undefined_symbol_list find reference from System.map
	#and write to linker script "symbol_list.ld"
	#print(SystemMap)
	symbol_list = open('symbol_list.ld','w')
	with open(SystemMap,'r') as system_map:
		while True:
			line = system_map.readline()
			if(not line):
				break
			entry = line.strip('\n').split(' ')
			symbol_name = entry[2]
			for symbol in undefined_symbol_list:
				if(symbol == symbol_name):
					reference_entry = symbol+ " = 0x"+entry[0]+";\n"
					symbol_list.write(reference_entry)
	system_map.close()
	symbol_list.close()

if __name__ == "__main__":
	#enlist symbols which references are not necessary
	exception_list = ["_sinit", "_sbss", "_sdata", "_ebss","_edata", "_einit", "_eronly", "__aeabi_atexit", "__dso_handle"]
	undefined_symbol_list = []
	relocatable_r = sys.argv[1]
	SystemMap = sys.argv[2]

	#for all the references in relocatable file, if symbol is not in exception list, enlist it to undefined_symbol_list
	with open(relocatable_r,'r') as RelacotableFile:
		while True:
			line = RelacotableFile.readline()
			if(not line):
				break
			sections = line.strip('\n').replace(' ','').split(' ')
			entry = sections[0].strip('U')
			flag = True
			for word in exception_list:
				if(entry == word):
					flag = False
					break
			if(flag == True):
				undefined_symbol_list.append(entry)
	generate_symbol_list(undefined_symbol_list,SystemMap)

