# Maze_car
效果展示视频：
https://www.bilibili.com/video/BV1PZ4y167rh/

# 概述
<Br/>分别在小车正前方、左方和右方安装共3个红外探头，连接STC主控芯片，通过红外是否有返回信号来判断是否有遮挡物，再经过程序处理，向小车发送下一步运动指示
<Br/>本程序利用C语言编写，分为名称对应、主要进程和转弯处理函数三部分。主要进程包括前进过程，后退过程和二者的交替处理三部分。处理函数包括基础转向函数和校准转向函数两部分。校准转向函数又分为延时函数、左转函数、右转函数、前进函数和后退函数四个函数模块。
<Br/>1.前进过程：通过红外判断并调用校准转向函数，间接调用基础转向函数实现小车运动，并记录“奇异点”。（主程序，下图解释部分）
<Br/>2.后退过程：通过红外判断配合后退函数存取“奇异点”并调整小车运动路径
<Br/>3.交替处理：通过循环判断语句实现不同函数的进入和退出

# 转弯处理
<Br/>1.基础转向函数：利用switch语句将小车转向和电机驱动信号分为前后左右停五个case
<Br/>利用switch语句将小车转向和电机驱动信号分为前,后,左,右,停五个case。需要注意的是，在连接电机时利用试触法确定电机是否符合程序转向要求，再进行连线和焊接，以免装反不已改正。同时，switch语句对应的变量设置为unsigned char 相比于int 而言较为节省芯片的存储空间。

<Br/>2.校准转向函数
<Br/>（1）延时函数:利用循环达到延时效果
<Br/>首先建立延时函数，利用变量x，y进行循环，从而定量计算时间。在利用while循环与延时函数进行配合达到延时和效果。主要转向操作有左转、右转、前进、后退四部分。每部分对应不同的红外判断操作。同时，为了方式小车由于惯性导致变向不准确，函数中加入了停车语句，以保证对小车转弯的速度和角度进行较为精确的控制。

<Br/>（2）左转函数:左转和直行交替进行直至左红外检测到墙壁
<Br/>在利用while循环与延时函数进行配合达到延时和效果。主要转向操作有左转、右转、前进、后退四部分。每部分对应不同的红外判断操作。同时，为了方式小车由于惯性导致变向不准确，函数中加入了停车语句，以保证对小车转弯的速度和角度进行较为精确的控制。同时，结合红外探测头的外部信息，调控小车在程序内的循环是否持续进行。

<Br/>（3）右转函数:右转和直行交替进行直至右红外检测到墙壁
<Br/>与左转函数类似，但需要注意的是，由于电机不同，可能对于程序产生相应的驱动实际速度不同，为了保证左转右转均能达到较为准确的直角，右转函数与左转函数的时间需要分别测定，不可以指测试单一方向。类似的，后退时所特有的转弯程序的时间也是需要另外设置的。

<Br/>(4)前进函数:利用停止和驱动交替实现速度控制
<Br/>主要用于利用交替行进停止，降低小车运动速度。通过直行延时和停止延时的笔直来控制小车速度。需要注意的是步长对于小车运动的影响，就是说在完成一次循环的途中，小车是否会错过路口的记录。因此，需要保证每次循环的时间尽量合适。在满足不影响小车记录路线的情况下，尽量大一些。应为过小的话会使小车产生抖动，影响行进。

<Br/>(5)后退函数:从“死胡同”回到合理的“奇异点”
<Br/>后退函数设计的主要思想是：令小车回到一个可以继续探索的“奇异点”。也就是说，小车需要“原路返回”，同时，排查每个经过的奇异点（已经记录过的）是否存在未完全探索的路口，进而判断是否需要继续执行倒车程序。需要注意的是，小车判断达到“奇异点”并不能时小车在路口的正中央，因此在对“奇异点”做出处理前要再另外加合适的倒车进程使小车回到路口中央。

<Br/>【注1】奇异点：小车运动中可以发生转向的点；
<Br/>【注2】死胡同：小车三个红外均检测到程序。
