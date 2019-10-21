安装方式1：安装libx11-dev、libfltk1.3-dev，则fltk-config安装完成
安装方式2：编译源代码
     ./configure
     make all
     make install
     则fltk-config安装完成
安装方式3：Windows下，可以采用MINGW里的msys进行类似的编译和安装

运行例子abc.cpp：
(1) fltk-config --compile abc.cpp
则可见g++命令，类似：
g++ -I/usr/local/include -I/usr/local/include/FL/images -mwindows -DWIN32 -DUSE_OPENGL32 -D_LARGEFILE_SOURCE -D_LARGE
FILE64_SOURCE -o 'abc' 'abc.cpp'  -mwindows /usr/local/lib/libf ltk.a -lole32 -luuid -lcomctl32 
（2）'abc.cpp'后增加其它文件：'Window.cpp' 'Simple_window.cpp' 'Graph.cpp' 'GUI.cpp'
（3）链接库：-L/usr/local/lib -lfltk_images -lfltk_png -lfltk_z -lfltk_jpeg -lfltk



