const unsigned int turboSampleRate = 22050;
const unsigned int turboSampleCount = 3435;
const signed char turboSamples[] = {
0, -1, -1, 12, 17, 2, 5, 3, -10, -7, 1, -7, 6, 25, 16, 2, 
3, -10, -16, -5, -5, -17, 1, 24, 15, 10, 0, -8, -16, -30, -25, -3, 
25, 35, 19, 7, -4, -16, -24, -26, -17, 6, 29, 26, 14, 19, -3, -32, 
-41, -46, -31, 25, 38, 38, 41, 33, 4, -34, -56, -63, -14, 33, 35, 57, 
45, 5, -8, -25, -83, -47, -3, 12, 38, 59, 23, 9, -3, -54, -79, -41, 
-1, 24, 57, 57, 33, 13, -33, -77, -61, -29, -14, 39, 68, 53, 21, 11, 
-17, -69, -43, -22, 0, 46, 66, 39, 22, 1, -39, -65, -35, -2, 26, 53, 
60, 34, 0, -34, -71, -59, -20, 21, 42, 59, 53, 15, -24, -66, -67, -37, 
2, 34, 60, 69, 30, -21, -55, -61, -51, -32, 18, 59, 71, 72, 16, -37, 
-60, -66, -70, 0, 58, 63, 67, 79, 34, -68, -89, -94, -59, 4, 40, 83, 
97, 66, -4, -76, -86, -66, -44, 13, 63, 83, 101, 37, -37, -68, -97, -106, 
-12, 52, 80, 92, 101, 20, -64, -100, -111, -85, -7, 61, 69, 97, 100, 29, 
-50, -98, -95, -53, -3, 28, 94, 119, 66, -8, -58, -95, -90, -47, 15, 70, 
97, 100, 47, -9, -69, -109, -96, -24, 24, 64, 90, 100, 71, -38, -86, -99, 
-82, -39, 10, 64, 93, 95, 43, -32, -80, -79, -71, -33, 21, 64, 108, 75, 
7, -48, -79, -92, -58, 3, 51, 76, 99, 54, -14, -59, -97, -96, -40, 17, 
57, 96, 90, 49, -11, -88, -86, -49, -17, 9, 63, 86, 71, 23, -27, -62, 
-71, -44, -9, 20, 57, 75, 44, 19, -33, -79, -72, -32, 1, 36, 54, 65, 
57, 0, -39, -70, -69, -32, -3, 14, 56, 79, 60, 16, -59, -78, -57, -30, 
-11, 20, 62, 63, 43, 2, -46, -59, -44, -34, -10, 18, 39, 73, 51, -12, 
-54, -54, -48, -24, 1, 11, 46, 79, 7, -30, -44, -54, -41, -24, 0, 35, 
65, 60, 20, -16, -47, -61, -40, -20, -12, 44, 69, 52, 15, -27, -64, -64, 
-31, 1, 24, 44, 60, 29, -14, -41, -56, -62, -28, 3, 16, 40, 72, 52, 
-24, -52, -77, -74, -39, -1, 34, 63, 69, 27, -20, -66, -83, -64, -20, 16, 
39, 56, 44, 25, -6, -55, -83, -55, -24, 9, 38, 62, 58, 23, -26, -72, 
-89, -69, -7, 25, 56, 74, 60, 26, -21, -58, -73, -54, -26, 23, 50, 61, 
56, 38, 3, -56, -70, -49, -13, 21, 53, 61, 42, 15, -25, -51, -41, -34, 
-10, 24, 48, 54, 37, 8, -18, -34, -44, -27, 1, 35, 52, 45, 34, -9, 
-29, -29, -28, -17, 3, 27, 34, 35, 18, -8, -20, -22, -13, -5, -3, 6, 
20, 22, 11, -5, -21, -27, -12, -2, 0, -1, 10, 20, 0, -14, -20, -25, 
-17, 0, -2, 2, 13, 11, 0, -14, -11, -3, 2, 0, -12, -2, 4, -3, 
5, 7, -13, -4, 1, 0, 4, -4, -3, 6, 6, 6, 3, -12, -7, -13, 
-15, 4, 15, 18, 10, 4, 3, -6, -12, -3, 16, 26, 9, -3, -9, -7, 
4, 0, -4, -1, 0, 4, 10, 10, -5, -8, 9, -5, -1, 19, 21, 23, 
13, -17, -29, -20, -10, 17, 24, 21, 24, 13, -17, -45, -30, -13, 4, 34, 
32, 12, 8, -16, -48, -39, -31, -25, 24, 52, 47, 38, -5, -47, -70, -56, 
-28, -1, 34, 67, 59, 25, -14, -76, -70, -50, -27, 25, 71, 60, 35, -7, 
-44, -62, -62, -33, 9, 50, 74, 64, 24, 2, -36, -69, -66, 3, 46, 56, 
54, 43, 16, -28, -60, -71, -45, -2, 34, 72, 63, 15, -25, -41, -60, -52, 
-14, 34, 57, 63, 46, -5, -45, -50, -58, -63, 18, 63, 76, 75, 44, -44, 
-74, -70, -63, -31, 32, 71, 78, 73, 19, -45, -71, -77, -61, -1, 52, 63, 
85, 62, -7, -59, -82, -91, -33, 28, 60, 89, 108, 68, -49, -88, -89, -78, 
-50, 38, 84, 103, 96, 53, -17, -95, -108, -91, -29, 48, 85, 102, 86, 22, 
-51, -89, -99, -73, 0, 64, 83, 98, 72, -1, -62, -99, -109, -76, 23, 64, 
89, 101, 75, -15, -67, -96, -97, -63, -5, 87, 109, 89, 52, -10, -80, -99, 
-73, -34, 27, 74, 79, 75, 40, -34, -82, -86, -67, -24, 28, 59, 77, 82, 
27, -40, -69, -78, -73, -19, 32, 76, 97, 82, 23, -67, -87, -73, -34, 0, 
41, 65, 76, 58, 3, -55, -74, -60, -36, 0, 29, 51, 75, 48, -9, -58, 
-73, -50, -31, -2, 38, 68, 74, 22, -37, -70, -65, -42, -16, 13, 38, 59, 
55, 32, -29, -62, -63, -45, -17, 13, 48, 66, 60, 26, -17, -55, -59, -38, 
-16, 12, 43, 72, 58, 11, -44, -72, -59, -30, -14, 20, 52, 73, 72, -5, 
-50, -64, -62, -47, 7, 30, 48, 71, 63, 16, -56, -75, -62, -32, -6, 27, 
79, 75, 39, -19, -66, -62, -44, -20, 8, 39, 60, 51, 13, -38, -67, -70, 
-54, -3, 27, 41, 52, 55, -2, -43, -68, -78, -52, -3, 29, 42, 65, 53, 
-3, -51, -74, -66, -35, -4, 15, 41, 49, 35, 0, -42, -73, -64, -25, 7, 
30, 52, 49, 26, -17, -64, -85, -71, -16, 7, 28, 51, 54, 33, -20, -57, 
-72, -55, -32, -1, 35, 63, 60, 33, -4, -54, -59, -47, -25, 7, 38, 63, 
56, 27, -8, -31, -46, -32, -9, 6, 32, 56, 37, 3, -17, -18, -26, -25, 
3, 6, 24, 46, 35, 3, -12, -25, -24, -11, 0, 11, 34, 43, 23, 3, 
-8, -25, -16, 1, 0, -5, 20, 19, 5, 1, 0, -16, -18, 0, -2, -1, 
18, 28, 9, -8, -23, -28, -15, 1, -5, 4, 20, 15, 2, -11, -22, -26, 
-16, -3, -2, 13, 21, 17, 22, 4, -42, -35, -18, -6, 10, 19, 12, 22, 
8, -22, -28, -22, -20, -3, 9, 8, 17, 25, 9, -10, -22, -31, -34, -8, 
9, 28, 41, 32, 11, -19, -29, -39, -33, -5, 16, 32, 41, 33, 14, -15, 
-30, -28, -30, -19, 6, 36, 42, 36, 8, -16, -19, -36, -51, -30, 6, 28, 
48, 55, 22, -8, -24, -47, -59, -36, 3, 40, 55, 56, 23, -6, -34, -63, 
-78, -64, 3, 40, 68, 78, 51, 2, -36, -85, -97, -57, -10, 51, 94, 88, 
50, 16, -34, -98, -86, -51, -14, 38, 103, 79, 44, 13, -45, -96, -79, -40, 
14, 78, 107, 80, 18, -18, -72, -108, -85, 2, 50, 92, 99, 63, 18, -63, 
-96, -76, -38, -9, 41, 103, 83, 36, -22, -67, -88, -73, -30, 28, 91, 120, 
43, -12, -54, -91, -93, -54, 29, 76, 106, 89, 32, -40, -85, -104, -71, -18, 
18, 80, 107, 74, 11, -42, -93, -93, -33, 4, 36, 86, 99, 44, -26, -82, 
-110, -95, -13, 26, 54, 93, 107, 58, -31, -70, -101, -98, -51, 38, 77, 110, 
102, 41, -26, -100, -112, -76, -2, 55, 77, 99, 87, 13, -58, -86, -90, -48, 
-4, 28, 76, 122, 77, -6, -56, -87, -102, -41, 17, 72, 114, 118, 62, -47, 
-85, -100, -77, -16, 34, 62, 95, 91, 27, -30, -69, -75, -48, -11, 14, 45, 
91, 71, 5, -53, -65, -66, -35, 17, 36, 51, 70, 29, -14, -43, -65, -60, 
-19, 12, 26, 53, 59, 34, -2, -51, -70, -43, -5, 9, 38, 49, 48, 29, 
-21, -58, -59, -29, 9, 14, 18, 44, 46, 15, -31, -58, -50, -17, 7, 24, 
29, 49, 61, -7, -40, -49, -54, -33, 3, 31, 48, 60, 49, 8, -51, -60, 
-47, -26, -13, 13, 60, 71, 47, -8, -47, -52, -44, -22, 4, 32, 64, 52, 
8, -31, -49, -45, -36, -30, 3, 39, 59, 67, 36, -33, -43, -49, -49, -33, 
8, 50, 72, 48, 4, -35, -62, -40, -20, -19, -5, 54, 65, 29, -18, -41, 
-51, -46, -13, -3, 10, 50, 56, 16, -21, -61, -63, -37, -9, 10, 31, 45, 
46, 25, -51, -68, -49, -22, 4, 16, 24, 31, 30, 8, -29, -51, -43, -20, 
9, 24, 27, 33, 27, 4, -32, -54, -51, -21, 11, 28, 23, 29, 12, -24, 
-34, -37, -43, -21, 9, 9, 22, 27, 18, 4, -28, -33, -35, -28, 1, 17, 
14, 24, 21, 0, -11, -24, -34, -23, -15, -22, -3, 36, 25, 17, 4, -17, 
-40, -35, -22, -12, 21, 52, 18, 7, 4, -26, -37, -22, -27, -7, 14, 23, 
38, 28, -1, -17, -25, -39, -47, -17, 19, 41, 39, 24, 0, -22, -20, -20, 
-23, -10, 18, 18, 14, 8, 7, 7, -2, -9, -28, -34, -7, 17, 26, 18, 
7, 10, 2, -40, -33, -5, 4, 6, 13, 16, 22, 22, 10, -10, -18, -9, 
-3, 1, 11, 24, 13, 9, 7, -1, -13, -28, -18, 3, 16, 26, 31, 0, 
-15, -15, -25, -23, -2, 23, 44, 44, 18, -5, -13, -32, -15, 0, -6, 17, 
29, -2, -12, -10, -16, -12, 10, 0, -6, 20, 34, 9, -11, -17, -32, -13, 
15, 5, 18, 34, 20, 0, -11, -46, -50, -10, 23, 32, 47, 23, -23, -43, 
-56, -66, -13, 34, 39, 32, 45, 31, -36, -51, -71, -76, -32, 13, 69, 99, 
76, 29, -34, -103, -74, -58, -45, 28, 99, 95, 54, -14, -75, -90, -86, -57, 
-7, 54, 107, 97, 26, 7, -50, -97, -78, -47, 22, 85, 91, 52, 33, 11, 
-88, -99, -57, -20, 14, 93, 87, 48, 29, -22, -92, -62, -16, 6, 46, 89, 
71, 2, -23, -53, -73, -53, 22, 52, 76, 82, 34, -20, -31, -68, -87, -40, 
17, 74, 88, 48, 1, -12, -40, -83, -49, -1, 41, 68, 78, 47, 0, -39, 
-77, -93, -28, 25, 52, 80, 97, 53, -41, -74, -94, -87, -48, 14, 72, 83, 
81, 33, -43, -87, -89, -72, -4, 54, 67, 93, 70, 13, -43, -97, -112, -45, 
-2, 29, 70, 102, 57, -15, -79, -105, -98, -53, 35, 54, 93, 123, 64, -26, 
-75, -86, -89, -45, 21, 63, 97, 90, 36, -18, -65, -86, -77, -36, 21, 55, 
90, 83, 15, -34, -63, -78, -44, -13, 24, 71, 95, 79, -8, -55, -63, -62, 
-53, -13, 40, 68, 88, 54, -9, -20, -36, -63, -40, -2, 25, 74, 72, 36, 
2, -23, -50, -58, -34, 10, 54, 64, 46, 21, -22, -55, -62, -43, 3, 31, 
53, 60, 51, 30, -34, -64, -53, -26, -8, 31, 55, 64, 48, 4, -39, -53, 
-37, -25, -6, 21, 53, 60, 31, -19, -48, -45, -26, -18, 0, 24, 38, 55, 
32, -14, -34, -44, -51, -28, 2, 31, 52, 60, 42, -28, -55, -47, -31, -24, 
-14, 25, 42, 45, 26, -23, -45, -32, -32, -25, -5, 26, 51, 40, 17, -27, 
-64, -66, -31, -17, -4, 26, 50, 19, -18, -44, -57, -57, -36, -9, -3, 24, 
53, 45, -4, -50, -52, -48, -33, -17, 9, 35, 50, 22, -20, -43, -58, -47, 
-31, -9, 15, 31, 40, 11, -28, -47, -55, -32, -8, 10, 25, 40, 47, 3, 
-32, -47, -48, -39, -19, 11, 18, 34, 43, 26, -24, -47, -49, -39, -14, 16, 
41, 52, 39, 1, -26, -34, -46, -35, -11, 15, 43, 52, 31, 11, -10, -36, 
-52, -33, -10, 20, 49, 52, 37, 18, -6, -42, -49, -27, 8, 31, 45, 38, 
21, 11, -12, -25, -18, -9, 0, 20, 24, 26, 24, 18, 12, -6, -9, 0, 
5, -2, -3, 21, 29, 18, 5, -6, -12, -7, -4, -5, -4, 6, 22, 9, 
-2, 8, 17, 8, -24, -29, -15, 8, 25, 22, 13, 11, -1, -22, -21, -17, 
-22, -6, 9, 17, 18, 15, 7, -3, -9, -22, -19, -5, 14, 28, 14, 9, 
-3, -16, -22, -22, -3, 7, 5, 10, 1, -14, -11, -13, -20, -3, 3, 3, 
12, 21, 12, -7, -18, -20, -16, 16, 15, -1, 5, 16, -2, -9, -17, -25, 
-7, 17, 15, 28, 38, 23, -12, -41, -42, -27, 10, 45, 43, 42, 33, -1, 
-35, -57, -61, -12, 42, 67, 70, 64, 37, -40, -70, -72, -60, -27, 53, 79, 
78, 66, 27, -43, -80, -84, -92, -40, 39, 79, 105, 74, 10, -45, -88, -106, 
-76, -13, 54, 98, 115, 51, -16, -66, -109, -114, -46, -5, 57, 114, 107, 62, 
-32, -88, -111, -100, -52, 5, 86, 114, 76, 17, -22, -82, -92, -53, -13, 11, 
60, 92, 41, -6, -51, -89, -90, -32, 2, 36, 92, 101, 4, -30, -57, -83, 
-71, -38, 41, 96, 105, 52, -12, -41, -86, -85, -40, 11, 44, 101, 93, 17, 
-38, -62, -96, -47, 22, 41, 58, 108, 105, -31, -65, -72, -89, -68, 15, 48, 
92, 120, 59, -26, -55, -82, -88, -36, 20, 55, 105, 90, 34, -12, -54, -121, 
-84, -12, 26, 56, 100, 91, 40, -29, -99, -117, -77, -9, 32, 91, 127, 98, 
-6, -72, -100, -83, -53, -19, 52, 109, 112, 56, 0, -46, -98, -87, -36, 14, 
44, 91, 91, 57, 7, -54, -99, -77, -35, 20, 67, 94, 107, 30, -54, -84, 
-80, -69, 1, 32, 48, 84, 86, 27, -50, -58, -62, -55, -19, 40, 66, 83, 
66, 9, -41, -56, -64, -53, -2, 38, 49, 59, 37, -8, -40, -52, -42, -17, 
11, 33, 49, 59, 25, -26, -43, -40, -46, -27, 14, 24, 44, 49, 21, -30, 
-34, -47, -52, -24, 10, 47, 54, 40, 8, -28, -47, -37, -27, -7, 14, 29, 
49, 36, 7, -19, -41, -50, -30, -6, 20, 42, 55, 52, -9, -40, -41, -51, 
-41, 6, 27, 57, 63, 34, 2, -29, -47, -43, -26, -6, 28, 61, 52, 29, 
-3, -35, -60, -50, -22, 8, 41, 68, 53, 19, -33, -59, -46, -44, -20, 14, 
42, 60, 50, -7, -44, -62, -60, -44, -22, 24, 59, 60, 35, -3, -53, -80, 
-66, -41, -4, 30, 52, 46, 19, -28, -69, -73, -45, -24, -5, 6, 25, 45, 
19, -31, -70, -76, -62, -25, 0, 22, 47, 50, 10, -60, -69, -61, -45, -15, 
10, 22, 37, 33, 8, -27, -48, -42, -43, -28, 7, 25, 33, 40, 14, -20, 
-37, -52, -31, 2, 20, 24, 32, 27, 4, -4, -12, -28, -20, 1, -4, 14, 
40, 41, 27, 16, -5, -18, -15, -13, 4, 21, 35, 42, 39, 29, 3, -7, 
-15, -23, -16, 16, 36, 39, 43, 40, 14, -6, -20, -35, -18, 17, 41, 43, 
27, 9, 0, -7, -19, -24, -11, 13, 22, 27, 22, 2, -2, -2, -25, -38, 
-9, 0, 12, 29, 25, 2, 4, -2, -24, -32, -20, -5, 10, 29, 15, -1, 
12, -2, -29, -30, -21, -24, 6, 20, 10, 10, 13, 8, -20, -37, -28, -8, 
5, 26, 42, 9, -11, -18, -35, -14, 4, 13, 32, 30, 16, -2, -26, -18, 
-8, -21, -8, 15, 16, 25, 8, -14, -15, -26, -22, 7, 23, 27, 38, 26, 
-1, -31, -50, -34, 1, 35, 47, 45, 38, -16, -40, -46, -57, -45, 6, 54, 
55, 51, 31, -7, -48, -55, -60, -47, 4, 66, 74, 59, 47, -18, -85, -91, 
-86, -45, 45, 107, 108, 74, 32, -49, -106, -102, -80, -7, 69, 109, 103, 74, 
23, -71, -96, -101, -73, -6, 83, 109, 90, 47, 10, -31, -98, -99, -34, 40, 
72, 86, 74, 27, -29, -71, -97, -55, 19, 53, 65, 78, 48, -26, -44, -70, 
-71, -24, 6, 32, 79, 64, 10, -13, -54, -82, -66, -19, 19, 52, 93, 48, 
-15, -36, -59, -101, -38, 32, 42, 71, 103, 7, -42, -65, -93, -83, -31, 29, 
59, 98, 90, 29, -31, -86, -90, -61, -12, 35, 102, 119, 57, -21, -52, -80, 
-104, -36, 31, 58, 103, 126, 5, -39, -59, -109, -105, 16, 50, 69, 114, 110, 
33, -52, -90, -108, -65, 6, 57, 84, 112, 70, -8, -52, -99, -90, -26, 29, 
49, 79, 94, 33, -21, -62, -97, -58, 11, 36, 52, 95, 86, 10, -23, -75, 
-103, -57, -3, 18, 74, 100, 64, 20, -54, -88, -68, -31, -13, 22, 87, 84, 
46, -9, -57, -78, -47, -17, 12, 45, 63, 48, 9, -28, -45, -42, -32, -15, 
17, 41, 51, 52, 23, -42, -42, -31, -44, -33, 32, 50, 61, 52, 7, -39, 
-42, -36, -37, -12, 30, 49, 41, 22, -24, -50, -34, -44, -38, 1, 32, 45, 
49, 20, -18, -47, -53, -49, -36, 18, 40, 51, 52, 20, -41, -56, -50, -35, 
-17, 0, 22, 46, 43, 11, -16, -30, -37, -36, -35, -14, 31, 66, 47, 17, 
-16, -60, -76, -23, -8, 18, 54, 56, 38, 14, -41, -76, -41, -5, -10, 6, 
38, 54, 50, 26, -40, -48, -29, -25, -25, 22, 56, 65, 46, -1, -47, -44, 
-34, -27, 4, 30, 40, 67, 37, -20, -43, -47, -61, -30, 5, 16, 36, 63, 
16, -30, -46, -52, -52, -28, 10, 21, 47, 52, 12, -42, -57, -60, -51, -28, 
6, 31, 44, 38, 4, -29, -52, -65, -48, -17, 5, 24, 42, 20, -5, -25, 
-47, -49, -23, -9, 10, 22, 32, 32, -6, -25, -41, -46, -24, 1, 14, 38, 
34, 17, 9, -17, -31, -28, -18, -12, -3, 29, 32, 31, 30, 5, -13, -4, 
-14, -12, 4, 3, 25, 39, 18, 6, 19, 11, -18, -3, -1, -5, 10, 21, 
15, 18, 19, -2, -15, -13, -21, -5, 22, 28, 21, 24, 12, -14, -23, -21, 
-30, -14, 15, 22, 23, 29, 0, -6, -4, -20, -30, -18, -3, 9, 18, 8, 
4, -5, -19, -28, -25, -8, 2, 20, 25, 8, -5, -8, -29, -23, -11, -7, 
16, 32, 18, 7, -5, -5, -10, -24, -11, -8, 1, 25, 22, 12, 17, 0, 
-18, -17, -13, -11, 3, 25, 30, 22, 14, -19, -25, -9, -11, -11, 45, 46, 
27, 12, -16, -29, -20, -28, -24, -3, 25, 48, 32, 18, -5, -47, -61, -36, 
-21, 18, 56, 54, 35, 6, -35, -67, -61, -36, -25, 31, 78, 68, 35, 6, 
-61, -88, -86, -60, -14, 34, 87, 80, 35, -17, -62, -102, -82, -36, 5, 61, 
92, 65, 37, -13, -63, -86, -87, -33, 36, 77, 87, 79, 38, -42, -73, -92, 
-90, -34, 63, 74, 81, 72, 19, -36, -71, -91, -68, -10, 41, 79, 88, 57, 
2, -53, -81, -90, -49, 26, 77, 88, 81, 14, -42, -69, -85, -80, -38, 49, 
81, 94, 79, 17, -61, -86, -98, -73, -8, 56, 106, 104, 39, -41, -73, -90, 
-82, -27, 46, 87, 103, 76, 7, -55, -78, -86, -91, 4, 59, 67, 90, 92, 
-12, -70, -92, -93, -62, -4, 54, 95, 115, 81, -3, -86, -100, -81, -33, 27, 
53, 108, 117, 50, -29, -74, -106, -83, -17, 23, 61, 109, 114, 24, -44, -83, 
-94, -82, -15, 27, 76, 125, 104, 34, -52, -107, -117, -70, -12, 32, 96, 113, 
77, 17, -40, -110, -105, -51, 2, 35, 84, 107, 54, -18, -80, -94, -75, -39, 
3, 48, 92, 111, 36, -27, -71, -95, -89, -56, 25, 74, 96, 85, 43, -10, 
-76, -95, -76, -24, 24, 69, 91, 71, 21, -31, -68, -68, -41, -10, 13, 45, 
83, 60, 9, -28, -57, -73, -38, -8, 21, 60, 85, 64, -10, -41, -54, -56, 
-37, -9, 28, 56, 65, 40, 1, -37, -40, -35, -25, -9, 16, 48, 52, 36, 
1, -32, -45, -34, -28, -12, 20, 43, 53, 30, -14, -46, -51, -44, -26, 5, 
31, 52, 63, 13, -31, -53, -51, -40, -22, 29, 46, 48, 44, 18, -31, -59, 
-57, -51, -17, 22, 54, 61, 41, -1, -44, -62, -55, -39, 0, 40, 52, 56, 
35, -20, -61, -63, -54, -18, 18, 37, 51, 60, 35, -35, -56, -60, -55, -28, 
6, 31, 57, 61, 9, -36, -44, -59, -47, -10, 10, 25, 59, 44, -2, -29, 
-42, -56, -29, -5, 7, 28, 51, 27, -9, -39, -58, -56, -38, -2, 11, 27, 
46, 35, 4, -41, -51, -42, -29, -14, 6, 26, 45, 31, -1, -19, -35, -38, 
-33, -24, -9, 18, 35, 27, 14, -4, -24, -40, -38, -31, -6, 29, 44, 39, 
22, -13, -41, -45, -36, -8, 16, 29, 45, 51, 15, -6, -27, -42, -39, -24, 
7, 32, 52, 53, 37, 1, -24, -39, -37, -24, -3, 39, 42, 31, 21, 3, 
-23, -29, -13, -3, 10, 24, 22, 18, 4, -10, -11, -11, -7, -7, -5, 11, 
21, 21, 14, 0, -13, -20, -25, -25, -10, 11, 19, 12, 5, -12, -18, -3, 
-2, -18, -10, 9, 6, 6, 4, -8, -5, -2, 0, };
