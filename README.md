# 嵌入式模块整理

> 在工作中常用的模块进行整理，平台为STM32



## 一、模块使用规则/说明

#### 1.1 `.Default`后缀文件的使用

> Module中的大部分代码是多平台公用的，例如`Array.c` `SimpleBuffer.c` `Convert.c`，但是也有需要硬件处理的或者不同业务的，例如`ESP8266_Handle.c`需要硬件串口，`ZcProtocol_Handle.c`不同设备有不同的协议处理。同时用Module代码会造成不同使用者的文件不相同，无法使用git更新代码（同样的文件名，不同平台/产品内容不同，在pull push时会影响其他人的代码）。

为了能够可以不断更新代码又不影响所有的使用者，加入了.gitignore规则。

* 需要修改的文件（例如配置文件、handle文件）的文件名末尾加上.Default
  * `Sys_Conf.h` ==> `Sys_Conf.h.Default`
  * `ESP8266_Handle.c`   ==> `ESP8266_Handle.c.Default`
* 把`*_Conf.h` `*_Handle.c`加入.gitignore列表中 

这样，用户在使用的过程中，将带有.Default的文件（`_Conf.h.Default`或者`_Handle.c.Default`）复制并将.Default去掉，在新复制的文件内修改即可。

```
Sys_Conf.h		# 任意修改，不会上传或更新
Sys_Conf.h.Default	# 会随着commit不断更新，第一次使用时应该复制并去掉.Default
```

<font color="red">可以通过根目录的 ModuleHandle.exe 完成 添加/删除 .Default 后缀的操作</font>

#### 1.2 头文件的引用

常见的头文件采用直接引用，引用方式有如下

* 查看头文件所在文件夹
* 打开IDE的设置界面，将头文件所在文件夹路径加入到头文件路径列表中
* 在.c文件中通过include 'xxx.h'的方式引入
* 编译时，编译器根据头文件路径列表，找到该文件并编译

这种方式会造成大量include ‘xxx.h’，尤其在核心逻辑处理.c文件中完全不知道在哪里引入的头文件，所以模块中的头文件引用，全部采用**相对路径引入**，有以下好处。

* 在拷贝Module之后无需设置工程文件的头文件路径列表
* 在使用时能够清晰的看到引用的头文件所在的文件夹。



引入方式按照如下顺序

* 先引入C标准库
* 再引入其他文件夹的头文件
* 再引入本文件(通常为.c)所在路径的头文件

```
#include "stdlib.h"
#include "string.h"			
#include "../Common/Array.h"
#include "../Common/Convert.h"
#include "ZcProtocol.h"		# 与ZcProtocol.h文件为同一文件夹，可以直接引入
```

其他非Module中的文件添加.h文件的时候，建议同样使用相对路径

```
#include "../Module/UartDma/Stm32_UartDma.h"
#include "../Module/ESP8266/ESP8266.h"
#include "../Module/ZcProtocol/http.h"
#include "../Module/ZcProtocol/ZcProtocol.h"
#include "../Module/ZcProtocol/ZcProtocol_API.h"
```





#### 1.3 命名规则
>带有**的是属于 “隔离” 文件

  * **配置文件 `xxx_Conf.h`，针对模块的配置头文件。
  * 模块基础文件 `xxx.c/h`，模块的基础处理，寄存器定义、基础的配置、基础结构定义
  * 接口文件 `xxx_API.c/h`，介于业务层与基础配置之间，读写控制接口等
  * **硬件接口文件 `xxx_HAL.c/h`，针对不同MCU进行自定义配置
  * **业务处理文件 `xxx_Handle.c/h`，模块的业务处理模块，不同场景存在不同的配置以及处理方式
  
 
  

