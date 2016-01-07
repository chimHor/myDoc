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

参考：
http://source.android.com/security/selinux/index.html
http://selinuxproject.org/page/Main_Page
