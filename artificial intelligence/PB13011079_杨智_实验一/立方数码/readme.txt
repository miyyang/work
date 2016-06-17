运行方式：

执行complie.sh之后，得到4个可执行文件，执行编译出来的可执行
文件即可。

注意事项：

1. 因为用的是相对路径，所以要在cpp文件的路径下编译和执行
2. 因为在A*算法中用了<unordered_set>来进行查重，所以编译选项要加上 —std=c++11，否则要把unordered_set 换成 set （之前发邮件问过助教，助教回复说可以用<unordered_set>的）
3. IDAh1.cpp和IDAh2.cpp中，有一行是 #define MAXNODE 999999999 ， 如果编译时报错或者运行时报错（segmentation fault）的话，可以把这个值改小一点，因为这个值是和机器相关的，在某些机器上这个值可能不合适。但是这个值改得太小的话可能会影响性能。

代码说明：
具体说明看文档

实验环境：
ubuntu 14.04
8GB memory
Intel Core i7-4720HQ CPU