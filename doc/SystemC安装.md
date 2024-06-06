# SystemC 安装
1. 源码地址：https://github.com/accellera-official/systemc
2. 编译systemc-3.0.0需要GNU C++ compiler (version 9.3 or later), or Clang C++ compiler (version 13.0 or later)。以及安装GNU Make (make)
3. 进入systemc顶层目录
4. 执行./config/bootstrap 用于生成生成配置可执行文件
5. 创建并切换至临时目录 
    1. mkdir build 
    2. cd build
6. 执行 ../configure --prefix=/usr/local/systemc-3.0.0 指定编译生成的路径
7. 编译 执行make
8. 编译结果检查 执行make check
9. 删除创建的临时目录
10. 设置环境变量（临时生效）
    1. export SYSTEMC_HOME=/home/sjh/work/systemc-3.0.0
    2. export LD_LIBRARY_PATH=/home/sjh/work/systemc-3.0.0/lib-linux64:$LD_LIBRARY_PATH
11. 设置环境变量（永久生效）
    
    ```bash
    ## 经过测试，文件中 只能设置某个路径，不能具体到 某个文件
    ##  echo {dir} >> /etc/ld.so.conf.d/{custom.conf}
    # vim /etc/ld.so.conf
    # vim /etc/ld.so.conf.d/{custom.conf}
     
    ## 将配置生效（root 权限执行）
    # ldconfig
    ```
    
12. 运行SystemC test
    1. cd test/scripts
    2. ./verify.pl systemc  在regression test suite中运行**所有的SystemC tests**
    3. ./verify.pl tlm  在regression test suite中运行**所有的TLM2 tests**
    4. ./verify.pl systemc tlm  在regression test suite中运行**所有的tests**
13. 新建main.cpp文件
    
    ```cpp
    #include <systemc.h>
    
    SC_MODULE (hello_world) 
    {
        SC_CTOR (hello_world)
        {
            SC_THREAD(say_hello);
        }
    
        void say_hello()
        {
            cout << "Hello World SystemC" << endl;
        }
    
    };
    
    int sc_main(int argc, char* argv[])
    {
        hello_world hello("HELLO");
        sc_start();
    
        return (0);
    }
    
    ```
    
14. 编译main.cpp，生成可执行文件
    
    ```bash
    g++ -o main main.cpp -I/home/sjh/work/systemc-3.0.0/include -L/home/sjh/work/systemc-3.0.0/lib-linux64 -lsystemc
    ```
    
15. 执行可执行文件 ./main
    
    ```bash
    (base) sjh@ubuntu22:~/work/systemc_workspace/test$ ./main 
    
            SystemC 3.0.0-Accellera --- Jun  5 2024 15:51:10
            Copyright (c) 1996-2024 by all Contributors,
            ALL RIGHTS RESERVED
    Hello World SystemC
    ```