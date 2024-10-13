# 指定编译器
CXX = g++
# 指定编译选项
#CXXFLAGS = -Wall -g

# 可执行文件名
TARGET = main

# 源文件
SRCS = main.cpp
# 头文件
HEADERS = LinkedList.h

# 默认目标
all: $(TARGET)

# 规则：如何编译源文件生成可执行文件
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# 清理目标
clean:
	rm -f $(TARGET)

