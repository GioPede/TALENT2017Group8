import pickle


filelist = ["-10.lev", "-09.lev", "-08.lev", "-07.lev", "-06.lev", "-05.lev", "-04.lev", "-03.lev", "-02.lev", "-01.lev", 
			"00.lev", "01.lev", "02.lev", "03.lev", "04.lev", "05.lev", "06.lev", "07.lev", "08.lev", "09.lev", "10.lev" ]

output = open("nush.dat", "w") 

for filename in filelist:
	file = open(filename, "r") 
	#skip 2 lines
	file.readline()
	file.readline()
	
	#get g value from filename
	g = float(filename.split(".")[0]) / 10.0

	#get GS energy, to be added to the others
	groundState = float(file.readline().split("g")[0])
	
	#skip 2 more lines
	file.readline()
	file.readline()

	#get the energy values
	E = []
	E.append(str(g))
	for i in range(0,20):
		E.append(str(float(file.readline().split("0 ")[0]) + groundState))
	output.write("  ".join(E))
	output.write("\n")
