//-------------------------------------------------------------------------//
//                                                                         //
//  This benchmark is an OpenCL version of the NPB BT code for multiple    //
//  devices. This OpenCL version is developed by the Center for Manycore   //
//  Programming at Seoul National University and derived from the MPI      //
//  Fortran versions in "NPB3.3-MPI" developed by NAS.                     //
//                                                                         //
//  Permission to use, copy, distribute and modify this software for any   //
//  purpose with or without fee is hereby granted. This software is        //
//  provided "as is" without express or implied warranty.                  //
//                                                                         //
//  Information on NPB 3.3, including the technical report, the original   //
//  specifications, source code, results and information on how to submit  //
//  new results, is available at:                                          //
//                                                                         //
//           http://www.nas.nasa.gov/Software/NPB/                         //
//                                                                         //
//  Send comments or suggestions for this OpenCL version to                //
//  cmp@aces.snu.ac.kr                                                     //
//                                                                         //
//          Center for Manycore Programming                                //
//          School of Computer Science and Engineering                     //
//          Seoul National University                                      //
//          Seoul 151-744, Korea                                           //
//                                                                         //
//          E-mail:  cmp@aces.snu.ac.kr                                    //
//                                                                         //
//-------------------------------------------------------------------------//

//-------------------------------------------------------------------------//
// Authors: Sangmin Seo, Jungwon Kim, Jun Lee, Gangwon Jo, Jeongho Nah,    //
//          and Jaejin Lee                                                 //
//-------------------------------------------------------------------------//

#ifndef __BT_H__
#define __BT_H__

#if CLASS == 'S'
#define PROBLEM_SIZE   12
#define NITER_DEFAULT  60
#define DT_DEFAULT     0.010

#elif CLASS == 'W'
#define PROBLEM_SIZE   24
#define NITER_DEFAULT  200
#define DT_DEFAULT     0.0008

#elif CLASS == 'A'
#define PROBLEM_SIZE   64
#define NITER_DEFAULT  200
#define DT_DEFAULT     0.0008

#elif CLASS == 'B'
#define PROBLEM_SIZE   102
#define NITER_DEFAULT  200
#define DT_DEFAULT     0.0003

#elif CLASS == 'C'
#define PROBLEM_SIZE   162
#define NITER_DEFAULT  200
#define DT_DEFAULT     0.0001

#elif CLASS == 'D'
#define PROBLEM_SIZE   408
#define NITER_DEFAULT  250
#define DT_DEFAULT     0.00002

#elif CLASS == 'E'
#define PROBLEM_SIZE   1020
#define NITER_DEFAULT  250
#define DT_DEFAULT     0.4e-5

#else
#error "Unknown class!"
#endif

#define AA            0
#define BB            1
#define CC            2
#define BLOCK_SIZE    5

#define max(x,y)    ((x) > (y) ? (x) : (y))

#define west      0
#define east      1
#define south     2
#define north     3
#define bottom    4
#define top       5
#define NUM_DIR   6

//--------------------------------------------------------------------------
// from set_constants()
//--------------------------------------------------------------------------
#define c1        1.4
#define c2        0.4
#define c3        0.1
#define c4        1.0
#define c5        1.4

#define dnxm1     (1.0 / (double)(PROBLEM_SIZE-1))
#define dnym1     (1.0 / (double)(PROBLEM_SIZE-1))
#define dnzm1     (1.0 / (double)(PROBLEM_SIZE-1))

#define c1c2      (c1 * c2)
#define c1c5      (c1 * c5)
#define c3c4      (c3 * c4)
#define c1345     (c1c5 * c3c4)

#define conz1     (1.0-c1c5)

#define tx1       (1.0 / (dnxm1 * dnxm1))
#define tx2       (1.0 / (2.0 * dnxm1))
#define tx3       (1.0 / dnxm1)

#define ty1       (1.0 / (dnym1 * dnym1))
#define ty2       (1.0 / (2.0 * dnym1))
#define ty3       (1.0 / dnym1)

#define tz1       (1.0 / (dnzm1 * dnzm1))
#define tz2       (1.0 / (2.0 * dnzm1))
#define tz3       (1.0 / dnzm1)

#define dx1       0.75
#define dx2       0.75
#define dx3       0.75
#define dx4       0.75
#define dx5       0.75

#define dy1       0.75
#define dy2       0.75
#define dy3       0.75
#define dy4       0.75
#define dy5       0.75

#define dz1       1.0
#define dz2       1.0
#define dz3       1.0
#define dz4       1.0
#define dz5       1.0

#define dxmax     max(dx3, dx4)
#define dymax     max(dy2, dy4)
#define dzmax     max(dz2, dz3)

#define dssp      (0.25 * max(dx1, max(dy1, dz1) ))

#define c4dssp    (4.0 * dssp)
#define c5dssp    (5.0 * dssp)

#define dt        DT_DEFAULT
#define dttx1     (dt*tx1)
#define dttx2     (dt*tx2)
#define dtty1     (dt*ty1)
#define dtty2     (dt*ty2)
#define dttz1     (dt*tz1)
#define dttz2     (dt*tz2)

