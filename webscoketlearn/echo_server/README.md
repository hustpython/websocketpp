## 运行websocketpp的一个例子

几个坑:
1.编译需要boost的相关支持
用命令行编译:
```
g++ ../echo_server.cpp -o text -lboost_system -lboost_thread -lpthread
```
2.找不到boolst_system
```
sudo ldconfig -v | grep -i "libboost_system"
```