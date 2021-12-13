
import cantools
import configparser
import sys
import os
#sys.path.append('..\\Framework')


class Operation(object):

    def __init__(self):
        config = configparser.ConfigParser()
        root=os.getcwd()
        config.read(root+"\\Config.ini", encoding='utf-8')
        self.dbc_file_name = config.get("DBC_FILE", "NAME")
        self.dbc_node_name = config.get("DBC_NODE", "NAME")
        self.db = cantools.db.load_file(root +"\\"+ self.dbc_file_name + ".dbc")
        self.Msg = {}
        self.Signals = {}
         
    def GetMessages(self):#get all message in dbc, regardless of node
        messages = self.db.messages
        #print(messages)
        return messages

    def GetSignals(self, message):
        signals = message.signals
        #print(signals)
        return signals

    def format_receivers(self, signal):#get receive node for signal
        if signal.receivers:
            return ' ' + ','.join(signal.receivers)
        else:
            return 'Vector__XXX'

    def format_senders(self, message):#get TX message for node
        if message.senders:
            return message.senders[0]
        else:
            return 'Vector__XXX'

    def tx_info(self):
        #count=0
        for message in self.GetMessages():
            list1 = []   
            if self.dbc_node_name == self.format_senders(message).strip():#get all TX message
                '''
                count=count+1
                print(str(count)+": "+message.name)  
                '''              
                for sig in self.GetSignals(message):
                    if self.dbc_node_name not in self.format_receivers(sig).strip():
                        self.Msg[message.name] = {}
                        self.Msg[message.name]['ID'] = message.frame_id
                        self.Msg[message.name]['CycleTime'] = message.cycle_time
                        self.Msg[message.name]['DLC'] = message.length
                        self.Msg[message.name]['SendType'] = message.send_type
                        self.Msg[message.name]['Type'] = "Tx"
                        self.Msg[message.name]['Attribute'] = message.dbc.attributes.values()
                        list1.append(sig.name)
                        #print(sig.name)
                        if sig.is_signed is False:
                            if sig.scale < 1:
                                Maximum = (2 ** sig.length - 1) * sig.scale + sig.offset
                                Minimum = 0 * sig.scale + sig.offset
                                self.Signals[sig.name] = {"Factor": sig.scale, "Offset": sig.offset,
                                                          "Maximum": Maximum, "Minimum": Minimum,
                                                          "Value Type": sig.is_signed, 'Length': sig.length,
                                                          "Start": sig.start, "Comment": sig.comment}
                            elif sig.scale == 1:
                                Maximum = (2 ** sig.length - 1) * sig.scale + sig.offset
                                Minimum = 0 * sig.scale + sig.offset
                                self.Signals[sig.name] = {"Factor": sig.scale, "Offset": sig.offset,
                                                          "Maximum": Maximum, "Minimum": Minimum,
                                                          "Value Type": sig.is_signed, 'Length': sig.length,
                                                          "Start": sig.start, "Comment": sig.comment}
                            else:
                                Maximum = (2 ** sig.length - 1) * sig.scale + sig.offset
                                Minimum = 0 * sig.scale + sig.offset
                                self.Signals[sig.name] = {"Factor": sig.scale, "Offset": sig.offset,
                                                          "Maximum": Maximum, "Minimum": Minimum,
                                                          "Value Type": sig.is_signed, 'Length': sig.length,
                                                          "Start": sig.start, "Comment": sig.comment}
                        else:
                            if sig.scale < 1:
                                Maximum = (2 ** (sig.length - 1) - 1) * sig.scale + sig.offset
                                Minimum = -((2 ** (sig.length - 1)) * sig.scale + sig.offset)
                                self.Signals[sig.name] = {"Factor": sig.scale, "Offset": sig.offset,
                                                          "Maximum": Maximum, "Minimum": Minimum,
                                                          "Value Type": sig.is_signed, 'Length': sig.length,
                                                          "Start": sig.start, "Comment": sig.comment}
                            elif sig.scale == 1:
                                Maximum = (2 ** (sig.length - 1) - 1) * sig.scale + sig.offset
                                Minimum = -((2 ** (sig.length - 1)) * sig.scale + sig.offset)
                                self.Signals[sig.name] = {"Factor": sig.scale, "Offset": sig.offset,
                                                          "Maximum": Maximum, "Minimum": Minimum,
                                                          "Value Type": sig.is_signed, 'Length': sig.length,
                                                          "Start": sig.start, "Comment": sig.comment}
                            else:
                                Maximum = (2 ** (sig.length - 1) - 1) * sig.scale + sig.offset
                                Minimum = -((2 ** (sig.length - 1)) * sig.scale + sig.offset)
                                self.Signals[sig.name] = {"Factor": sig.scale, "Offset": sig.offset,
                                                          "Maximum": Maximum, "Minimum": Minimum,
                                                          "Value Type": sig.is_signed, 'Length': sig.length,
                                                          "Start": sig.start, "Comment": sig.comment}
            if len(list1) == 0:
                pass
            else:
                self.Msg[message.name]['Signals'] = list1
                #print(len(list1))
        print(len(self.Msg))
        print(len(self.Signals))

    def rx_info(self):
        #count=0
        for message in self.GetMessages():           
            list2 = []
            if self.dbc_node_name != self.format_senders(message).strip():
                '''
                count=count+1
                print(str(count)+": "+message.name)
                '''
                for sig in self.GetSignals(message):
                    if self.dbc_node_name in self.format_receivers(sig).strip():#get all receive signal for selected node
                        self.Msg[message.name] = {}
                        self.Msg[message.name]['ID'] = message.frame_id
                        self.Msg[message.name]['CycleTime'] = message.cycle_time
                        self.Msg[message.name]['DLC'] = message.length
                        self.Msg[message.name]['SendType'] = message.send_type
                        self.Msg[message.name]['Type'] = "Rx"
                        self.Msg[message.name]['Attribute'] = message.dbc.attributes.values()
                        list2.append(sig.name)
                        if sig.length>32:
                            self.Signals[sig.name] = {"Factor": sig.scale, "Offset": sig.offset,
                                                            "Maximum": sig.maximum, "Minimum": sig.minimum,
                                                            "Value Type": sig.is_signed, 'Length': sig.length,
                                                            "Start": sig.start, "Comment": sig.comment,
                                                            "Choices": sig.choices, "DataType": sig.is_float,
                                                            "DataLength": 64}
                        else:
                            self.Signals[sig.name] = {"Factor": sig.scale, "Offset": sig.offset,
                                                            "Maximum": sig.maximum, "Minimum": sig.minimum,
                                                            "Value Type": sig.is_signed, 'Length': sig.length,
                                                            "Start": sig.start, "Comment": sig.comment,
                                                            "Choices": sig.choices, "DataType": sig.is_float,
                                                            "DataLength": 32}

                        #print(sig.name)
                        '''
                        if sig.is_signed is False:
                            if sig.scale < 1:
                                Maximum = (2 ** sig.length - 1) * sig.scale + sig.offset
                                Minimum = 0 * sig.scale + sig.offset
                                self.Signals[sig.name] = {"Factor": sig.scale, "Offset": sig.offset,
                                                          "Maximum": Maximum, "Minimum": Minimum,
                                                          "Value Type": sig.is_signed, 'Length': sig.length,
                                                          "Start": sig.start, "Comment": sig.comment,
                                                          "Choices": sig.choices, "DataType": sig.is_float}
                            elif sig.scale == 1:
                                Maximum = (2 ** sig.length - 1) * sig.scale + sig.offset
                                Minimum = 0 * sig.scale + sig.offset
                                self.Signals[sig.name] = {"Factor": sig.scale, "Offset": sig.offset,
                                                          "Maximum": Maximum, "Minimum": Minimum,
                                                          "Value Type": sig.is_signed, 'Length': sig.length,
                                                          "Start": sig.start, "Comment": sig.comment,
                                                          "Choices": sig.choices, "DataType": sig.is_float}
                            else:
                                Maximum = (2 ** sig.length - 1) * sig.scale + sig.offset
                                Minimum = 0 * sig.scale + sig.offset
                                self.Signals[sig.name] = {"Factor": sig.scale, "Offset": sig.offset,
                                                          "Maximum": Maximum, "Minimum": Minimum,
                                                          "Value Type": sig.is_signed, 'Length': sig.length,
                                                          "Start": sig.start, "Comment": sig.comment,
                                                          "Choices": sig.choices, "DataType": sig.is_float}
                        else:
                            if sig.scale < 1:
                                Maximum = (2 ** (sig.length - 1) - 1) * sig.scale + sig.offset
                                Minimum = -((2 ** (sig.length - 1)) * sig.scale + sig.offset)
                                self.Signals[sig.name] = {"Factor": sig.scale, "Offset": sig.offset,
                                                          "Maximum": Maximum, "Minimum": Minimum,
                                                          "Value Type": sig.is_signed, 'Length': sig.length,
                                                          "Start": sig.start, "Comment": sig.comment,
                                                          "Choices": sig.choices, "DataType": sig.is_float}
                            elif sig.scale == 1:
                                Maximum = (2 ** (sig.length - 1) - 1) * sig.scale + sig.offset
                                Minimum = -((2 ** (sig.length - 1)) * sig.scale + sig.offset)
                                self.Signals[sig.name] = {"Factor": sig.scale, "Offset": sig.offset,
                                                          "Maximum": Maximum, "Minimum": Minimum,
                                                          "Value Type": sig.is_signed, 'Length': sig.length,
                                                          "Start": sig.start, "Comment": sig.comment,
                                                          "Choices": sig.choices, "DataType": sig.is_float}
                            else:
                                Maximum = (2 ** (sig.length - 1) - 1) * sig.scale + sig.offset
                                Minimum = -((2 ** (sig.length - 1)) * sig.scale + sig.offset)
                                self.Signals[sig.name] = {"Factor": sig.scale, "Offset": sig.offset,
                                                          "Maximum": Maximum, "Minimum": Minimum,
                                                          "Value Type": sig.is_signed, 'Length': sig.length,
                                                          "Start": sig.start, "Comment": sig.comment,
                                                          "Choices": sig.choices, "DataType": sig.is_float}
                        '''
            if len(list2) == 0:
                pass
            else:
                self.Msg[message.name]['Signals'] = list2
        print(len(self.Msg))
        print(len(self.Signals))


    def generate_file(self, file_name):#generate CAPL file
        CycTimeL=[]
        with open(file_name + ".can", 'w') as f:
            f.write("/*@!Encoding:936*/\n")
            f.write("\nincludes\n{\n\n}\n")
            f.write("\nvariables\n{\n")
            for key in self.Msg:
                if self.Msg[key]['Type'] == "Rx":
                    f.write("   message "+key+" Msg_"+key+";\n") 
                if self.Msg[key]['CycleTime']  not in CycTimeL:
                    CycTimeL.append(self.Msg[key]['CycleTime']) 
            for cyctime in  CycTimeL:                                
                f.write("   msTimer " + "Timer_" + str(cyctime) + "ms;\n")
            f.write("}\n\n")
            f.write("on start\n{\n")
            for cyctime in  CycTimeL:#set timer
                f.write("   setTimerCyclic(Timer_" + str(cyctime) + "ms, " + str(cyctime) + ");\n")
            f.write("}\n\n")
            for cyctime in  CycTimeL:
                f.write("on timer " + "Timer_" + str(cyctime) + "ms\n{\n")
                for key in self.Msg:
                    if self.Msg[key]['CycleTime'] == cyctime:
                        for keys in self.Msg[key]['Signals']:
                            f.write("   Msg_" + key + "." + keys + ".phys = @sysvar::Msg"+key+"::Sig"+keys+";\n")
                        f.write("   output(Msg_" + key + ");\n")
                f.write("}\n")

    def generate_var_file(self, file_name): #generate CANoe Sysvar file
         with open(file_name + ".vsysvar", 'w') as f:
             f.write('<?xml version=\"1.0\" encoding=\"utf-8\"?>\n')
             f.write('<systemvariables version=\"4\">\n')
             f.write('  <namespace name=\"\" comment=\"\" interface=\"\">\n')
             for key in self.Msg:                
                 if self.Msg[key]['Type'] == "Rx":                    
                     f.write('    <namespace name=\"Msg'+key+'\" comment=\"\" interface=\"\">\n')
                     for keys in self.Msg[key]['Signals']: 
                         if((self.Signals[keys]['Minimum'] != None)):
                            if(self.Signals[keys]["Minimum"]>0):
                                start_v=self.Signals[keys]["Minimum"]
                            elif(self.Signals[keys]["Maximum"]<0):
                                start_v=self.Signals[keys]["Maximum"]
                            else:
                                start_v=0
                         else:
                             start_v=0
                         if (type(self.Signals[keys]['Factor'])== int) & (self.Signals[keys]['Minimum'] == None):
                             f.write('      <variable anlyzLocal=\"2\" readOnly=\"false\" valueSequence=\"false\" unit=\"\" name=\"Sig'+keys+'\" comment=\"\" bitcount=\"'+str(self.Signals[keys]['DataLength'])+'\" isSigned=\"false\" encoding=\"65001\" type=\"int\" startValue=\"'+str(start_v)+'\" minValue=\"'+str(0)+'\" minValuePhys=\"'+str(0)+'\" maxValue=\"'+str(0)+'\" maxValuePhys=\"'+str(0)+'\" />\n')
                         elif (type(self.Signals[keys]['Factor'])== float) & (self.Signals[keys]['Minimum']== None):
                             f.write('      <variable anlyzLocal=\"2\" readOnly=\"false\" valueSequence=\"false\" unit=\"\" name=\"Sig'+keys+'\" comment=\"\" bitcount=\"'+str(self.Signals[keys]['DataLength'])+'\" isSigned=\"false\" encoding=\"65001\" type=\"float\" startValue=\"'+str(start_v)+'\" minValue=\"'+str(0)+'\" maxValue=\"'+str(0)+'\" />\n')
                         elif (type(self.Signals[keys]['Factor'])== int) & (self.Signals[keys]['Minimum']>=0):
                             f.write('      <variable anlyzLocal=\"2\" readOnly=\"false\" valueSequence=\"false\" unit=\"\" name=\"Sig'+keys+'\" comment=\"\" bitcount=\"'+str(self.Signals[keys]['DataLength'])+'\" isSigned=\"false\" encoding=\"65001\" type=\"int\" startValue=\"'+str(start_v)+'\" minValue=\"'+str(self.Signals[keys]["Minimum"])+'\" minValuePhys=\"'+str(self.Signals[keys]["Minimum"])+'\" maxValue=\"'+str(self.Signals[keys]["Maximum"])+'\" maxValuePhys=\"'+str(self.Signals[keys]["Maximum"])+'\" />\n')
                         elif (type(self.Signals[keys]['Factor'])== float) & (self.Signals[keys]['Minimum']>=0):
                             f.write('      <variable anlyzLocal=\"2\" readOnly=\"false\" valueSequence=\"false\" unit=\"\" name=\"Sig'+keys+'\" comment=\"\" bitcount=\"'+str(self.Signals[keys]['DataLength'])+'\" isSigned=\"false\" encoding=\"65001\" type=\"float\" startValue=\"'+str(start_v)+'\" minValue=\"'+str(self.Signals[keys]["Minimum"])+'\" maxValue=\"'+str(self.Signals[keys]["Maximum"])+'\" />\n')
                         elif (type(self.Signals[keys]['Factor'])== int) & (self.Signals[keys]['Minimum']<0):
                             f.write('      <variable anlyzLocal=\"2\" readOnly=\"false\" valueSequence=\"false\" unit=\"\" name=\"Sig'+keys+'\" comment=\"\" bitcount=\"'+str(self.Signals[keys]['DataLength'])+'\" isSigned=\"true\" encoding=\"65001\" type=\"int\" startValue=\"'+str(start_v)+'\" minValue=\"'+str(self.Signals[keys]["Minimum"])+'\" minValuePhys=\"'+str(self.Signals[keys]["Minimum"])+'\" maxValue=\"'+str(self.Signals[keys]["Maximum"])+'\" maxValuePhys=\"'+str(self.Signals[keys]["Maximum"])+'\" />\n')
                         elif (type(self.Signals[keys]['Factor'])== float) & (self.Signals[keys]['Minimum']<0):
                             f.write('      <variable anlyzLocal=\"2\" readOnly=\"false\" valueSequence=\"false\" unit=\"\" name=\"Sig'+keys+'\" comment=\"\" bitcount=\"'+str(self.Signals[keys]['DataLength'])+'\" isSigned=\"true\" encoding=\"65001\" type=\"float\" startValue=\"'+str(start_v)+'\" minValue=\"'+str(self.Signals[keys]["Minimum"])+'\" maxValue=\"'+str(self.Signals[keys]["Maximum"])+'\" />\n')
                     f.write('    </namespace>\n')
             f.write('  </namespace>\n')
             f.write('</systemvariables>')

    def run(self):
        #self.tx_info()
        self.rx_info()
        self.generate_file("ECU_Default_Value_CAPL")
        self.generate_var_file("ECU_Default_Value_CAPL")
        #print(self.Msg)

def main():
    op = Operation()
    op.run()
    #print("aaa")   


if __name__ == '__main__':
    main()
