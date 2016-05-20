# Performance Evaluation in Color-based Image Retrieval Using Artificial Bee Colony Algorithm


**Keywords:** Image-Retrieval Artificial-Bee-Colony-Algorithm C++

**Abstract:** 

This paper focus on the application of artificial bee colony algorithm’s content based image retrieval (CBIR). The first step is to extract eigenvalues of color moments, color information entropy and color histogram, and then gain a comprehensive color eigenvalues, which is used to represent corresponding image, via weighting the three color eigenvalues after unitization and quantization. The next step to build an image feature library based on the image library. A traditional searching algorithm can be adopted to search the images to get the retrieved results. The third step is to search the images by artificial bee colony algorithm, mainly by global search strategy and local search strategy. In addition, global search strategy and retain elite strategy could accelerate this algorithmic’s astringency, while local search strategy and local area depend on the fitness to improve the accuracy of algorithmic. Finally, the author adopts Recall- Precision Chart to make a comparison between traditional searching algorithm and artificial bee colony algorithm. The result suggests that the effect of artificial bee colony algorithm is far more better than traditional searching algorithm. Artificial bee colony searching algorithm is able to find out the color image that satisfied to customer needs more accurately and effectively with a higher precision ratio and recall ratio.

**Conclusion:** 

This paper focus on the extraction of three color eigenvalues: color moments, color information entropy and color histogram. Color moments and color information entropy are operated in RGB color space, while color histogram is operated in the HSV color space, which is transformed from RGB color space on consider its particularity. Then we quantize the color histogram to reduce dimensionality. After that, a one-dimensional comprehensive eigenvalue is used to represent relevant image after normalization. Finally, we adopt traditional searching algorithm and artificial bee colony algorithm, which put forward in this paper to search images after the construction of image feature database.

The next step after extracting eigenvalues in target image and image database is to carry out the retrieval. There are two problems in conventional retrieval algorithm: low-efficiency, especially with a large database, and worse search result, which may leads to worse P-R (Precision-Recall) effect because of the interference from unrelated images. However, in comparison with traditional retrieval algorithm, artificial bee colony algorithm has two advantages in research: the research coverage can be limited to a better area by global search strategy. As a result, the number of search images is smaller and could increase the correlation between the results and target images, hence improve the quality of search results. The same is to local search strategy. We just need to decide the scale of area according to the fitness, a better fitness corresponding to a larger area, and vice versa. The reduction of images in the search area brings the improvement of scouting speed directly. The results show artificial bee colony algorithm brings some research significance to CBIR.


* The project is supported by the National Natural Science Foundation of China (Grant No. 61201458)

**Copyright Notices:** 

**Wang Z**, Liu X, Zhang J. Performance evaluation in color-based image retrieval using artificial bee colony algorithm[J]. J. Inf. Comput. Sci, 2014, 11(4): 1077-1086.


# 前言

## 阅读人群

在详细介绍该项目之前，先和大家介绍该项目的由来，借此可以认识该项目具体处于一个什么样的位置、级别以及具体解决了什么问题和解决到什么程度，再由此判断自己是否需要花费更多的时间继续阅读。什么样的人群比较适合阅读该项目？作者推荐以下人群：`1. 正在学习 C++ 的人`，`2. 对图像检索 | 元启发式智能算法感兴趣的人`。

排名有分先后，为什么首推的是正在学习 `c++` 的小伙伴？理由很简单，笔者作为一名过来者，在学习 `C++` 的路上，一直希望有好的项目可以值得自己学习，至少可以让自己从 `0` 到 `1`，从细节到整体独立完成整个项目开发过程。而该项目很适合这个需求，因此笔者首推目前正在学习 `C++` 的同学，有此需求的话，可以及推荐往下看。第二，由于该项目研究的领域属于图像检索方面，同时涉及到 `2005` 年提出的人工蜂群算法（一种元启发式算法），因此，对图像检索及启发式算法感兴趣的同学可以借此项目了解个大概。


## 项目由来

