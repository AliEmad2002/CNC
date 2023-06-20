(Acceleration settings)
M204 P36000 T36000

(Rapid speed)
G00 F1200.00

(Auto leveling map probing)
G29 L0 R10 F0 B15 N6 N6

(Tool change)
M06

(Probing new tool)
G30

(Give chance for removing probing wires)
M06

(Zeroing Z-axis after probing)
G92 X0 Y0 Z0