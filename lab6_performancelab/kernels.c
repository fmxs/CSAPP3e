/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/*
 * Please fill in the following team struct
 */
team_t team = {
    "有apple全家桶的人是我", /* Team name */

    "Jiayan Xu",            /* First member full name */
    "jiayan.xu@xiaomi.com", /* First member email address */

    "", /* Second member full name (leave blank if none) */
    ""  /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/
char rotate_xjy_str[] = "20230117 将(i,j)换到(j,i)并交换一半的行";
void rotate_xjy_core(int dim, pixel *a, pixel *b){
    // 遍历矩阵上三角 将元素按照对角线交换
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            if(i >= j)
            {
                continue;
            }
            // 矩阵A的上三角的元素 赋值到 矩阵B的下三角
            b[RIDX(j, i, dim)] = a[RIDX(i, j, dim)];
            // 矩阵A的下三角元素 赋值到 矩阵B的上三角
            b[RIDX(i, j, dim)] = a[RIDX(j, i, dim)];
        }
    }
    // 循环范围(0, dim/2)
    // 遍历矩阵的行，将行按照矩阵水平中线交换
    int range = dim/2;
    for(int i = 0; i < range; i++)
    {
        // 行号为 i 时，目标行号为 dim - i - 1。
        int targetRow = dim - i -1;
        // 交换两行的每个元素
        for(int j = 0; j < dim; j++){
            int temp = b[RIDX(i, j, dim)];
            b[RIDX(i, j, dim)] = b[RIDX(targetRow, j, dim)];
            b[RIDX(targetRow, j, dim)] = temp;
        }
    }
}

// 旋转图像
// 首先，它在外层循环中使用了i += 32的方式来遍历图像，在内层循环中使用了j来遍历图像的每一行。在内层循环中，程序使用了一系列的*dst = *src语句来完成旋转操作。通过这些语句，程序将图像的每个像素的值从源图像中复制到目标图像中，并在每次操作后将源图像指针和目标图像指针分别移动到下一行。
// 在程序中还使用了一些类似于dst += dim;和src += dim;的语句来控制图像指针的移动，这样程序就可以在遍历完一整行之后立即移动到下一行。
// 在这种方式下，程序可以在一次循环中完成大量的旋转操作，而不是在多个循环中重复执行相同的操作，从而提高了程序的性能。
char rotate_32_str[] = "20230117 32路展开";
void rotate_32_core(int dim, pixel *src, pixel *dst)
{
    int i, j = 0;
    dst += (dim - 1 ) * dim;
    for(i = 0; i < dim; i += 32)// 调换了访问顺序
    {
        for(j = 0; j < dim; j++)
        {// 使用了循环展开技术来优化旋转图像的性能
            *dst = *src; dst++; src += dim; *dst = *src; dst++; src += dim;
            *dst = *src; dst++; src += dim; *dst = *src; dst++; src += dim;
            *dst = *src; dst++; src += dim; *dst = *src; dst++; src += dim;
            *dst = *src; dst++; src += dim; *dst = *src; dst++; src += dim;
            *dst = *src; dst++; src += dim; *dst = *src; dst++; src += dim;
            *dst = *src; dst++; src += dim; *dst = *src; dst++; src += dim;
            *dst = *src; dst++; src += dim; *dst = *src; dst++; src += dim;
            *dst = *src; dst++; src += dim; *dst = *src; dst++; src += dim;
            *dst = *src; dst++; src += dim; *dst = *src; dst++; src += dim;
            *dst = *src; dst++; src += dim; *dst = *src; dst++; src += dim;
            *dst = *src; dst++; src += dim; *dst = *src; dst++; src += dim;
            *dst = *src; dst++; src += dim; *dst = *src; dst++; src += dim;
            *dst = *src; dst++; src += dim; *dst = *src; dst++; src += dim;
            *dst = *src; dst++; src += dim; *dst = *src; dst++; src += dim;
            *dst = *src; dst++; src += dim; *dst = *src; dst++; src += dim;
            *dst = *src; dst++; src += dim; *dst = *src; 

            src += 31 * dim;
            src++;
            dst += 31;
            dst += dim;
        }
        src += 31 * dim;
        dst += 32;
        dst += dim * dim;
    }
}


