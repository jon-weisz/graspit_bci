#!/usr/bin/env python

import time
import threading

import rpcz
from graspit_services import *


class RPCZAppManager():
	def __init__(self,server_address,services):
		self.app = rpcz.Application()
		self.appThread = ServerThread(self.app,server_address,services)

	def start(self):
		self.appThread.start()

	def shutdown(self):
		print "shutting down server"
		self.app.terminate()
		self.appThread.join()

class ServerThread(threading.Thread):
	def __init__(self, app, server_address,services):
		threading.Thread.__init__(self)
		self.app = app
		server = rpcz.Server(self.app)
		self.server_address = server_address

		for service in services:
			server.register_service(service(),service.__name__)

		server.bind(server_address)

	def run(self):
		print "Serving requests at: " + self.server_address
		self.app.run()


#this shows how to run the server
#with stubbed out services, useful 
#for debugging with graspit
def example_run():
	SERVER_ADDRESS = "tcp://*:5561"

	SERVICES = [RecognitionService, 
					  CameraOriginService,
					  CheckGraspReachabilityService,
					  ExecuteGraspService]

	rpczAppManager = RPCZAppManager(SERVER_ADDRESS,SERVICES)
	rpczAppManager.start()

	while True:
		try:
			time.sleep(1)
		except (KeyboardInterrupt, SystemExit):
			break

	rpczAppManager.shutdown()

if __name__ == "__main__":
	example_run()