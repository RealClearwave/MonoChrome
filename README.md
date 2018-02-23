# Illegal
The new console RPG game framework.

**怎么使用该框架**
1.创建一个名为 ‘Characters’的文件夹，用于存放回合脚本
2.创建一个名为 ‘Scripts’的文件夹用于存放任务脚本
3.编译basic或C++版的源程序，开启框架。

**怎么编写脚本**
回合脚本应如下编写。
···cpp
@Characters_Start //开始符
gutc\Hello.log //您的人物
Polaris\Hello.log //您的人物
ttyclear\Hello.log //您的人物
@Characters_End //结束符
···
并保存为 ‘scr + 回合（第几回合，无前导零） + .log’