/*
 * naive_rotate - The naive baseline version of rotate
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst)
{
    int i, j;

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            dst[RIDX(dim - 1 - j, i, dim)] = src[RIDX(i, j, dim)];
}

/*
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst)
{
    naive_rotate(dim, src, dst);
    rotate_xjy_core(dim, src, dst);
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_rotate_functions()
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);
    add_rotate_function(&rotate, rotate_descr);
    /* ... Register additional test functions here */
    add_rotate_function(&rotate_xjy_core, rotate_xjy_str);
}

/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct
{
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/*
 * initialize_pixel_sum - Initializes all fields of sum to 0
 */
static void initialize_pixel_sum(pixel_sum *sum)
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 计算该像素点的像素值总和
 * accumulate_sum - Accumulates field values of p in corresponding
 * fields of sum
 */
static void accumulate_sum(pixel_sum *sum, pixel p)
{
    sum->red += (int)p.red;
    sum->green += (int)p.green;
    sum->blue += (int)p.blue;
    sum->num++;
    return;
}

/* 将当前像素换成像素的平均值
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum)
{
    current_pixel->red = (unsigned short)(sum.red / sum.num);
    current_pixel->green = (unsigned short)(sum.green / sum.num);
    current_pixel->blue = (unsigned short)(sum.blue / sum.num);
    return;
}

/*
 * avg - Returns averaged pixel value at (i,j)
 */
static pixel avg(int dim, int i, int j, pixel *src)
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for (ii = max(i - 1, 0); ii <= min(i + 1, dim - 1); ii++)
        for (jj = max(j - 1, 0); jj <= min(j + 1, dim - 1); jj++)
            accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst)
{
    int i, j;

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth - Your current working version of smooth.
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst)
{
    naive_smooth(dim, src, dst);
}