该项目由作者和几位小伙伴在大学期间共同完成，同时感谢笔者的大学班主任作为指导，最后还顺利发表了一篇 `EI` 检索的期刊论文 [`(Performance Evaluation in Color-based Image Retrieval Using Artificial Bee Colony Algorithm)`](http://www.joics.com/publishedpapers/2014_11_4_1077_1086.pdf)。

往事总归难回首，该项目也一样。现在看来，由于当时的知识储备有限，做出来的东西问题不少，堪称不忍直视。但，就像每个人的青春纪念品一样，它始终代表了笔者大学时期诸多奋斗步伐中的一小步，尽管如今它显得不尽完善，但始终代表了过去努力做到最好的一个自我状态。

故事是这样子的，笔者当年在大二上的时候申请了国家大学生创新创业实验计划，那年作为我校数学建模基地的助教之一，日常负责组织参加数模的同学（`40` 人左右）进行论文写作和发表一事，在一年一度的国创项目申请到来之际，也投了自己的项目申请书。印象中数模基地的 `10` 位助教中只有笔者的项目被批下来了，大学仅少数的 `RP` 峰值时刻。

关于[大学生创新创业实验计划](http://baike.baidu.com/link?url=3nutFi7J9MgYOsxhqTcz2EJcuivZA4f-xf_1hzb81603BtMnlky3C8kdgaEZY2oxoEpF4e-bPv1Mdh7KEMj-n_)，是教育部一年一度让 `120` 所高校鼓励在校学生进行创新性实验研究，力求培养学生的主动积极和创新思维。分校级、省级和国家级，该项目申请到的是国家级。

关于项目的灵感来源，当年笔者大二上，正好是 `Google` 发布了以图查图的搜索功能，那会还很少有人知道有以图查图的搜索模式存在，而且印象中 'Google' 的以图查图搜索结果并不是很好，速度和精度远没有现在的体验好。所以，笔者很初生牛犊不怕虎地灵机一动，能不能把课余时间看的 `人工蜂群算法` 用在图像检索应用上，看看是否可以提高速度和精度。结果就这么上了，当年真是艺低人胆大。

下面进入正题。

# 绪论

图像检索经历了两个发展阶段，第一个阶段为七十年代后期出现的基于文本的图像检索阶段 `[5]`，但由于随着多媒体技术和计算机网络的飞速发展，数字图像正以惊人的速度增长，基于文本的图像检索暴露出一系列不足 `[6]`。在九十年代早期开始了基于内容的图像检索阶段 `[7][8]`。

如今，基于内容的图像检索已成为热门的研究领域。而基于颜色的图像检索作为 `CBIR` 中所采取的主要手段之一，随着数字化图像颜色特征分析技术的成熟，也得到很大的发展 `[9]`。颜色直方图作为基础而重要的颜色特征，继承了颜色对几何变换的坑性，而且其提取和相似度计算相对简单，但是基于颜色直方图丢失了颜色的空间信息，并且存在特征维数过高等问题，针对这些问题，`Qiu G.P.` 等人提出了滤波器将图像中的不同频率分层，来量化图像亮度的方法 `[10]`。宋擒豹等人提出颜色位置直方图的方法，以解决直方图不具备空间信息的问题 `[11]`。而 `Stricker M.` 提出了一种简单有效的颜色特征描述方法，即颜色矩，有效地降低了颜色特征值的维度 `[12]`。`John` 提出采用图像颜色的信息熵来描述图像的颜色特征，这种方法有效地将颜色直方图从多维降到一维 `[13]`。王向阳则提出将图像位平面应用到图像检索中，以图像较高位平面的特征作为图像的索引 `[14]`。综上所述，基于颜色的图像检索涉及多个研究领域，有着广泛的应用前景，并且仍有许多关键技术尚未解决或不够完善，因此，研究该项技术既有深远的意义，同时也将面临巨大的挑战 `[15]`。

单一的特征值往往会强化图像的某部分信息而忽略其它部分，这样就不利于最终检索效果的提高。为了弥补单一特征值的缺陷，我们将颜色直方图，颜色矩和颜色信息熵三种主流的特征值分别进行归一化，然后分别设置不同的权重，根据权重进行线性合并而得到最终的综合特征向量。通过 `Microsoft Visual Studio 2010` 实现传统检索算法和人工蜂群算法的图像检索系统，通过人工蜂群算法在图像检索上的全局搜索策略和局部搜索策略，有效地提高了检索速度和精度。从而证明该算法对基于内容的图像检索领域有一定的意义。


# 图像特征值提取

常规的图像检索算法通常是采用单一的特征值来描述图片的颜色特征，这样会有多种弊端，比如单一的特征值往往会强化图像的某部分信息而忽略其它部分，这样就不利于最终检索结果的提高。因而为了弥补单一特征值的该缺陷，我们采用了多特征值来作为图像的最终特征值，其中主要实现了颜色矩，颜色信息熵，颜色直方图三种主流的特征值类型。

## 颜色矩

颜色矩已经成功应用在 `QBIC` 等图像检索系统上 `[16][17]`，由于颜色信息主要分布于低阶矩中，所以使用一阶矩，二阶矩和三阶矩足以表示图像的颜色的分布信息，和通常采用的颜色直方图相比较，颜色矩突出的特点在于不需要对图像特征进行向量化。具体计算如下所示：

其中 `f(i,j)` 表示彩色图像第 `i` 个颜色通道分量中灰度为 `j` 的像素出现的概率，`N` 表示图像中的像素个数。因此，图像的三个分量的 `R，G，B` 的前三阶颜色矩组成了一个 `9` 维直方图向量，即图像的颜色矩特征如公式`（4）`所示：

由于该算法涉及求乘积，平方，三次方等操作，致使整个算法的计算量特别大，因此基于颜色的图像检索系统一般不会单独使用该特征对图像进行检索，在实际操作中往往用来过滤图像以减小检索范围 `[19]`。

## 颜色信息熵

数字图像由像素构成，不同灰度值的像素点占据不同的空间，形成不同的分布，使图像呈现不同的表现形式 `[16]`。图像的颜色熵主要通过计算图像中对应像素的熵值来分析当前图像所对应的特征信息。对一幅含有 `N` 种颜色值的数字图像

其中 `pi` 表示第 `i` 种颜色值像素在整幅图像中出现的概率。

由于熵值的计算对应的计算量较大，因而为了在计算性能和特征值效果之间做出均衡，这里使用了 `3` 维的熵特征向量。这样子图像可视化的级别就由多维级别降到一维。如公式`（6）`所示


## 颜色直方图

虽然 `RGB` 彩色模型被广泛应用于 `CRT` 设备显示彩色图像，但它并不是以一致的尺度表示色彩，不符合人对颜色的感知心理 `[17]`。而基于颜色的图像检索一般要求选取具有视觉一致性的颜色空间，而 `HSV` 颜色空间是一种适合人眼视觉感知的颜色模型 `[18][19]`。因此在基于内容的图像检索中，应用这种颜色空间模型会更适合用户的视觉判断。`RGB` 和 `HSV` 颜色空间如图 `1` 所示

从 `RGB` 颜色空间到 `HSV` 颜色空间的变换 `[20]`可以用如下公式来表示：

现定义 `r1`、`g1`、`b1`分别为：

另外定义一个`h1`，该 `h1` 由新定义的 `r1`、`g1`、`b1` 得到。

最后，可以通过以上计算的中间变量，计算 `h` 的值，该值的定义如下所示：

由上述公式可知：

由于人眼对颜色的分辨能力有一定局限性，因此对整个颜色空间进行适当的量化是必要的，即选择代表性的颜色，丢弃那些无显著视觉意义的信息，从而使图像的检索过程能节约大量的计算时间。

因此，我们将 `H`，`S`，`V` 每个分量按照人的颜色感知进行非等间隔的量化，即把色度 `H` 空间分成 `14` 份，饱和度 `S` 和亮度 `V` 空间分别分成 `3` 份，并根据色彩的不同范围进行量化，把量化后的 `3` 个颜色分量合成一维特征向量：

其中，`Qs`, `Qv` 分别是颜色分量 `s` 和 `v` 的量化级。通过以上步骤，在 `HSV` 颜色空间把颜色特征量化到 `N` 个颜色空间，可以得到 `N` 柄的一维直方图。此颜色直方图是对图像进行匹配的依据。

## 三种颜色特征值的综合

由于单一的图像特征值对于图像的特征描述常常会有所偏重，进而也就会导致相应的检索结果也会出现误差。而将多种不同的特征值进行综合就可以在一定程度上弥补单一特征值的缺陷或是不足，进而可以得到更好的检索结果。

对于多种特征值向一个综合特征值的组合公式主要如下所示：

其中，每个单一的 `Vi` 都是已经单位化后的特征向量，`ai` 表示每个单一的特征向量所对应的权重值。 
我们在得到三种独立的特征值之后分别将其归一化，之后分别设置不同的权重，根据权重进行线性合并而得到最终的特征向量。

通过上述理论公式可知，在计算综合特征值时需要涉及到以下几个步骤：

`Step1: `三种独立特征向量的提取。

`Step2: `独立特征向量的单位化。

`Step3: `综合特征值的计算。


# 基于人工蜂群算法的检索

基于蜂群算法的检索是使用智能优化算法来对图像库进行检索，蜂群算法的原理比较复杂，主要来源于仿生学原理，其中主要的算法过程如下。

## 对于当前的图像库生成初始蜂群

一个蜂群即是包含有多个蜂个体的集合，这里的单个蜂对应的意义即为在数据库中的每个图像的位置以及其上的图像与目标图像之间的相似度，用该相似度可以来评估当前蜂个体的优劣。生成初始化蜂群的操作如下：

其中，`min` 为解空间的下界值，`max` 为解空间的上界值，`Rand (0, 1)` 为 `0` 到 `1` 之间的随机数。这一更新公式代表了算法的全局搜索策略。该侦察蜂群体的维护，使得算法具有较好的全局搜索能力，从而避免蜂群陷入局部极值。

这里主要是使用了随机化算法来生成初始蜂群。接下来需要对当前的蜂群进行评估，以判断其是否是一个合法的蜂群。一个直观的依据就是该蜂群中最优的那个蜂个体能否满足算法的相似度需求，如果可以的话就认为其是一个合适的蜂群，否则的话就不是。因而判断蜂群是还是合法就主要涉及两部操作：计算蜂群中每个个体与目标图像的相似度，这里我们采用欧式距离 `[21]` 作为适应度函数算出相对应的适应度判断其中的最优蜂是否满足阈值要求。

上述判断操作结束之后可以得到两种情况结果：

- 当前的蜂群合法；
- 当前的蜂群不合法；

对于不合法的蜂群，其对应的意义是：当前蜂群中的每个个体与目标图像的相似度差距均较大，这样的话对其中的任何一个个体进行领域搜索来试图求出最终的解并没有太大的意义，因而这样的蜂群就不能够被使用，用公式`（14）`求解出新的蜂群。

如此一来，如果当前操作得到了一个不合法的蜂群，接下来的操作就需要计算另外的一个蜂群，并再判断，一直到获得了一个符合要求的蜂群为止。

## 合法蜂群中的领域计算

得到了相应的合法蜂群之后，接下来就可以使用该蜂群中的个体在解空间的局部进行搜索，代表了局部邻域搜索策略，其更新公式为：

其中，`rand (0, 1)` 为 `0` 到 `1` 之间的随机数；`ngh` 值称为花丛半径大小，即邻域搜索半径。
该值是蜂群算法的一个重要参数，该值的大小随优化问题而定，对该值的设定能够影响算法的性能,要根据经验来调整。一般来说如果此领域越小对应的算法效率越高，但同时会降低算法的精确度；领域越大则与之相反。领域搜索相对于整个数据库的搜索最显著的变化就是搜索区域的减小，进而带来的影响就是搜索效率的提高。

这里需要注意的是，对于一个蜂群，其中可能包含很多个蜂个体，但其中又会有相应的优劣性不同（即相似度的差异）。对于这其中的蜂个体，算法没有必要对其中的每一个都进行相应的领域搜索，只需要针对其中的较好的蜂个体进行领域搜索即可。相似度更高的图片获得更多的观察蜂对领域进行检索，通过适应度可以计算出它们对应的概率值p，通过使用公式`（17）`

其中 `fiti` 是图片 `i` 和被检索图片之间的相似度，`CS` 是蜂群大小。通过 `pi` 就可以得到对应侦察蜂的数量。

领域计算的结果是得到一个相对于数据库中的图像的相关区域的一个索引范围标记，这个范围的首尾也即对应数据库中图像元素的起始，这即是我们进行下一步领域搜索的限定范围。

## 基于人工蜂群算法的检索步骤

得到了当前蜂群所对应的搜索领域之后，即可以进行该领域上的搜索。这里注意领域空间与整个数据库空间之间的关系：领域必定是整个数据库空间的一个子集。这里的子集大小就是由算法的参数进行相应的设置。

`Step1：`定义初始化值：蜂群大小，迭代次数等。 

`Step2：`指定检索关键图 `Q`，并从图像数据库中读出该图。

`Step3：`颜色空间的转换，提取图像的特征向量，对特征向量进行量化得到一维特征向量。

`Step4：`全局随机搜索进行匹配，计算各自适应度值。

`Step5：`采用精英策略，保留适应度值靠前的所有个体，摒弃较差的个体。

`Step6：`对保留的个体进行领域搜索，当出现所有精英解都达不到要求时，摒弃所有解，进行全局搜索。重复`Step4`。

`Step7：`按相似性距离进行降序排序。

`Step8：`返回相似性较高的检索结果。

# 检索系统实现

基于上述的理论基础，最终，我们实现了一个高效的图像检索程序，其实现主要采用了 `MFC` 作为程序与 `UI` 的框架；其中的图像加载与渲染则采用了可以高效渲染的 `OpenGL`。我们随机抽取一张图片作为检索图，看传统检索方法和人工蜂群算法下的检索情况，如下图所示：

通过传统算法检索图和人工蜂群算法检索图的直观比较，可以看出人工蜂群算法检索图的检索效果明显比前者好。另一方面，基于人工蜂群算法的检索时间比前者明显得到改善，我们对图像库的里面的每一类图片做了检索，统计出传统检索算法和人工蜂群检索算法的检索时间，如表1所示

基于人工蜂群算法的检索方法，大大提高了检索的精确性以及缩短了检索的时间，为了更近一步的检验人工蜂群算法对图像检索起到的作用，我们将进一步利用其它指标对其进行评价。

# 检索效果检验

为了能够比较人工蜂群算法检索算法与传统检索算法的区别，我们采用公认的两个评价指标：查准率和查全率

（1）查准率（Precision）：它的含义是，在一次检索过程中，系统返回的相关图像数目占所有返回结果数目的比例，当Precision=100%时，表示查询结果均为相关图像。

（2）查全率（Recall）：表示在查询结果中，与目标相关的图像占图像数据库中所有相关图像数目的比例，当Recall=100%时表示全部与目标相关的图像均被检索出来。

查准率和查全率越高，表明该检索系统的效果越好。然而，通常情况下这两项指标是一对矛盾，当要求查准率较高时，查全率较低，反之亦然。

对算法的结果进行查准率和查全率统计是完整工作很重要的一部分。RP曲线可以反映出检索系统与检索算法的优劣。其主要统计检索结果与目标图像有关联（属于同一类的图像）的分布，并以曲线的形式给出。在该算法中同样实现了RP曲线的统计与显示功能，其如下所示：

其中横轴为查全率（Recall），纵轴为查准率（Precision）。其中同时给出了使用常规遍历搜索和蜂群搜索两种结果，并以不同的颜色绘制，以便方便地查看出两者之间的性能与结果差异。RP曲线的评价标准是：曲线越往右上方则对就应的结果越好（也即曲线所对的两个坐标轴的积分面积越大），通过这个标准可以轻易地判断两个检索算法的优劣。
# 结论

本文通过提取图像的颜色矩，颜色信息熵以及颜色直方图等三个颜色特征值。其中颜色矩和颜色信息熵都是在RGB颜色空间下操作，而考虑到颜色直方图的特殊性，我们先将RGB颜色空间转换为HSV颜色空间，再在HSV颜色空间下提取图像的颜色直方图，然后将颜色直方图进行量化，减少维数。接着将它们归一化后合并为一维综合特征值来表示相应的图像。在建立图像特征库后，分别采用传统检索算法和本文提出的人工蜂群算法对图像进行检索。

对目标图片与图片数据库提取特征值之后下一步的操作就是执行检索。常规的检索算法一般有两个问题：算法的效率较低，其劣势特别突显在数据库的规模较大的情况下。搜索结果较差，存在一个无关图片对相关图片干扰的问题，这样可能就会导致最后搜索结果对应的P-R （Precision-Recall）效果较差。而使用人工蜂群算法对图像库进行搜索相对于传统检索算法主要有以下两方面的优势：通过全局搜索策略可以将搜索的范围限制于一个更优的领域之内，这样搜索对应的图像数量较少，且能够增加结果与目标图像之间的关联度，进而提高结果的质量。而局域搜索策略也与上相同，由于只需要根据适应度大小来决定领域范围大小，越好的适应度对应越大的领域，相对差一点的适应度对应的领域范围就越小，在领域内搜索的图像也较少，因而带来的直接影响就是搜索速度的提高。从而证明人工蜂群算法对于基于内容的图像检索有一定的研究意义。


