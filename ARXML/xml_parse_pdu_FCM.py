import sys
#sys.path.append('..\\Framework')
import os
import configparser
import xml.dom.minidom


class Operation(object):

    def __init__(self):
        self.config = configparser.ConfigParser()
        root=os.getcwd()
        self.config.read(root+"\\Config_fcm.ini", encoding='utf-8')
        self.xml = self.config.get("IPD_COMMUNICATION_XML", "NAME")
        self.cluster =self.config.get("CAN_CLUSTER","NAME")
        self.Frame_Pdu = {}
        self.Pdu_Signal = {}
        self.Container_Pdu = {}
        self.Data_Type = {}
        self.Compu_Method = {}

    def get_info(self, filename,clustername):
        root=os.getcwd()
        doc = xml.dom.minidom.parse(root+"\\" + filename + ".arxml")
        doc.toxml("utf-8")
        root = doc.documentElement
        ar_packages = root.getElementsByTagName("AR-PACKAGE")
        for ar_package in ar_packages:
            '''
            if ar_package.childNodes[1].childNodes[0].nodeValue == "Topology":
                elements = ar_package.childNodes[3]
                CAN_CLUSTERs = elements.getElementsByTagName("CAN-CLUSTER")
                for CAN_CLUSTER in CAN_CLUSTERs:
                    # 获取IPD的CAN_CLUSTER_NAME
                    CAN_CLUSTER_NAME = CAN_CLUSTER.childNodes[1].childNodes[0].nodeValue
                    # print(CAN_CLUSTER_NAME)
                    self.Frame_Pdu[CAN_CLUSTER_NAME] = {}
                    CAN_PHYSICAL_CHANNELs = CAN_CLUSTER.getElementsByTagName("CAN-PHYSICAL-CHANNEL")
                    for CAN_PHYSICAL_CHANNEL in CAN_PHYSICAL_CHANNELs:
                        # 获取IPD的CAN_PHYSICAL_CHANNEL_NAME
                        CAN_PHYSICAL_CHANNEL_NAME = CAN_PHYSICAL_CHANNEL.childNodes[1].childNodes[0].nodeValue
                        # print(CAN_PHYSICAL_CHANNEL_NAME)
                        self.Frame_Pdu[CAN_CLUSTER_NAME][CAN_PHYSICAL_CHANNEL_NAME] = {}
                        self.Frame_Pdu[CAN_CLUSTER_NAME][CAN_PHYSICAL_CHANNEL_NAME]['Tx_Frames'] = {}
                        self.Frame_Pdu[CAN_CLUSTER_NAME][CAN_PHYSICAL_CHANNEL_NAME]['Rx_Frames'] = {}
                        CAN_FRAME_TRIGGERINGs = CAN_PHYSICAL_CHANNEL.getElementsByTagName("CAN-FRAME-TRIGGERING")
                        for CAN_FRAME_TRIGGERING in CAN_FRAME_TRIGGERINGs:
                            # 获取IPD的CAN_FRAME_TRIGGERING_NAME
                            # CAN_FRAME_TRIGGERING_NAME = CAN_FRAME_TRIGGERING.childNodes[1].childNodes[0].nodeValue
                            FRAME_PORT_REFs = CAN_FRAME_TRIGGERING.getElementsByTagName("FRAME-PORT-REFS")
                            for FRAME_PORT_REF in FRAME_PORT_REFs:
                                # 获取IPD的FRAME_PORT_REF_NAME
                                FRAME_PORT_REF_NAME = FRAME_PORT_REF.childNodes[1].childNodes[0].nodeValue
                                FRAME_PORT = FRAME_PORT_REF_NAME.split("/")[-1:][0]
                                # print(FRAME_PORT)
                                if FRAME_PORT == "FramePort_In":
                                    # 获取IPD的FRAME_NAME
                                    FRAME_REFs = CAN_FRAME_TRIGGERING.getElementsByTagName("FRAME-REF")[0].childNodes[0].nodeValue
                                    FRAME_REF_NAME = FRAME_REFs.split("/")[-1:][0]
                                    self.Frame_Pdu[CAN_CLUSTER_NAME][CAN_PHYSICAL_CHANNEL_NAME]['Rx_Frames'][FRAME_REF_NAME] = {}
                                    self.Frame_Pdu[CAN_CLUSTER_NAME][CAN_PHYSICAL_CHANNEL_NAME]['Rx_Frames'][FRAME_REF_NAME]['ID'] = {}
                                    self.Frame_Pdu[CAN_CLUSTER_NAME][CAN_PHYSICAL_CHANNEL_NAME]['Rx_Frames'][FRAME_REF_NAME]['PDU'] = {}
                                    # 获取IPD的FRAME_IDENTIFIER
                                    IDENTIFIERs = CAN_FRAME_TRIGGERING.getElementsByTagName("IDENTIFIER")[0].childNodes[0].nodeValue
                                    a = hex(int(IDENTIFIERs))
                                    b = a.replace("0x", "").upper()
                                    self.Frame_Pdu[CAN_CLUSTER_NAME][CAN_PHYSICAL_CHANNEL_NAME]['Rx_Frames'][FRAME_REF_NAME]['ID'] = "0x" + b
                                    # 获取IPD的FRAME_PDU
                                    PDU_TRIGGERING_REFs = CAN_FRAME_TRIGGERING.getElementsByTagName("PDU-TRIGGERING-REF")[0].childNodes[0].nodeValue
                                    PDU_TRIGGERING_REF_NAME = PDU_TRIGGERING_REFs.split("/")[-1:][0].split("PduTr")[1]
                                    self.Frame_Pdu[CAN_CLUSTER_NAME][CAN_PHYSICAL_CHANNEL_NAME]['Rx_Frames'][FRAME_REF_NAME]['PDU'] = PDU_TRIGGERING_REF_NAME
                                elif FRAME_PORT == "FramePort_Out":
                                    # 获取IPD的FRAME_NAME
                                    FRAME_REFs = CAN_FRAME_TRIGGERING.getElementsByTagName("FRAME-REF")[0].childNodes[0].nodeValue
                                    FRAME_REF_NAME = FRAME_REFs.split('/')[-1:][0]
                                    self.Frame_Pdu[CAN_CLUSTER_NAME][CAN_PHYSICAL_CHANNEL_NAME]['Tx_Frames'][FRAME_REF_NAME] = {}
                                    self.Frame_Pdu[CAN_CLUSTER_NAME][CAN_PHYSICAL_CHANNEL_NAME]['Tx_Frames'][FRAME_REF_NAME]['ID'] = {}
                                    self.Frame_Pdu[CAN_CLUSTER_NAME][CAN_PHYSICAL_CHANNEL_NAME]['Tx_Frames'][FRAME_REF_NAME]['PDU'] = {}
                                    # 获取IPD的FRAME_IDENTIFIER
                                    IDENTIFIERs = CAN_FRAME_TRIGGERING.getElementsByTagName("IDENTIFIER")[0].childNodes[0].nodeValue
                                    a = hex(int(IDENTIFIERs))
                                    b = a.replace("0x", "").upper()
                                    self.Frame_Pdu[CAN_CLUSTER_NAME][CAN_PHYSICAL_CHANNEL_NAME]['Tx_Frames'][FRAME_REF_NAME]['ID'] = "0x" + b
                                    # 获取IPD的FRAME_PDU
                                    PDU_TRIGGERING_REFs = CAN_FRAME_TRIGGERING.getElementsByTagName("PDU-TRIGGERING-REF")[0].childNodes[0].nodeValue
                                    PDU_TRIGGERING_REF_NAME = PDU_TRIGGERING_REFs.split("/")[-1:][0].split("PduTr")[1]
                                    self.Frame_Pdu[CAN_CLUSTER_NAME][CAN_PHYSICAL_CHANNEL_NAME]['Tx_Frames'][FRAME_REF_NAME]['PDU'] = PDU_TRIGGERING_REF_NAME
                                else:
                                    print(FRAME_PORT)
            '''
           
            #get all the info of pdu with signal
            if ar_package.childNodes[1].childNodes[0].nodeValue == "PDUs":
                elements = ar_package.childNodes[3]
                FRAME_PORTs = elements.getElementsByTagName('I-SIGNAL-I-PDU-GROUP')
                for FRAME_PORT in FRAME_PORTs:
                    FRAME_PORTs_NAME = FRAME_PORT.childNodes[1].childNodes[0].nodeValue
                    self.Frame_Pdu[FRAME_PORTs_NAME] = {}
                    self.Frame_Pdu[FRAME_PORTs_NAME]['PDU'] = []
                    if FRAME_PORTs_NAME == (clustername+"_Rx"):#TBD, depends on frame port name
                        self.Frame_Pdu[FRAME_PORTs_NAME]['Type'] = "RX_PDU"
                        I_SIGNAL_I_PDU_REFs = FRAME_PORT.getElementsByTagName("I-SIGNAL-I-PDU-REF-CONDITIONAL")
                        for I_SIGNAL_I_PDU_REF in I_SIGNAL_I_PDU_REFs:
                            I_SIGNAL_I_PDU_REF_name = I_SIGNAL_I_PDU_REF.childNodes[1].childNodes[0].nodeValue
                            self.Frame_Pdu[FRAME_PORTs_NAME]['PDU'].append(I_SIGNAL_I_PDU_REF_name.split('/')[-1:][0])
                            
                    else:
                        self.Frame_Pdu[FRAME_PORTs_NAME]['Type'] = "TX_PDU"
                        I_SIGNAL_I_PDU_REFs = FRAME_PORT.getElementsByTagName("I-SIGNAL-I-PDU-REF-CONDITIONAL")
                        for I_SIGNAL_I_PDU_REF in I_SIGNAL_I_PDU_REFs:
                            I_SIGNAL_I_PDU_REF_name = I_SIGNAL_I_PDU_REF.childNodes[1].childNodes[0].nodeValue
                            self.Frame_Pdu[FRAME_PORTs_NAME]['PDU'].append(I_SIGNAL_I_PDU_REF_name.split('/')[-1:][0])
                            
                    #print(self.Frame_Pdu[FRAME_PORTs_NAME]['PDU'])
                
                NM_PDUs = elements.getElementsByTagName("NM-PDU")    
                for NM_PDU in NM_PDUs:
                    # 获取IPD的NM_PDU
                    NM_PDU_NAME = NM_PDU.childNodes[1].childNodes[0].nodeValue
                    #print(NM_PDU_NAME)
                    self.Pdu_Signal[NM_PDU_NAME] = {}
                    self.Pdu_Signal[NM_PDU_NAME]['Type'] = "NM_Signal"
                    self.Pdu_Signal[NM_PDU_NAME]['Signal'] = []
                    I_SIGNAL_TO_I_PDU_MAPPINGs = NM_PDU.getElementsByTagName("I-SIGNAL-TO-I-PDU-MAPPING")
                    for I_SIGNAL_TO_I_PDU_MAPPING in I_SIGNAL_TO_I_PDU_MAPPINGs:
                        # 获取IPD的NM_PDU_SIGNAL
                        I_SIGNAL_TO_I_PDU_MAPPING_NAME = I_SIGNAL_TO_I_PDU_MAPPING.childNodes[1].childNodes[0].nodeValue
                        self.Pdu_Signal[NM_PDU_NAME]['Signal'].append(I_SIGNAL_TO_I_PDU_MAPPING_NAME)

                I_SIGNAL_I_PDUs = elements.getElementsByTagName("I-SIGNAL-I-PDU")
                for I_SIGNAL_I_PDU in I_SIGNAL_I_PDUs:
                    # 获取IPD的I_PDU
                    I_SIGNAL_I_PDU_NAME = I_SIGNAL_I_PDU.childNodes[1].childNodes[0].nodeValue
                    #print(I_SIGNAL_I_PDU_NAME)                    
                    self.Pdu_Signal[I_SIGNAL_I_PDU_NAME] = {}
                    self.Pdu_Signal[I_SIGNAL_I_PDU_NAME]['Type'] = "I_Signal"
                    REFLECTITION_PERIODS = I_SIGNAL_I_PDU.getElementsByTagName("REPETITION-PERIOD")
                    for REFLECTITION_PERIOD in REFLECTITION_PERIODS:
                        self.Pdu_Signal[I_SIGNAL_I_PDU_NAME]['TimePeriod'] = 5
                    TIME_PERIODs = I_SIGNAL_I_PDU.getElementsByTagName("TIME-PERIOD")
                    for TIME_PERIOD in TIME_PERIODs:
                        self.Pdu_Signal[I_SIGNAL_I_PDU_NAME]['TimePeriod'] = TIME_PERIOD.childNodes[1].childNodes[0].nodeValue
                    self.Pdu_Signal[I_SIGNAL_I_PDU_NAME]['Signal'] = []
                    I_SIGNAL_TO_I_PDU_MAPPINGs = I_SIGNAL_I_PDU.getElementsByTagName("I-SIGNAL-TO-I-PDU-MAPPING")                  
                    for I_SIGNAL_TO_I_PDU_MAPPING in I_SIGNAL_TO_I_PDU_MAPPINGs:
                        # 获取IPD的I_PDU_SIGNAL
                        I_SIGNAL_TO_I_PDU_MAPPING_NAME = I_SIGNAL_TO_I_PDU_MAPPING.childNodes[1].childNodes[0].nodeValue
                        if I_SIGNAL_TO_I_PDU_MAPPING.childNodes[3].nodeName=="I-SIGNAL-GROUP-REF":#delete group signal
                            pass
                        else:
                            self.Pdu_Signal[I_SIGNAL_I_PDU_NAME]['Signal'].append(I_SIGNAL_TO_I_PDU_MAPPING_NAME)
                            
                
            
            
            if ar_package.childNodes[1].childNodes[0].nodeValue == "Signals":
                elements = ar_package.childNodes[3]
                I_SIGNALs = elements.getElementsByTagName("I-SIGNAL")
                for I_SIGNAL in I_SIGNALs:
                    # 获取IPD的Signal
                    I_SIGNAL_NAME = I_SIGNAL.childNodes[1].childNodes[0].nodeValue[1:]
                    
                    self.Data_Type[I_SIGNAL_NAME] = {}
                    data_length = int(I_SIGNAL.getElementsByTagName("LENGTH")[0].childNodes[0].nodeValue)                   
                    if data_length>32:
                        self.Data_Type[I_SIGNAL_NAME]['DataLength'] = 64
                    else:
                        self.Data_Type[I_SIGNAL_NAME]['DataLength'] = 32
                    self.Data_Type[I_SIGNAL_NAME]['BaseType'] = {}
                    self.Data_Type[I_SIGNAL_NAME]['Compu_Method'] = {}
                    NETWORK_REPRESENTATION_PROPs = I_SIGNAL.getElementsByTagName("NETWORK-REPRESENTATION-PROPS")
                    for NETWORK_REPRESENTATION_PROP in NETWORK_REPRESENTATION_PROPs:
                        # 获取IPD的Signal的BaseType
                        BASE_TYPE_REF_NAME = NETWORK_REPRESENTATION_PROP.getElementsByTagName("BASE-TYPE-REF")[0].childNodes[0].nodeValue
                        self.Data_Type[I_SIGNAL_NAME]['BaseType'] = BASE_TYPE_REF_NAME.split("/")[-1:][0]
                        # 获取IPD的Signal的COMPU-METHOD
                        COMPU_METHOD_REF_NAME = NETWORK_REPRESENTATION_PROP.getElementsByTagName("COMPU-METHOD-REF")[0].childNodes[0].nodeValue
                        self.Data_Type[I_SIGNAL_NAME]['Compu_Method'] = COMPU_METHOD_REF_NAME.split("/")[-1:][0]
            
            #get signal value scope for all signal
            if ar_package.childNodes[1].childNodes[0].nodeValue == "CompuMethods":
                elements = ar_package.childNodes[3]
                COMPU_METHODs = elements.getElementsByTagName("COMPU-METHOD")
                for COMPU_METHOD in COMPU_METHODs:
                    COMPU_METHOD_NAME = COMPU_METHOD.childNodes[1].childNodes[0].nodeValue
                    
                    self.Compu_Method[COMPU_METHOD_NAME] = {}
                    if COMPU_METHOD.getElementsByTagName("CATEGORY")[0].childNodes[0].nodeValue == "LINEAR":
                        Min = COMPU_METHOD.getElementsByTagName("LOWER-LIMIT")[0].childNodes[0].nodeValue
                        Max = COMPU_METHOD.getElementsByTagName("UPPER-LIMIT")[0].childNodes[0].nodeValue
                        if Max == Min:
                            self.Compu_Method[COMPU_METHOD_NAME].update({"Max": 1, "Min": 0})
                        else:
                            self.Compu_Method[COMPU_METHOD_NAME].update({"Max": float(Max), "Min": float(Min)})
                        COMPU_NUMERATORs = COMPU_METHOD.getElementsByTagName("COMPU-NUMERATOR")
                        for COMPU_NUMERATOR in COMPU_NUMERATORs:
                            Offset = COMPU_NUMERATOR.childNodes[1].childNodes[0].nodeValue
                            Factor = COMPU_NUMERATOR.childNodes[3].childNodes[0].nodeValue
                            self.Compu_Method[COMPU_METHOD_NAME].update({"Offset": float(Offset), "Factor": float(Factor)})
                            max_value=self.Compu_Method[COMPU_METHOD_NAME]['Factor']*self.Compu_Method[COMPU_METHOD_NAME]['Max']+self.Compu_Method[COMPU_METHOD_NAME]['Offset']
                            min_value=self.Compu_Method[COMPU_METHOD_NAME]['Factor']*self.Compu_Method[COMPU_METHOD_NAME]['Min']+self.Compu_Method[COMPU_METHOD_NAME]['Offset']
                            self.Compu_Method[COMPU_METHOD_NAME].update({"Maximum": max_value,"Minimum":min_value})
                    elif COMPU_METHOD.getElementsByTagName("CATEGORY")[0].childNodes[0].nodeValue == "TEXTTABLE":
                        COMPU_SCALES = COMPU_METHOD.getElementsByTagName("COMPU-SCALE")
                        COMPU_SCALE_NUM =0
                        for COMPU_SCALE in COMPU_SCALES:
                            COMPU_SCALE_NUM = COMPU_SCALE_NUM + 1
                        self.Compu_Method[COMPU_METHOD_NAME].update({"Offset": 0, "Factor": 1, "Max": COMPU_SCALE_NUM-1, "Min": 0,"Maximum": COMPU_SCALE_NUM-1,"Minimum":0})
                    elif COMPU_METHOD.getElementsByTagName("CATEGORY")[0].childNodes[0].nodeValue == "SCALE_LINEAR_AND_TEXTTABLE":
                        COMPU_NUMERATORs = COMPU_METHOD.getElementsByTagName("COMPU-NUMERATOR")
                        if len(COMPU_NUMERATORs) != 0:
                            for COMPU_NUMERATOR in COMPU_NUMERATORs:
                                Offset = COMPU_NUMERATOR.childNodes[1].childNodes[0].nodeValue
                                Factor = COMPU_NUMERATOR.childNodes[3].childNodes[0].nodeValue
                                self.Compu_Method[COMPU_METHOD_NAME].update({"Offset": float(Offset), "Factor": float(Factor)})
                                self.Compu_Method[COMPU_METHOD_NAME].update({"Max": 1, "Min": 0})
                        else:
                            self.Compu_Method[COMPU_METHOD_NAME].update({"Offset": 0, "Factor": 1})
                            self.Compu_Method[COMPU_METHOD_NAME].update({"Max": 1, "Min": 0})
                    elif COMPU_METHOD.getElementsByTagName("CATEGORY")[0].childNodes[0].nodeValue == "IDENTICAL":
                        self.Compu_Method[COMPU_METHOD_NAME].update({"Offset": 0, "Factor": 1, "Max": 1, "Min": 0})
                    else:
                        print(COMPU_METHOD.getElementsByTagName("CATEGORY")[0].childNodes[0].nodeValue)
                    

    def generate_file(self, file_name):
        CycTimeL=[]
        with open(file_name + ".can", 'w') as f:
            f.write("/*@!Encoding:936*/\n")
            f.write("\nincludes\n{\n\n}\n")
            f.write("\nvariables\n{\n")
            for key in self.Frame_Pdu:
                if self.Frame_Pdu[key]['Type'] == "RX_PDU":                    
                    for key1 in self.Frame_Pdu[key]['PDU']:
                        f.write("   pdu "+key1+" pdu_"+key1+";\n") 
                        #print(self.Pdu_Signal[key1]['TimePeriod'])
                        if self.Pdu_Signal[key1]['TimePeriod']  not in CycTimeL:
                            print(key1+":  "+str(self.Pdu_Signal[key1]['TimePeriod']))
                            CycTimeL.append(self.Pdu_Signal[key1]['TimePeriod']) 
            for cyctime in  CycTimeL: 
                cyctime1 = int(float(cyctime)*1000)                             
                f.write("   msTimer " + "Timer_" + str(cyctime1) + "ms;\n")
            f.write("}\n\n")
            f.write("on start\n{\n")
            for cyctime in  CycTimeL:#set timer
                cyctime1 = int(float(cyctime)*1000) 
                f.write("   setTimerCyclic(Timer_" + str(cyctime1) + "ms, " + str(cyctime1) + ");\n")
            f.write("}\n\n")
            for cyctime in  CycTimeL:
                cyctime1 = int(float(cyctime)*1000)  
                f.write("on timer " + "Timer_" + str(cyctime1) + "ms\n{\n")
                for key in self.Frame_Pdu:
                    if self.Frame_Pdu[key]['Type'] == "RX_PDU":
                        for key1 in self.Frame_Pdu[key]['PDU']:
                            if self.Pdu_Signal[key1]['TimePeriod'] == cyctime:
                                for keys in self.Pdu_Signal[key1]['Signal']:
                                    f.write("   pdu_" + key1 + ".I" + keys + ".phys = @sysvar::Msg"+key1+"::Sig"+keys+";\n") #@sysvar::Msg"+key1+"::Sig"+keys
                                f.write("   triggerPDU(pdu_" + key1 + ");\n")
                f.write("}\n")

    def generate_sysvar(self, var_filename):
        with open(var_filename + ".vsysvar", 'w') as f:
             f.write('<?xml version=\"1.0\" encoding=\"utf-8\"?>\n')
             f.write('<systemvariables version=\"4\">\n')
             f.write('  <namespace name=\"\" comment=\"\" interface=\"\">\n')
             for key in self.Frame_Pdu:                
                 if self.Frame_Pdu[key]['Type'] == "RX_PDU":   
                     for key1 in self.Frame_Pdu[key]['PDU']:                 
                        f.write('    <namespace name=\"Msg'+key1+'\" comment=\"\" interface=\"\">\n')
                        for keys in self.Pdu_Signal[key1]['Signal']: 
                            #print(keys)
                            if keys not in self.Compu_Method:
                                self.Compu_Method[keys] = self.Compu_Method[(self.Data_Type[keys]['Compu_Method'])]
                            if((self.Compu_Method[keys]['Minimum'] != None)):
                                if(self.Compu_Method[keys]["Minimum"]>0):
                                    start_v=self.Compu_Method[keys]["Minimum"]
                                elif(self.Compu_Method[keys]["Maximum"]<0):
                                    start_v=self.Compu_Method[keys]["Maximum"]
                                else:
                                    start_v=0
                            else:
                                start_v=0
                            if (type(self.Compu_Method[keys]['Factor'])== int) & (self.Compu_Method[keys]['Minimum'] == None):
                                f.write('      <variable anlyzLocal=\"2\" readOnly=\"false\" valueSequence=\"false\" unit=\"\" name=\"Sig'+keys+'\" comment=\"\" bitcount=\"'+str(self.Data_Type[keys]['DataLength'])+'\" isSigned=\"false\" encoding=\"65001\" type=\"int\" startValue=\"'+str(start_v)+'\" minValue=\"'+str(0)+'\" minValuePhys=\"'+str(0)+'\" maxValue=\"'+str(0)+'\" maxValuePhys=\"'+str(0)+'\" />\n')
                            elif (type(self.Compu_Method[keys]['Factor'])== float) & (self.Compu_Method[keys]['Minimum']== None):
                                f.write('      <variable anlyzLocal=\"2\" readOnly=\"false\" valueSequence=\"false\" unit=\"\" name=\"Sig'+keys+'\" comment=\"\" bitcount=\"'+str(self.Data_Type[keys]['DataLength'])+'\" isSigned=\"false\" encoding=\"65001\" type=\"float\" startValue=\"'+str(start_v)+'\" minValue=\"'+str(0)+'\" maxValue=\"'+str(0)+'\" />\n')
                            elif (type(self.Compu_Method[keys]['Factor'])== int) & (self.Compu_Method[keys]['Minimum']>=0):                               
                                f.write('      <variable anlyzLocal=\"2\" readOnly=\"false\" valueSequence=\"false\" unit=\"\" name=\"Sig'+keys+'\" comment=\"\" bitcount=\"'+str(self.Data_Type[keys]['DataLength'])+'\" isSigned=\"false\" encoding=\"65001\" type=\"int\" startValue=\"'+str(start_v)+'\" minValue=\"'+str(self.Compu_Method[keys]["Minimum"])+'\" minValuePhys=\"'+str(self.Compu_Method[keys]["Minimum"])+'\" maxValue=\"'+str(self.Compu_Method[keys]["Maximum"])+'\" maxValuePhys=\"'+str(self.Compu_Method[keys]["Maximum"])+'\" />\n')
                            elif (type(self.Compu_Method[keys]['Factor'])== float) & (self.Compu_Method[keys]['Minimum']>=0):
                                f.write('      <variable anlyzLocal=\"2\" readOnly=\"false\" valueSequence=\"false\" unit=\"\" name=\"Sig'+keys+'\" comment=\"\" bitcount=\"'+str(self.Data_Type[keys]['DataLength'])+'\" isSigned=\"false\" encoding=\"65001\" type=\"float\" startValue=\"'+str(start_v)+'\" minValue=\"'+str(self.Compu_Method[keys]["Minimum"])+'\" maxValue=\"'+str(self.Compu_Method[keys]["Maximum"])+'\" />\n')
                            elif (type(self.Compu_Method[keys]['Factor'])== int) & (self.Compu_Method[keys]['Minimum']<0):
                                f.write('      <variable anlyzLocal=\"2\" readOnly=\"false\" valueSequence=\"false\" unit=\"\" name=\"Sig'+keys+'\" comment=\"\" bitcount=\"'+str(self.Data_Type[keys]['DataLength'])+'\" isSigned=\"true\" encoding=\"65001\" type=\"int\" startValue=\"'+str(start_v)+'\" minValue=\"'+str(self.Compu_Method[keys]["Minimum"])+'\" minValuePhys=\"'+str(self.Compu_Method[keys]["Minimum"])+'\" maxValue=\"'+str(self.Compu_Method[keys]["Maximum"])+'\" maxValuePhys=\"'+str(self.Compu_Method[keys]["Maximum"])+'\" />\n')
                            elif (type(self.Compu_Method[keys]['Factor'])== float) & (self.Compu_Method[keys]['Minimum']<0):
                                f.write('      <variable anlyzLocal=\"2\" readOnly=\"false\" valueSequence=\"false\" unit=\"\" name=\"Sig'+keys+'\" comment=\"\" bitcount=\"'+str(self.Data_Type[keys]['DataLength'])+'\" isSigned=\"true\" encoding=\"65001\" type=\"float\" startValue=\"'+str(start_v)+'\" minValue=\"'+str(self.Compu_Method[keys]["Minimum"])+'\" maxValue=\"'+str(self.Compu_Method[keys]["Maximum"])+'\" />\n')
                        f.write('    </namespace>\n')
             f.write('  </namespace>\n')
             f.write('</systemvariables>')
             

    def run(self):
        self.get_info(self.xml,self.cluster)
        self.generate_sysvar("ECU_Default_Value_SysVar_ARXML_FCM")
        self.generate_file("ECU_Default_Value_CAPL_ARXML_FCM")

def main():
    op = Operation()
    op.run()


if __name__ == '__main__':
    main()