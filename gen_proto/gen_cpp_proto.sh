#!/bin/bash

SRC=${GRASPIT}/protocols
DST=${GRASPIT}/gen_proto

protoc --proto_path=${SRC} --cpp_out=${DST} ${SRC}/GraspitMessage.proto 
protoc --proto_path=${SRC} --cpp_out=${DST} ${SRC}/Drawable.proto 
