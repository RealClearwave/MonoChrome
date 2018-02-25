

# Illegal
The new console RPG game framework.

**怎么使用该框架**

1.创建一个名为 ‘Characters’的文件夹，用于存放回合脚本

2.创建一个名为 ‘Scripts’的文件夹用于存放人物脚本

3.编译basic或C++版的源程序，开启框架。

**怎么编写脚本**

回合脚本应如下编写。


@Characters_Start //开始符

gutc\Hello.log //您的人物

Polaris\Hello.log //您的人物

ttyclear\Hello.log //您的人物

@Characters_End //结束符

Power=180 //定义变量
IQ=7 //定义变量
Like=10 //定义变量

并保存为 ‘scr + 回合（第几回合，无前导零） + .log’

人物脚本配合回合脚本存放。

如下图所示。

Characters

       ├─gutc
       
          ------Hello.log
          
       ├─Polaris
       
          ------Hello.log
          
       └─ttyclear
       
          ------Hello.log

脚本编写如下：（以gutc\Hello.log举例）

hello！#$

%hello.exe%$

Hi！#$

Are you ok?#$


其中，

‘#’表示换行，‘$’表示将话语权交给下一个角色,‘%’表示运行程序。

*IQ-5# ----> IQ -= 5;

*IQ+5# ----> IQ += 5;

*IQ=5# ----> IQ = 5;

~IQ~ ----> 输出'IQ'

^A>(=,<)B:(Expr1):(Expr2)^ ----> if (A>(=,<)B) (Expr1); else (Expr2);

'(Expr1)'Expr2; ----> while(Expr1) Expr2;

选择:

[Text1]

Text2,Expr1;

Text3,Expr2;

...  ,...  ;

Textn,Exprn;

#
