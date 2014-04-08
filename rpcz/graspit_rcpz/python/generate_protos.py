#!/usr/bin/env python

from rpcz import compiler
from os import listdir
from os.path import isfile, join

# compiler.generate_proto('../common/search.proto', '.')
# compiler.generate_proto(
#         '../common/search.proto', '.',
#         with_plugin='python_rpcz', suffix='_rpcz.py',
#         plugin_binary=
#             '../../build/src/rpcz/plugin/python/protoc-gen-python_rpcz')

output_dir = './gen_proto'
input_path = '../common/'

proto_files = [ f for f in listdir(input_path) if isfile(join(input_path,f)) ]

for proto_file in proto_files:
    full_proto_file_path = input_path + proto_file
    compiler.generate_proto(full_proto_file_path, output_dir)
    compiler.generate_proto(
        full_proto_file_path, output_dir,
        with_plugin='python_rpcz', suffix='_rpcz.py',
        plugin_binary=
            '../../build/src/rpcz/plugin/python/protoc-gen-python_rpcz')


