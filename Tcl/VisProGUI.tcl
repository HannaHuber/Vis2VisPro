# Set window title
wm title . VisProGUI

# Create a frame for buttons and entry.

frame .top -borderwidth 10
pack .top -side top -fill x

# Create the command buttons.

button .top.quit -text Quit -command exit
set but [button .top.run -text "Update" -command UpdateM]
pack .top.quit .top.run -side right

# Create a labeled entry for the command

label .top.l -text M-Parameter: -padx 0
entry .top.cmd -width 20 -relief sunken \
	-textvariable command
pack .top.l -side left
pack .top.cmd -side left -fill x -expand true

# Set up key binding equivalents to the buttons

bind .top.cmd <Return> UpdateM
focus .top.cmd

# Run the program and arrange to read its input

proc UpdateM {} {
	global command 
	setM $command\n
}



