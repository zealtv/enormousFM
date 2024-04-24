import os, time, sys
from csv import reader
from pyOSC3 import OSCServer, OSCClient, OSCMessage


server = OSCServer( ("localhost", 7770) )
server.timeout = 0
run = True

client = OSCClient()
client.connect( ("localhost", 6661) )



if __name__ == "__main__":
    # watch_for_shutdown_file()
    #ARG 1 config.csv path
    #ARG 2 MAC Address

    print(sys.argv[1])

    # open file in read mode
    with open(sys.argv[1], 'r') as read_obj:
        # pass the file object to reader() to get the reader object
        csv_reader = reader(read_obj, skipinitialspace=True)
        # Iterate over each row in the csv using reader object
        for row in csv_reader:
            # row variable is a list that represents a row in csv
            print(row)
            if row[0] == sys.argv[2]:
                print('MATCH')
                print('ID: ', float(row[1]))
                msg = OSCMessage("/id")
                msg.append(row[1], 'f')
                client.send(msg)