from gen_proto import geometry_msgs_pb2
from gen_proto import graspable_object_pb2
from gen_proto import run_recognition_pb2
from gen_proto import get_camera_origin_pb2
from gen_proto import check_grasp_reachability_pb2
from gen_proto import execute_grasp_pb2

from gen_proto import run_recognition_rpcz
from gen_proto import get_camera_origin_rpcz
from gen_proto import check_grasp_reachability_rpcz
from gen_proto import execute_grasp_rpcz



class BaseService(object): 
    def __init__(self,*args):
        self.count = 0

    def run(self,request,reply):
    	print "received " + self.__class__.__name__+" request " + str(self.count)
    	self.count += 1
    	response = self.buildResponse(request,reply)
    	reply.send(response)



class RecognitionService(run_recognition_rpcz.ObjectRecognitionService, BaseService):

	def buildResponse(self,request,reply):
		return run_recognition_pb2.ObjectRecognitionResponse()

class CameraOriginService(get_camera_origin_rpcz.CameraOriginService, BaseService):

	def buildResponse(self,request,reply):
		return get_camera_origin_pb2.CameraOriginResponse()

class CheckGraspReachabilityService(check_grasp_reachability_rpcz.CheckGraspReachabilityService, BaseService):

	def buildResponse(self,request,reply):
		return check_grasp_reachability_pb2.CheckGraspReachabilityResponse()

class ExecuteGraspService(execute_grasp_rpcz.ExecuteGraspService, BaseService):

	def buildResponse(self,request,reply):
		return execute_grasp_pb2.ExecuteGraspResponse()