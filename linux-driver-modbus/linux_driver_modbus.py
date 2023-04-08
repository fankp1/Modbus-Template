#!/usr/bin/python3


import abc
import subprocess
import json
import os
import logging
from threading import Event,Lock,Timer

from APM_MDAS import APM_Interface,APM_Device
import APM_HWID as platform

class ModbusDevice(APM_Device):

    def __init__(self, interface, id, name, serial, modelID):
        self.schema = "em.json"
        super().__init__(interface, id, name, serial, modelID)

class SunspecDevice(APM_Device):

    def __init__(self, interface, id, name, serial, modelID):
        self.schema = "em.json"
        super().__init__(interface, id, name, serial, modelID)

#---------------------------------------------------
#------Support HAT----------------------------------
#---------------------------------------------------
class ModBus_SupportHAT(APM_Interface):
    
    def __init__(self,client):
        self.devices = []
        self.port = ""
        self.interval = 0.95
        self.lock = Lock()
        self.client = client
        self.flag = Event()
        self.name = "ModBus (Internal)"
        self.retries = 0
        super().__init__()

    def _search(self):
        found = 0
        found += self.search("9600")
        found += self.search("115200")
        if(found==0):
            Timer(60, self._retry).start()
            #self.logger.info(" retrying in 60 seconds...")
        #print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    
    def detect(self):
        ret = subprocess.check_output(["./bin/i2c",platform._i2c_m])
        if(ret.find(b'Error')==-1):
            self.port = platform._uart_m
            #tmp = subprocess.check_output(["ls","/sys/class/gpio"])
            #if(tmp.find(b'gpio131')==-1):
            #    os.system('echo "131" > /sys/class/gpio/export')
            return True
        else:
            return False

    def search(self,baud):
        if(len(self.devices)>0):
            self.cleanup()
        data = searchDevices(self.lock,self.port,baud,10)
        if data:
            #if(data["count"]==1):
            #    self.logger.info(" found 1 Device on %d" % int(baud))
            #else:
            self.logger.debug(self.name+": found %d Devices on %d" % (data["count"],int(baud)))
            for val in data["devices"]:
                if( val["name"] == "SUNSPEC" ):
                    dev = SunspecDevice(self,str(val["address"]),val["name"],val["serial"],val["modelID"])
                else:
                    dev = ModbusDevice(self,str(val["address"]),val["name"],val["serial"],val["modelID"])
                self.logger.info(dev.__repr__())
                self.devices.append(dev)
            return data["count"]
        else:
            return 0
    
    def read(self,device):
            device.interface.lock.acquire()
            output = subprocess.check_output(["./modules/linux-driver-modbus/bin/read",self.port,"115200",device.id,device.modelID])
            device.interface.lock.release()
            if output:
                output = output.decode('ascii')
                try:
                    content = output[output.index("----------")+11:]
                except: 
                    content = 0
                if content:
                    try:
                        data = json.loads(content)
                    except:
                        data = 0
                    if data:
                        if(isinstance(device,SunspecDevice)):
                            content = parseSunspec(data)
                        data = content.replace("GUID",device.serial)
                        device.interface.client.publish(data_element=device.de,payload=data,retain=True)

    def cleanup(self):
        self.flag.set()
        self.devices.clear()
#---------------------------------------------------
#---------------------------------------------------