#define c2dttx1   (2.0*dttx1)
#define c2dtty1   (2.0*dtty1)
#define c2dttz1   (2.0*dttz1)

#define dtdssp    (dt*dssp)

#define comz1     dtdssp
#define comz4     (4.0*dtdssp)
#define comz5     (5.0*dtdssp)
#define comz6     (6.0*dtdssp)

#define c3c4tx3   (c3c4*tx3)
#define c3c4ty3   (c3c4*ty3)
#define c3c4tz3   (c3c4*tz3)

#define dx1tx1    (dx1*tx1)
#define dx2tx1    (dx2*tx1)
#define dx3tx1    (dx3*tx1)
#define dx4tx1    (dx4*tx1)
#define dx5tx1    (dx5*tx1)

#define dy1ty1    (dy1*ty1)
#define dy2ty1    (dy2*ty1)
#define dy3ty1    (dy3*ty1)
#define dy4ty1    (dy4*ty1)
#define dy5ty1    (dy5*ty1)

#define dz1tz1    (dz1*tz1)
#define dz2tz1    (dz2*tz1)
#define dz3tz1    (dz3*tz1)
#define dz4tz1    (dz4*tz1)
#define dz5tz1    (dz5*tz1)

#define c2iv      2.5
#define con43     (4.0/3.0)
#define con16     (1.0/6.0)

#define xxcon1    (c3c4tx3*con43*tx3)
#define xxcon2    (c3c4tx3*tx3)
#define xxcon3    (c3c4tx3*conz1*tx3)
#define xxcon4    (c3c4tx3*con16*tx3)
#define xxcon5    (c3c4tx3*c1c5*tx3)

#define yycon1    (c3c4ty3*con43*ty3)
#define yycon2    (c3c4ty3*ty3)
#define yycon3    (c3c4ty3*conz1*ty3)
#define yycon4    (c3c4ty3*con16*ty3)
#define yycon5    (c3c4ty3*c1c5*ty3)

#define zzcon1    (c3c4tz3*con43*tz3)
#define zzcon2    (c3c4tz3*tz3)
#define zzcon3    (c3c4tz3*conz1*tz3)
#define zzcon4    (c3c4tz3*con16*tz3)
#define zzcon5    (c3c4tz3*c1c5*tz3)
//--------------------------------------------------------------------------


#ifdef USE_CPU
#pragma OPENCL EXTENSION cl_amd_fp64: enable
#pragma OPENCL EXTENSION cl_amd_printf: enable
#else
#pragma OPENCL EXTENSION cl_khr_fp64: enable
#endif

#include "bt_dim.h"

/* Below constants should be the same as those in sp.c!! */
#ifdef USE_CPU
#define COPY_FACES_OUT1_DIM   COPY_FACES_OUT1_DIM_CPU
#define COPY_FACES_OUT2_DIM   COPY_FACES_OUT2_DIM_CPU
#define COPY_FACES_OUT3_DIM   COPY_FACES_OUT3_DIM_CPU
#define COPY_FACES_IN1_DIM    COPY_FACES_IN1_DIM_CPU
#define COPY_FACES_IN2_DIM    COPY_FACES_IN2_DIM_CPU
#define COPY_FACES_IN3_DIM    COPY_FACES_IN3_DIM_CPU
#define COMPUTE_RHS1_DIM      COMPUTE_RHS1_DIM_CPU
#define COMPUTE_RHS2_DIM      COMPUTE_RHS2_DIM_CPU
#define COMPUTE_RHS6_DIM      COMPUTE_RHS6_DIM_CPU
#define X_SOLVE_DIM           X_SOLVE_DIM_CPU
#define Y_SOLVE_DIM           Y_SOLVE_DIM_CPU
#define Z_SOLVE_DIM           Z_SOLVE_DIM_CPU
#define ADD_DIM               ADD_DIM_CPU

#else //GPU
#define COPY_FACES_OUT1_DIM   COPY_FACES_OUT1_DIM_GPU
#define COPY_FACES_OUT2_DIM   COPY_FACES_OUT2_DIM_GPU
#define COPY_FACES_OUT3_DIM   COPY_FACES_OUT3_DIM_GPU
#define COPY_FACES_IN1_DIM    COPY_FACES_IN1_DIM_GPU
#define COPY_FACES_IN2_DIM    COPY_FACES_IN2_DIM_GPU
#define COPY_FACES_IN3_DIM    COPY_FACES_IN3_DIM_GPU
#define COMPUTE_RHS1_DIM      COMPUTE_RHS1_DIM_GPU
#define COMPUTE_RHS2_DIM      COMPUTE_RHS2_DIM_GPU
#define COMPUTE_RHS6_DIM      COMPUTE_RHS6_DIM_GPU
#define X_SOLVE_DIM           X_SOLVE_DIM_GPU
#define Y_SOLVE_DIM           Y_SOLVE_DIM_GPU
#define Z_SOLVE_DIM           Z_SOLVE_DIM_GPU
#define ADD_DIM               ADD_DIM_GPU

#endif

#endif //__BT_H__

