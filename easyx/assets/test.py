#!/usr/bin/env python
# coding: utf-8

# In[4]:


import time
from Raspblock import Raspblock
ROBOT = Raspblock()

def moveforward_duration(robot, duration):
    start = time.perf_counter()
    while True:
        if (time.perf_counter() - start >= duration):
            break
        robot.Speed_Wheel_control(4, 4, 4, 4)
        
def moveback_duration(robot, duration):
    start = time.perf_counter()
    while True:
        if (time.perf_counter() - start >= duration):
            break
        robot.Speed_Wheel_control(-4, -4, -4, -4)
        
def turnright_duration(robot, duration):
    start = time.perf_counter()
    while True:
        if (time.perf_counter() - start >= duration):
            break
        robot.Speed_Wheel_control(-4, 2, -2, 4)
        
def turnleft_duration(robot, duration):
    start = time.perf_counter()
    while True:
        if (time.perf_counter() - start >= duration):
            break
        robot.Speed_Wheel_control(4, -2, 2, -4)
    
def main():
    moveforward_duration(ROBOT, 2)
    
main()


# In[1]:


import Raspblock
dir(Raspblock)


# In[ ]:




