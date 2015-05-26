##mjRandom

Stochastic point cloud generator. The first inlet accepts a float from 0..1 to traverse the cloud. The second inlet takes a value for the seed of the random number, the third inlet selects the number of points. It generates a 3-dimensional matrix of unit 1 where (x : 0..1) (y : 0..1) (z : 0..1). Random values are calculated using the C Macro RAND MAX and the function rand().17 The data provided by these objects is not limited to providing coordinates for sound sources. It can be used for other purposes. For example, to easily create tables without writing much code for modulating other parameters