file_name = "inter.txt" # set me
output_filename = "rainbow.txt"

with open(file_name) as f:
	note_sets = f.readlines()

with open(output_filename, 'w') as f:
	for i in range(len(note_sets)):
		notes = note_sets[i]
		notes = notes.rstrip();
		f.write("controller.goTo(\"" + notes + "\");\n")
		f.write("delay(noteDelay);\n")