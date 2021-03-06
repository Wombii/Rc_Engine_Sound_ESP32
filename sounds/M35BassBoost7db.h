const unsigned int sampleRate = 14000;  // 22050, but we want to slow it down a bit
const unsigned int sampleCount = 7865;
const signed char samples[] = {
0, 20, 48, 56, 53, 53, 58, 63, 72, 77, 77, 87, 114, 114, 109, 109,
110, 111, 114, 115, 114, 112, 110, 109, 110, 111, 113, 111, 99, 72, 55, 35, 
15, 2, -10, -21, -34, -46, -54, -56, -47, -33, -22, -17, -9, 1, 10, 18, 
29, 40, 49, 59, 62, 61, 55, 48, 46, 63, 74, 76, 70, 56, 47, 55, 
59, 60, 57, 41, 14, 7, 3, 2, 10, 14, 7, 3, -7, -23, -37, -45, 
-43, -31, -23, -25, -32, -44, -49, -44, -29, -13, -4, 0, -1, -2, 1, 5, 
10, 41, 60, 68, 73, 65, 28, 5, -16, -36, -45, -42, -36, -39, -47, -56, 
-60, -57, -39, -16, -5, -9, -20, -47, -55, -44, -33, -32, -36, -47, -48, -44, 
-49, -63, -70, -69, -67, -56, -42, -31, -19, -19, -21, -17, -9, -10, -24, -24, 
-14, -4, -4, -16, -32, -47, -46, -37, -41, -55, -59, -70, -73, -63, -61, -78, 
-80, -82, -82, -72, -49, -45, -36, -17, 2, 18, 32, 26, 16, 14, 14, 12, 
16, 14, 7, 10, 18, 8, -1, -13, -32, -39, -32, -33, -30, -18, -19, -31, 
-36, -42, -51, -48, -40, -38, -25, -15, -19, -28, -35, -43, -45, -40, -36, -29, 
-18, -12, -7, -2, -2, -9, -9, -2, 2, 7, 14, 20, 21, 16, 15, 12, 
6, 0, -6, -19, -19, -11, -6, -7, -9, -15, -23, -17, -3, 6, 27, 37, 
31, 27, 30, 21, 5, 12, 17, 17, 22, 14, 0, -3, 3, 5, 6, 5, 
2, 2, 8, 17, 22, 28, 27, 22, 20, 19, 10, 5, 1, -2, -1, 0, 
-2, 2, 6, 4, 1, -2, -6, -7, -7, -6, -1, 3, 3, 4, 1, -6, 
-12, -14, -17, -18, -19, -24, -31, -31, -30, -25, -20, -21, -19, -7, 4, 10, 
20, 24, 13, 14, 20, 26, 34, 36, 29, 30, 35, 36, 42, 48, 44, 47, 
58, 67, 77, 97, 100, 100, 103, 104, 103, 104, 103, 104, 103, 102, 103, 100, 
84, 59, 45, 43, 36, 26, 16, 2, -8, 3, 4, 2, 5, 4, -1, 5, 
0, -6, -5, -3, -1, 13, 14, 9, 6, -1, -5, 4, 8, 2, -4, -7, 
-10, -9, -7, -1, 7, 8, 3, -1, -7, -10, -13, -27, -39, -47, -54, -61, 
-62, -47, -34, -20, -5, 4, 9, 23, 25, 20, 20, 23, 28, 42, 53, 52, 
40, 21, -21, -39, -48, -48, -40, -34, -52, -63, -64, -61, -51, -20, -3, 18, 
33, 29, 14, -6, -9, 5, 18, 21, 28, 23, 2, -14, -28, -45, -37, -17, 
-4, 7, 10, -2, -11, -7, -3, 4, 12, 15, 10, -6, -29, -57, -84, -101, 
-105, -95, -66, -36, -28, -57, -82, -99, -102, -86, -52, -38, -30, -42, -78, -101, 
-100, -103, -78, -34, -20, -29, -46, -64, -58, -37, -26, -12, -7, -17, -28, -29, 
-30, -25, -10, 7, 26, 42, 46, 48, 46, 34, 30, 33, 8, -14, -18, -13, 
-11, -13, -32, -51, -51, -34, -28, -39, -47, -35, -24, -13, -6, -11, 0, 29, 
47, 49, 53, 45, 31, 21, 6, -17, -29, -33, -43, -44, -44, -58, -71, -65, 
-62, -52, -32, -27, -28, -8, 4, 2, 2, 5, 1, 8, 14, 5, -5, -8, 
-12, -14, -14, -22, -39, -43, -29, -17, -12, -11, -15, -11, 1, 7, 6, 4, 
2, 5, 17, 31, 37, 33, 23, 20, 24, 35, 44, 45, 40, 41, 40, 36, 
31, 21, 18, 22, 24, 15, 5, -2, 0, 5, 6, 2, -3, -3, 0, 4, 
4, 4, 14, 20, 20, 18, 14, 12, 11, 11, 12, 13, 8, -2, -4, -2, 
0, 0, -5, -16, -17, -10, -3, 2, 6, 14, 21, 29, 30, 21, 12, 11, 
11, 18, 25, 21, 5, 3, 6, 18, 34, 45, 55, 65, 80, 97, 110, 114, 
114, 115, 115, 113, 113, 115, 115, 114, 115, 113, 92, 57, 43, 25, 9, -3, 
-18, -16, -5, 5, 18, 40, 70, 89, 107, 112, 110, 110, 110, 109, 108, 107, 
106, 105, 100, 90, 79, 69, 54, 29, 18, 11, 11, 15, 15, 4, -8, -20, 
-24, -21, -25, -23, -20, -26, -29, -23, -25, -33, -40, -52, -62, -63, -58, -43, 
-25, -13, -2, 16, 21, 31, 39, 32, 11, -17, -27, -34, -38, -36, -31, -34, 
-45, -56, -64, -67, -54, -44, -34, -18, -7, -7, -5, -9, -20, -26, -20, -8, 
-9, -24, -48, -74, -94, -95, -70, -41, -18, -1, 3, -19, -36, -44, -36, -14, 
20, 17, -3, -30, -52, -63, -61, -48, -20, 13, 30, 19, -24, -57, -80, -79, 
-62, -34, -27, -36, -57, -75, -81, -77, -72, -76, -91, -98, -91, -82, -82, -88, 
-93, -80, -47, -42, -47, -49, -37, -19, -19, -33, -48, -58, -52, -37, -39, -41, 
-30, -22, -15, 11, 8, -8, -17, -22, -26, -14, -13, -31, -47, -42, -29, -10, 
-5, -16, -24, -11, 9, 0, -8, -9, -5, 10, 47, 53, 49, 47, 40, 28, 
26, 13, -11, -23, -24, -31, -29, -33, -54, -65, -49, -31, -34, -39, -52, -55, 
-30, 0, -15, -33, -40, -33, 2, 8, -8, -19, -12, 0, 7, 4, -13, -33, 
-34, -15, 12, 10, -8, -34, -46, -33, -27, -30, -41, -51, -44, -15, -10, -20, 
-30, -27, 5, 21, 15, -3, -19, -23, -4, 9, 8, 2, 0, 5, 21, 21, 
11, -1, -5, 10, 29, 39, 34, 24, 19, 26, 32, 31, 22, 13, 9, 5, 
-3, -16, -29, -36, -32, -22, -18, -23, -35, -46, -50, -46, -45, -50, -50, -41, 
-27, -24, -25, -31, -34, -16, 1, 9, 10, 3, -8, -5, 9, 14, 13, 14, 
13, 13, 21, 23, 12, 2, 4, 9, 15, 15, 6, -3, -7, -14, -24, -31, 
-34, -32, -13, -4, -3, -3, 1, 13, 29, 47, 69, 92, 98, 97, 99, 98, 
99, 98, 99, 98, 98, 99, 98, 98, 95, 94, 93, 96, 95, 79, 50, 38, 
19, -10, -38, -54, -65, -71, -71, -71, -72, -60, -49, -41, -34, -35, -39, -30, 
-20, -4, 19, 33, 36, 41, 45, 50, 58, 61, 63, 72, 67, 46, 27, 19, 
19, 23, 24, 21, 11, -20, -36, -45, -50, -52, -53, -62, -68, -72, -78, -84, 
-86, -71, -41, -11, 7, 14, 11, 12, 21, 26, 20, 9, -10, -14, -17, -23, 
-19, -6, 9, 24, 38, 43, 45, 46, 40, 44, 58, 56, 46, 36, 19, 10, 
12, 12, 22, 45, 37, 25, 15, -4, -21, -23, -32, -40, -46, -68, -97, -94, 
-94, -98, -96, -86, -49, -31, -39, -63, -78, -55, -13, 31, 53, 49, 26, -27, 
-56, -71, -66, -46, -26, -25, -40, -70, -95, -96, -95, -88, -61, -32, -21, -21, 
-34, -39, -34, -27, -29, -33, -37, -40, -39, -41, -48, -40, -28, -26, -24, -16, 
-11, 3, 22, 30, 27, 34, 44, 49, 49, 44, 34, 22, 11, 10, 9, 1, 
-15, -25, -4, 7, 4, -4, -21, -35, -16, -3, -3, -4, 2, 4, 4, -1, 
-19, -33, -30, -10, -9, -10, -11, -19, -35, -42, -47, -52, -45, -29, -9, -3, 
-4, -15, -25, -28, -24, -19, -12, -6, 0, 7, 5, 5, 5, 2, 0, 2, 
3, 5, 9, 9, 9, 16, 22, 22, 15, 11, 17, 18, 16, 11, 3, -6, 
-11, -7, 0, 7, 13, 19, 21, 18, 15, 12, 9, 10, 9, 9, 12, 19, 
21, 26, 38, 49, 50, 46, 39, 31, 36, 34, 15, -8, -14, -9, -8, -10, 
-21, -35, -41, -41, -44, -48, -54, -59, -56, -51, -48, -46, -46, -40, -32, -21, 
-12, -6, -4, 2, 11, 22, 30, 33, 34, 45, 57, 68, 70, 66, 62, 61, 
60, 56, 49, 45, 53, 58, 60, 67, 75, 78, 86, 91, 93, 98, 106, 105, 
107, 108, 102, 100, 107, 114, 114, 111, 101, 88, 79, 72, 73, 80, 83, 79, 
78, 84, 90, 94, 94, 89, 83, 86, 90, 92, 90, 84, 82, 80, 69, 50, 
36, 28, 30, 35, 32, 20, 6, -8, -13, -15, -16, -17, -20, -23, -28, -37, 
-47, -53, -50, -35, -13, 4, 12, 18, 39, 53, 58, 60, 68, 84, 90, 92, 
85, 66, 36, -11, -33, -50, -67, -76, -73, -67, -55, -44, -44, -39, -23, -16, 
-4, 5, 7, 8, -4, -27, -43, -45, -45, -42, -29, -25, -27, -39, -58, -62, 
-45, -28, -13, 4, 20, 45, 63, 68, 66, 66, 66, 65, 65, 65, 41, -7, 
-57, -68, -75, -87, -101, -109, -111, -111, -109, -96, -72, -51, -43, -47, -51, -50, 
-40, -10, 0, -9, -35, -73, -105, -115, -113, -112, -110, -105, -103, -107, -111, -113, 
-113, -102, -52, -28, -15, 0, 8, 6, 22, 27, 26, 31, 30, 11, -10, -22, 
-43, -56, -56, -58, -58, -65, -79, -78, -64, -40, -14, 8, 14, 12, 4, -13, 
-26, -36, -45, -44, -24, -26, -40, -55, -67, -74, -78, -81, -78, -69, -60, -37, 
-23, -24, -34, -38, -31, -2, 17, 17, 4, -5, -7, -11, -11, -22, -40, -48, 
-48, -51, -51, -49, -49, -43, -29, -30, -28, -23, -28, -37, -19, -3, 1, 4, 
4, 0, 14, 26, 22, 17, 22, 22, 19, 20, 22, 30, 38, 27, 17, 20, 
24, 26, 26, 19, 10, 11, 13, 6, 6, 6, -2, -4, 7, 19, 35, 42, 
39, 33, 32, 28, 25, 18, 8, 1, 6, 20, 20, 13, 2, -8, -7, 4, 
7, 11, 16, 21, 26, 21, 11, 3, -2, -7, -9, -10, -9, -7, -11, -22, 
-28, -21, -13, -8, -9, -12, -7, 2, 7, 4, 0, 2, 14, 29, 39, 45, 
52, 57, 61, 76, 93, 103, 112, 113, 113, 113, 113, 112, 112, 114, 112, 113, 
113, 89, 77, 75, 69, 62, 57, 37, 34, 37, 35, 29, 23, 7, 8, 24, 
38, 48, 57, 53, 48, 50, 51, 52, 50, 45, 45, 46, 45, 38, 21, 16, 
14, 8, 1, 1, 11, 32, 56, 76, 83, 67, 51, 43, 43, 49, 64, 82, 
75, 58, 39, 9, -31, -30, -15, 5, 22, 15, -36, -61, -73, -68, -38, 5, 
45, 45, 15, -35, -71, -82, -72, -43, -10, 1, -12, -44, -59, -50, -25, 2, 
29, 59, 66, 69, 67, 55, 44, 42, 43, 53, 64, 63, 44, 18, -17, -48, 
-76, -94, -89, -74, -57, -42, -41, -59, -66, -61, -35, 1, 32, 62, 69, 56, 
29, 5, -7, -2, -1, -14, -33, -62, -99, -101, -104, -101, -68, -31, -20, -30, 
-56, -83, -87, -82, -63, -27, 5, 9, -8, -35, -49, -57, -57, -53, -50, -60, 
-64, -61, -66, -80, -74, -46, -11, 21, 37, 34, 36, 44, 45, 42, 33, 13, 
-19, -38, -57, -71, -72, -60, -52, -41, -33, -33, -38, -40, -23, 0, 20, 29, 
29, 35, 34, 30, 31, 29, 8, -5, -14, -32, -59, -79, -87, -87, -87, -89, 
-92, -84, -55, -39, -25, -18, -20, -12, 1, 7, 13, 23, 22, -4, -9, -7, 
-11, -16, -18, -34, -46, -48, -48, -54, -47, -34, -18, 0, 9, 7, 10, 19, 
30, 40, 45, 42, 33, 25, 18, 7, -10, -43, -58, -61, -56, -51, -45, -33, 
-25, -7, 19, 34, 41, 53, 59, 66, 75, 79, 71, 63, 49, 38, 33, 26, 
11, 7, 2, -5, -16, -30, -55, -58, -47, -31, -20, -20, -19, -14, -10, -3, 
6, 9, 3, -3, -7, -9, -10, -21, -28, -28, -29, -31, -29, -29, -24, -12, 
-4, 2, 16, 23, 31, 43, 50, 46, 50, 50, 43, 42, 45, 38, 29, 21, 
12, 5, 5, 5, -1, -1, 4, 11, 27, 34, 37, 39, 45, 52, 56, 57, 
53, 50, 53, 58, 58, 63, 72, 78, 85, 105, 111, 111, 111, 112, 113, 113, 
112, 111, 111, 112, 111, 110, 110, 106, 90, 63, 26, 5, -19, -41, -57, -63, 
-61, -62, -63, -55, -35, -14, 1, 17, 35, 49, 61, 75, 81, 83, 75, 61, 
52, 45, 42, 40, 35, 28, 23, 23, 26, 34, 42, 46, 50, 57, 58, 50, 
33, 11, -29, -53, -62, -60, -57, -49, -42, -47, -49, -50, -51, -37, -21, -6, 
2, -3, -17, -37, -48, -43, -19, 6, 21, 38, 34, 14, -3, -15, -34, -35, 
-28, -20, -10, 0, 6, 5, 0, -9, -14, -18, -17, -6, -1, -13, -27, -46, 
-64, -67, -55, -48, -48, -52, -61, -67, -62, -55, -45, -32, -21, -16, -21, -37, 
-55, -53, -49, -44, -38, -36, -51, -64, -76, -95, -111, -115, -113, -115, -112, -100, 
-91, -76, -63, -60, -59, -55, -56, -41, -24, -24, -40, -52, -59, -59, -51, -48, 
-50, -47, -32, -27, -29, -34, -36, -30, -15, -2, 19, 38, 44, 32, 23, 17, 
14, 9, -8, -38, -44, -44, -44, -45, -49, -55, -48, -39, -41, -47, -44, -46, 
-48, -48, -50, -51, -27, -7, -1, -5, -13, -25, -42, -42, -41, -48, -50, -34, 
-29, -27, -27, -35, -42, -32, -30, -35, -27, -15, -13, -12, -15, -26, -28, -14, 
-10, -15, -13, -9, -8, -3, 4, 8, 20, 33, 42, 53, 79, 88, 90, 92, 
90, 75, 64, 54, 44, 39, 34, 29, 33, 28, 13, 3, -1, -9, -8, -7, 
-12, -16, -12, -8, 1, 15, 26, 32, 42, 41, 35, 31, 28, 26, 32, 37, 
39, 42, 40, 26, 21, 19, 18, 20, 23, 19, 21, 20, 13, 8, -1, -9, 
-7, 4, 10, 12, 11, 5, -2, -7, -12, -12, -10, -9, -3, 1, 5, 14, 
17, 23, 34, 42, 50, 66, 79, 98, 109, 110, 109, 109, 110, 109, 108, 107, 
108, 109, 109, 108, 106, 102, 83, 71, 61, 51, 44, 36, 21, 13, 8, 8, 
10, 3, 3, 9, 15, 20, 25, 22, 18, 20, 20, 22, 28, 27, 18, 13, 
14, 15, 14, 15, 20, 32, 41, 37, 15, 2, -4, 1, 11, 13, -9, -33, 
-51, -57, -51, -36, -32, -27, -15, 2, 19, 27, 21, 11, 3, 1, 9, 31, 
44, 56, 62, 58, 44, 33, 16, 4, 4, 8, 10, 1, -24, -43, -41, -29, 
1, 26, 36, 32, 26, 2, -13, -8, 5, 20, 47, 79, 80, 80, 80, 67, 
22, -19, -53, -62, -53, -40, -24, -28, -42, -53, -53, -40, -2, 7, -4, -17, 
-26, -17, 3, 15, 19, 22, 17, 9, 6, -8, -36, -66, -88, -104, -105, -102, 
-102, -105, -104, -102, -104, -103, -91, -66, -28, -26, -43, -61, -67, -60, -43, -30, 
-21, -25, -24, -11, -23, -50, -74, -84, -81, -75, -75, -65, -48, -31, -14, -8, 
-15, -13, -4, -1, 13, 25, 21, 7, -1, -4, -15, -29, -41, -41, -31, -15, 
-6, -20, -33, -42, -41, -5, 10, 1, -13, -18, -14, 1, -5, -27, -48, -53, 
-44, -25, -30, -51, -64, -60, -46, -47, -58, -71, -72, -58, -45, -50, -58, -66, 
-66, -51, -27, -25, -28, -28, -19, -8, -13, -20, -24, -22, -8, 12, 11, 1, 
-14, -28, -29, -14, -14, -24, -34, -35, -4, 20, 25, 16, 13, 17, 30, 44, 
42, 22, 6, 8, 17, 25, 23, 17, 19, 34, 34, 25, 15, 7, 10, 30, 
33, 28, 25, 19, 9, 12, 9, -3, -9, -4, 8, 17, 22, 12, -9, -25, 
-28, -14, 0, 3, -4, -18, -23, -16, -8, -9, -14, -9, -2, 5, 9, 7, 
6, 18, 24, 29, 28, 21, 13, 15, 17, 21, 25, 29, 48, 64, 80, 95, 
105, 106, 105, 107, 109, 111, 111, 109, 109, 106, 97, 85, 67, 30, 5, -16, 
-23, -16, -7, 6, 21, 35, 52, 79, 108, 109, 107, 106, 104, 103, 104, 105, 
107, 107, 107, 103, 81, 68, 55, 34, 9, -33, -53, -59, -48, -25, 2, 28, 
24, 5, -14, -20, -8, 28, 44, 44, 31, 5, -44, -62, -58, -42, -23, -11, 
-29, -54, -73, -80, -75, -51, -1, 20, 28, 25, 20, 22, 22, 23, 28, 33, 
34, 31, 18, 3, -14, -36, -64, -73, -83, -87, -74, -50, -27, -18, -12, -12, 
-15, -11, -4, -9, -20, -38, -58, -66, -52, -35, -23, -19, -25, -37, -31, -8, 
27, 56, 64, 51, 31, 6, -3, 4, 19, 22, 11, -10, -26, -30, -33, -28, 
-22, -28, -41, -49, -63, -62, -47, -28, -9, 11, 1, -15, -23, -27, -27, -15, 
-8, 0, 8, 4, -19, -70, -94, -100, -87, -66, -41, -48, -67, -75, -72, -63, 
-45, -36, -38, -48, -55, -54, -46, -37, -31, -28, -24, -23, -36, -46, -48, -43, 
-28, -18, -20, -12, -6, -2, 15, 30, 13, 1, 2, 1, 11, 21, 12, -7, 
-25, -48, -71, -63, -44, -25, -10, -8, -28, -36, -38, -46, -52, -36, -24, -12, 
1, -6, -35, -56, -54, -51, -44, -40, -54, -61, -50, -44, -33, -19, -24, -18, 
-1, 8, 16, 21, -2, -13, -6, 0, -1, 0, -14, -39, -48, -46, -54, -63, 
-54, -44, -29, -11, -10, -18, -7, 10, 25, 44, 56, 59, 72, 79, 72, 64, 
53, 49, 56, 58, 48, 40, 36, 31, 31, 32, 18, -10, -9, -3, 3, 12, 
15, -4, -14, -16, -13, -2, 8, 7, 1, -9, -19, -23, -29, -28, -14, 4, 
12, 12, -6, -18, -13, 4, 23, 36, 31, 19, 13, 12, 13, 18, 15, 11, 
14, 20, 19, 14, 8, -2, -3, 4, 8, 8, 7, 0, -6, -7, -4, 1, 
5, 8, 18, 33, 56, 69, 77, 83, 95, 103, 101, 102, 101, 102, 101, 99, 
99, 100, 101, 100, 101, 99, 96, 87, 61, 28, 6, -17, -41, -63, -73, -76, 
-71, -72, -76, -70, -62, -57, -40, -31, -22, -5, 11, 24, 56, 73, 82, 91, 
89, 65, 52, 34, 14, 7, 4, 0, 10, 13, 8, 7, 1, 1, 14, 20, 
19, 16, -2, -16, -24, -26, -24, -23, -30, -40, -58, -79, -89, -89, -85, -78, 
-73, -64, -48, -33, -14, 15, 35, 42, 41, 7, -11, -5, 9, 29, 59, 59, 
46, 24, 1, -9, -5, 4, 25, 46, 49, 38, -1, -35, -37, -10, 17, 39, 
34, 8, -19, -45, -70, -71, -56, -47, -40, -42, -59, -64, -45, -20, 14, 49, 
55, 39, 20, 0, -14, -21, -37, -46, -49, -59, -78, -93, -95, -98, -98, -87, 
-74, -76, -88, -93, -86, -66, -41, -30, -28, -20, -13, -11, -11, -20, -23, -12, 
-4, -14, -32, -39, -45, -40, -27, -21, -13, -9, -12, -13, -7, -3, -5, 3, 
16, 22, 25, 18, 7, 7, 13, 10, -1, -13, -16, -10, -1, -7, -24, -40, 
-45, -38, -23, -26, -42, -36, -33, -33, -29, -26, -21, -11, -12, -18, -13, -12, 
-29, -49, -64, -71, -65, -61, -67, -68, -62, -58, -61, -73, -76, -67, -51, -42, 
-49, -46, -30, -15, -9, -12, -19, -16, -5, 4, 1, -8, -18, -17, -13, -8, 
-4, -9, -16, -18, -19, -23, -21, -9, -13, -22, -24, -21, -22, -35, -40, -32, 
-14, -3, -12, -22, -25, -13, 7, 22, 17, 14, 23, 36, 48, 55, 46, 34, 
29, 30, 31, 30, 21, 12, 11, 11, 5, -15, -24, -27, -26, -27, -30, -31, 
-33, -33, -33, -37, -42, -42, -42, -37, -26, -16, -8, -3, 1, 3, 13, 28, 
31, 26, 27, 32, 47, 79, 83, 79, 80, 81, 82, 84, 83, 87, 100, 112, 
118, 122, 121, 122, 122, 123, 123, 123, 122, 124, 121, 112, 106, 102, 97, 91, 
87, 83, 77, 75, 78, 78, 75, 75, 74, 68, 61, 57, 58, 69, 72, 72, 
71, 70, 70, 77, 85, 89, 89, 89, 79, 65, 54, 39, 22, 7, -11, -11, 
-8, -12, -14, -15, -21, -20, -16, -15, -8, 14, 28, 41, 49, 52, 49, 45, 
49, 59, 73, 79, 50, 17, -24, -63, -76, -73, -76, -67, -39, -17, -9, -2, 
10, 24, 45, 55, 41, -9, -42, -68, -75, -64, -53, -32, -15, -14, -23, -30, 
-38, -44, -31, -15, -2, 18, 43, 45, 50, 57, 63, 72, 75, 69, 60, 49, 
37, 29, 25, 20, 13, 3, -16, -41, -47, -48, -45, -45, -58, -86, -89, -75, 
-52, -31, -25, -45, -65, -81, -81, -72, -66, -70, -85, -98, -100, -101, -91, -68, 
-46, -33, -29, -30, -20, -18, -29, -36, -31, -19, -5, 10, 17, 22, 22, 0, 
-13, -17, -20, -21, -19, -23, -22, -11, -2, 3, 19, 22, 18, 14, 5, -4, 
-6, -15, -28, -34, -33, -20, -7, -6, -12, -16, -21, -22, -13, -9, -11, -10, 
-16, -24, -17, -16, -19, -11, 9, 16, 24, 26, 18, 14, 2, -16, -20, -21, 
-23, -16, -21, -34, -35, -32, -32, -22, -28, -40, -41, -39, -47, -49, -42, -35, 
-20, -5, 0, -3, -3, -5, -4, 1, 9, 10, 9, 6, 3, 3, 3, -1, 
-2, -1, 3, 9, 15, 12, 5, -1, 3, 17, 23, 28, 29, 31, 42, 52, 
50, 50, 51, 49, 51, 54, 53, 55, 55, 50, 38, 23, 6, -4, -9, -14, 
-23, -30, -36, -37, -31, -21, -11, -4, 1, 1, -2, -8, -14, -23, -28, -27, 
-21, -14, -14, -21, -31, -35, -33, -26, -25, -25, -22, -18, -11, -7, 0, 10, 
20, 30, 48, 69, 93, 103, 103, 104, 103, 104, 103, 104, 104, 100, 100, 103, 
95, 75, 57, 27, 14, 8, -3, -15, -27, -33, -30, -20, -12, -1, 28, 41, 
45, 44, 40, 39, 42, 45, 56, 74, 88, 89, 77, 57, 38, 26, 21, 20, 
18, 14, 6, -4, -8, -5, -5, 3, 23, 50, 85, 96, 97, 92, 85, 76, 
50, 24, -1, -25, -43, -51, -58, -65, -72, -75, -74, -79, -73, -41, -1, 24, 
44, 68, 68, 62, 58, 53, 39, -9, -47, -65, -62, -45, -22, -29, -51, -67, 
-59, -25, 44, 67, 55, 22, -6, -15, 15, 49, 69, 71, 53, 0, -28, -44, 
-54, -64, -80, -95, -82, -62, -48, -43, -43, -28, 6, 38, 57, 69, 69, 41, 
9, -6, 7, 39, 63, 47, 14, -31, -74, -96, -96, -97, -97, -96, -96, -83, 
-79, -83, -76, -57, -32, 7, 17, 23, 29, 24, 4, -25, -27, -10, 5, -1, 
-35, -51, -61, -63, -46, -21, -10, -12, -9, -1, 13, 45, 60, 60, 49, 32, 
11, -1, -7, -20, -33, -37, -35, -23, -27, -46, -61, -60, -26, 2, 14, 16, 
34, 63, 77, 64, 50, 44, 45, 46, 30, 12, -2, -11, -13, -7, -5, -10, 
-22, -31, -25, 2, 5, 0, 2, 3, -4, -2, 4, -2, -16, -36, -65, -61, 
-44, -38, -48, -63, -76, -79, -74, -64, -54, -36, 3, 14, 11, 10, 15, 31, 
38, 30, 7, -10, -14, -12, -6, -7, -27, -42, -39, -28, -22, -19, -17, -9, 
-4, -5, -3, -1, -1, 1, 0, 2, 14, 26, 26, 18, 10, 7, 3, 2, 
5, 13, 19, 23, 21, 14, 7, 8, 8, 4, -7, -23, -33, -21, -9, -11, 
-25, -40, -53, -46, -26, -11, -10, -17, -22, -14, 0, 12, 17, 9, -14, -17, 
-5, 9, 14, 10, 5, 3, 10, 21, 30, 30, 23, 23, 34, 42, 40, 32, 
20, 14, 20, 31, 34, 27, 19, 13, 11, 15, 39, 52, 55, 55, 53, 45, 
45, 53, 67, 83, 100, 115, 116, 116, 116, 112, 111, 112, 113, 116, 117, 116, 
117, 117, 116, 115, 115, 116, 115, 96, 60, 26, 2, -15, -22, -23, -29, -42, 
-47, -33, -22, -10, 1, 4, 4, 17, 30, 46, 65, 80, 86, 75, 63, 56, 
58, 62, 77, 93, 98, 96, 98, 92, 74, 71, 63, 50, 34, 11, -31, -57, 
-71, -72, -72, -75, -61, -47, -46, -57, -70, -69, -50, -32, -27, -32, -44, -65, 
-61, -45, -24, -5, -2, -3, 7, 15, 18, 20, 13, 5, 1, 0, 10, 35, 
64, 69, 68, 48, 13, -24, -34, -30, -21, -23, -33, -60, -81, -85, -79, -67, 
-51, -52, -63, -71, -84, -93, -79, -69, -61, -50, -42, -41, -59, -80, -85, -61, 
-29, 9, 26, 34, 33, 24, -5, -62, -80, -87, -95, -107, -114, -114, -112, -112, 
-114, -115, -99, -74, -51, -37, -29, -27, -34, -36, -38, -40, -38, -31, -25, -20, 
-17, -25, -36, -39, -36, -32, -26, -16, -9, 1, 7, 12, 17, 22, 27, 28, 
23, 11, -6, -20, -29, -33, -40, -48, -50, -48, -51, -62, -77, -86, -89, -87, 
-60, -31, -8, 5, 8, -8, -14, -10, -6, -4, -1, 6, 7, -1, -19, -37, 
-49, -58, -50, -34, -31, -35, -19, -14, -16, -10, -9, -13, 4, 16, 20, 26, 
29, 18, 1, -5, -8, 0, 5, 0, 6, 13, 18, 24, 19, -1, 3, 14, 
25, 37, 49, 48, 45, 41, 36, 41, 52, 53, 51, 42, 27, 15, 9, 8, 
9, 10, 6, 1, 5, 10, 15, 18, 22, 37, 51, 59, 56, 48, 38, 19, 
14, 17, 18, 15, 17, 15, 11, 9, 3, -12, -30, -27, -22, -18, -15, -14, 
-18, -18, -13, -7, -1, -3, -10, -12, -6, 3, 6, -7, -11, -8, -2, 8, 
27, 63, 85, 99, 102, 101, 102, 103, 102, 103, 102, 102, 102, 102, 103, 99, 
85, 69, 61, 58, 48, 32, 19, 13, 15, 12, 7, 8, 13, 9, 1, -6, 
-8, -6, -6, -9, -12, -10, -5, -3, -1, 0, 0, 8, 25, 40, 50, 50, 
39, 23, 16, 14, 20, 30, 29, 21, 19, 6, -3, -9, -14, -13, -10, -21, 
-25, -26, -27, -23, -16, -18, -17, -10, -2, 14, 52, 71, 76, 66, 41, 17, 
-2, -6, -9, -18, -31, -36, -22, -10, 4, 23, 45, 65, 51, 22, 5, -1, 
-13, -20, -1, 26, 52, 72, 77, 57, 29, -10, -37, -33, 0, 27, 39, 25, 
4, -10, -33, -31, -5, 30, 61, 72, 59, 51, 47, 42, 45, 54, 49, 45, 
41, 30, 18, -17, -59, -88, -91, -92, -89, -72, -74, -91, -89, -71, -38, -14, 
1, 9, 5, -13, -30, -30, -31, -26, -22, -38, -62, -88, -102, -100, -88, -74, 
-81, -90, -80, -54, -27, -6, -8, -15, -18, -17, -9, -3, 5, 14, 21, 22, 
12, -1, -19, -32, -32, -28, -24, -23, -34, -50, -52, -41, -43, -42, -38, -34, 
-20, 6, 5, -2, -8, -8, -1, -1, -18, -34, -42, -41, -27, -36, -65, -89, 
-89, -73, -45, -37, -38, -33, -20, -14, -23, -33, -38, -40, -37, -24, -15, -9, 
-9, -16, -24, -34, -44, -55, -55, -42, -26, 1, 9, 0, -8, -2, 7, 8, 
7, 0, -6, -5, -2, -5, -10, -15, -19, -13, 5, 12, 13, 10, 11, 26, 
30, 25, 20, 22, 26, 24, 18, 14, 17, 27, 36, 32, 18, 3, -6, -6, 
6, 11, 12, 10, 2, -6, -10, -15, -22, -25, -27, -31, -22, -10, -5, -4, 
0, 11, 14, 9, -4, -13, -7, 24, 38, 41, 40, 39, 44, 44, 42, 42, 
43, 42, 41, 44, 47, 49, 50, 53, 72, 92, 109, 115, 114, 114, 115, 117, 
116, 117, 114, 94, 83, 69, 49, 31, 15, 2, 6, 15, 24, 32, 41, 53, 
71, 90, 105, 113, 112, 113, 113, 112, 111, 110, 109, 109, 110, 106, 94, 70, 
43, 17, -1, -14, -22, -16, -1, 14, 24, 29, 29, 10, -7, -18, -22, -14, 
15, 24, 18, -5, -40, -69, -76, -61, -37, -13, -2, -1, -6, -11, -11, -4, 
-2, -6, -7, -12, -21, -22, -10, 22, 35, 32, 16, -10, -45, -88, -96, -94, 
-92, -90, -89, -95, -100, -100, -89, -60, -21, -11, -9, -17, -33, -32, -13, 5, 
7, -4, -9, -4, -3, -3, -10, -21, -33, -58, -64, -63, -61, -52, -23, 8, 
44, 61, 58, 57, 53, 26, -3, -16, -14, -6, -3, -10, -23, -38, -56, -71, 
-75, -76, -75, -82, -86, -65, -52, -45, -44, -54, -67, -70, -58, -35, -15, -15, 
-32, -47, -62, -65, -52, -37, -25, -32, -44, -44, -30, -17, -19, -31, -44, -50, 
-46, -21, -3, 2, -5, -14, -25, -37, -46, -55, -60, -60, -54, -35, -24, -14, 
-3, 9, 23, 25, 19, 4, -6, -3, 5, -1, -14, -23, -20, -12, -16, -32, 
-44, -50, -51, -33, -17, -8, -6, -12, -27, -30, -16, -10, -14, -21, -27, -12, 
5, 1, -22, -38, -41, -33, -17, -4, 4, 16, 27, 24, 21, 18, 9, 0, 
9, 20, 31, 34, 23, -6, -20, -30, -32, -26, -19, -10, 2, 11, 14, 18, 
23, 31, 48, 65, 74, 76, 73, 71, 69, 65, 61, 61, 59, 50, 38, 24, 
14, 13, 15, 16, 16, 11, 6, -7, -13, -10, -5, 0, 9, 32, 45, 52, 
52, 43, 29, 24, 24, 31, 36, 31, 20, 19, 21, 21, 13, 0, -11, -12, 
-4, 11, 21, 14, 6, 1, 7, 22, 28, 12, 1, -4, -2, 6, 13, 9, 
-2, -8, -7, -1, 18, 28, 35, 41, 48, 54, 70, 81, 90, 99, 105, 107, 
107, 105, 103, 103, 105, 106, 106, 105, 106, 105, 104, 106, 105, 104, 104, 87, 
52, 9, -12, -30, -49, -65, -71, -71, -69, -64, -61, -62, -53, -39, -28, -21, 
-14, -6, 17, 40, 57, 66, 64, 55, 57, 67, 78, 83, 82, 68, 61, 61, 
54, 43, 41, 41, 38, 35, 29, 18, -11, -36, -54, -66, -76, -77, -63, -56, 
-58, -66, -76, -81, -74, -67, -64, -61, -57, -53, -49, -38, -19, 5, 26, 40, 
44, 50, 50, 44, 40, 37, 30, 26, 23, 22, 24, 20, 14, 9, -4, -27, 
-55, -52, -30, -2, 19, 29, 23, 5, -17, -30, -26, 4, 13, -6, -39, -69, 
-91, -77, -45, -18, -5, -8, -33, -43, -40, -29, -17, -14, -34, -44, -41, -32, 
-20, -10, -4, 3, 0, -14, -27, -48, -63, -68, -61, -56, -61, -75, -83, -80, 
-66, -50, -32, -15, -20, -30, -49, -67, -62, -43, -24, -5, 8, 5, -29, -45, 
-34, -11, 2, 1, -9, -1, 14, 14, 5, 3, 6, 5, 8, 17, 24, 23, 
7, -16, -34, -45, -47, -36, -37, -44, -45, -47, -58, -61, -60, -55, -48, -43, 
-43, -42, -41, -42, -38, -35, -45, -47, -40, -42, -50, -56, -67, -67, -48, -33, 
-32, -38, -48, -55, -53, -51, -50, -36, -30, -36, -41, -45, -50, -43, -37, -33, 
-26, -21, -27, -23, -15, -14, -17, -28, -38, -35, -24, -17, -15, -14, -13, -6, 
2, 5, 2, -7, -13, -12, 0, 11, 6, 1, 3, 5, 7, 7, 4, 8, 
17, 22, 22, 19, 9, 8, 13, 17, 20, 17, 10, 12, 19, 19, 13, 5, 
1, -3, -6, -10, -14, -22, -33, -41, -45, -48, -46, -44, -46, -49, -46, -40, 
-27, -9, 11, 24, 33, 39, 40, 47, 54, 57, 62, 67, 65, 62, 63, 64, 
66, 70, 73, 83, 95, 103, 107, 112, 111, 112, 114, 114, 108, 98, 90, 86, 
80, 73, 61, 52, 50, 54, 61, 69, 80, 81, 82, 85, 82, 74, 67, 57, 
47, 46, 47, 51, 50, 46, 47, 53, 59, 70, 78, 84, 85, 84, 74, 63, 
56, 50, 43, 34, 12, -7, -25, -37, -39, -37, -48, -61, -68, -69, -70, -51, 
-20, 5, 16, 22, 29, 53, 75, 92, 92, 88, 86, 67, 26, -19, -46, -53, 
-32, -13, -6, -17, -38, -58, -81, -80, -67, -52, -40, -54, -79, -90, -89, -91, 
-93, -62, -30, -12, -7, -11, -9, 24, 52, 68, 66, 44, -1, -24, -24, 0, 
30, 51, 65, 57, 47, 47, 55, 64, 61, 46, 28, 14, 6, 9, 0, -25, 
-52, -76, -94, -103, -102, -99, -88, -85, -101, -108, -105, -98, -77, -60, -61, -50, 
-32, -19, -14, -28, -84, -106, -104, -95, -78, -55, -38, -42, -54, -65, -64, -46, 
-31, -20, -18, -22, -27, -21, -4, 15, 25, 22, 1, -35, -43, -39, -20, 1, 
-4, -31, -54, -63, -54, -32, -22, -31, -31, -34, -42, -40, -24, -21, -17, -19, 
-29, -30, -27, -29, -27, -22, -24, -35, -44, -50, -42, -28, -11, 5, 21, 26, 
21, 13, 0, -8, -16, -26, -31, -34, -43, -50, -59, -63, -61, -54, -52, -46, 
-39, -37, -34, -30, -32, -34, -35, -39, -41, -38, -30, -19, -12, -12, -15, -9, 
-2, 3, 9, 15, 11, 11, 19, 30, 41, 49, 45, 46, 50, 49, 44, 31, 
21, 20, 25, 26, 20, 6, -7, -11, -4, 7, 18, 39, 47, 49, 51, 55, 
57, 50, 38, 30, 32, 36, 27, 13, 0, 0, 10, 16, 16, 14, 9, 12, 
26, 37, 35, 28, 21, 23, 33, 34, 28, 29, 33, 37, 42, 37, 27, 19, 
14, 12, 11, 3, -3, 0, 7, 15, 35, 50, 63, 76, 91, 103, 111, 110, 
109, 109, 110, 109, 109, 109, 108, 109, 103, 61, 31, 5, -19, -33, -34, -35, 
-35, -32, -26, -17, 11, 26, 39, 62, 87, 100, 101, 101, 98, 86, 68, 42, 
23, 0, -25, -43, -49, -56, -63, -67, -64, -47, -17, 27, 45, 69, 89, 92, 
91, 89, 65, 28, 5, -11, -26, -31, -38, -45, -48, -47, -37, -28, -21, -17, 
-25, -49, -63, -73, -77, -65, -33, 17, 30, 23, 0, -32, -62, -86, -79, -54, 
-25, -4, 9, 6, -3, -17, -31, -31, -12, 20, 62, 77, 75, 76, 42, 4, 
-13, -20, -31, -38, -44, -59, -77, -93, -98, -83, -58, -18, 26, 51, 44, -8, 
-45, -53, -26, 8, 35, 35, 20, -3, -32, -64, -86, -62, -14, 29, 39, 17, 
-27, -43, -42, -28, -7, 31, 41, 33, 14, -8, -32, -75, -93, -95, -92, -86, 
-77, -82, -92, -89, -70, -47, -26, -12, -6, -1, 14, 30, 25, 22, 19, 14, 
14, 12, 0, -3, -13, -33, -51, -60, -51, -32, -19, -16, -14, -20, -19, -1, 
24, 43, 56, 52, 34, 11, -11, -29, -31, -16, -3, -4, -16, -31, -48, -38, 
-16, -7, -9, -5, -7, -4, 5, 2, -9, -9, -11, -10, -3, -13, -42, -72, 
-83, -86, -79, -85, -103, -99, -100, -93, -64, -44, -42, -31, -11, 11, 24, 15, 
-10, 2, 23, 35, 37, 14, -7, -15, -17, -26, -44, -72, -80, -74, -57, -45, 
-44, -49, -47, -35, -11, 9, 13, 11, 9, 8, 18, 24, 1, -9, -5, -2, 
1, 5, -13, -22, -20, -17, -13, -12, -13, 0, 16, 21, 20, 6, -9, -8, 
6, 8, 1, -10, -28, -36, -30, -29, -28, -26, -28, -21, -5, -3, -20, -29, 
-32, -17, 12, 35, 46, 46, 41, 42, 47, 38, 26, 16, 12, 24, 39, 42, 
33, 25, 23, 30, 47, 67, 71, 75, 77, 74, 70, 64, 56, 55, 57, 56, 
47, 37, 24, 18, 19, 20, 26, 42, 65, 93, 113, 115, 115, 115, 114, 114, 
113, 114, 113, 112, 112, 110, 109, 109, 107, 108, 104, 95, 66, 36, 9, -7, 
-21, -32, -36, -36, -36, -34, -33, -34, -31, -32, -32, -23, -11, 5, 6, -1, 
-3, 0, 1, 6, 8, 11, 25, 51, 90, 97, 95, 94, 94, 88, 88, 94, 
85, 59, 32, 7, -25, -36, -52, -72, -80, -78, -72, -62, -57, -57, -57, -64, 
-62, -51, -40, -33, -25, -23, -35, -43, -49, -55, -53, -44, -27, -15, -20, -34, 
-45, -36, -12, 21, 52, 70, 70, 59, 46, 36, 26, 18, 9, -8, -25, -40, 
-48, -43, -55, -73, -72, -67, -63, -40, -28, -8, 4, -11, -30, -33, -47, -50, 
-32, -14, -7, -22, -55, -77, -77, -81, -71, -48, -44, -47, -47, -62, -61, -59, 
-61, -43, -17, -12, -16, -21, -32, -43, -49, -43, -31, -26, -32, -44, -61, -64, 
-62, -66, -66, -53, -28, -18, -17, -21, -15, -4, -4, -1, 4, 9, 21, 22, 
5, 0, 5, 3, -5, -20, -28, -20, -12, -21, -27, -22, -15, -3, 0, -13, 
-28, -36, -41, -37, -34, -41, -46, -43, -47, -48, -44, -56, -66, -71, -69, -51, 
-28, -10, -5, -1, -1, -2, -8, -25, -41, -55, -64, -60, -39, -34, -39, -47, 
-50, -42, -26, -26, -25, -15, -2, 10, 10, -6, -18, -16, -12, -1, 10, 22, 
31, 32, 23, 7, 5, 2, -4, -8, -8, -6, -6, -11, -14, -14, -7, 1, 
7, 10, 11, 11, 10, 9, 4, 7, 19, 29, 29, 25, 21, 21, 20, 16, 
19, 27, 39, 55, 68, 61, 53, 50, 49, 51, 50, 34, 24, 18, 11, 9, 
-2, -13, -18, -21, -18, -8, -7, -20, -29, -31, -28, -6, 4, 3, 4, 4, 
5, 23, 28, 32, 39, 39, 40, 79, 104, 111, 108, 108, 110, 110, 109, 109, 
108, 106, 105, 105, 104, 108, 109, 89, 57, 53, 52, 53, 50, 34, 28, 25, 
21, 17, 13, 15, 19, 24, 30, 35, 41, 50, 46, 35, 24, 11, -12, -21, 
-24, -20, -6, 8, 12, 17, 24, 26, 24, 18, 18, 30, 44, 50, 45, 26, 
8, -12, -32, -48, -57, -58, -55, -49, -44, -42, -38, -31, -25, -6, 22, 45, 
63, 59, 44, 29, 17, 8, 5, 4, 1, -8, -33, -65, -85, -87, -87, -74, 
-51, -31, -20, -14, -12, 3, 39, 79, 80, 76, 77, 78, 54, -1, -19, -28, 
-28, -19, -9, -10, -15, -27, -34, -23, 18, 36, 44, 52, 53, 42, 12, -3, 
-13, -26, -41, -37, -14, 4, 4, -26, -75, -100, -96, -99, -100, -71, -7, -4, 
-18, -34, -47, -49, -36, -14, 12, 28, 23, -5, -58, -72, -78, -83, -83, -76, 
-74, -67, -62, -69, -76, -72, -53, -14, 25, 40, 34, 25, 26, 28, 25, 14, 
7, 13, 6, -15, -36, -56, -69, -67, -72, -70, -49, -30, -20, -12, -9, -14, 
-16, -13, 0, 26, 51, 64, 67, 56, 32, 10, -1, -6, -6, 1, 1, -3, 
-4, -4, -28, -46, -55, -55, -45, -35, -39, -38, -40, -53, -68, -78, -87, -77, 
-60, -49, -41, -28, -22, -12, 0, -2, -15, -29, -27, -24, -28, -35, -38, -36, 
-31, -28, -31, -34, -33, -32, -28, -27, -28, -23, -8, 2, 15, 24, 24, 21, 
11, 4, 5, 12, 16, 8, -7, -21, -23, -18, -11, 0, 8, 17, 27, 32, 
31, 26, 24, 23, 24, 29, 33, 26, 20, 15, 7, 0, -1, 0, -1, -5, 
-8, -10, -15, -17, -15, -12, -8, 5, 8, 7, 6, 7, 14, 23, 21, 22, 
27, 28, 30, 31, 22, 15, 15, 14, 10, 17, 24, 26, 29, 35, 49, 69, 
92, 108, 117, 119, 117, 116, 115, 116, 118, 120, 118, 114, 100, 74, 54, 37, 
26, 21, 17, 15, 31, 46, 64, 92, 115, 120, 119, 119, 119, 118, 117, 118, 
117, 116, 116, 116, 116, 111, 92, 67, 49, 39, 35, 29, 24, 14, 1, -6, 
-5, 5, 7, 6, 6, 8, 11, 6, -2, -8, -19, -33, -44, -45, -45, -42, 
-38, -33, -11, 15, 41, 64, 76, 58, 31, 6, -9, -9, -3, 10, 14, 9, 
-6, -23, -38, -56, -70, -79, -76, -65, -36, -4, 19, 17, -6, -38, -82, -94, 
-81, -53, -24, -6, -31, -66, -89, -99, -105, -81, -50, -24, -3, 2, 3, 25, 
29, 24, 21, 15, 3, -9, -10, 7, 14, -2, -36, -61, -76, -73, -60, -50, 
-58, -80, -97, -95, -74, -27, 1, 17, 19, 9, -5, -11, -5, -3, -8, -16, 
-32, -75, -101, -113, -113, -110, -109, -102, -90, -78, -76, -82, -81, -81, -81, -69, 
-47, -26, -16, -25, -39, -47, -49, -45, -43, -48, -56, -61, -59, -55, -55, -50, 
-45, -39, -28, -1, 15, 32, 45, 41, 27, 38, 52, 57, 53, 40, 8, -11, 
-21, -26, -32, -44, -55, -56, -65, -72, -69, -57, -49, -33, -19, -10, -4, -18, 
-39, -50, -47, -40, -32, -26, -27, -26, -25, -32, -44, -54, -61, -49, -25, -10, 
-4, -2, -4, -2, 6, 9, 6, 6, 7, 9, 6, -25, -53, -68, -78, -84, 
-81, -67, -55, -45, -43, -39, -29, -11, 8, 27, 33, 41, 60, 65, 71, 76, 
77, 75, 56, 42, 32, 26, 25, 19, 5, -5, -8, -6, -1, 0, -4, -4, 
-2, 2, 7, 0, -14, -19, -11, -1, 4, -8, -25, -32, -31, -29, -16, -8, 
-4, 3, 9, 10, 18, 21, 14, 15, 25, 35, 43, 46, 38, 29, 27, 24, 
24, 22, 12, 4, 1, -10, -12, -10, -13, -14, -6, -3, 0, 3, 2, 7, 
28, 37, 47, 59, 60, 58, 69, 77, 93, 107, 108, 107, 106, 106, 107, 107, 
108, 107, 108, 107, 106, 107, 108, 108, 107, 106, 101, 80, 33, 7, -18, -43, 
-61, -67, -66, -66, -64, -63, -60, -52, -41, -28, -4, 16, 29, 53, 73, 81, 
78, 70, 63, 51, 45, 46, 49, 46, 34, 14, 11, 18, 29, 37, 37, 28, 
19, 14, 14, 12, -4, -22, -39, -57, -75, -81, -76, -77, -76, -73, -68, -42, 
-14, 19, 47, 63, 63, 43, 26, 14, 12, 14, 12, 14, 9, -2, -9, -13, 
-22, -23, -21, -15, -11, -14, -21, -22, -22, -15, 4, 47, 69, 76, 74, 61, 
39, 14, -1, -17, -25, -32, -43, -65, -82, -87, -72, -45, -10, 4, 4, -14, 
-38, -51, -46, -32, -21, -20, -24, -27, -35, -50, -64, -66, -52, -25, -17, -24, 
-41, -64, -86, -93, -83, -73, -62, -53, -51, -51, -63, -84, -93, -83, -53, -22, 
1, -4, -22, -29, -22, -8, 0, -10, -14, -3, -1, -6, -6, -7, -7, 0, 
-4, -9, -8, -12, -15, 3, 12, 21, 32, 28, 13, 9, 9, 6, 4, 0, 
-5, -3, -5, -11, -12, -10, -10, -15, -26, -34, -34, -32, -32, -35, -43, -49, 
-52, -55, -61, -75, -84, -82, -74, -56, -44, -42, -44, -42, -36, -34, -35, -44, 
-49, -43, -33, -32, -35, -47, -55, -51, -39, -41, -47, -53, -49, -22, -16, -23, 
-28, -30, -23, 2, 5, -3, -10, -14, -15, -1, -5, -25, -44, -56, -58, -43, 
-34, -37, -36, -32, -21, -11, -12, -15, -7, 7, 26, 33, 29, 22, 25, 34, 
30, 22, 8, -6, -8, 3, 9, 12, 6, -3, -9, -9, -9, -14, -23, -29, 
-25, -22, -25, -35, -51, -56, -36, -26, -27, -38, -47, -43, -15, 2, 7, 4, 
2, 23, 43, 59, 62, 55, 49, 62, 78, 86, 80, 64, 50, 57, 70, 79, 
86, 90, 96, 110, 121, 123, 125, 126, 123, 126, 127, 127, 127, 115, 104, 114, 
118, 113, 111, 98, 99, 112, 113, 110, 113, 104, 99, 101, 99, 96, 95, 85, 
81, 80, 77, 75, 76, 73, 72, 75, 73, 68, 60, 60, 65, 69, 72, 74, 
62, 49, 36, 20, 2, -12, -20, -29, -35, -41, -42, -29, -9, 24, 66, 93, 
98, 83, 49, 16, 2, 3, 20, 27, 17, -10, -46, -73, -81, -75, -54, -30, 
-25, -38, -62, -84, -88, -74, -45, 11, 33, 31, 13, -15, -37, -35, -25, -17, 
-17, -28, -54, -62, -60, -45, -18, 4, 16, 19, 22, 22, 15, 4, -7, -11, 
-7, 7, 24, 48, 52, 36, 9, -17, -42, -77, -88, -85, -78, -76, -76, -73, 
-70, -56, -33, -18, -16, -21, -33, -49, -72, -92, -98, -97, -97, -94, -94, -101, 
-110, -109, -97, -72, -46, -38, -47, -58, -63, -61, -51, -28, -14, -4, 1, 3, 
-1, -13, -20, -26, -27, -20, -15, -21, -28, -28, -21, -16, -9, -10, -15, -13, 
-8, -5, 0, -4, -9, -9, -14, -28, -29, -31, -30, -20, -18, -29, -19, -7, 
2, 14, 13, -2, -1, -4, -10, -7, -2, -5, -16, -37, -51, -44, -32, -34, 
-33, -33, -36, -32, -34, -34, -28, -26, -22, -15, -21, -25, -16, -8, -9, -9, 
-12, -15, -13, -18, -40, -47, -50, -44, -26, -10, 1, 7, 5, 0, 2, 5, 
11, 16, 16, 14, 14, 4, -4, -4, -1, 5, 13, 18, 18, 20, 24, 23, 
17, 7, 12, 20, 26, 31, 27, 19, 18, 24, 27, 30, 28, 21, 16, 8, 
-5, -9, -2, -3, -5, -3, 3, 11, 15, 22, 34, 41, 35, 14, -6, -19, 
-18, -14, -17, -28, -39, -44, -39, -31, -27, -25, -23, -16, -4, 4, 6, 11, 
14, 15, 23, 34, 39, 44, 52, 59, 77, 107, 109, 108, 109, 108, 109, 108, 
109, 110, 110, 109, 109, 105, 86, 66, 52, 33, 0, -18, -35, -43, -39, -30, 
-14, -3, 0, -1, 6, 27, 65, 83, 94, 102, 107, 106, 106, 101, 87, 69, 
48, 21, 8, -5, -15, -18, -19, -14, 4, 30, 56, 81, 101, 101, 100, 100, 
100, 96, 61, 25, -7, -33, -43, -27, -14, -7, -7, -24, -50, -75, -68, -40, 
-13, -9, -23, -41, -56, -68, -59, -22, 48, 67, 40, -14, -61, -82, -90, -75, 
-33, 12, 42, 59, 50, 32, 27, 36, 47, 62, 74, 80, 75, 54, 19, -30, 
-46, -48, -50, -67, -86, -92, -91, -93, -90, -90, -88, -46, 11, 46, 53, 37, 
11, 19, 37, 45, 43, 44, 37, 16, -11, -40, -66, -66, -44, -23, 1, 14, 
6, -7, -27, -63, -81, -65, -40, -27, -29, -37, -58, -83, -96, -93, -93, -79, 
-54, -53, -89, -90, -67, -36, -9, 9, 35, 51, 50, 39, 28, 13, 21, 33, 
31, 21, 16, 0, -31, -63, -80, -72, -38, 10, 16, 3, -13, -14, 5, 19, 
38, 57, 71, 79, 80, 67, 48, 38, 28, -9, -23, -21, -24, -35, -40, -34, 
-22, -21, -35, -39, -29, -20, -12, 1, 9, 18, 15, 3, -2, -3, -15, -35, 
-56, -65, -65, -62, -67, -75, -72, -53, -32, -25, -22, 1, 13, 29, 45, 41, 
29, 28, 23, 12, 4, 1, -2, -13, -25, -35, -43, -53, -59, -61, -64, -52, 
-37, -33, -27, -21, -15, 3, 20, 12, -12, -16, -9, 5, 6, -15, -21, -19, 
-12, 0, 5, -10, -8, -5, -10, -8, -2, -6, -2, 7, 9, 6, 0, -7, 
-10, -9, -11, -17, -32, -45, -48, -42, -32, -19, -5, -3, -1, -1, -8, -10, 
-3, -2, 0, 8, 11, 8, 3, 2, 10, 21, 30, 28, 13, 0, 2, 15, 
34, 43, 42, 35, 36, 43, 50, 50, 45, 40, 40, 34, 22, 16, 8, 0, 
0, 12, 22, 31, 40, 47, 56, 74, 92, 109, 115, 115, 116, 116, 116, 115, 
116, 116, 114, 112, 111, 112, 112, 113, 112, 112, 112, 111, 114, 108, 88, 66, 
42, 14, -11, -42, -55, -61, -61, -61, -62, -43, -24, -4, 13, 24, 40, 50, 
56, 56, 51, 47, 44, 40, 43, 57, 71, 81, 95, 98, 96, 95, 93, 78, 
58, 26, -12, -43, -65, -72, -64, -61, -64, -74, -86, -89, -80, -66, -57, -56, 
-68, -77, -75, -66, -51, -33, -22, -28, -41, -52, -47, -29, -4, 10, 11, -5, 
-20, -17, 0, 27, 54, 63, 47, -9, -40, -47, -33, -6, 20, 14, -16, -46, 
-68, -68, -31, -10, 2, -8, -46, -86, -111, -103, -75, -51, -49, -58, -87, -99, 
-89, -67, -36, 0, -3, -18, -35, -51, -54, -37, -37, -43, -55, -76, -89, -89, 
-97, -101, -93, -81, -47, -30, -28, -27, -29, -43, -73, -90, -95, -81, -59, -36, 
-36, -47, -63, -68, -52, -20, -3, 16, 26, 18, 4, -12, -11, 3, 23, 39, 
47, 31, 1, -25, -43, -48, -33, -23, -22, -20, -27, -47, -56, -57, -65, -61, 
-48, -35, -22, -17, -27, -37, -38, -30, -22, -16, -17, -19, -23, -27, -23, -26, 
-38, -45, -33, -28, -21, -11, -8, -12, -15, -19, -24, -24, -21, -17, -10, -11, 
-16, -18, -18, -19, -21, -24, -23, -16, 0, };
