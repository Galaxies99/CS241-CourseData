# CS241-Homework
CS241 Homework Source Code

目前更新了三周的小作业啦~

作业地址：https://www.educoder.net/

### week01：高精度四则运算的实现

高精度四则运算：对于加法、减法对位相加或相减；对于乘法利用朴素的 $O(n^2)$ 模拟实现；对于除法模拟移位、试除操作。

特别提及：对于大整数乘法，有着一种时间复杂度可以达到 $O(n \log n)$ 的算法：Fast Fourier Transformation（快速傅里叶变换），以及与之思想相同的基于模意义下原根的 NTT（快速数论变换），这里不赘述，有兴趣的同学可以自行上网查询相关资料。

本周作业的代码参见 Weekly-homework 文件夹下的 week01 子文件夹的 main.cpp ，内部的 Number 类重载了高精度的加减乘除，Expression 类在实现四则运算的基础上，进一步实现了表达式求值。

本周题目主要难点：**高精度除法★★**

### week02：多项式求导与多项式除法

多项式求导的操作非常基本，即对于每一项分开求导，利用 b \not= 0 时的式 (ax^b)'=abx^{b-1} 即可得到答案。

多项式除法的操作也非常基本，即为 **长除法** 。从高次项向低次项处理，乘以能够消去高次项的系数 k 再相减即可得到商的一项。

本周作业的代码参见 Weekly-homework 文件夹下的 week02 子文件夹的 Polynomial.hpp 以及 main.cpp。

其中，Polynomial.hpp 中主要实现了多项式类 Polynomial，支持用 string 字符串初始化，求导及多项式除法。

其中，对于多项式的储存的方法为：将（指数，系数）二元组 (a, k) 存入 vector 中，再按 a 的大小排序。

本周题目主要难点：**字符串处理★★★**，**多项式存储方法★☆**， **多项式除法★★**
$$

$$




### week03：多项式的牛顿迭代法与线性方程组的高斯消元

**牛顿迭代法**

当牛顿迭代法应用在区间 [a, b] 上，区间需要满足：

- f(a)f(b) < 0
- $\forall x \in [a, b], f'(x) \not= 0$
- $\forall x \in (a, b),  sgn(f''(x)) = C$  ，其中 $C$ 为常数，$sgn(x)$ 为符号函数。
- \forall x \in [a, b] f'(x) \not= 0
- $\forall x \in (a, b),  sgn(f''(x)) = C$  ，其中 $C$ 为常数，$sgn(x)$ 为符号函数。
- $a - \frac{f(a)}{f'(a)} \leq b, b - \frac{f(b)}{f'(b)} \geq a$

那么可令x_0 = t (t \in [a, b])，利用牛顿迭代公式：
$$
x_n=x_{n-1} - \frac{f(x_{n-1})}{f'(x_{n-1})}
$$
迭代若干次即可得到结果。

**线性方程组的高斯消元**

将方程组化成矩阵形式 A\mathbb{x} = B，删去线性相关的方程组，然后将 A 化为三角矩阵（利用方程之间的加减），再回代得到 \mathbb{x} 的取值。

**代码实现**

单纯的算法代码见 Gauss-Algorithm.cpp 和 Newton_Algorithm.cpp。

本周的作业代码参见 LinearEquations.hpp，Polynomial.hpp（和之前的完全相同）以及 main.cpp。

对于牛顿迭代，需要注意的地方有：

- 由于数据问题，不能将牛顿迭代法的判断条件 (4) 应用在代码中，会导致错误（其实是数据有错）；
- 迭代精度 1e-5，判断精度 1e-9。

对于高斯消元，需要注意的地方有：

- 对于不同变元下标的处理，可以参见 LinearEquations.hpp 中 LinearEquation 类的 add_new_equation 和 refresh 函数的处理方法；
- 对于字符串的处理，和 Polynomial.hpp 类似，需要注意的是引入了等号；
- 精度大约取 1e-9 合适；
- 在代码中，实际我实现了区分无穷解和无解的部分，当 pair 的 second 为 -1 表示无解，为 1 表示无穷解，为 0 表示有唯一解；
- 利用 week02 作业的 Polynomial.hpp 中的 Tools :: output(double x) 进行截位输出。

本周题目主要难点：**字符串处理★★★☆**，**牛顿迭代法★☆**，**高斯消元★★★**





下周一再见啦~

Last Update on Sept. 23th.



