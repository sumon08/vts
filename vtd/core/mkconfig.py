#!/usr/bin/python3

if __name__ == "__main__":
	config_header =  open("config.hxx","w+")
	config_header.write("/* auto generated file, do not modify or delete */\n\n")
	config_header.write("#ifndef __INCLUDE_VTS_CONFIG_H\n")
	config_header.write("#define __INCLUDE_VTS_CONFIG_H\n\n")
	with open(".config","r") as config:
		while True:
			line = str(config.readline())
			if(not line):
				break
			if(len(line)>1):
				if(line[0]!='#'):
					line = line.replace('=',' ')
					if(line[len(line)-2]=='y'):
						line = line.replace('y','1')
					#line = line.strip('\n')
					#print(line)
					output = "#define "+line
					config_header.write(str(output))
	config_header.write("\n#endif //__INCLUDE_VTS_CONFIG_H\n")

	config.close()
	config_header.close()
