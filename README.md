# 15-Digital-Problem
人工智能课程大作业  

## 演示平台
* Visual Studio 2017编辑器
* C++语言/C语言
## Astar算法求解15数码问题
* A*（A-Star）算法是求解最短路最有效的直接搜索方法，也是许多其他问题的常用启发式算法。
* 其基本思想是：定义一个评价函数f，对当前的搜索状态进行评估，找出一个最有希望的结点来扩展。评价函数形式为：f(n)=g(n)+h(n)。其中f(n)是从初始状态经由状态n到目标状态的代价估计，g(n) 是在状态空间中从初始状态到状态n的实际代价，h(n) 是从状态n到目标状态的最佳路径的估计代价。
* A*算法要求启发函数中的h(n)是处在h*(n)的下届范围，即满足h(n)<=h*(n).
## IDAstar算法求解15数码问题
* 设置每次可达的最大深度depth，若没有到达目标状态则加深最大深度。采用估值函数，剪掉f(n)大于depth的路径。

## 总结归纳

- 这次的大作业还是比较粗糙的，参考了很多网上的8数码问题的资料，希望可以继续努力！