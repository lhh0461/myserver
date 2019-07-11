#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import codecs
import os
import xml.etree.ElementTree as ET

struct_id2name = {}
struct_name2id = {}

function_id2key = {}
function_key2id = {}

all_struct_list = {}
all_function_list = {}

RPC_SERVER = 1
RPC_CLIENT = 2
RPC_HOST = 3

field2id = {
    "RPC_INT32":1,
    "RPC_STRING":2,
    "RPC_PB":3,
    "RPC_FLOAT":4,
    "RPC_INT16":5,
    "RPC_INT8":6,
}

def parse_args(child):
    arg_list = []
    for arg in child:
        if arg.tag == "arg":
            arg_list.append(arg.text)
    return arg_list

def parse_function(child, rpc_type):
    function_key = "" 
    c_imp = 0
    path = "" 
    name = "" 
    arg_list = [] 
    deamon = 1
    desc = ""
    for function in child:
        if function.tag == "path":
            path = function.text
        if function.tag == "function":
            name = function.text
        if function.tag == "args":
            arg_list = parse_args(function)
        if function.tag == "deamon":
            deamon = function.text
        if function.tag == "c_imp":
            c_imp = function.text
        if function.tag == "desc":
            desc = function.text
    function_key = path + ":" + name
    all_function_list[function_key] = {
        "path":path,
        "function":name,
        "c_imp" :c_imp,
        "deamon" :deamon,
        "arg_list" :arg_list,
        "rpc_type" :rpc_type,
        "desc" :desc,
    }
        

def parse():
    files = os.listdir("rpc")
    for f in files:
        if os.path.splitext(f)[-1] == ".xml":
            file_name = "rpc/" + f
            tree = ET.parse(file_name)
            root = tree.getroot()
            for child in root:
                if child.tag == "server":
                    parse_function(child, RPC_SERVER)
                elif child.tag == "client":
                    parse_function(child, RPC_CLIENT)
                elif child.tag == "host":
                    parse_function(child, RPC_HOST)

def sort_function():
    global function_key2id
    global function_id2key
    function_id = 1
    sorted_list = all_function_list.keys()
    sorted_list.sort()
    for function_key in sorted_list:
        function_id2key[function_id] = function_key
        function_key2id[function_key] = function_id
        function_id += 1

def write_file():
    global struct_id2name
    global struct_name2id
    global function_id2key
    with open("rpc/rpc.cfg", 'w') as f:
        f.write('function_table_num:{num}\n'.format(num=len(all_function_list))) 
        sorted_id_list = function_id2key.keys()
        for function_id in sorted_id_list:
            function_key = function_id2key[function_id]
            function_data = all_function_list[function_key]
            f.write('function_id:{function_id},arg_num:{arg_num},path={path},function={function},c_imp={c_imp},deamon={deamon}\n'.
                    format(function_id=function_id,arg_num=len(function_data["arg_list"]),path=function_data["path"],function=function_data["function"],
                        c_imp=function_data["c_imp"],deamon=function_data["deamon"])) 
            for arg_data in function_data["arg_list"]:
                f.write('arg_type:%d\n' %(field2id[arg_data]))

    with codecs.open("script/rpc_id.py", "w", "utf-8") as f:
        print >>f, u'# -*- coding: utf-8 -*-'
        print >>f, u'# 此文件由脚本生成，请勿修改！'
        print >>f, u''
        print >>f, u'# 以下是协议ID'
        sorted_id_list = function_id2key.keys()
        for function_id in sorted_id_list:
            function_key = function_id2key[function_id]
            function_data = all_function_list[function_key]
            print >>f , u'{function_name} = {function_id} #{desc}'.format(function_name=function_data["function"].upper(), function_id=function_id, desc=function_data["desc"])
            

                
if __name__ == '__main__':
    parse()
    sort_function()
    write_file()
    print"parse rpc ok"

#    print("show function list\n",all_function_list)
#    print("show struct list\n",all_struct_list)
#    print("show struct name2id\n",struct_name2id)
#    print("show struct id2name\n",struct_id2name)

