# Set window title
wm title . VisProGUI

# Create a frame for buttons and entry.

frame .top -borderwidth 10
pack .top -side top -fill x

# Create the command buttons.

button .top.quit -text Quit -command exit
set butM [button .top.updateM -text "Update" -command UpdateM]

# Create a labeled entry for the command

label .top.labM -text M-Parameter: -padx 0
entry .top.cmdM -width 20 -relief sunken \
	-textvariable commandM

grid .top.labM  -row 0 -column 0 -sticky e
grid .top.cmdM -row 0 -column 1 -sticky e
grid .top.updateM -row 0 -column 2 -sticky e
grid .top.quit -row 1 -column 2 -sticky wens 

# Set up key binding equivalents to the buttons

bind .top.cmdM <Return> UpdateM
focus .top.cmdM

# Run the program and arrange to read its input

proc UpdateM {} {
	global commandM 
	setM $commandM\n
}



