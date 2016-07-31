#make
###概念
目标，依赖，命令
规则，描述什么情况下如何重建目标文件
根据依赖关系，决定是否执行规则所定义的命令的过程，称为执行规则
伪目标，没有任何依赖的目标

###MakeFile注意事项
1. 命令以TAB开头
2. 使用反斜杠连接上下两行，反斜杠后不能有不能有空格或TAB


###语法规则
1. include包含其他makefile时，如果makefile也是一个目标，会执行规则重建这个目标。当所有makefile都是最新时，再清除当前所有解析的内容，重新解析makefile，根据目标执行规则
2. MAKEFILE_LIST包含了当前所有读取过的makefile，最后一个字为当前的makefile
3. 变量的赋值
```
IMMEDIATE = DEFERRED
IMMEDIATE ?= DEFERRED
IMMEDIATE := IMMEDIATE
IMMEDIATE += DEFERRED or IMMEDIATE
define IMMEDIATE
    DEFERRED
Endef
```
4. 规则定义
```
IMMEDIATE : IMMEDIATE ; DEFERRED
	DEFERRED
```
5. 依赖类型，ORDER-ONLY-PREREQUISITES只有在目标不存在，第一次生成的时候才有依赖关系
```
TARGETS : NORMAL_PREREQUISITES | ORDER-ONLY-PREREQUISITES
```
6. 文件通配符(*)：只能用于目标，依赖，命令中。其他情况用wildcard函数
7. 