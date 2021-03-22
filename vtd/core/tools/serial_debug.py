#!/usr/bin/python3

import serial

vts = serial.Serial("/dev/ttyUSB0",115200)

if __name__ == "__main__":
    start_stop = "f8"
    channel_id = "01"
    command = "81"
    while(True):
        cmd = str(input(""))
        if(cmd == "quit"):
            break
        elif(cmd.find("channel")!=-1):
            channel_id = cmd[-2:]
            print("channel  id set to:"+channel_id)
        elif(cmd.find("command")!=-1):
            command = cmd[-2:]
            print("new command set to:"+command)
        else:
            
            data_length = int(len(cmd)/2)
            dl = ("%02x" % data_length)
            data = bytearray.fromhex(channel_id+command+dl+cmd)

            checksum = 0xff
            for value in data:
                checksum^=value
            checksum_str = ("%02x" % checksum)
            cmd = start_stop+channel_id+command+dl+cmd+checksum_str+start_stop
            byte_array = bytearray.fromhex(cmd)
            #print(byte_array)
            for byte in byte_array:
                print("%02X " % byte,end="")
            print()
            vts.write(byte_array)
        cmd=""
    vts.close()