#make
###概念
目标，依赖，命令
规则，描述**什么**情况下**如何**重建目标文件
根据依赖关系，决定是否执行规则所定义的命令的过程，称为执行规则
伪目标，没有任何依赖的目标

###MakeFile注意事项
1. 命令以TAB开头
2. 使用反斜杠连接上下两行，反斜杠后不能有不能有空格或TAB


###语法规则
1. include包含其他makefile时，如果makefile也是一个目标，会执行规则重建这个目标。上述过程可能会重复多次，直到所有makefile都是最新时，再清除当前所有解析的内容，重新解析makefile，根据目标执行规则
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
7. 双冒号依赖规则与单冒号依赖规则区别:
  - 多条单冒号依赖规则会合并，依赖关系和会合在一起，最后一组规则命令会override前面的命令，一旦根据合并的依赖关系满足构建条件，只执行最后的一组命令
  - 多条单，依赖关系不会合并，满足哪组依赖关系条件就执行哪组命令，可能会执行多组命令
8. 每一条命令的pwd不会相互影响
9. 命令执行出错会自动停止构建，除非在命令前加上`-`
10. if语句语法（if语句可以放在构建命令中）
```
if(n)eq ($(a),$(b))
xxx
else
yyy
endif
if(n)def VARIABLE_NAME
xxx
else
yyy
endif
```
11. define定义构建命令组，define中间的换行认为是`;`
12. 内建函数调用
```
$(FUNCTION ARGUMENTS)
```
13. define定义函数，调用方法
```
define fun
#$(1), $(2) ...
endef
$(call fun,PARA..)
```