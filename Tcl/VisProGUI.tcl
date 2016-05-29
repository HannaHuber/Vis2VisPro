# Set window title
wm title . VisProGUI

# Create a frame for buttons and entry.

frame .top -borderwidth 10
pack .top -side top -fill x

# Create the command buttons.

set butEnv [button .top.updateEnv -text "Secondary Objects" -command SetEnv]
set butItem [button .top.updateItem -text "Objects of Interest " -command SetItem]

set butNear [button .top.updateNear -text "Update Near Plane" -command UpdateNear]
set butFar [button .top.updateFar -text "Update Far Plane" -command UpdateFar]
set butDrill [button .top.updateDrill -text "Update Drill Angle" -command UpdateDrill]

set butStart [button .top.startSim -text "Start" -command StartSim]
set butQ [button .top.quit -text "Quit" -command exit]

# Create default values

set commandM 1
set commandEnv ../Models/Japanese/japaneseHouse.dae
set commandItem ../Models/Japanese/japaneseNoCarpet.dae

set commandDrill 40
set commandNear 0.1
set commandFar 180.0

# Create a labeled entry for the command

# label .top.labM -text M-Parameter: -padx 0

entry .top.cmdEnv -width 80 -relief sunken \
	-textvariable commandEnv
entry .top.cmdItem -width 80 -relief sunken \
	-textvariable commandItem

entry .top.cmdNear -width 80 -relief sunken \
	-textvariable commandNear
entry .top.cmdFar -width 80 -relief sunken \
	-textvariable commandFar
entry .top.cmdDrill -width 80 -relief sunken \
	-textvariable commandDrill

# grid .top.labM  -row 2 -column 0 -sticky e

grid .top.updateEnv -row 0 -column 0 -sticky wens
grid .top.cmdEnv -row 0 -column 1 -sticky e

grid .top.updateItem -row 1 -column 0 -sticky wens
grid .top.cmdItem -row 1 -column 1 -sticky e

grid .top.updateNear -row 2 -column 0 -sticky wens
grid .top.cmdNear -row 2 -column 1 -sticky e

grid .top.updateFar -row 3 -column 0 -sticky wens
grid .top.cmdFar -row 3 -column 1 -sticky e

grid .top.updateDrill -row 4 -column 0 -sticky wens
grid .top.cmdDrill -row 4 -column 1 -sticky e

grid .top.startSim -row 5 -column 0 -sticky wens 
grid .top.quit -row 5 -column 1 -sticky e 

# Set up key binding equivalents to the buttons

bind .top.cmdEnv <Return> SetEnv
bind .top.cmdItem <Return> SetItem

bind .top.cmdNear <Return> UpdateNear
bind .top.cmdFar <Return> UpdateFar
bind .top.cmdDrill <Return> UpdateDrill

focus .top.startSim

# Run the program and arrange to read its input

proc UpdateNear {} {
	global commandNear 
	setNearPlane $commandNear
}

proc UpdateFar {} {
	global commandFar 
	setFarPlane $commandFar
}

proc UpdateDrill {} {
	global commandDrill 
	setDrillAngle $commandDrill
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

