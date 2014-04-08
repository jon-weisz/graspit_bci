include(rpcz_functions)
find_package(ProtobufPlugin REQUIRED)
PROTOBUF_GENERATE_CPP(GRASPIT_PB_SRCS GRASPIT_PB_HDRS
	 ../common/geometry_msgs.proto
	 ../common/run_recognition.proto
	 ../common/graspable_object.proto
	 ../common/get_camera_origin.proto
	 ../common/check_grasp_reachability.proto
	 ../common/execute_grasp.proto
	 ../common/grasp.proto
	 )
PROTOBUF_GENERATE_RPCZ(GRASPIT_RPCZ_SRCS GRASPIT_RPCZ_HDRS 	 
	 ../common/geometry_msgs.proto
	 ../common/run_recognition.proto
	 ../common/graspable_object.proto
	 ../common/get_camera_origin.proto
	 ../common/check_grasp_reachability.proto
	 ../common/execute_grasp.proto
	 ../common/grasp.proto
	 )

add_library(graspit_pb ${GRASPIT_PB_SRCS} ${GRASPITSEARCH_PB_HDRS} ${GRASPIT_RPCZ_SRCS}
                      ${GRASPITSEARCH_RPCZ_HDRS})
target_link_libraries(graspit_pb ${PROTOBUF_LIBRARY})
include_directories(${PROJECT_BINARY_DIR}/graspit_rcpz)

#add_executable(example_client example_client.cc)
#target_link_libraries(graspit_client rpcz graspit_pb)

#add_executable(example_server example_server.cc)
#target_link_libraries(graspit_server rpcz example_pb)
