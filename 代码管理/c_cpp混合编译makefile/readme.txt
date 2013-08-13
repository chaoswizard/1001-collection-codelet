1 CPP的函数使用 extern "C" 在CPP的函数实现文件中进行声明，可放到头文件然后include到.cpp中。
2 makefile中 LD使用 CXX.
3 子模块参考 submodule中的makefile，然后在上层目录makefile倒数第二行include