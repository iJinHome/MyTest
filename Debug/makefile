#create:2018-10-12
#auther:zsl,wb

#方便阅读本文件的知识
#(1)字符'\'表示换行
#(2)所有目标的第一条指令前必须有一个tab，不可用4个空格代替
#(3)$@  表示目标文件
#   $^  表示所有的依赖文件
#   $<  表示第一个依赖文件
#   $?  表示比目标还要新的依赖文件列表

#定义本文件中使用到的变量【根据实际需要修改】
#控制台输出程序路径
printf    := echo

#.C文件文件夹
SRC_C := ./srcc
#.S文件文件夹
SRC_S := ./srcs
#.o文件存放目录
D_OBJ := ./obj
#.d文件存放目录
D_MK  := ./dmk
#.C文件列表
SRC_CList := $(wildcard ./srcc/*.c)
#.CPP文件列表
#【20200305 1/8】 姜家乐&王浩波 新增.cpp的文件列表，仿照.c文件列表添加
SRC_CPPList := $(wildcard ./srcc/*.cpp)
#.s文件列表
#【20200305 2/8】 姜家乐&王浩波 新增.S文件列表，并将原来.s和.S进行区分
SRC_sList := $(wildcard ./srcs/*.s)
#.S文件列表
SRC_SList := $(wildcard ./srcs/*.S)

#链接文件(.ld)的存储路径
linkFile := "F:\交通灯\03_MCU\Linker_file\STM32L431RCTX_FLASH.ld"
#定义生成的文件名
finalGoal := 交通灯
#定义头文件所在的路径
include := -I"F:\交通灯\.git" -I"F:\交通灯\.settings" -I"F:\交通灯\01_Doc" -I"F:\交通灯\02_CPU" -I"F:\交通灯\03_MCU" -I"F:\交通灯\04_GEC" -I"F:\交通灯\05_UserBoard" -I"F:\交通灯\06_SoftComponent" -I"F:\交通灯\07_NosPrg" -I"F:\交通灯\Debug" -I"F:\交通灯\.git\hooks" -I"F:\交通灯\.git\info" -I"F:\交通灯\.git\logs" -I"F:\交通灯\.git\objects" -I"F:\交通灯\.git\refs" -I"F:\交通灯\.git\logs\refs" -I"F:\交通灯\.git\logs\refs\heads" -I"F:\交通灯\.git\objects\01" -I"F:\交通灯\.git\objects\02" -I"F:\交通灯\.git\objects\07" -I"F:\交通灯\.git\objects\08" -I"F:\交通灯\.git\objects\0a" -I"F:\交通灯\.git\objects\10" -I"F:\交通灯\.git\objects\13" -I"F:\交通灯\.git\objects\16" -I"F:\交通灯\.git\objects\17" -I"F:\交通灯\.git\objects\19" -I"F:\交通灯\.git\objects\20" -I"F:\交通灯\.git\objects\25" -I"F:\交通灯\.git\objects\2d" -I"F:\交通灯\.git\objects\30" -I"F:\交通灯\.git\objects\32" -I"F:\交通灯\.git\objects\33" -I"F:\交通灯\.git\objects\34" -I"F:\交通灯\.git\objects\35" -I"F:\交通灯\.git\objects\38" -I"F:\交通灯\.git\objects\3b" -I"F:\交通灯\.git\objects\3e" -I"F:\交通灯\.git\objects\43" -I"F:\交通灯\.git\objects\45" -I"F:\交通灯\.git\objects\4c" -I"F:\交通灯\.git\objects\4d" -I"F:\交通灯\.git\objects\58" -I"F:\交通灯\.git\objects\59" -I"F:\交通灯\.git\objects\66" -I"F:\交通灯\.git\objects\6a" -I"F:\交通灯\.git\objects\6f" -I"F:\交通灯\.git\objects\71" -I"F:\交通灯\.git\objects\75" -I"F:\交通灯\.git\objects\7c" -I"F:\交通灯\.git\objects\82" -I"F:\交通灯\.git\objects\84" -I"F:\交通灯\.git\objects\86" -I"F:\交通灯\.git\objects\8d" -I"F:\交通灯\.git\objects\92" -I"F:\交通灯\.git\objects\94" -I"F:\交通灯\.git\objects\95" -I"F:\交通灯\.git\objects\96" -I"F:\交通灯\.git\objects\98" -I"F:\交通灯\.git\objects\9b" -I"F:\交通灯\.git\objects\9d" -I"F:\交通灯\.git\objects\a0" -I"F:\交通灯\.git\objects\a3" -I"F:\交通灯\.git\objects\a9" -I"F:\交通灯\.git\objects\aa" -I"F:\交通灯\.git\objects\ab" -I"F:\交通灯\.git\objects\ac" -I"F:\交通灯\.git\objects\b6" -I"F:\交通灯\.git\objects\ba" -I"F:\交通灯\.git\objects\bb" -I"F:\交通灯\.git\objects\be" -I"F:\交通灯\.git\objects\c3" -I"F:\交通灯\.git\objects\c5" -I"F:\交通灯\.git\objects\c6" -I"F:\交通灯\.git\objects\ce" -I"F:\交通灯\.git\objects\d1" -I"F:\交通灯\.git\objects\d4" -I"F:\交通灯\.git\objects\d6" -I"F:\交通灯\.git\objects\d8" -I"F:\交通灯\.git\objects\db" -I"F:\交通灯\.git\objects\dd" -I"F:\交通灯\.git\objects\e0" -I"F:\交通灯\.git\objects\e3" -I"F:\交通灯\.git\objects\e4" -I"F:\交通灯\.git\objects\e6" -I"F:\交通灯\.git\objects\e7" -I"F:\交通灯\.git\objects\ea" -I"F:\交通灯\.git\objects\eb" -I"F:\交通灯\.git\objects\ec" -I"F:\交通灯\.git\objects\f0" -I"F:\交通灯\.git\objects\f3" -I"F:\交通灯\.git\objects\f8" -I"F:\交通灯\.git\objects\fb" -I"F:\交通灯\.git\objects\fd" -I"F:\交通灯\.git\objects\ff" -I"F:\交通灯\.git\objects\info" -I"F:\交通灯\.git\objects\pack" -I"F:\交通灯\.git\refs\heads" -I"F:\交通灯\.git\refs\tags" -I"F:\交通灯\03_MCU\Linker_file" -I"F:\交通灯\03_MCU\MCU_drivers" -I"F:\交通灯\03_MCU\startup" -I"F:\交通灯\Debug\obj" -I"F:\交通灯\Debug\srcc" -I"F:\交通灯\Debug\srcs"
#定义优化级别。共有O0、O1、O2、Os和Og，默认使用Og
opt := Og
#.o文件列表
#【20200305 3/8】 姜家乐&王浩波 将原来的OBJ_C改为OBJ-CS，新增.S的.o生成文件

#把.c文件替换为.o文件
OBJ_CS := $(addprefix $(D_OBJ)/,$(patsubst %.c,%.o,$(notdir $(SRC_CList))))
#把.cpp文件替换为.o文件
OBJ_CS += $(addprefix $(D_OBJ)/,$(patsubst %.cpp,%.o,$(notdir $(SRC_CPPList))))
#把.s文件替换为.o文件  
OBJ_CS += $(addprefix $(D_OBJ)/,$(patsubst %.s,%.o,$(notdir $(SRC_sList))))
#把.S文件替换为.o文件  
OBJ_CS += $(addprefix $(D_OBJ)/,$(patsubst %.S,%.o,$(notdir $(SRC_SList))))

#.d文件列表
#【20200305 4/8】 姜家乐&王浩波 新增.S的.d生成文件

#把.c文件替换为.d文件
SRC_MK := $(addprefix $(D_OBJ)/, $(patsubst %.c,%.d,$(notdir $(SRC_CList))))
#把.cpp文件替换为.d文件
SRC_MK += $(addprefix $(D_OBJ)/, $(patsubst %.cpp,%.d,$(notdir $(SRC_CPPList))))
#把.s文件替换为.d文件
SRC_MK += $(addprefix $(D_OBJ)/, $(patsubst %.s,%.d,$(notdir $(SRC_sList))))
#把.S文件替换为.d文件  
SRC_MK += $(addprefix $(D_OBJ)/, $(patsubst %.S,%.d,$(notdir $(SRC_SList))))


#将文件夹./Source中的.c文件编译为.o文件
#【20200305 5/8】 姜家乐&王浩波 将优先级-O0改成-$(opt),以下所有均修改
$(D_OBJ)/%.o:$(SRC_C)/%.c
	arm-none-eabi-gcc "$^" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG \
-DSTM32L431xx -c $(include) -$(opt) -ffunction-sections -fdata-sections -Wall -fstack-usage \
-MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" 

#将文件夹./Source中的.cpp文件编译为.o文件
#【20200305 6/8】 姜家乐&王浩波 新增.cpp的编译成.o文件的规则格式
$(D_OBJ)/%.o:$(SRC_C)/%.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -c $(include) -$(opt) \
-ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics \
-fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)"  -MT"$@" \
--specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

#将文件夹./Source中的.s文件编译为.o文件 
$(D_OBJ)/%.o:$(SRC_S)/%.s
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c $(include) -x assembler-with-cpp \
--specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

#将文件夹./Source中的.S文件编译为.o文件 
#【20200305 7/8】 姜家乐&王浩波 新增.S的编译成.o文件的规则格式
$(D_OBJ)/%.o:$(SRC_S)/%.S
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c $(include) -x assembler-with-cpp \
--specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"




# 罗列文件中的目标。目标为希望生成的文件。其中“all”和“clean”为伪目标
all:default.size.stdout $(finalGoal).lst $(finalGoal).hex 

#【20200305 8/8】 姜家乐&王浩波 将原来的gcc改为g++,并将OBJ_C改为OBJ_CS

$(finalGoal).elf: $(OBJ_CS)
	arm-none-eabi-g++ -o "$(finalGoal).elf" $(OBJ_CS) -mcpu=cortex-m4 -T $(linkFile) \
--specs=nosys.specs -Wl,-Map="$(finalGoal).map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 \
-mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@$(printf) 'Finished building target: $@'
	@$(printf) ' '

$(finalGoal).hex: $(finalGoal).elf $(finalGoal).lst
	arm-none-eabi-objcopy -O ihex "$<"  "$@"
	@$(printf) 'Finished building: $@'
	@$(printf) ' '

# 【20200604 5/5】 查看芯片内存使用情况
default.size.stdout: $(finalGoal).elf
	arm-none-eabi-size  $(finalGoal).elf
	@echo 'Finished building: $@'
	@echo ' '
	
$(finalGoal).lst: $(finalGoal).elf
	arm-none-eabi-objdump -h -S "$(finalGoal).elf" > "$(finalGoal).lst"
	@$(printf) 'Finished building: $@'
	@$(printf) ' '

#设置清理工作空间的伪目标
#仅删除目标文件，其它文件若未发生变动则不编译，有利于提高编译速度
fastClean:
	rm -rf "$(finalGoal).elf" "$(finalGoal).hex" "$(finalGoal).map"
	-@$(printf) 'make: fast clean has be done'
	-@$(printf) ' '
#删除所有中间文件和目标文件，全部重新编译	
clean:
	rm -rf  "$(finalGoal).elf" "$(finalGoal).hex" "$(finalGoal).map" "$(finalGoal).lst" "$(finalGoal).hex" $(OBJ_C) $(SRC_MK)
	-@$(printf) 'make: clean has be done'
	-@$(printf) ' '
test:
	arm-none-eabi-size  $(finalGoal).elf
	@$(printf) 'Finished building: $@'
	@$(printf) ' '
	-@$(printf)  $(OBJ_C)
	
#指定哪些目标为伪目标
.PHONY: all clean fastClean test


