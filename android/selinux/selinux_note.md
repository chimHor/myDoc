#SELinux(Android)

SELinux 全称 Security Enhanced Linux (安全强化 Linux)，是 MAC (Mandatory Access Control，强制访问控制系统)的一个实现，++**目的在于明确的指明某个进程可以访问哪些资源(文件、网络端口等)**++。
强制访问控制系统的用途在于增强系统抵御 0-Day 攻击(利用尚未公开的漏洞实现的攻击行为)的能力。所以它不是网络防火墙或 ACL 的替代品，在用途上也不重复。

**++Android 在SELinux上作了一些定制。++**有人把它叫做SEAndroid。在4.3上开始引入selinux，使用
Permissive模式，4.4上使用部分Enforcing模式，5.0开始全面Enforcing模式

#####Android selinux保护覆盖范围
- 文件
- 属性
- binder通信
- socket通信

#####Android selinux相关代码配置路径
- external/sepolicy：提供了Android平台中的安全策略源文件。同时，该目录下的tools还提供了诸如m4,checkpolicy等编译安全策略文件的工具。注意，这些工具运行于主机（即不是提供给Android系统使用的）
- external/libselinux：提供了Android平台中的libselinux，供Android系统使用。
- external/libsepol：提供了供安全策略文件编译时使用的一个工具checkcon。


####SELinux运行状态
#####获取当前 SELinux 运行状态
`getenforce`
可能返回结果有三种：Enforcing、Permissive 和 Disabled。Disabled 代表 SELinux 被禁用，Permissive 代表仅记录安全警告但不阻止可疑行为，Enforcing 代表记录警告且阻止可疑行为。

#####改变 SELinux 运行状态
`setenforce [ Enforcing | Permissive | 1 | 0 ]`
该命令可以立刻改变 SELinux 运行状态，在 Enforcing 和 Permissive 之间切换，结果保持至关机。一个典型的用途是看看到底是不是 SELinux 导致某个服务或者程序无法运行。若是在 setenforce 0 之后服务或者程序依然无法运行，那么就可以肯定不是 SELinux 导致的。


###SEAndroid TE规则语法
##### context（label）
在selinux里面context和label是同一个含义，中文上面理解标签（label）更加容易理解。
selinux的基本控制权限的方法是，给不同的进程、文件打上标签（label），通过定义不同label之前的关系，来实现权限控制。

打开selinux的情况下执行：
`ls -Z /init.rc`
看到：
`-rwxr-x---  root    root       u:object_r:rootfs:s0  init.rc`
这里一共有4项内容： u , object_r, rootfs, s0
u表示user， object_r表示role，  rootfs表示type，  s0是Security Level
通过不同的user， role，tcontext，Security Level来控制权限


另外执行:
`ps -Z init`
看到：
`u:r:init:s0         root   1    0   /init`
和文件类似，也是4项内容

**Android上面只用到了type这个label来控制权限，其他三个label在selinux里面也可以完成其他机制的权限控制。所以下面的内容只涉及基于type权限控制的规则和关系**


#### type，domain，scontext，tcontext
MAC的机制分两中角色，主体和客体，主体就是发起动作的一方，就是指进程，客体是可以是各种资源（主要是文件形式），主体和客体都有一个标签叫type。但是进程的type一般不称为type，称为domain。可以理解为domain就是特指进程的type。

进程的selinux的context（label），有时能看到打印叫做scontext，文件的context（label），有时候看到打印也叫做tcontext，如下面一条avc打印：
```
avc: denied  { connectto } for  pid=2671 comm="ping" path="/dev/socket/dnsproxyd"
scontext=u:r:shell:s0 tcontext=u:r:netd:s0 tclass=unix_stream_socket
```

#### allow语句
下面是一条allow语句的例子
`allow netd proc:file write`
这个语句的含义是**允许netd(domain)对type为proc的object_class为file的文件进行写操作**。具体语法分析为：
- allow：TE的allow语句，表示授权。除了allow之外，还有allowaudit、dontaudit、neverallow等。
- netd：source type，主体的domain。
- proc：target type，客体的type
- file：代表Object Class。它代表能够给subject操作的一类东西。例如File、Dir、socket等。在Android系统中，有一个其他Linux系统没有的Object Class，那就是Binder。
- write：在该类Object Class中所定义的操作。

#### object class及其操作
客体除了type这个标签还有一个属性叫做object class。type和object class的区别是:假设在应用层，我有足够的权限，我可以改变一个文件的type，可以改为a，可以改为b，但是无法修改object class，这个文件的object class是由文件本身决定的。比如一个普通文件，它的object class就是file，就不能改成blk_file（块设备文件）。

allow语句例子中的write为操作，这个操作这个操作和object class相关，和type无关。我有两个socket文件，基于权限考虑，我让他们打上不同type，这样可以允许不同进程访问不同socket文件。操作和object class相关，比如socket文件，进程可以open这个socket，然后监听它，一个普通文件就不会有监听的操作。所以object class中的socket就有listen这个操作的定义，普通文件就没有。所以文件的object class是文件本身决定的，应用层有修改文件type的可能，但不可能修改object class。

Android上面的object class的**声明**参考android/external/sepolicy/security_classes，每个object class定义的操作参考android/external/sepolicy/access_vectors，access_vectors的语法比较好理解，其中有一个inherits表示继承关系

#### 进程domain以及domain的转化

所有进程是由init进程fork出来，init进程本身有自己的domain，但fork出来的子进程的也有自己的domain，所以必须有一个domain的转化过程。


#### 文件type配置
各个文件的type总会有一个初始的定义

###### init.rc中的restorecon命令


###### 新建文件的tcontext

#### property，binder的selinux规则

#### 小结
1. SEAndroid是通过type来控制权限，进程有自己的type（domain），资源（文件，属性，binder等）也有自己的type
2. 进程的domain是有多少种是硬编码（sepolicy），是系统编译的时候决定。进程实际运行时的domain可以发生改变，但是否允许改变和允许改变成哪个domain也是硬编码（sepolicy）
3. 资源本身的type有初始化值，是硬编码（sepolicy）。

#### android 里面selinux的一些hook判断



参考：
http://source.android.com/security/selinux/index.html
http://selinuxproject.org/page/Main_Page
