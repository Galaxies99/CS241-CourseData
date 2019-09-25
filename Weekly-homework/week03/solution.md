### week03：多项式的牛顿迭代法与线性方程组的高斯消元

**牛顿迭代法**

当牛顿迭代法应用在区间 [a, b] 上，区间需要满足：

- f(a)f(b) < 0
- $\forall x \in [a, b], f'(x) \not= 0$
- $\forall x \in (a, b),  sgn(f''(x)) = C$  ，其中 $C$ 为常数，$sgn(x)$ 为符号函数。
- $a - \frac{f(a)}{f'(a)} \leq b, b - \frac{f(b)}{f'(b)} \geq a$

那么可令x_0 = t (t \in [a, b])，利用牛顿迭代公式：
$$
x_n=x_{n-1} - \frac{f(x_{n-1})}{f'(x_{n-1})}
$$
迭代若干次即可得到结果。

**线性方程组的高斯消元**

将方程组化成矩阵形式 $A\mathbb{x} = B$，删去线性相关的方程组，然后将 $A$ 化为三角矩阵（利用方程之间的加减），再回代得到 $\mathbb{x}$ 的取值。

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

