# Set window title
wm title . VisProGUI

# Create a frame for buttons and entry.

frame .top -borderwidth 10
pack .top -side top -fill x

# Create the command buttons.

set butQ [button .top.quit -text "Quit" -command exit]
set butM [button .top.updateM -text "Update M" -command UpdateM]
set butEnv [button .top.updateEnv -text "Open Env" -command SetEnv]
set butItem [button .top.updateItem -text "Open Item" -command SetItem]

set butStart [button .top.startSim -text "Start" -command StartSim]

# Create default values

set commandM 1
set commandEnv ../Models/Japanese/japaneseHouse.dae
set commandItem ../Models/Japanese/japaneseNoCarpet.dae

# Create a labeled entry for the command

# label .top.labM -text M-Parameter: -padx 0

entry .top.cmdM -width 80 -relief sunken \
	-textvariable commandM
entry .top.cmdEnv -width 80 -relief sunken \
	-textvariable commandEnv
entry .top.cmdItem -width 80 -relief sunken \
	-textvariable commandItem

# grid .top.labM  -row 2 -column 0 -sticky e
grid .top.updateM -row 2 -column 0 -sticky wens
grid .top.cmdM -row 2 -column 1 -sticky e

grid .top.updateEnv -row 0 -column 0 -sticky wens
grid .top.cmdEnv -row 0 -column 1 -sticky e

grid .top.updateItem -row 1 -column 0 -sticky wens
grid .top.cmdItem -row 1 -column 1 -sticky e

grid .top.startSim -row 3 -column 0 -sticky wens 
grid .top.quit -row 3 -column 1 -sticky e 

# Set up key binding equivalents to the buttons

bind .top.cmdM <Return> UpdateM
bind .top.cmdEnv <Return> SetEnv
bind .top.cmdItem <Return> SetItem

focus .top.startSim

# Run the program and arrange to read its input

proc UpdateM {} {
	global commandM 
	setM $commandM
}

proc StartSim {} {
	startSim
}

proc SetEnv {} {
	global commandEnv 

	set types {
		{{DAE Files}       {.dae}        }
	}
	set filename [tk_getOpenFile -filetypes $types]
	set commandEnv $filename
	setEnvironment $filename
}

proc SetItem {} {
	global commandItem 

	set types {
		{{DAE Files}       {.dae}        }
	}
	set filename [tk_getOpenFile -filetypes $types]
	set commandItem $filename
	setItem $filename
}

