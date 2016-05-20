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

## `CBIR` 国内外研究现状

### 国外研究成果

基于内容的图像检索技术是当前研究的热点，许多著名杂志如 `IEEE Trans. on PAMI`、`IEEE Trans. on image processing` 等纷纷设专刊介绍该领域研究的最新成果，著名的国际会议如：`IEEE conference of CVPR`、`ACM conference on multimedia` 等纷纷设立专题交流最新的研究成果。各大研究机构和公司都推出了他们的系统：

 - `IBM` 的 `QBIC` 系统
 
`IBM` 的 `QBIC` 是第一个商业化的基于内容的图像检索系统，它的系统结构包括图像入库、特征计算、查询阶段三部分，允许使用例子图像、用户构建的草图和图画、选择的颜色和纹理模式、镜头和目标运动和其他图形信息等，对大型图像和视频数据库进行查询。

它的系统框架和结构对后来图像检索系统具有深远的影响。

- 新加坡大学和 `MIT` 媒体实验室的 `Photobook` 系统

该系统是用于交互式浏览和搜索图像库的工具。图像在装入时按形状、纹理和人脸的面部外形三种特征自动分类，同时还能结合文本关键字进行查询，图像根据类别通过显著语义特征压缩编码。

- `Virage` 公司的 `Virage` 系统

该系统是基于内容的图像搜索引擎，比 `QBIC` 更进一步，支持基于颜色、颜色布局、纹理和结构（对象边界信息）及这四个原子查询的任意组合。其主要有 `3` 方面的功能：图像分析、图像比较和图像管理，技术的核心是 `VirageEngine` 以及在图像对象层上的操作。

- 美国哥伦比亚大学的 `VisualSEEK` 系统

`VisualSEEK` 图像查询系统是一个可视化的图像特征搜索引擎，实现了互联网上的“基于内容”的图像/视频检索系统，它由四部分组成：图形用户界面、服务器应用、图像检索服务器、图像归档。在 `VisualSEEK` 中，整幅图的颜色分布使用全局颜色直方图，区域颜色的索引采用二进制颜色集的表达方法。它采用基于小波变换的方法来表示图像的纹理特征。

### 国内研究成果

相对国外而言，国内在这方面的研究起步相对较晚：

- 浙江大学从 `95` 年开始进行多媒体图像检索的研究，完成了基于颜色和基于形状的图像原型系统，总体设计思想是允许用户找到包含特定颜色、纹理和形状的图像。

- 中科院计算技术研究所开发了一个图像检索原型系统 `“ImageSeek"`，作为“中国数字图书馆示范工程”课题的一个关键技术。该系统实现了基于文本、颜色、纹理特征的图像检索。

- 杭州贝尔研发的具有自主知识产权的智能图像检索系统，通过提取图像的颜色、纹理和形状等特征，实现了基于图像内容的快速智能检索，被列入 `2001` 年信息产业部重点科研计划。

## `CBIR` 的应用前景

目前，对基于内容的图像检索技术的研究具有重要的理论价值和现实意义。随着科技的发展，`CBIR` 技术为大规模图像数据的管理和访问提供了有力的支持，在商业、医疗、公安、军事等领域，有着广泛的应用前景：

- 电子商务

随着互联网的迅速普及，电子商务发展迅猛，2007年中国电子商务交易总额达 `2.17` 万亿元，比上年度增长 `90%`。在互联网上，商家大多以图像的形式向用户展示商品，因此 `CBIR` 技术可以为消费者提供方便快捷的交易平台 `[1]`。

- 知识产权

知识产权保护问题在当今社会备受关注，而图像是知识产权的主要载体之一。比如一个新商标的注册，为了避免造成侵权行为，首先需要通过和已经注册的商标做比对来确定是否与其它商标雷同，对于这类问题，使用 `CIBR` 系统是一种高效的解决方式。

- 医疗诊断

现代医疗器械和技术的发展，产生了大量的医用图像信息，如 `CT、X` 光片等。以往相似病例的诊断图像可以用来做辅助诊断，`CIBR` 技术可以帮助医生在图像库里查找出与当前诊断图像相似的图像。目前，医学图像检索已成为 `CIBR` 应用的一个主要方向 `[2]`。

- 公安系统

通过图像信息查找和确认凶犯是目前公安部门常用的手段。根据指纹、鞋印和人脸的图像进行特征鉴别的检索系统，己经被世界各地的公安部门广泛采用 `[3]`。

- 军事领域

在军事领域，`CIBR` 技术也有着巨大的应用需求，例如，从雷达图像和卫星照片里识别敌方目标、巡航导弹的制导系统以及战场的实时分析等 `[4]`。

## 综述总结

图像检索经历了两个发展阶段，第一个阶段为七十年代后期出现的基于文本的图像检索阶段 `[5]`，但由于随着多媒体技术和计算机网络的飞速发展，数字图像正以惊人的速度增长，基于文本的图像检索暴露出一系列不足 `[6]`。在九十年代早期开始了基于内容的图像检索阶段 `[7][8]`。

如今，基于内容的图像检索已成为热门的研究领域。而基于颜色的图像检索作为 `CBIR` 中所采取的主要手段之一，随着数字化图像颜色特征分析技术的成熟，也得到很大的发展 `[9]`。颜色直方图作为基础而重要的颜色特征，继承了颜色对几何变换的坑性，而且其提取和相似度计算相对简单，但是基于颜色直方图丢失了颜色的空间信息，并且存在特征维数过高等问题，针对这些问题，`Qiu G.P.` 等人提出了滤波器将图像中的不同频率分层，来量化图像亮度的方法 `[10]`。宋擒豹等人提出颜色位置直方图的方法，以解决直方图不具备空间信息的问题 `[11]`。而 `Stricker M.` 提出了一种简单有效的颜色特征描述方法，即颜色矩，有效地降低了颜色特征值的维度 `[12]`。`John` 提出采用图像颜色的信息熵来描述图像的颜色特征，这种方法有效地将颜色直方图从多维降到一维 `[13]`。王向阳则提出将图像位平面应用到图像检索中，以图像较高位平面的特征作为图像的索引 `[14]`。综上所述，基于颜色的图像检索涉及多个研究领域，有着广泛的应用前景，并且仍有许多关键技术尚未解决或不够完善，因此，研究该项技术既有深远的意义，同时也将面临巨大的挑战 `[15]`。

单一的特征值往往会强化图像的某部分信息而忽略其它部分，这样就不利于最终检索效果的提高。为了弥补单一特征值的缺陷，我们将颜色直方图，颜色矩和颜色信息熵三种主流的特征值分别进行归一化，然后分别设置不同的权重，根据权重进行线性合并而得到最终的综合特征向量。通过 `Microsoft Visual Studio 2010` 实现传统检索算法和人工蜂群算法的图像检索系统，通过人工蜂群算法在图像检索上的全局搜索策略和局部搜索策略，有效地提高了检索速度和精度。从而证明该算法对基于内容的图像检索领域有一定的意义。

