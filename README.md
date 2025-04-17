# Turbomon
本仓库是在Turbomon基础上，CARRERA针对RDMA协议的算子实现测试

## 拓扑
应用一个server使用RDMA将已经预算好的sketch数据发送，接收端可以是server也可以是dpu

## 环境依赖
基于CMake和MakeFile为C++环境，C++11以上应该都能兼容，Python依赖Jinja2

## 用法
直接运行test.sh即可，参数如下：

--op: max | min | exist | distinct | merge | filter | all

--sketch: cm | cs | es | hp | um | sl

--mode: send | recv

op参数含义为开启算子，开启后运行会用算子去处理sketch数据，支持任意个op同时开启，但每个算子都要用--op指明

sketch参数表示运行哪个sketch，因为RDMA网卡有限，不能同时进行多个测试，但通过修改绑定的IP和MAC是可以同时测试的

mode表示收发模式，应先开启发送端后再启动接收端，尽量留出几秒时间等待编译

## 可能问题
在不同设备上运行需要修改test.h中绑定的IP和MAC地址