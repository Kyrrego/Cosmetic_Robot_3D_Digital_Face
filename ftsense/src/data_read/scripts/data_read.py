#!/usr/bin/env python3

import rospy
import pickle
from geometry_msgs.msg import WrenchStamped
import time

class WrenchStampedListener:
    def __init__(self) -> None:
        rospy.Subscriber("/ethdaq_data", WrenchStamped, self.data_cb)
        self.data = []

    def data_cb(self, msg: WrenchStamped) -> None:
        force = msg.wrench.force
        self.data.append((force.x, force.y, force.z))
        rospy.loginfo_once("getmsg")
    
    def save(self):
        filename = f"/home/robo/Cosmetic_Robot_3D_Digital_Face/data/{time.time()}.p"
        pickle.dump(self.data, open(filename, "wb"))
        print(f"saved in file {filename}")


if __name__ == "__main__":
    rospy.init_node("data_recorder")
    listener = WrenchStampedListener()
    rospy.on_shutdown(listener.save)
    rospy.spin()


