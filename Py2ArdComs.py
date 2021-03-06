import serial, time
import struct
import mraa


class Py2ArdComs:
	Testing = 0
	ThreadRun = 1
	Count = 0
	# arduino = serial.Serial(port="/home/root/tty1", baudrate=115200, timeout = 1)
	arduino=serial.Serial()
	arduino.baudrate=115200
	arduino.port="/home/root/tty1"
	arduino.open()
	arduino.isopne()
	FromArduinoData = 0
	ToArduinoData = 1

	def __init__(self):
		time.sleep(1) #give the connection a second to settle


	def stop(self):
		self.ThreadRun = 0

	def FromArduino(self, toArduinoData):
		self.ToArduinoData = toArduinoData
		return self.FromArduinoData 

	def run(self):
		data = 0
		while (self.ThreadRun):
		#if Testing mode is on, this takes care that the program does not run forever	
			if(self.Testing):
				print data
				self.Count = self.Count+1
				if(self.Count>100):
					self.ThreadRun = 0

			data = self.arduino.readline()[:-2] #the last bit gets rid of the new-line chars
			if data:
				self.FromArduinoData = data
				self.arduino.write(struct.pack('>B', self.ToArduinoData))
		print("Exiting the coms protocol...")			

if __name__ == '__main__':
	coms = Py2ArdComs()
	coms.run()