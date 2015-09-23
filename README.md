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