import os, sys
from time import sleep
from csv import reader
from pyOSC3 import OSCServer, OSCClient, OSCMessage


server = OSCServer( ("localhost", 7770) )
client = OSCClient()
client.connect( ("localhost", 6661) )


def config_callback(path='', tags='', args='', source=''):
    print("loading: ", sys.argv[1])

    # open file in read mode
    with open(sys.argv[1], 'r') as read_obj:
        # pass the file object to reader() to get the reader object
        csv_reader = reader(read_obj, skipinitialspace=True)
        # Iterate over each row in the csv using reader object
        for row in csv_reader:
            # row variable is a list that represents a row in csv
            if row[0] == sys.argv[2]:
                print('MAC MATCHED LINE IN CONFIG')
                msg = OSCMessage("/id")
                msg.append(row[1], 'f')
                client.send(msg)

                msg.clear("/pos")
                msg.append(row[2], typehint='f')
                msg.append(row[3], typehint='f')
                client.send(msg)


def update_callback(path='', tags='', args='', source=''):
    directory = os.path.dirname(os.path.realpath(__file__))
    update_script = os.path.join(directory, "update.sh")
    print("UPDATE!")
    os.system(update_script)
        

def shutdown_callback(path='', tags='', args='', source=''):
    print("SHUTDOWN!")
    os.system("systemctl poweroff")


server.addMsgHandler( "/config", config_callback )
server.addMsgHandler( "/update", update_callback )
server.addMsgHandler( "/shutdown", shutdown_callback )


if __name__ == "__main__":
    #ARG 1 config.csv path
    #ARG 2 MAC Address

    config_callback()

    while True:
        sleep(1)
        server.handle_request()