// 优化策略：将点分情况讨论，三种情况：四个角点，边上的点，其他点
char smooth_xjy_str[] = "smooth: split area from others";
void smooth_xjy(int dim, pixel *src, pixel *dst)
{   
    // 声明一个结构体 sum 并初始化结构体 sum 的各个值
    pixel_sum sum;
    initialize_pixel_sum(&sum); 

    // point1:计算点(0, 0)相邻点的像素总和，并将点(0,0)的像素改成平均值。每个point有3个相邻点
    accumulate_sum(&sum, src[RIDX(0, 0, dim)]);
    accumulate_sum(&sum, src[RIDX(0, 1, dim)]);
    accumulate_sum(&sum, src[RIDX(1, 0, dim)]);
    accumulate_sum(&sum, src[RIDX(1, 1, dim)]);
    assign_sum_to_pixel(&dst[RIDX(0, 0, dim)], sum);

    // point2:计算点(dim-1, 0)相邻点的像素总和，并将点(dim-1,0)的像素改成平均值
    accumulate_sum(&sum, src[RIDX(dim-1, 0, dim)]);
    accumulate_sum(&sum, src[RIDX(dim-1, 1, dim)]);
    accumulate_sum(&sum, src[RIDX(dim-2, 0, dim)]);
    accumulate_sum(&sum, src[RIDX(dim-2, 1, dim)]);
    assign_sum_to_pixel(&dst[RIDX(dim-1, 0, dim)], sum);

    // point3:计算点(dim-1, dim-1)相邻点的像素总和，并将点(dim-1, dim-1)的像素改成平均值
    accumulate_sum(&sum, src[RIDX(dim-1, dim-1, dim)]);
    accumulate_sum(&sum, src[RIDX(dim-1, dim-2, dim)]);
    accumulate_sum(&sum, src[RIDX(dim-2, dim-1, dim)]);
    accumulate_sum(&sum, src[RIDX(dim-2, dim-2, dim)]);
    assign_sum_to_pixel(&dst[RIDX(dim-1, dim-1, dim)], sum);

    // point4:计算点(0, dim-1)相邻点的像素总和，并将点(0, dim-1)的像素改成平均值
    accumulate_sum(&sum, src[RIDX(0, dim-1, dim)]);
    accumulate_sum(&sum, src[RIDX(0, dim-2, dim)]);
    accumulate_sum(&sum, src[RIDX(1, dim-1, dim)]);
    accumulate_sum(&sum, src[RIDX(1, dim-2, dim)]);
    assign_sum_to_pixel(&dst[RIDX(0, dim-1, dim)], sum);

    // line1:计算顶部行，点(0,1),(0,2)...(0,dim-2)相邻点的像素总和，并将每个点的像素改成相应平均值。line中的每个点有5个相邻点
    for(int j = 1; j <= dim-2; j++)
    {
        accumulate_sum(&sum, src[RIDX(0, j, dim)]);
        accumulate_sum(&sum, src[RIDX(0, j-1, dim)]);
        accumulate_sum(&sum, src[RIDX(0, j+1, dim)]);
        accumulate_sum(&sum, src[RIDX(1, j, dim)]);
        accumulate_sum(&sum, src[RIDX(1, j-1, dim)]);
        accumulate_sum(&sum, src[RIDX(1, j+1, dim)]);
        assign_sum_to_pixel(&dst[RIDX(0, j, dim)], sum);
    }

    // line2:计算底部行，点(dim-1,1),(dim-1,2),...(dim-1,dim-2)
    for(int j = 1; j <= dim-2; j++)
    {
        accumulate_sum(&sum, src[RIDX(dim-1, j, dim)]);
        accumulate_sum(&sum, src[RIDX(dim-1, j-1, dim)]);
        accumulate_sum(&sum, src[RIDX(dim-1, j+1, dim)]);
        accumulate_sum(&sum, src[RIDX(dim-2, j, dim)]);
        accumulate_sum(&sum, src[RIDX(dim-2, j-1, dim)]);
        accumulate_sum(&sum, src[RIDX(dim-2, j+1, dim)]);
        assign_sum_to_pixel(&dst[RIDX(dim-1, j, dim)], sum);
    }

    // line3:计算左边列，计算点(1,0),(2,0),...,(dim-2,0)
    for(int i = 1; i <= dim-2; i++)
    {
        accumulate_sum(&sum, src[RIDX(i, 0, dim)]);
        accumulate_sum(&sum, src[RIDX(i+1, 0, dim)]);
        accumulate_sum(&sum, src[RIDX(i-1, 0, dim)]);
        accumulate_sum(&sum, src[RIDX(i, 1, dim)]);
        accumulate_sum(&sum, src[RIDX(i+1, 1, dim)]);
        accumulate_sum(&sum, src[RIDX(i-1, 1, dim)]);
        assign_sum_to_pixel(&dst[RIDX(i, 0, dim)], sum);
    }

    // line4:计算右边列，计算点(1,dim-1),(2,dim-1),...,(dim-2,dim-1)
    for(int i = 1; i <= dim-2; i++)
    {
        accumulate_sum(&sum, src[RIDX(i, dim-1, dim)]);
        accumulate_sum(&sum, src[RIDX(i+1, dim-1, dim)]);
        accumulate_sum(&sum, src[RIDX(i-1, dim-1, dim)]);
        accumulate_sum(&sum, src[RIDX(i, dim-2, dim)]);
        accumulate_sum(&sum, src[RIDX(i+1, dim-2, dim)]);
        accumulate_sum(&sum, src[RIDX(i-1, dim-2, dim)]);
        assign_sum_to_pixel(&dst[RIDX(i, dim-1, dim)], sum);
    }

    // inner point:计算剩下的点，每个点有8个相邻点
    for(int i = 1; i <= dim-2; i++)
    {
        for(int j = 1; j <= dim-2; j++)
        {
            initialize_pixel_sum(&sum);
            accumulate_sum(&sum, src[RIDX(i, j, dim)]);
            accumulate_sum(&sum, src[RIDX(i-1, j, dim)]);// 上
            accumulate_sum(&sum, src[RIDX(i+1, j, dim)]);// 下
            accumulate_sum(&sum, src[RIDX(i, j-1, dim)]);// 左
            accumulate_sum(&sum, src[RIDX(i, j+1, dim)]);// 右
            accumulate_sum(&sum, src[RIDX(i-1, j-1, dim)]);// 左上
            accumulate_sum(&sum, src[RIDX(i-1, j+1, dim)]);// 右上
            accumulate_sum(&sum, src[RIDX(i+1, j-1, dim)]);// 左下
            accumulate_sum(&sum, src[RIDX(i+1, j+1, dim)]);// 右下
            assign_sum_to_pixel(&dst[RIDX(i, j, dim)], sum);
        }
    }
}

/*********************************************************************
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_smooth_functions()
{
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
    add_smooth_function(&smooth_xjy, smooth_xjy_str);
}
