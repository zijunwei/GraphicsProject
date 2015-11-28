#ifndef UTILS_H
#define UTILS_H

#define PI         3.14159265358979323846
#define NUMBER_OF_SUPERPIXELS 10


#define STROKE_DISTANCE_THRESHOLD  60       // 3.2 stroke neighborhood graph threshold 
#define LAMBDA_THETA               0.005    //attribute process for stroke orientation: local isotropy
#define THETA_RANDOM_RANGE         0.005    //attribute process for stroke orientation: control the range of random number
#define N_ITERATION_ORIENTATION    100      //number of iterations for stroke process 

#define LAMBDA_SIZE               0.005    //attribute process for stroke size: size contrast
#define SIZE_RANDOM_RANGE         0.005    //attribute process for stroke size: control the range of random number for size randomness 
#define N_ITERATION_SIZE          100      //number of iterations for stroke process size 

#define LAMBDA_COLOR              0.005    //attribute process for stroke size: size contrast
#define COLOR_RANDOM_RANGE         0.005    //attribute process for stroke size: control the range of random number for size randomness 
#define N_ITERATION_COLOR          100      //number of iterations for stroke process size 

#endif /* defined(UTILS_H) */