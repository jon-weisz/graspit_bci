#!/usr/bin/env python

from rpcz import compiler

# compiler.generate_proto('../common/search.proto', '.')
# compiler.generate_proto(
#         '../common/search.proto', '.',
#         with_plugin='python_rpcz', suffix='_rpcz.py',
#         plugin_binary=
#             '../../build/src/rpcz/plugin/python/protoc-gen-python_rpcz')

output_dir = './gen_proto'

compiler.generate_proto('../common/geometry_msgs.proto', output_dir)
compiler.generate_proto(
        '../common/geometry_msgs.proto', output_dir,
        with_plugin='python_rpcz', suffix='_rpcz.py',
        plugin_binary=
            '../../build/src/rpcz/plugin/python/protoc-gen-python_rpcz')

compiler.generate_proto('../common/graspable_object.proto', output_dir)
compiler.generate_proto(
        '../common/graspable_object.proto', output_dir,
        with_plugin='python_rpcz', suffix='_rpcz.py',
        plugin_binary=
            '../../build/src/rpcz/plugin/python/protoc-gen-python_rpcz')

compiler.generate_proto('../common/run_recognition.proto', output_dir)
compiler.generate_proto(
        '../common/run_recognition.proto', output_dir,
        with_plugin='python_rpcz', suffix='_rpcz.py',
        plugin_binary=
            '../../build/src/rpcz/plugin/python/protoc-gen-python_rpcz')

compiler.generate_proto('../common/check_grasp_reachability.proto', output_dir)
compiler.generate_proto(
        '../common/check_grasp_reachability.proto', output_dir,
        with_plugin='python_rpcz', suffix='_rpcz.py',
        plugin_binary=
            '../../build/src/rpcz/plugin/python/protoc-gen-python_rpcz')

compiler.generate_proto('../common/get_camera_origin.proto', output_dir)
compiler.generate_proto(
        '../common/get_camera_origin.proto', output_dir,
        with_plugin='python_rpcz', suffix='_rpcz.py',
        plugin_binary=
            '../../build/src/rpcz/plugin/python/protoc-gen-python_rpcz')
