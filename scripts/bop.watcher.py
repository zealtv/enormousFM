## TODO this should have an OSC listener for shutting down and updating
## See yellow notebook for details

import os
import time

def watch_for_shutdown_file():
    directory = os.path.dirname(os.path.realpath(__file__))
    shutdown_file = os.path.join(directory, "cmd.shutdown.tmp")
    update_file = os.path.join(directory, "cmd.update.tmp")
    update_script = os.path.join(directory, "update.sh")

    while True:
        if os.path.exists(shutdown_file):
            os.remove(shutdown_file)
            print("SHUTDOWN!")
            os.system("systemctl poweroff")
            break

        if os.path.exists(update_file):
            os.remove(update_file)
            print("UPDATE!")
            os.system(update_script)

        time.sleep(5)

if __name__ == "__main__":
    watch_for_shutdown_file()