��װ��ʽ1����װlibx11-dev��libfltk1.3-dev����fltk-config��װ���
��װ��ʽ2������Դ����
     ./configure
     make all
     make install
     ��fltk-config��װ���
��װ��ʽ3��Windows�£����Բ���MINGW���msys�������Ƶı���Ͱ�װ

��������abc.cpp��
(1) fltk-config --compile abc.cpp
��ɼ�g++������ƣ�
g++ -I/usr/local/include -I/usr/local/include/FL/images -mwindows -DWIN32 -DUSE_OPENGL32 -D_LARGEFILE_SOURCE -D_LARGE
FILE64_SOURCE -o 'abc' 'abc.cpp'  -mwindows /usr/local/lib/libf ltk.a -lole32 -luuid -lcomctl32 
��2��'abc.cpp'�����������ļ���'Window.cpp' 'Simple_window.cpp' 'Graph.cpp' 'GUI.cpp'
��3�����ӿ⣺-L/usr/local/lib -lfltk_images -lfltk_png -lfltk_z -lfltk_jpeg -lfltk