#---------------------------------------------------
#------USB Dongle-----------------------------------
#---------------------------------------------------
class ModBus_UsbDongle(APM_Interface):
    
    def __init__(self,client):
        self.devices = []
        self.port = ""
        self.interval = 0.95
        self.lock = Lock()
        self.client = client
        self.flag = Event()
        self.name = "ModBus (USB Dongle)"
        self.retries = 0
        super().__init__()

    def _search(self):
        found = 0
        found += self.search("9600")
        found += self.search("115200")
        if(found==0):
            Timer(60, self._retry).start()
            self.logger.info(" retrying in 60 seconds...")
        #print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    
    def detect(self):
        ret = subprocess.check_output(["ls","/dev/serial/by-id/"])
        if(ret.find(b'usb-1a86_USB2.0')!=-1):
            self.port = "/dev/serial/by-id/usb-1a86_USB2.0-Serial-if00-port0"
            return True
        else:
            return False

    def search(self,baud):
        if(len(self.devices)>0):
            self.cleanup()
        data = searchDevices(self.lock,self.port,baud,10)
        if data:
            #if(data["count"]==1):
            #    self.logger.info(" found 1 Device on %d" % int(baud))
            #else:
            self.logger.debug(self.name+": found %d Devices on %d" % (data["count"],int(baud)))
            for val in data["devices"]:
                if( val["name"] == "SUNSPEC" ):
                    dev = SunspecDevice(self,str(val["address"]),val["name"],val["serial"],val["modelID"])
                else:
                    dev = ModbusDevice(self,str(val["address"]),val["name"],val["serial"],val["modelID"])
                self.logger.info(dev.__repr__())
                self.devices.append(dev)
            return data["count"]
        else:
            return 0

    def read(self,device):
            device.interface.lock.acquire()
            output = subprocess.check_output(["./modules/linux-driver-modbus/bin/read",self.port,"115200",device.id,device.modelID])
            device.interface.lock.release()
            if output:
                output = output.decode('ascii')
                try:
                    content = output[output.index("----------")+11:]
                except: 
                    content = 0
                if content:
                    try:
                        data = json.loads(content)
                    except:
                        data = 0
                    if data:
                        if(isinstance(device,SunspecDevice)):
                            content = parseSunspec(data)
                        data = content.replace("GUID",device.serial)
                        device.interface.client.publish(data_element=device.de,payload=data,retain=True)
                        
    
    def cleanup(self):
        self.flag.set()
        self.devices.clear()
#---------------------------------------------------
#---------------------------------------------------
                            
def parseSunspec(data):
    try:
        data['sys']['Hz'] = round(float(float(data['sys']['Hz'])*pow(10,data['sys']['SF_Hz'])),4)
        data['sys']['kW'] = round(float(float(data['sys']['kW'])*pow(10,data['sys']['SF_kW']))*(-0.001),4)
        data['sys']['kVA'] = round(float(float(data['sys']['kVA'])*pow(10,data['sys']['SF_kVA']))*(0.001),4)
        data['sys']['kvar'] = round(float(float(data['sys']['kvar'])*pow(10,data['sys']['SF_kVAR']))*(-0.001),4)
    
        if(int(data['sys']['SF_kWH'])> 65530):
            data['sys']['kWh-'] = round(float(data['sys']['kWh-']),4)
        else:
            data['sys']['kWh-'] = round(float(float(data['sys']['kWh-'])*pow(10,data['sys']['SF_kWH'])),4)
        data['l1']['A'] = round(float(float(data['l1']['A'])*pow(10,data['sys']['SF_I']))*(-1),4)
        data['l2']['A'] = round(float(float(data['l2']['A'])*pow(10,data['sys']['SF_I']))*(-1),4)
        data['l3']['A'] = round(float(float(data['l3']['A'])*pow(10,data['sys']['SF_I']))*(-1),4)
   
        if(int(data['l1']['V']) == 65535):
            data['l1']['V'] = None
        else:
            data['l1']['V'] = round(float(float(data['l1']['V'])*pow(10,data['sys']['SF_U'])),4)
    
        if(int(data['l2']['V']) == 65535):
            data['l2']['V'] = None
        else:
            data['l2']['V'] = round(float(float(data['l2']['V'])*pow(10,data['sys']['SF_U'])),4)
    
        if(int(data['l3']['V']) == 65535):
            data['l3']['V'] = None
        else:
            data['l3']['V'] = round(float(float(data['l3']['V'])*pow(10,data['sys']['SF_U'])),4)

        del data['sys']['SF_Hz']
        del data['sys']['SF_kW']
        del data['sys']['SF_kVA']
        del data['sys']['SF_kVAR']
        del data['sys']['SF_U']
        del data['sys']['SF_I']
        del data['sys']['SF_kWH']
    
    except Exception as e:
        logging.getLogger('mdas-log').error("parse sunspec: "+str(data['sys']['SF_kWH']))
        return ""

    content = json.dumps(data)
    return content

def searchDevices(lock,port,baud,maxAddress):
    counter = 0
    success = 0
    while((success==0)and(counter<3)):
        lock.acquire()
        output = subprocess.check_output(["./modules/linux-driver-modbus/bin/search",port,baud,str(maxAddress)])
        lock.release()
        try:
            data = json.loads(output.decode('utf-8'))
            success = 1
        except Exception as e:
            #print(e)
            success = 0
        counter += 1
    if success==1:
        return data
    else:
        return 0
