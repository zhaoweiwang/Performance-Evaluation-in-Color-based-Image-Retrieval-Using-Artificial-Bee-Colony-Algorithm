# Performance-Evaluation-in-Color-based-Image-Retrieval-Using-Artificial-Bee-Colony-Algorithm


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

在详细介绍该项目之前，先和大家介绍该项目的由来，借此可以认识该项目具体处于一个什么样的位置、级别以及具体解决了什么问题和解决到什么程度，再由此判断自己是否需要花费更多的时间继续阅读。

什么样的人群比较适合阅读该项目？作者推荐以下三类人群：`1. 正在学习 C++ 的人`，`2. 对图像检索 | 元启发式智能算法感兴趣的人`，`3. 可能或即将成为我老大的人`。

排名有分先后，为什么首推的是正在学习 `c++` 的小伙伴？理由很简单，笔者作为一名过来者，在学习 `C++` 的路上，一直希望有好的项目可以值得自己学习，至少可以让自己从 `0` 到 `1`，从细节到整体独立完成整个项目开发过程。而该项目很适合这个需求，因此笔者首推目前正在学习 `C++` 的同学，有此需求的话，可以及推荐往下看。

第二，由于该项目研究的领域属于图像检索方面，同时涉及到 `2005` 年提出的人工蜂群算法（一种元启发式算法），因此，对图像检索及启发式算法感兴趣的同学可以借此项目了解个大概。

第三，作为一个小顺带，或许笔者以后的老大想了解自己做过啥，可能可以到这里瞅两眼。特此声明，该项目不代表本人目前的水平，但有一定的参考价值。

## 项目由来

该项目由作者和几位小伙伴在大学期间共同完成，同时感谢笔者的大学班主任作为指导，最后还顺利发表了一篇 `EI` 检索的期刊论文 [`(Performance Evaluation in Color-based Image Retrieval Using Artificial Bee Colony Algorithm)`](http://www.joics.com/publishedpapers/2014_11_4_1077_1086.pdf)。

往事总归难回首，该项目也一样。现在看来，由于当时的知识储备有限，做出来的东西问题不少，堪称不忍直视。但，就像每个人的青春纪念品一样，它始终代表了笔者大学时期诸多奋斗步伐中的一小步，尽管如今它显得不尽完善，但始终代表了过去努力做到最好的一个自我状态。

故事是这样子的，笔者当年在大二上的时候申请了国家大学生创新创业实验计划，那年作为我校数学建模基地的助教之一，日常负责组织参加数模的同学（`40` 人左右）进行论文写作和发表一事，在一年一度的国创项目申请到来之际，也投了自己的项目申请书。印象中数模基地的 `10` 位助教中只有笔者的项目被批下来了，大学仅少数的 `RP` 峰值时刻。

关于[大学生创新创业实验计划](http://baike.baidu.com/link?url=3nutFi7J9MgYOsxhqTcz2EJcuivZA4f-xf_1hzb81603BtMnlky3C8kdgaEZY2oxoEpF4e-bPv1Mdh7KEMj-n_)，是教育部一年一度让 `120` 所高校鼓励在校学生进行创新性实验研究，力求培养学生的主动积极和创新思维。分校级、省级和国家级，该项目申请到的是国家级。

关于项目的灵感来源，当年笔者大二上，正好是 `Google` 发布了以图查图的搜索功能，那会还很少有人知道有以图查图的搜索模式存在，而且印象中 'Google' 的以图查图搜索结果并不是很好，速度和精度远没有现在的体验好。所以，笔者很初生牛犊不怕虎地灵机一动，能不能把课余时间看的 `人工蜂群算法` 用在图像检索应用上，看看是否可以提高速度和精度。结果就这么上了，当年真是艺低人胆大。

下面进入正题。

# 绪论

## 图像检索领域简介

从 `20` 世纪 `70` 年代开始，有关图像检索的研究就已经开始。当时研究的主要是对图像用文本进行注解（关键字），然后利用基于文本的数据库管理系统 `（DBMS）` 来进行图像检索，该技术称为基于文本的图像检索技术`（Text-based Image Retrieval，简称 TBIR）`。

`TBIR` 沿用了传统文本检索技术，回避了对图像可视化元素的分析，从图像名称、图像尺寸、压缩类型、作者、年代等方面标引图像，一般以关键词形式的提问查询图像。图像所在页面的主题、图像的文件名称、与图像密切环绕的文字内容、图像的链接地址等都被用作图像分析的依据，根据这些文本分析结果推断其中图像的特征。在图像数字化之前，档案管理者、图书管理员都是采用这种方式组织和管理图像。

到 `90` 年代以后，多媒体信息迅速膨胀，全世界的数字图像的容量以惊人的速度增长，这些图像分布在世界各地，它们都是无序、无索引的。由于人工标注具有太大的主观性和不确定性，基于文本的图像检索在图像的数据量非常大的时候存在很大困难：

 - 手工对图像进行注释所需的工作量太大。
 
 - 许多图像很难用文字的方式进行描述。
 
 - 不同的人对同一幅图像的理解不一样，即使是同一个人，在不同环境下对同一幅图像理解也不完全相同，这样使得对图像的描述不唯一，造成检索结果的千差万别。
 
 - 由于世界上存在许多语种，采用不同的语言文字对图像进行描述而建立的索引在应用中造成了一定的障碍。


基于文本的图像检索存在很大的局限性，图像中包含的大量有用信息无法被有效的访问和利用，在这样的环境下寻找资料是非常主观的，因此人们提出了一种新的对图像内容语义的检索技术，基于内容的图像检索`（Content-based Image Retrieval，简称 CBIR）`。它利用图像自身的特征，如颜色、纹理、形状等特征来进行检索，充分利用了图像本身的信息，具有较强的客观性。

