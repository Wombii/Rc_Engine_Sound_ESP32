const unsigned int sampleRate = 22050;
const unsigned int sampleCount = 4251;
const signed char samples[] = {
0, -1, 6, 19, 23, 15, 18, 25, 34, 46, 68, 101, 123, 110, 86, 63,
55, 60, 58, 58, 69, 72, 52, 20, 8, 1, -5, -11, -24, -67, -72, -66, 
-59, -46, -26, -23, -17, -6, -6, -16, -26, -23, -11, 10, 26, 31, 28, 28, 
21, 14, 10, 4, 14, 26, 37, 40, 35, 42, 51, 51, 53, 48, 31, 25, 
32, 31, 13, -12, -32, -21, 6, 27, 21, -7, -43, -55, -60, -54, -45, -35, 
-9, -10, -32, -47, -43, -24, -3, 13, 14, 1, -11, -16, -18, -11, 7, 24, 
28, 13, -6, -29, -46, -51, -27, -10, -13, -22, -26, -19, 0, 4, 2, 6, 
17, 23, 25, 27, 30, 40, 53, 51, 46, 40, 35, 29, 22, 13, 8, 2, 
-1, -5, -7, -20, -39, -50, -53, -55, -68, -67, -56, -40, -18, 0, 0, -15, 
-26, -15, 10, 36, 52, 56, 45, 35, 29, 35, 48, 59, 67, 62, 48, 38, 
32, 35, 37, 31, 15, -2, -10, -12, -10, -6, 6, 22, 34, 36, 32, 31, 
30, 26, 24, 25, 24, 31, 29, 18, -1, -21, -27, -27, -28, -35, -41, -41, 
-43, -44, -46, -57, -63, -65, -54, -43, -45, -49, -52, -48, -29, -17, -15, -16, 
-9, 1, -5, -20, -22, -10, 10, 43, 47, 38, 31, 32, 38, 37, 28, 18, 
10, 3, 2, -7, -22, -34, -38, -22, -2, -15, -27, -32, -36, -41, -56, -68, 
-71, -64, -53, -47, -39, -30, -18, -6, -1, -2, -5, -16, -26, -31, -26, -9, 
2, 5, 2, 3, 4, 11, 20, 28, 31, 24, 14, 17, 24, 27, 22, 15, 
13, 22, 23, 16, 8, 7, 23, 22, 25, 26, 20, 26, 33, 33, 24, 11, 
4, 1, -3, -6, -7, -12, -24, -28, -26, -19, -9, 6, 21, 15, 5, 6, 
16, 24, 21, 9, -11, -20, -2, 32, 41, 37, 27, 22, 21, 20, 19, 17, 
12, 8, 11, 15, 10, 0, -6, -9, -12, -12, -26, -34, -22, -7, 4, 1, 
1, 6, 6, 2, -1, -3, -9, -10, 0, 14, 19, 20, 22, 31, 50, 64, 
55, 41, 25, 10, 4, 4, 3, 1, -8, -12, -4, 9, 11, 2, -1, -4, 
-7, -10, -16, -27, -37, -34, -28, -25, -19, -13, -8, -11, -13, -13, -6, 3, 
-1, -9, -2, 10, 21, 26, 28, 28, 35, 35, 26, 21, 24, 36, 43, 36, 
22, 4, -24, -39, -45, -45, -49, -53, -66, -81, -84, -78, -73, -63, -49, -30, 
-17, -19, -30, -38, -28, -11, 4, 13, 18, 20, 15, 5, -7, -20, -21, -3, 
21, 39, 49, 44, 38, 40, 43, 50, 52, 47, 26, 7, -5, -23, -39, -46, 
-36, -18, -9, -11, -21, -28, -31, -38, -42, -48, -55, -55, -53, -49, -46, -40, 
-22, -14, -13, -11, 1, 15, 20, 20, 22, 25, 23, 21, 23, 24, 20, 14, 
12, -1, -6, 5, 24, 37, 38, 20, 8, -3, -12, -24, -24, -11, 7, 26, 
33, 35, 25, 10, -3, -12, -15, -16, -28, -40, -46, -45, -39, -31, -26, -18, 
-7, 5, 11, 3, 4, 11, 18, 25, 25, 13, 1, 1, 5, 6, 13, 13, 
17, 27, 34, 36, 13, -9, -20, -28, -34, -29, -19, -17, -16, -16, -13, -9, 
-1, 14, 29, 39, 55, 74, 84, 92, 91, 86, 74, 59, 60, 69, 73, 69, 
55, 50, 44, 36, 34, 34, 30, 16, -4, -14, -17, -15, -11, -12, -18, -24, 
-27, -41, -50, -48, -34, -14, 2, 13, 19, 25, 23, 17, 10, 12, 19, 30, 
41, 48, 43, 33, 26, 22, 17, 14, 11, 13, 12, 6, -2, -6, -14, -25, 
-33, -40, -42, -52, -69, -78, -77, -75, -74, -81, -83, -82, -72, -56, -30, -14, 
-2, 3, -4, -13, -22, -18, -5, -2, -7, -10, -11, -14, -14, -8, 0, -2, 
-10, -20, -26, -23, -17, -12, -21, -31, -40, -46, -42, -35, -35, -35, -29, -19, 
-17, -26, -40, -50, -50, -44, -32, -24, -16, -13, -14, -15, -9, -7, -11, -16, 
-17, -11, -3, 4, 9, 14, 17, 22, 22, 20, 22, 28, 34, 34, 33, 32, 
31, 36, 31, 29, 27, 20, 18, 20, 22, 20, 18, 16, 14, 12, 4, -3, 
-7, -13, -19, -6, 8, 18, 25, 26, 19, 14, 13, 11, 12, 16, 15, 5, 
2, 1, -2, -2, 4, 9, 8, -2, -16, -21, -19, -15, -17, -23, -26, -18, 
-10, -5, -5, -10, -13, -14, -18, -20, -19, -17, -10, 12, 24, 33, 39, 42, 
48, 52, 57, 58, 58, 62, 65, 73, 81, 83, 83, 79, 64, 54, 43, 30, 
19, 5, -2, -12, -28, -38, -40, -41, -40, -41, -36, -24, -17, -5, 4, 18, 
28, 32, 37, 33, 35, 39, 39, 37, 24, 20, 17, 13, 2, -14, -31, -42, 
-47, -49, -50, -51, -58, -64, -66, -63, -63, -70, -65, -52, -38, -27, -17, -4, 
8, 22, 30, 32, 26, 21, 14, 13, 13, 11, 21, 25, 24, 25, 29, 30, 
19, 2, -19, -38, -53, -62, -64, -69, -79, -84, -77, -60, -51, -47, -46, -43, 
-41, -53, -53, -44, -32, -26, -32, -36, -40, -39, -33, -18, 20, 40, 52, 56, 
57, 58, 72, 76, 75, 70, 61, 46, 36, 28, 22, 20, 13, 10, 7, -1, 
-9, -14, -10, -11, -12, -13, -13, -12, -5, 0, 3, 9, 18, 21, 24, 32, 
34, 26, 11, -12, -19, -13, -5, -8, -9, -3, 3, 9, 11, 7, 5, 4, 
-5, -10, -5, 5, 11, 13, 17, 23, 27, 25, 28, 37, 41, 40, 33, 24, 
17, 10, -1, -14, -23, -28, -34, -37, -37, -34, -27, -27, -33, -29, -18, -8, 
2, 11, 8, 4, 3, 1, 7, 11, 9, 9, 12, 9, -5, -12, -22, -31, 
-36, -38, -33, -31, -33, -39, -48, -60, -69, -77, -82, -85, -83, -61, -40, -23, 
-15, -8, 0, 16, 35, 51, 58, 56, 47, 44, 42, 42, 39, 35, 39, 44, 
53, 58, 58, 60, 51, 45, 48, 53, 54, 47, 39, 26, 12, 5, 2, -9, 
-14, -17, -12, -3, 3, 11, 9, 0, -7, -17, -35, -43, -51, -59, -57, -45, 
-28, -17, -3, 13, 29, 43, 43, 39, 37, 35, 37, 36, 27, 9, -14, -30, 
-37, -33, -30, -32, -32, -31, -23, -18, -21, -27, -29, -28, -31, -31, -25, -18, 
-15, -10, 7, 20, 26, 23, 16, 11, 11, 9, 0, -10, -16, -28, -29, -32, 
-40, -51, -56, -46, -34, -28, -34, -43, -42, -32, -22, -21, -34, -45, -38, -24, 
-12, -9, -6, -2, 5, 14, 25, 29, 23, 22, 27, 28, 26, 18, 12, 9, 
16, 27, 28, 19, 4, -14, -14, -8, 2, 17, 32, 41, 49, 56, 64, 66, 
58, 64, 68, 63, 62, 60, 42, 28, 16, 11, 10, 10, 11, 11, 12, 16, 
22, 36, 49, 65, 73, 69, 55, 33, 27, 27, 28, 27, 25, 29, 32, 32, 
29, 25, 18, 14, 5, -5, -3, 5, 12, 6, -6, -16, -23, -21, -24, -32, 
-39, -45, -53, -67, -66, -60, -50, -38, -32, -35, -43, -49, -52, -55, -45, -27, 
-9, 2, 10, 18, 22, 20, 15, 5, -4, -13, -23, -24, -19, -16, -17, -28, 
-36, -42, -41, -40, -43, -52, -53, -44, -35, -33, -30, -24, -14, -3, 3, 3, 
0, -4, -8, -4, 3, 9, 16, 10, -2, -15, -22, -16, -6, 7, 13, 7, 
3, 2, 0, -1, 0, -1, -1, 3, 5, 6, 9, 12, 1, -6, -11, -18, 
-27, -37, -50, -51, -43, -28, -11, 2, 10, 5, -4, -15, -21, -18, -15, -13, 
-9, -1, 6, 23, 34, 34, 36, 36, 36, 42, 40, 37, 31, 17, -13, -30, 
-38, -44, -54, -66, -75, -79, -81, -84, -88, -89, -73, -51, -27, -10, -8, -8, 
-2, 8, 21, 40, 58, 82, 87, 87, 85, 79, 71, 65, 63, 62, 64, 66, 
71, 73, 72, 71, 63, 50, 39, 31, 23, 13, 2, -4, -3, 5, 19, 24, 
11, -16, -27, -33, -34, -35, -37, -48, -50, -48, -45, -43, -42, -37, -22, -2, 
10, 13, 10, 15, 26, 39, 51, 60, 63, 55, 44, 39, 39, 54, 73, 87, 
89, 85, 82, 74, 70, 69, 72, 72, 61, 27, -2, -25, -37, -43, -51, -57, 
-61, -60, -53, -49, -41, -30, -18, -10, -11, -21, -36, -44, -49, -52, -49, -28, 
-12, 1, 6, 7, 12, 24, 23, 24, 30, 37, 47, 55, 57, 62, 63, 61, 
49, 36, 27, 20, 12, 3, -16, -28, -35, -38, -37, -33, -32, -38, -41, -40, 
-34, -20, -18, -23, -29, -31, -30, -33, -41, -49, -52, -43, -32, -19, -17, -21, 
-25, -29, -27, -21, -28, -40, -49, -62, -75, -69, -56, -42, -30, -22, -24, -32, 
-44, -52, -51, -38, -27, -19, -11, -2, 1, -5, -12, -21, -29, -35, -48, -62, 
-69, -65, -58, -53, -45, -42, -36, -31, -31, -30, -24, -23, -16, -9, -4, -5, 
-12, -18, -22, -14, 1, 12, 19, 24, 26, 25, 22, 21, 25, 24, 22, 22, 
30, 38, 37, 36, 42, 47, 44, 41, 38, 39, 41, 40, 42, 42, 39, 37, 
31, 30, 31, 28, 26, 26, 32, 54, 73, 90, 98, 96, 84, 61, 53, 51, 
55, 64, 73, 77, 78, 78, 73, 67, 61, 54, 48, 46, 46, 44, 40, 33, 
28, 25, 19, 2, -10, -17, -21, -22, -16, -9, -11, -20, -35, -54, -68, -65, 
-51, -43, -35, -23, -9, 5, 22, 36, 40, 40, 38, 31, 21, 12, 6, -1, 
2, 11, 19, 22, 11, -7, -21, -27, -26, -26, -23, -28, -36, -45, -54, -57, 
-55, -48, -37, -27, -23, -27, -36, -46, -58, -65, -66, -64, -54, -50, -47, -43, 
-31, -8, 0, 0, -7, -15, -15, -6, -6, -7, -12, -17, -9, 10, 9, 3, 
-5, -10, -9, -7, -4, 8, 20, 22, 15, 5, -6, -9, -11, -8, 2, 3, 
-6, -19, -33, -52, -56, -51, -39, -28, -21, -14, -12, -7, -4, -2, -3, -5, 
-2, 3, 11, 14, 12, 15, 20, 28, 35, 41, 51, 59, 63, 64, 64, 66, 
70, 65, 57, 47, 36, 27, 23, 12, 0, -7, -17, -17, -5, 2, 3, -2, 
-9, -25, -39, -44, -41, -38, -40, -38, -31, -23, -19, -23, -22, -18, -23, -33, 
-33, -22, -8, 0, 4, 4, 5, 9, 15, 26, 40, 53, 60, 57, 52, 50, 
48, 45, 43, 39, 28, 15, 4, -2, 11, 21, 19, 11, 2, -3, 0, 2, 
-8, -22, -25, -26, -23, -14, -7, -4, -3, -9, -9, -9, -13, -11, -7, -14, 
-23, -31, -39, -43, -31, -20, -15, -9, -5, -6, -8, -10, -5, 6, 15, 20, 
22, 24, 23, 18, 15, 17, 21, 20, 16, 10, 3, -4, -14, -25, -36, -42, 
-40, -36, -25, -22, -30, -41, -49, -43, -31, -21, -16, -16, -16, -20, -19, -9, 
6, 22, 34, 36, 38, 41, 43, 48, 47, 43, 38, 26, 9, -17, -27, -35, 
-41, -47, -55, -54, -45, -37, -26, -14, -3, 7, 20, 31, 37, 36, 32, 31, 
29, 32, 35, 33, 30, 26, 20, 19, 21, 22, 14, 1, -7, -7, -5, 3, 
4, 1, -7, -17, -25, -25, -18, -7, 2, 1, -13, -20, -15, 3, 20, 28, 
26, 19, 11, 8, 10, 15, 22, 21, 17, 16, 10, 7, 15, 22, 26, 25, 
18, -5, -24, -38, -46, -46, -44, -46, -49, -46, -36, -31, -15, 2, 11, 15, 
12, 7, -1, -7, -4, 5, 8, 8, 8, 9, 14, 19, 25, 34, 41, 45, 
44, 35, 24, 16, 10, 2, -7, -17, -31, -36, -35, -31, -29, -23, -9, -4, 
-6, -12, -8, 7, 38, 49, 48, 35, 17, 3, 3, 10, 25, 36, 27, 0, 
-17, -26, -19, -9, -1, 6, 4, -7, -16, -17, 2, 21, 38, 46, 48, 44, 
32, 30, 33, 32, 28, 25, 16, 9, 10, 5, -10, -15, -12, -10, -9, -13, 
-17, -17, -14, -7, -6, -12, -16, -10, -10, -19, -36, -56, -69, -62, -47, -31, 
-18, -16, -9, -1, 4, 5, 1, -11, -32, -33, -33, -32, -29, -23, -23, -24, 
-26, -28, -33, -33, -32, -38, -40, -39, -41, -41, -36, -24, -16, -12, -5, -1, 
5, 7, 0, -13, -20, -23, -33, -45, -51, -46, -28, -14, -1, 10, 16, 23, 
25, 20, 17, 19, 21, 28, 34, 34, 35, 36, 31, 26, 18, 4, -8, -16, 
-26, -24, -21, -24, -29, -34, -37, -37, -34, -29, -17, 2, 12, 25, 26, 19, 
23, 32, 37, 39, 41, 46, 50, 54, 53, 45, 41, 47, 51, 48, 33, 11, 
-4, -8, -3, -5, -5, 1, 5, 1, -4, -3, 2, 13, 25, 16, 6, 4, 
5, 12, 27, 38, 40, 45, 51, 61, 73, 89, 90, 79, 65, 56, 43, 40, 
38, 36, 40, 39, 18, 11, 13, 17, 14, 6, -7, -26, -43, -46, -34, -28, 
-33, -33, -33, -31, -27, -32, -34, -37, -43, -45, -48, -49, -52, -52, -53, -53, 
-41, -38, -35, -27, -15, 0, 7, 1, -9, -22, -28, -30, -23, -8, 4, 7, 
3, -12, -17, -14, -9, -3, -3, -17, -17, -17, -24, -33, -40, -48, -42, -35, 
-37, -46, -61, -58, -50, -49, -50, -43, -25, -23, -28, -30, -24, -7, 7, 26, 
43, 45, 37, 28, 29, 30, 29, 29, 27, 32, 40, 49, 57, 61, 68, 74, 
69, 55, 38, 23, 15, 15, 18, 21, 22, 20, 13, 3, -8, -7, -2, -3, 
-6, -9, -7, 1, 3, 6, 19, 29, 35, 35, 24, 13, 1, 1, 10, 13, 
2, -3, -2, 0, 1, 2, 1, 1, 3, 1, -9, -24, -42, -45, -46, -52, 
-61, -78, -85, -76, -60, -45, -32, -30, -29, -22, -18, -13, -9, -4, 5, 6, 
0, -7, -6, -1, -1, -2, -3, 0, 4, 4, 2, 1, 7, 17, 21, 14, 
-1, -17, -25, -20, -9, 2, -2, -13, -19, -23, -19, -10, -2, 6, 15, 36, 
40, 36, 36, 40, 44, 46, 44, 38, 31, 14, -4, 2, 11, 13, 10, 6, 
13, 24, 31, 42, 52, 60, 59, 51, 42, 38, 33, 29, 35, 36, 34, 31, 
26, 18, 7, 0, 0, 0, -4, -6, -12, -14, -9, -3, 1, -3, -12, -24, 
-33, -33, -28, -28, -28, -27, -26, -28, -32, -34, -27, -17, -10, -4, -4, -4, 
-1, 2, -1, 0, 6, 7, 4, 3, 7, 14, 19, 16, 11, 6, 0, -6, 
-18, -34, -45, -51, -54, -52, -45, -37, -30, -29, -30, -31, -33, -37, -43, -49, 
-44, -36, -35, -40, -42, -36, -26, -15, -6, 0, 5, 9, 12, 8, 6, 7, 
-8, -21, -25, -22, -17, -14, -11, -5, -1, 3, 11, 23, 21, 19, 21, 20, 
16, 10, 6, 8, 15, 18, 13, 5, -6, -10, -10, -12, -11, -8, -7, -5, 
1, 5, 7, 14, 19, 21, 21, 12, 8, 7, 6, 6, 10, 16, 23, 32, 
44, 55, 54, 45, 42, 42, 38, 30, 20, 16, 13, 1, -12, -21, -20, -9, 
3, 12, 13, 14, 15, 13, 15, 20, 28, 31, 25, 19, 7, -2, -1, 6, 
13, 18, 17, 12, 6, 3, -4, -14, -25, -27, -10, -2, 4, 9, 14, 16, 
8, -1, -3, 9, 27, 45, 45, 37, 36, 41, 37, 12, 2, 3, 8, 9, 
7, 10, 8, 4, 2, 2, 4, -5, -22, -32, -30, -21, -2, 10, 18, 16, 
13, 12, 13, 7, -5, -16, -21, -20, -16, -14, -17, -19, -17, -6, -9, -22, 
-39, -48, -45, -34, -32, -35, -37, -29, -15, -11, -10, -7, 2, 11, 14, 8, 
5, 8, 10, 8, 9, 19, 23, 18, 18, 10, -6, -25, -38, -40, -41, -42, 
-45, -45, -37, -28, -25, -27, -27, -22, -19, -20, -24, -16, -5, 3, 13, 17, 
12, 1, -11, -25, -36, -37, -40, -41, -40, -40, -36, -27, -30, -37, -46, -54, 
-61, -65, -48, -26, -14, -8, 2, 5, 4, 7, 11, 16, 21, 23, 23, 19, 
20, 27, 38, 44, 45, 40, 31, 16, 15, 16, 11, -3, -18, -35, -38, -37, 
-37, -30, -14, 13, 27, 30, 28, 26, 19, 3, -14, -21, -20, -8, 13, 18, 
20, 22, 21, 16, 3, -7, -17, -25, -29, -26, -24, -21, -12, -3, 1, 6, 
5, 2, 6, 17, 27, 40, 48, 55, 58, 61, 56, 51, 45, 35, 28, 26, 
34, 34, 31, 34, 39, 43, 44, 38, 33, 35, 36, 31, 28, 19, 8, -1, 
-2, 3, 5, 5, 2, -4, -6, -4, 0, 6, 9, 10, 17, 23, 27, 20, 
18, 25, 23, 21, 20, 24, 30, 33, 30, 31, 34, 33, 28, 23, 24, 25, 
18, 3, -15, -39, -51, -57, -56, -54, -54, -55, -57, -58, -52, -44, -32, -19, 
-5, 9, 19, 20, 17, 10, -1, -13, -20, -24, -30, -38, -47, -48, -41, -28, 
-28, -30, -31, -34, -39, -42, -39, -33, -29, -30, -33, -38, -41, -34, -25, -20, 
-14, -14, -11, -6, -1, 4, -1, -5, -9, -10, -8, -13, -17, -19, -18, -16, 
-18, -21, -20, -17, -9, -3, 3, 14, 19, 19, 12, 14, 24, 25, 27, 27, 
24, 21, 12, 8, 3, 0, -3, -4, -3, -11, -19, -26, -37, -38, -34, -23, 
-15, -17, -27, -41, -39, -33, -27, -30, -38, -45, -42, -35, -30, -24, -13, -10, 
-8, -7, -5, 3, 20, 30, 38, 39, 32, 26, 31, 42, 47, 47, 46, 44, 
46, 46, 44, 44, 42, 34, 24, 8, -10, -22, -23, -17, -17, -19, -21, -22, 
-33, -37, -39, -37, -33, -32, -23, -19, -11, -4, 0, 7, 20, 29, 35, 40, 
43, 47, 52, 54, 60, 63, 61, 53, 43, 34, 30, 30, 26, 20, 12, 1, 
-6, -12, -25, -32, -36, -35, -28, -20, -12, -5, 7, 18, 21, 15, 12, 14, 
21, 32, 38, 40, 38, 35, 36, 37, 39, 42, 41, 38, 36, 37, 28, 18, 
9, 3, -3, -9, -15, -18, -17, -14, -15, -17, -21, -21, -16, -18, -24, -35, 
-40, -44, -53, -60, -56, -46, -41, -38, -39, -42, -43, -39, -31, -22, -17, -12, 
5, 15, 23, 32, 40, 34, 19, 14, 11, 12, 15, 15, 15, 17, 16, 14, 
12, 14, 16, 9, 0, -10, -15, -13, -11, -4, -3, -11, -21, -26, -27, -26, 
-22, -17, -4, 3, 3, 0, -4, -11, -12, -10, -13, -16, -12, -6, 4, 7, 
9, 12, 12, 9, 9, 12, 8, -3, -11, -11, -9, -3, 0, 1, 9, 17, 
14, 10, 7, 5, 6, -2, -16, -22, -22, -18, -17, -18, -9, 0, 2, -4, 
-11, -20, -34, -54, -67, -52, -31, -12, 8, 27, 45, 64, 56, 34, 13, -1, 
-8, -16, -27, -31, -29, -23, -10, -4, 1, 2, -4, -13, -11, -4, -6, -16, 
-32, -42, -43, -45, -44, -36, -18, 14, 28, 31, 25, 19, 12, -5, -7, 2, 
15, 23, 29, 41, 50, 58, 65, 67, 62, 49, 29, 9, -4, -4, -4, -7, 
1, 13, 11, 11, 9, 4, -2, -12, -27, -33, -21, -7, 6, 19, 32, 49, 
55, 56, 54, 50, 22, -7, -26, -37, -43, -38, -21, -3, 7, 7, -1, -13, 
-11, -7, -3, 0, -5, -10, -13, -13, -8, 2, 14, 26, 35, 37, 37, 38, 
36, 31, 28, 29, 28, 13, -13, -25, -37, -43, -44, -46, -39, -25, -16, -8, 
4, 7, -1, -7, -15, -21, -31, -49, -57, -59, -50, -40, -34, -14, 0, 11, 
11, 9, 11, 13, 5, -8, -19, -28, -34, -43, -48, -45, -38, -25, -11, -10, 
-1, 7, 7, -4, -12, -15, -17, -21, -29, -18, -4, 2, 12, 20, 30, 44, 
36, 22, 9, 2, -8, -20, -26, -21, -7, 0, -10, -9, -13, -24, -33, -38, 
-38, -35, -35, -32, -30, -26, -21, -20, -21, -20, -10, 7, 6, 8, 20, 33, 
40, 53, 53, 47, 40, 30, 18, 19, 21, 29, 44, 59, 79, 85, 80, 70, 
66, 60, 47, 34, 23, 20, 19, 15, 15, 18, 22, 22, 20, 10, -1, -7, 
-7, -9, -14, -17, -20, -22, -23, -20, -8, -7, -6, 2, 11, 6, -10, -3, 
12, 21, 20, 18, 11, 11, 14, 15, 12, 7, 8, 9, 5, 7, 17, 26, 
23, 19, 14, 13, 10, 1, 6, 11, 9, 5, 1, 4, 8, 1, -14, -23, 
-27, -22, -18, -15, -12, -7, -7, -10, -11, -16, -24, -38, -39, -40, -47, -52, 
-57, -50, -41, -43, -45, -47, -39, -25, -10, 0, -2, -7, -10, -10, -7, 3, 
12, 13, -4, -20, -28, -25, -18, -19, -25, -30, -35, -36, -35, -35, -26, -16, 
-12, -15, -13, -11, -15, -18, -16, -11, -8, -13, -18, -21, -24, -27, -23, -12, 
4, 16, 16, 10, 6, 5, 3, -2, -10, -14, -22, -31, -33, -25, -22, -26, 
-30, -34, -29, -25, -22, -11, 5, 27, 40, 41, 38, 35, 27, 21, 20, 22, 
30, 28, 18, 9, 10, 21, 37, 39, 34, 22, 10, 7, 5, 0, -7, -14, 
-22, -31, -32, -35, -35, -28, -20, -3, 7, 15, 24, 34, 48, 57, 66, 70, 
73, 76, 83, 86, 85, 83, 75, 67, 70, 62, 51, 42, 38, 28, 13, 4, 
3, 6, -1, -30, -40, -39, -33, -26, -24, -25, -20, -13, -11, -8, 2, 12, 
19, 20, 15, 9, -7, -20, -30, -30, -23, -16, -11, 0, 10, 19, 23, 24, 
23, 15, 5, -1, -5, -16, -23, -27, -28, -21, 1, 16, 28, 30, 24, 13, 
-2, -5, -3, 2, 4, 2, 3, 10, 16, 19, 19, 13, 6, -1, -6, -7, 
-6, -13, -17, -24, -30, -31, -28, -23, -17, -9, 0, 7, 4, -3, -15, -28, 
-40, -51, -60, -60, -52, -37, -19, -3, 9, 14, 23, 30, 28, 8, -1, 1, 
3, -1, -6, -8, -7, -13, -36, -63, -77, -67, -53, -45, -39, -30, -11, -3, 
1, 2, 5, 7, 0, 2, 7, 6, 6, 7, 12, 16, 9, -7, -16, -5, 
12, 26, 30, 28, 31, 37, 26, 6, -14, -20, -15, -15, -17, -11, 0, 0, 
-21, -34, -47, -50, -43, -31, -8, 4, 12, 13, 10, 15, 19, 22, 27, 32, 
39, 41, 38, 37, 32, 27, 25, 32, 38, 39, 30, 18, 12, 11, 11, 2, 
-11, -16, -21, -22, -19, -20, -27, -32, -31, -36, -40, -39, -36, -31, -27, -23, 
-25, -31, -38, -36, -25, -19, -17, -20, -22, -5, 8, 19, 29, 30, 9, -5, 
-8, -3, -2, -1, 8, 13, 18, 17, 9, 4, 23, 44, 52, 49, 41, 32, 
28, 30, 34, 37, 39, 37, 34, 30, 28, 28, 25, 5, -12, -21, -19, -9, 
1, 3, 2, -4, -11, -16, -18, -12, 5, 23, 31, 28, 14, 9, 8, 10, 
18, 26, 33, 40, 43, 38, 27, 10, 8, 11, 14, 14, 16, 34, 44, 52, 
58, 58, 48, 35, 15, -15, -46, -65, -68, -55, -44, -37, -38, -47, -51, -43, 
-38, -36, -32, -18, -9, -6, -13, -25, -37, -52, -58, -60, -55, -46, -39, -42, 
-43, -37, -29, -21, -21, -26, -27, -23, -19, -28, -39, -39, -36, -31, -35, -48, 
-48, -44, -39, -33, -25, -8, 3, 15, 24, 31, 37, 37, 34, 27, 26, 31, 
36, 41, 48, 55, 52, 38, 13, -4, -16, -18, -13, -10, -15, -21, -24, -22, 
-17, 6, 30, 44, 46, 48, 50, 49, 50, 51, 46, 38, 30, 14, 0, -5, 
9, 28, 42, 43, 40, 40, 40, 34, 24, 17, 8, 2, 3, 8, 18, 23, 
21, 15, 16, 26, 27, 22, 13, 6, 3, 8, 2, -14, -25, -28, -23, -8, 
-2, 1, 4, 3, -4, -9, -9, -5, -3, -1, 6, 5, 6, 8, 3, -3, 
-14, -27, -40, -50, -47, -32, -25, -22, -23, -26, -29, -27, -23, -20, -17, -13, 
-13, -15, -13, -11, -18, -32, -38, -33, -31, -31, -26, -16, 4, 13, 11, 2, 
-9, -15, -6, 1, 6, 7, 3, 13, 25, 29, 24, 14, 3, -3, -1, 3, 
9, 8, -11, -27, -39, -44, -42, -32, -20, -18, -16, -15, -20, -25, -29, -29, 
-30, -34, -44, -57, -57, -55, -51, -40, -26, -6, 0, 8, 20, 34, 42, 46, 
47, 47, 45, 39, 30, 27, 22, 17, 13, 8, -1, -12, -22, -33, -41, -37, 
-30, -19, -6, 1, 7, 13, 11, 7, 6, 8, 12, 23, 26, 28, 32, 36, 
41, 45, 47, 48, 54, 67, 81, 84, 90, 96, 105, 110, 106, 102, 92, 76, 
57, 40, 15, -2, -16, -28, -43, -65, -77, -88, -96, -102, -109, -115, -119, -124, 
-127, -126, -116, -89, -71, -58, -54, -57, -58, -48, -35, -18, -4, 5, 26, 44, 
58, 63, 64, 69, 77, 84, 93, 95, 89, 80, 75, 68, 57, 42, 31, 22, 
12, 4, 2, 2, -6, -14, -17, -15, -11, -9, -13, -12, -9, -13, -18, -17, 
-11, -4, -1, 1, 6, 6, 7, -2, -16, -19, -9, 6, 8, 9, 12, 16, 
21, 36, 47, 53, 54, 59, 61, 53, 46, 37, 23, 14, 14, 7, -3, -10, 
-15, -21, -27, -28, -28, -28, -32, -34, -30, -25, -21, -16, 2, 34, 42, 45, 
45, 42, 44, 44, 38, 25, 7, -7, -22, -30, -33, -38, -43, -46, -44, -39, 
-37, -43, -48, -53, -55, -54, -57, -65, -72, -69, -65, -59, -55, -58, -67, -75, 
-71, -62, -48, -29, -12, 14, 28, 35, 33, 24, 15, 12, 11, 7, 2, 0, 
-6, -10, -12, -20, -31, -38, -45, -42, -30, -22, -19, -13, -9, -10, -19, -32, 
-49, -68, -70, -73, -73, -68, -61, -40, -20, -10, 0, };
