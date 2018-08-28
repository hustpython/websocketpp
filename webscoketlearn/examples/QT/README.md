## Qt chat 编译

mkdir build

创建文件夹 lib

创建子文件夹 Release,Debug

编译sioclient
```
mkdir Release  
cd Release  
cmake -DCMAKE_BUILD_TYPE=Release ..  
make 
```
拷贝boost库

```
build
└── lib
    ├── Debug
    │   ├── libboost_date_time.a
    │   ├── libboost_random.a
    │   ├── libboost_system.a
    │   ├── libsioclient.a
    │   └── libsioclient_tls.a
    └── Release
        ├── libboost_date_time.a
        ├── libboost_random.a
        ├── libboost_system.a
        ├── libsioclient.a
        └── libsioclient_tls.a
```
qtcreater 中 编译 Qt

选择 Release模式

运行 QtDemo