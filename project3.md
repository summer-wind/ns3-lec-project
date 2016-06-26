##第三次报告
本次的任务是建立在project2Topo1.cc文件上的，也就是说生成的.tr文件与.pcap文件都是依靠project2Topo1.cc来建立的。

关于PyViz的安装，首先在命令行输入sudo apt-get install python-dev python-pygraphviz python-kiwi python-pygoocanvas 
                     python-gnome2 python-gnomedesktop python-rsvg发现报错，原因是没找到python-gnomedesktop包，于是我在原命令中去掉了这部分，因为ppt上说python-rsvg中已经包含了python-gnomedesktop包。顺利安装。
当我尝试输入命令./waf --run third --vis时，报错，找好长时间，才发现原因是Python bindings并没有enable。于是输入sudo apt-get install python-pygccxml，并且之后重新编译了一次（./waf configure）发现上面提示Python bindings已经enabled。再次输入命令./waf --run third --vis成功运行。

关于wireshark的安装，我直接运行命令#sudo groupadd  wireshark就安装完成。再在.pcap的文件上右击，选择用wireshark打开，就行了
