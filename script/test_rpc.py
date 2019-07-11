#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import rpc_id
import rpc

rpc_call(uid, "Rpc_Client_Hello", {"uid":111, "msg":"test"}, 1)
rpc_call(uid, "rpc_host_test", {"uid":111, "msg":"test"}, 1)

def rpc_server_hello_world(uid, hello_req, num)
       
