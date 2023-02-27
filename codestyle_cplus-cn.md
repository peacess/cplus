[中文](./codestyle_cplus-cn.md)

# Code Style -- cplus 0.1

## 名词



## 规则
[参见](https://github.com/peacess/code_styles/blob/master/development_roles-cn.md)

```c++
int32_t fun_name(){
   //定义数据
   int32_t data = 0;
   //生成数据
   {}
   //使用数据
   return data;
}
```

## Name

[遵守C++的命名](https://en.cppreference.com/w/cpp/named_req)  
常用单词[Words](https://github.com/peacess/code_styles/blob/master/words_cn_en.md)   

1. 所有源代码文件名，使用小写，加下划线
2. 命名使用有明确函义的英文单词
3. 使用一至的单词顺命名。  
    一般是动词-名词-错误。这里有一种特殊的情况是，是某一分类下内容，可以在动词前面增加一个分类的前缀如 Eth---，或Btc---等

## 目录文件

1. 单元测试？
2. 所有的demo放入“ 仓库名/demo ” 目录中
3. 如果是框架或基础库，需要“仓库名/sample”

## 代码

1. 使用确定大小的类型，如int32_t而不少使用int类型，int只使用在局部，如循环变量等，像成员变量、或交互，或持久等都使用确定大小类型
2. 函数入参优先使用const &


### 多线程

### 代码提交前准备


### 测试


## 文档


## 库使用说明

### 

## 参考
[cppreference](https://en.cppreference.com/w/)

