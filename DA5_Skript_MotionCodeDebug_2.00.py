"""<pre>
#*============================================================================*#
#*                               Dunkermotoren                                *#
#* File         : DA5_Skript_DebugMotionCodeTemplate_2.00.py                  *#
#*                                                                            *#
#* Project      : Skript to translate MotionCode Debug Variables              *#
#* System       : Python 3 --> DA5                                            *#
#* Version      : 002.00                                                      *#
#* Company      : Dunkermotoren GmbH                                          *#
#*                                                                            *#
#* Author       : Alexander Haberstroh                                        *#
#* Date         : 01.03.2022                                                  *#
#*============================================================================*#
#*                                                                            *#
#* DriveAssistant 5 needed!!!                                                 *#
#*                                                                            *#
#* How to use:                                                                *#
#* Copy Skript in the MotionCode Source folder (Workspace). Or copy the Skript*#
#* in the same folder as the MotionParameter.h file of the MotionCode.        *#
#*                                                                            *#
#*----------------------------------------------------------------------------*#
#*============================================================================*#
</pre>"""

#-----------------------------------------------------------------------------------------------------------------------
# Import
import time

#-----------------------------------------------------------------------------------------------------------------------
# Variables
Address = "127"             # CANopen NodeId 1..127
#Address = "192.168.0.1"    # Industrial Ethernet IP-Adress
#Address = "0"              # EtherCAT Device Number

#-----------------------------------------------------------------------------------------------------------------------
# Read the lines of MotionParameter.h which defines the Names to values of Debug variables
ClearOutputWindow()
rawDataEnumMYCommand = []
rawDataEnumProgramState =[]
rawDataEnumMYStatus = []
statusEnum = 0

# Open MotionParameter.h file
try:
   MP = open("./inc/MotionParameter.h")
except:
   try:
      MP = open("./MotionParameter.h")
   except FileNotFoundError:
      raise Exception("Error!!! MotionParameter.h File not found!!!")

# Search for lines in enums namesFor_MY_Command, namesFor_ProgramState and namesFor_MY_Status
for line in MP:
    if "enum tags_for_myCommand" in line:
      statusEnum = 1
    elif "enum tags_for_debugProgramState" in line:
      statusEnum = 3
    elif "enum tags_for_myStatus" in line:
      statusEnum = 5      
    if statusEnum == 1:
      rawDataEnumMYCommand.append(line)
      if line == "};\n":
         statusEnum = 2
    if statusEnum == 3:
      rawDataEnumProgramState.append(line)
      if line == "};\n":
         statusEnum = 4
    if statusEnum == 5:
      rawDataEnumMYStatus.append(line)
      if line == "};\n":
         statusEnum = 6
MP.close()

#print()
#print(rawDataEnumMYCommand)
#print(rawDataEnumProgramState)
#print(rawDataEnumMYStatus)

#-----------------------------------------------------------------------------------------------------------------------
# Filter the readed lines 
def filterRawData(rawData):
   output = []
   for line in rawData:                # Jede Zeile durchsuchen
      if "," in line:
         name = ""                     # Merker für State-Name
         number = ""                   # Merker für State-Nummer
         detectComment = 0             # Merker ob Zeile auskommentiert oder nicht
         detectBoader = 0              # Merker ob vor oder hinter dem "=", also ob Name oder Zahl
         for char in line:             # Jeden Buchstaben/char betrachten
            if detectComment == 0:     # Falls noch nicht erkannt, prüfen ob Zeile auskommentiert
               if char == "/":         # Wenn auskommentiert hier abbrechen
                  detectComment = 1
                  break
               elif char != " " and char != "\t":# Sobald erkannt, dass kein Kommentar merken
                  detectComment = 2
            if detectComment == 2:     # Wenn kein Kommentar Auswertung starten
               if char == ",":         # Bei , ist Zeile vorbei, danach höchstens noch Kommentare
                  break
               if char == "=":         # Bei "=" wird erkannt, dass jetzt Name vorbei ist und ab sofort Zahl ermittelt wird
                  detectBoader = 1
               if detectBoader == 0 and char != " " and char != "\t":# Falls gültiges Zeichen und Name den Buchstaben an Name anhängen
                  name += char
               else:
                  if char != "=" and char != " " and char != "\t": # Falls gültiges Zeichen und Zahl den Buchstaben an Number anhängen
                     number += char
         if detectComment == 2:        # Falls Zeile nicht auskommentiert Werte an output anhängen
            if "0x" in number:         # Falls Hex-wert diesen entsprechend konvertieren und das "0x" filtern
               output.append(int(number[2:len(number)], 16))
            else:
               output.append(int(number))
            output.append(name)
   return output

FilteredDataEnumMYCommand = filterRawData(rawDataEnumMYCommand)
FilteredDataEnumProgramState = filterRawData(rawDataEnumProgramState)
FilteredDataEnumMYStatus = filterRawData(rawDataEnumMYStatus)

print()
print(FilteredDataEnumMYCommand)
print(FilteredDataEnumProgramState)
print(FilteredDataEnumMYStatus)

#-----------------------------------------------------------------------------------------------------------------------
# Read and Translate the actual Debug Variables of the connected drive
MYCommand = None
ProgramState = None
MYStatus = None

def ReadAndTranslateDebugParameters():
   global MYCommand
   global ProgramState
   global MYStatus
   MYCommand = AcyclicRd(Address, ParameterId.MOTIONCODE_PARAMETER_UI32_01)
   try:
      MYCommand = FilteredDataEnumMYCommand[FilteredDataEnumMYCommand.index(MYCommand)+1]
   except:
      MYCommand = "Undefined"
   ProgramState = AcyclicRd(Address, ParameterId.MOTIONCODE_PARAMETER_UI32_03)
   try:
      ProgramState = FilteredDataEnumProgramState[FilteredDataEnumProgramState.index(ProgramState)+1]
   except:
      ProgramState  = "Undefined"
   MYStatus = AcyclicRd(Address, ParameterId.MOTIONCODE_PARAMETER_UI32_02)
   try:
      MYStatus = FilteredDataEnumMYStatus[FilteredDataEnumMYStatus.index(MYStatus)+1]
   except:
      MYStatus  = "Undefined"

while(1):
   ReadAndTranslateDebugParameters()
   #print(MA_Cmd, MA_State, M_State)
   #print('{0:15s} {1:35s} {2:23s}'.format(MA_Cmd, MA_State, M_State))
   print("myCommand =", MYCommand)
   print("debugProgramState =", ProgramState)
   print("myStatus =", MYStatus)
   print()
   time.sleep(0.5)
   