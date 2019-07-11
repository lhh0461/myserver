#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import sys

a = {1:1,2:2}
b = {"hello":"world"}
c = ["hello"]
print("ref",sys.getrefcount(a))
c += [a]
print("ref",sys.getrefcount(a))
print(c)
del a
print(c)
