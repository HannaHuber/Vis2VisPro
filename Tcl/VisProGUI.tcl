# Set window title
wm title . VisProGUI

# Create a frame for buttons and entry.

frame .top -borderwidth 10
pack .top -side top -fill x

# Create the command buttons.

button .top.quit -text Quit -command exit

set butM [button .top.updateM -text "Update" -command UpdateM]

set butEnv [button .top.updateEnv -text "Set" -command SetEnv]
set butItem [button .top.updateItem -text "Set" -command SetItem]

set butStart [button .top.startSim -text "Start" -command StartSim]

# Create a labeled entry for the command

label .top.labM -text M-Parameter: -padx 0
entry .top.cmdM -width 20 -relief sunken \
	-textvariable commandM
label .top.labEnv -text Environment: -padx 0
entry .top.cmdEnv -width 20 -relief sunken \
	-textvariable commandEnv
label .top.labItem -text Item: -padx 0
entry .top.cmdItem -width 20 -relief sunken \
	-textvariable commandItem

grid .top.labM  -row 0 -column 0 -sticky e
grid .top.cmdM -row 0 -column 1 -sticky e
grid .top.updateM -row 0 -column 2 -sticky e

grid .top.labEnv  -row 1 -column 0 -sticky e
grid .top.cmdEnv -row 1 -column 1 -sticky e
grid .top.updateEnv -row 1 -column 2 -sticky e

grid .top.labItem  -row 2 -column 0 -sticky e
grid .top.cmdItem -row 2 -column 1 -sticky e
grid .top.updateItem -row 2 -column 2 -sticky e

grid .top.startSim -row 3 -column 0 -sticky e 
grid .top.quit -row 3 -column 2 -sticky wens 

# Set up key binding equivalents to the buttons

bind .top.cmdM <Return> UpdateM
# focus .top.cmdM
focus .top.startSim

# Run the program and arrange to read its input

proc UpdateM {} {
	global commandM 
	setM $commandM\n
}

proc StartSim {} {
	startSim
}

proc SetEnv {} {
	global commandEnv 
	setEnvironment $commandEnv\n
}

proc SetItem {} {
	global commandItem 
	setItem $commandItem\n
}

