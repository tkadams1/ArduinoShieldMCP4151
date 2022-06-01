#!/bin/python3

# Importing Libraries
import serial  #pip install pyserial
import time
import rclpy
from rclpy.node import Node

from std_msgs.msg import String

#This defines the serial port or arduino ID to use for serial communication
arduinoID = '/dev/serial/by-id/usb-Arduino__www.arduino.cc__0043_959323334323514001B2-if00'
#sets up the serial connection
arduino = serial.Serial(port= arduinoID, baudrate=9600, timeout=.1)


class MinimalSubscriber(Node):

    def __init__(self):
        super().__init__('minimal_subscriber')
        self.subscription = self.create_subscription(
            String,
            'main_drive_motor_uint8',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def write_read(self, x):
        arduino.write(bytes(x, 'utf-8'))
        time.sleep(0.05)
        data = arduino.readline()
        return data

    def listener_callback(self, msg):
        self.get_logger().info('I heard: "%s"' % msg.data)
        num = msg.data # Taking input from user
        print(type(msg.data))
        value = self.write_read(num + '\n') # Sending the input to the arduino
        print(value) # printing the value returned from the arduino


def main(args=None):
    rclpy.init(args=args)

    minimal_subscriber = MinimalSubscriber()

    rclpy.spin(minimal_subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()