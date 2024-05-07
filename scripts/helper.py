import os, sys
from time import sleep
from csv import reader
from pyOSC3 import OSCServer, OSCClient, OSCMessage
import atexit

server = OSCServer( ('127.0.0.1', 7770) )
client = OSCClient()
client.connect( ('127.0.0.1', 6661) )


def config_callback(path='', tags='', args='', source=''):

    directory = os.path.dirname(os.path.realpath(__file__))
    config_file = os.path.join(directory, "config.csv")
    print("loading: ", config_file)

    # open file in read mode
    with open(config_file, 'r') as read_obj:
        # pass the file object to reader() to get the reader object
        csv_reader = reader(read_obj, skipinitialspace=True)
        # Iterate over each row in the csv using reader object
        for row in csv_reader:
            # row variable is a list that represents a row in csv
            if row[0] == sys.argv[1]:
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

def exit_handler():
    print("exiting.  closing server...")
    server.close()

server.addMsgHandler( "/config", config_callback )
server.addMsgHandler( "/update", update_callback )
server.addMsgHandler( "/shutdown", shutdown_callback )
atexit.register(exit_handler)

#ARG 1 MAC Address
if __name__ == "__main__":

    config_callback()

    while True:
        sleep(1)
        server.handle_request()
