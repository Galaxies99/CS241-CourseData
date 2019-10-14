### week06 树与图的识别

给出若干条边（为树边时为父亲儿子关系，为图边时仅表示连通关系） $(a_i, b_i)$ 以及若干个根节点 $rt$ 构成的图，求出该图是由多少个子图构成，每个子图的类型以及权值和、大小分别是多少。

类型包括：单点、二叉树、树、图。

判定方法：

- Step 1：按照给定的边可以建出原图 G （父亲到儿子连有向边） 和反图 Gr（边全部反向）
- Step 2：给定的根节点所在连通块必然为（单点、二叉树、树），单点可以直接判断，二叉树和树利用一次 DFS 进行区分即可。
- Step 3：给定的根节点之外，还可能存在其他树但是没有给定根节点，这些树根的特点是没有父亲。找到原图中所有没有父亲的点x，判断x所在的连通块是否构成一棵树。
- Step 3.1：如何判断x所在的连通块是否构成一棵树？在原图上 DFS，每到一个结点，判断反图中，这个节点的边数。如果是一棵树，反图中该结点边数为0或1（0为根节点情况，1为其余结点情况）（因为必然存在儿子到父亲的反边）。
- Step 3.2：如果是一棵树，按照 Step 2 相同的方法判断二叉树与树即可；否则留给 Step 4。
- Step 4：剩下的就是图了，对原图和反图的并进行 DFS 找连通块即可。

坑点：

- 一条边 $(x, y)$ 可以是二叉树；
- 存在不给根节点的树（如一条边的情况）；
- 输出时的单复数注意区分…… graph(s)...
- 忘了…想到再说

本周题目主要难点：**字符串处理★★**，**树与图的判定★★★**






