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

附:
QtCreater 无法输入中文问题
```
将 libfcitxplatforminputcontextplugin.so 拷贝到以下目录中，可能有一些不需要，为保险起见可以都复制，如果还不行选择较最新版本的libfcitxplatforminputcontextplugin.so


/home/mxq/Qt5.10.1/5.10.1/gcc_64/plugins/platforminputcontexts

/home/mxq/Qt5.10.1/Tools/QtCreator/lib/Qt/plugins/platforminputcontexts

/home/mxq/Qt5.10.1/Tools/QtCreator/lib/qtcreator/plugins

/home/mxq/Qt5.10.1/Tools/QtCreator/lib/qtcreator/plugins/platforminputcontexts
```
