### week05 一元线性回归

给出 n 个坐标 $(x_1, y_1), (x_2, y_2), ..., (x_n, y_n)$ ，利用**最小二乘法**对其进行线性拟合并计算相关系数。

相关系数：
$$
r = \frac{\sum_{i=1}^n(x_i-\bar{x})(y_i-\bar{y})}{\sqrt{\sum_{i=1}^n(x_i-\bar{x})^2}\sqrt{\sum_{i=1}^n(y_i-\bar{y})^2}}
$$
其中，
$$
\bar{x} = \frac{1}{n} \sum_{i=1}^n x_i, \bar{y} = \frac{1}{n} \sum_{i=1}^n y_i
$$
当 r \geq 0.75 时认为有**强线性相关**关系，拟合为y = ax+b

其中，
$$
a=\frac{\sum_{i=1}^nx_iy_i-n\bar{x}\bar{y}}{\sum_{i=1}^nx_i^2-n\bar{x}^2}\\
b=\bar{y}-a\bar{x}
$$
即为所求。

需要注意的地方：

- 输出三个 error 的情况需要判断：点数小于2或者大于100（虽然不会超过10行）或者有特殊字符（这里没有）；

- 有部分情况需要输出相关系数 r 和两个 error；

- 建议对于 double 类型的数输出时进行加减一个小量来抵消误差，如：

  ```c++
  if(y > 0) y += 0.000001;
  else y -= 0.000001;
  ```

  然后再进行截断输出。

本周题目主要难点：**字符串处理★★★（可以不用写）**，**最小二乘法求一元线性回归★**







