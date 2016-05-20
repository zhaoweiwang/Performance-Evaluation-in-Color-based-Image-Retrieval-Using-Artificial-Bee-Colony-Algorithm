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