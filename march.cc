#include "march.h"
#include "vector.h"
#include "biomes.h"
#include <cstdlib>
#include <array>
#include <map>

int edgeTable[256]={
0x0  , 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,
0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,
0x190, 0x99 , 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,
0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,
0x230, 0x339, 0x33 , 0x13a, 0x636, 0x73f, 0x435, 0x53c,
0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,
0x3a0, 0x2a9, 0x1a3, 0xaa , 0x7a6, 0x6af, 0x5a5, 0x4ac,
0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,
0x460, 0x569, 0x663, 0x76a, 0x66 , 0x16f, 0x265, 0x36c,
0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,
0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff , 0x3f5, 0x2fc,
0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,
0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55 , 0x15c,
0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,
0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0xcc ,
0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,
0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,
0xcc , 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,
0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,
0x15c, 0x55 , 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,
0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,
0x2fc, 0x3f5, 0xff , 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,
0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,
0x36c, 0x265, 0x16f, 0x66 , 0x76a, 0x663, 0x569, 0x460,
0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,
0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa , 0x1a3, 0x2a9, 0x3a0,
0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c,
0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x33 , 0x339, 0x230,
0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,
0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x99 , 0x190,
0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,
0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0   };
int triTable[256][16] =
{{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, -1},
{3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, -1},
{3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, -1},
{3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, -1},
{9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1},
{9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
{2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, -1},
{8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, -1},
{9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
{4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, -1},
{3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, -1},
{1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, -1},
{4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, -1},
{4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, -1},
{9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
{5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, -1},
{2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, -1},
{9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
{0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
{2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, -1},
{10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1},
{4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, -1},
{5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, -1},
{5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1},
{9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, -1},
{0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1},
{1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1},
{10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, -1},
{8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, -1},
{2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1},
{7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1},
{9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, -1},
{2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, -1},
{11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1},
{9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, -1},
{5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, -1},
{11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, -1},
{11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
{1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, -1},
{9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1},
{5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, -1},
{2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
{0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
{5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, -1},
{6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, -1},
{3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, -1},
{6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, -1},
{5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, -1},
{1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
{10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, -1},
{6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, -1},
{8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, -1},
{7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, -1},
{3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
{5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, -1},
{0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1},
{9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, -1},
{8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, -1},
{5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, -1},
{0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, -1},
{6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, -1},
{10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1},
{10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, -1},
{8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, -1},
{1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, -1},
{3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, -1},
{0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1},
{10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, -1},
{3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, -1},
{6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, -1},
{9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, -1},
{8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, -1},
{3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, -1},
{6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1},
{0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, -1},
{10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, -1},
{10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, -1},
{2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, -1},
{7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, -1},
{7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, -1},
{2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, -1},
{1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, -1},
{11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, -1},
{8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, -1},
{0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, -1},
{7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
{10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
{2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
{6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, -1},
{7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, -1},
{2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, -1},
{1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, -1},
{10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1},
{10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, -1},
{0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, -1},
{7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, -1},
{6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1},
{8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1},
{9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, -1},
{6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1},
{4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, -1},
{10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, -1},
{8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1},
{0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, -1},
{1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1},
{8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, -1},
{10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, -1},
{4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, -1},
{10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
{5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
{11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, -1},
{9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
{6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, -1},
{7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, -1},
{3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, -1},
{7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, -1},
{9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, -1},
{3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, -1},
{6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, -1},
{9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, -1},
{1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, -1},
{4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, -1},
{7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, -1},
{6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, -1},
{3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, -1},
{0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, -1},
{6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, -1},
{0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, -1},
{11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, -1},
{6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, -1},
{5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, -1},
{9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, -1},
{1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, -1},
{1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, -1},
{10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, -1},
{0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, -1},
{5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, -1},
{10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, -1},
{11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, -1},
{9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, -1},
{7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, -1},
{2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1},
{8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, -1},
{9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, -1},
{9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, -1},
{1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, -1},
{9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, -1},
{9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1},
{5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, -1},
{0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, -1},
{10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, -1},
{2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, -1},
{0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, -1},
{0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, -1},
{9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, -1},
{5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, -1},
{3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, -1},
{5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, -1},
{8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, -1},
{0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, -1},
{9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1},
{0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, -1},
{1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, -1},
{3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, -1},
{4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, -1},
{9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, -1},
{11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, -1},
{11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, -1},
{2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, -1},
{9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, -1},
{3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, -1},
{1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, -1},
{4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, -1},
{4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, -1},
{0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1},
{3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, -1},
{3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, -1},
{0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, -1},
{9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, -1},
{1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};
int cubeVerts[8][3] = {
  {0,0,0},
  {1,0,0},
  {1,1,0},
  {0,1,0},
  {0,0,1},
  {1,0,1},
  {1,1,1},
  {0,1,1}
};
int edgeIndex[12][2] = {
  {0,1},
  {1,2},
  {2,3},
  {3,0},
  {4,5},
  {5,6},
  {6,7},
  {7,4},
  {0,4},
  {1,5},
  {2,6},
  {3,7}
};

void marchingCubes(int dims[3], float *potential, int shift[3], int indexOffset, float *positions, unsigned int *faces, unsigned int &positionIndex, unsigned int &faceIndex) {
  positionIndex = 0;
  faceIndex = 0;

  int n = 0;
  float grid[8] = {0};
  int edges[12] = {0};
  int x[3] = {0};

  //March over the volume
  for(x[2]=0; x[2]<dims[2]-1; ++x[2], n+=dims[0])
  for(x[1]=0; x[1]<dims[1]-1; ++x[1], ++n)
  for(x[0]=0; x[0]<dims[0]-1; ++x[0], ++n) {
    //For each cell, compute cube mask
    int cube_index = 0;
    for(int i=0; i<8; ++i) {
      int *v = cubeVerts[i];
      float s = potential[
        (x[0]+v[0]) +
        (((x[2]+v[2])) * dims[0]) +
        ((x[1]+v[1]) * dims[0] * dims[1])
      ];

      grid[i] = s;
      cube_index |= (s > 0) ? 1 << i : 0;
    }
    //Compute vertices
    int edge_mask = edgeTable[cube_index];
    if(edge_mask == 0) {
      continue;
    }
    for(int i=0; i<12; ++i) {
      if((edge_mask & (1<<i)) == 0) {
        continue;
      }
      edges[i] = positionIndex / 3;
      int *e = edgeIndex[i];
      int *p0 = cubeVerts[e[0]];
      int *p1 = cubeVerts[e[1]];
      float a = grid[e[0]];
      float b = grid[e[1]];
      float d = a - b;
      float t = a / d;
      for(int j=0; j<3; ++j) {
        positions[positionIndex + j] = ((x[j] + p0[j]) + t * (p1[j] - p0[j])) + shift[j];
      }
      positionIndex += 3;
    }
    //Add faces
    int *f = triTable[cube_index];
    for(int i=0;f[i]!=-1;i+=3) {
      faces[faceIndex] = edges[f[i]] + indexOffset;
      faces[faceIndex + 1] = edges[f[i+1]] + indexOffset;
      faces[faceIndex + 2] = edges[f[i+2]] + indexOffset;
      faceIndex += 3;
    }
  }
}

/* void collideBoxEther(int dims[3], float *potential, int shift[3], float *positionSpec, bool &collided, bool &floored, bool &ceiled) {
  float positions[8 * 1024];
  unsigned int indices[8 * 1024];
  unsigned int numPositions;
  unsigned int numIndices;

  marchingCubes(dims, potential, shift, 0, positions, indices, numPositions, numIndices);

  std::vector<Tri> triangles;
  triangles.reserve(numIndices / 3);
  for (unsigned int i = 0; i < numIndices; i += 3) {
    Tri t(
      Vec(positions[indices[i + 0] * 3 + 0], positions[indices[i + 0] * 3 + 1], positions[indices[i + 0] * 3 + 2]),
      Vec(positions[indices[i + 1] * 3 + 0], positions[indices[i + 1] * 3 + 1], positions[indices[i + 1] * 3 + 2]),
      Vec(positions[indices[i + 2] * 3 + 0], positions[indices[i + 2] * 3 + 1], positions[indices[i + 2] * 3 + 2])
    );
    triangles.push_back(t);
  }

  Vec position(positionSpec[0], positionSpec[1], positionSpec[2]);

  collided = false;
  floored = false;
  ceiled = false;

  // horizontal
  {
    for (int dy = 1; dy <= 2; dy++) {
      // back-front
      Vec maxRestitutionVector;
      float maxRestitutionVectorSize = 0;
      for (int dx = -1; dx <= 1; dx++) {
        const Ray ray(Vec(position.x + dx * 0.5, position.y + 0.4 - 2.0 + dy, position.z), Vec(0, 0, 1));
        for (const Tri &triangle : triangles) {
          Vec intersectionVector;
          if (ray.intersectTriangle(triangle, intersectionVector)) {
            float restitutionVectorSize = intersectionVector.z - position.z;
            if (restitutionVectorSize > 0 && restitutionVectorSize <= 0.5 && restitutionVectorSize > maxRestitutionVectorSize) {
              maxRestitutionVector = Vec(0, 0, -(0.5 - restitutionVectorSize));
              maxRestitutionVectorSize = restitutionVectorSize;
            }
          }
        }
      }

      // front-back
      for (int dx = -1; dx <= 1; dx++) {
        const Ray ray(Vec(position.x + dx * 0.5, position.y + 0.4 - 2.0 + dy, position.z), Vec(0, 0, -1));
        for (const Tri &triangle : triangles) {
          Vec intersectionVector;
          if (ray.intersectTriangle(triangle, intersectionVector)) {
            float restitutionVectorSize = position.z - intersectionVector.z;
            if (restitutionVectorSize > 0 && restitutionVectorSize <= 0.5 && restitutionVectorSize > maxRestitutionVectorSize) {
              maxRestitutionVector = Vec(0, 0, 0.5 - restitutionVectorSize);
              maxRestitutionVectorSize = restitutionVectorSize;
            }
          }
        }
      }

      // left-right
      Vec maxRestitutionVector2;
      float maxRestitutionVectorSize2 = 0;
      for (int dz = -1; dz <= 1; dz++) {
        const Ray ray(Vec(position.x, position.y + 0.4 - 2.0 + dy, position.z + dz * 0.5), Vec(1, 0, 0));
        for (const Tri &triangle : triangles) {
          Vec intersectionVector;
          if (ray.intersectTriangle(triangle, intersectionVector)) {
            float restitutionVectorSize = intersectionVector.x - position.x;
            if (restitutionVectorSize > 0 && restitutionVectorSize <= 0.5 && restitutionVectorSize > maxRestitutionVectorSize2) {
              maxRestitutionVector2 = Vec(-(0.5 - restitutionVectorSize), 0, 0);
              maxRestitutionVectorSize2 = restitutionVectorSize;
            }
          }
        }
      }

      // right-left
      for (int dz = -1; dz <= 1; dz++) {
        const Ray ray(Vec(position.x, position.y + 0.4 - 2.0 + dy, position.z + dz * 0.5), Vec(-1, 0, 0));
        for (const Tri &triangle : triangles) {
          Vec intersectionVector;
          if (ray.intersectTriangle(triangle, intersectionVector)) {
            float restitutionVectorSize = position.x - intersectionVector.x;
            if (restitutionVectorSize > 0 && restitutionVectorSize <= 0.5 && restitutionVectorSize > maxRestitutionVectorSize2) {
              maxRestitutionVector2 = Vec(0.5 - restitutionVectorSize, 0, 0);
              maxRestitutionVectorSize2 = restitutionVectorSize;
            }
          }
        }
      }

      if (maxRestitutionVectorSize > 0.0) {
        position += maxRestitutionVector;
        collided = true;
        ceiled = true;
      }
      if (maxRestitutionVectorSize2 > 0.0) {
        position += maxRestitutionVector2;
        collided = true;
        ceiled = true;
      }
    }
  }
  // up
  {
    const Ray topLeftRay(Vec(position.x - 0.5, position.y + 0.4 - 1, position.z - 0.5), Vec(0, 1, 0));
    const Ray topRightRay(Vec(position.x + 0.5, position.y + 0.4 - 1, position.z - 0.5), Vec(0, 1, 0));
    const Ray bottomLeftRay(Vec(position.x - 0.5, position.y + 0.4 - 1, position.z + 0.5), Vec(0, 1, 0));
    const Ray bottomRightRay(Vec(position.x + 0.5, position.y + 0.4 - 1, position.z + 0.5), Vec(0, 1, 0));
    const Ray middleRay(Vec(position.x, position.y + 0.4, position.z), Vec(0, -1, 0));

    // find max restitution vector
    Vec maxRestitutionVector;
    float maxRestitutionVectorSize = 0;
    for (const Tri &triangle : triangles) {
      Vec intersectionVector;
      if (topLeftRay.intersectTriangle(triangle, intersectionVector)) {
        const float restitutionVectorSize = (position.y + 0.4) - intersectionVector.y;
        if (restitutionVectorSize < 1) {
          if (restitutionVectorSize > maxRestitutionVectorSize) {
            maxRestitutionVector = Vec(0, -restitutionVectorSize, 0);
            maxRestitutionVectorSize = restitutionVectorSize;
          }
        }
      }
      if (topRightRay.intersectTriangle(triangle, intersectionVector)) {
        const float restitutionVectorSize = (position.y + 0.4) - intersectionVector.y;
        if (restitutionVectorSize < 1) {
          if (restitutionVectorSize > maxRestitutionVectorSize) {
            maxRestitutionVector = Vec(0, -restitutionVectorSize, 0);
            maxRestitutionVectorSize = restitutionVectorSize;
          }
        }
      }
      if (bottomLeftRay.intersectTriangle(triangle, intersectionVector)) {
        const float restitutionVectorSize = (position.y + 0.4) - intersectionVector.y;
        if (restitutionVectorSize < 1) {
          if (restitutionVectorSize > maxRestitutionVectorSize) {
            maxRestitutionVector = Vec(0, -restitutionVectorSize, 0);
            maxRestitutionVectorSize = restitutionVectorSize;
          }
        }
      }
      if (bottomRightRay.intersectTriangle(triangle, intersectionVector)) {
        const float restitutionVectorSize = (position.y + 0.4) - intersectionVector.y;
        if (restitutionVectorSize < 1) {
          if (restitutionVectorSize > maxRestitutionVectorSize) {
            maxRestitutionVector = Vec(0, -restitutionVectorSize, 0);
            maxRestitutionVectorSize = restitutionVectorSize;
          }
        }
      }
      if (middleRay.intersectTriangle(triangle, intersectionVector)) {
        const float restitutionVectorSize = (position.y + 0.4) - intersectionVector.y;
        if (restitutionVectorSize < 1) {
          if (restitutionVectorSize > maxRestitutionVectorSize) {
            maxRestitutionVector = Vec(0, -restitutionVectorSize, 0);
            maxRestitutionVectorSize = restitutionVectorSize;
          }
        }
      }
    }
    if (maxRestitutionVectorSize > 0.0) {
      collided = true;
      ceiled = true;

      position += maxRestitutionVector;
    }
  }
  // down
  {
    const Ray topLeftRay(Vec(position.x - 0.5, position.y + 0.4 - 1, position.z - 0.5), Vec(0, -1, 0));
    const Ray topRightRay(Vec(position.x + 0.5, position.y + 0.4 - 1, position.z - 0.5), Vec(0, -1, 0));
    const Ray bottomLeftRay(Vec(position.x - 0.5, position.y + 0.4 - 1, position.z + 0.5), Vec(0, -1, 0));
    const Ray bottomRightRay(Vec(position.x + 0.5, position.y + 0.4 - 1, position.z + 0.5), Vec(0, -1, 0));
    const Ray middleRay(Vec(position.x, position.y + 0.4, position.z), Vec(0, -1, 0));

    // find max restitution vector
    Vec maxRestitutionVector;
    float maxRestitutionVectorSize = 0;
    for (const Tri &triangle : triangles) {
      Vec intersectionVector;
      if (topLeftRay.intersectTriangle(triangle, intersectionVector)) {
        const float restitutionVectorSize = intersectionVector.y - (position.y + 0.4 - 2);
        if (restitutionVectorSize < 1) {
          if (restitutionVectorSize > maxRestitutionVectorSize) {
            maxRestitutionVector = Vec(0, restitutionVectorSize, 0);
            maxRestitutionVectorSize = restitutionVectorSize;
          }
        }
      }
      if (topRightRay.intersectTriangle(triangle, intersectionVector)) {
        const float restitutionVectorSize = intersectionVector.y - (position.y + 0.4 - 2);
        if (restitutionVectorSize < 1) {
          if (restitutionVectorSize > maxRestitutionVectorSize) {
            maxRestitutionVector = Vec(0, restitutionVectorSize, 0);
            maxRestitutionVectorSize = restitutionVectorSize;
          }
        }
      }
      if (bottomLeftRay.intersectTriangle(triangle, intersectionVector)) {
        const float restitutionVectorSize = intersectionVector.y - (position.y + 0.4 - 2);
        if (restitutionVectorSize < 1) {
          if (restitutionVectorSize > maxRestitutionVectorSize) {
            maxRestitutionVector = Vec(0, restitutionVectorSize, 0);
            maxRestitutionVectorSize = restitutionVectorSize;
          }
        }
      }
      if (bottomRightRay.intersectTriangle(triangle, intersectionVector)) {
        const float restitutionVectorSize = intersectionVector.y - (position.y + 0.4 - 2);
        if (restitutionVectorSize < 1) {
          if (restitutionVectorSize > maxRestitutionVectorSize) {
            maxRestitutionVector = Vec(0, restitutionVectorSize, 0);
            maxRestitutionVectorSize = restitutionVectorSize;
          }
        }
      }
      if (middleRay.intersectTriangle(triangle, intersectionVector)) {
        const float restitutionVectorSize = intersectionVector.y - (middleRay.origin.y + 0.4 - 2);
        if (restitutionVectorSize < 1) {
          if (restitutionVectorSize > maxRestitutionVectorSize) {
            maxRestitutionVector = Vec(0, restitutionVectorSize, 0);
            maxRestitutionVectorSize = restitutionVectorSize;
          }
        }
      }
    }
    if (maxRestitutionVectorSize > 0.0) {
      collided = true;
      floored = true;

      position += maxRestitutionVector;
    }
  }

  if (collided) {
    positionSpec[0] = position.x;
    positionSpec[1] = position.y;
    positionSpec[2] = position.z;
  }
} */

inline int getPotentialIndex(int x, int y, int z, int dimsP3[3]) {
  return (x + 1) +
    (z + 1) * dimsP3[0] +
    (y + 1) * dimsP3[0] * dimsP3[1];
}

inline void setLights(const std::array<float, 3> &v, unsigned char *field, unsigned char *lights, unsigned int lightIndex, int dims[3]) {
  int x = (int)std::floor(v[0]);
  int y = (int)std::floor(v[1]);
  int z = (int)std::floor(v[2]);
  int index = x +
    (z * dims[0]) +
    (y * dims[0] * dims[1]);
  lights[lightIndex] = field[index];
}
inline void setUvs(const std::tuple<float, float> &color, float *uvs, unsigned int uvIndex) {
  uvs[uvIndex] = std::get<0>(color);
  uvs[uvIndex+1] = std::get<1>(color);
}
inline unsigned char getAo(int x, int y, int z, std::function<float(int, int, int)> getPotential) {
  unsigned char numOpens = 0;
  for(int dy = -1; dy <= 1; dy++) {
    int ay = y + dy;
    for(int dz = -1; dz <= 1; dz++) {
      int az = z + dz;
      for(int dx = -1; dx <= 1; dx++) {
        int ax = x + dx;
        float potential = getPotential(ax, ay, az);
        if (potential > 0) {
          numOpens++;
        }
      }
    }
  }
  return numOpens;
}

template<bool transparent>
inline void marchingCubesRaw(int dims[3], std::function<float(int, int, int)> getPotential, std::function<unsigned char(int)> getBiome, unsigned char *heightfield, unsigned char *lightfield, float shift[3], float scale[3], float yLimit, float *positions, float *normals, float *uvs, float *barycentrics, unsigned char *aos, unsigned int &positionIndex, unsigned int &normalIndex, unsigned int &uvIndex, unsigned int &barycentricIndex, unsigned int &aoIndex, unsigned char *skyLights, unsigned char *torchLights, unsigned int &lightIndex) {
  int n = 0;
  float grid[8] = {0};
  std::array<std::array<float, 3>, 12> edges;
  int x[3] = {0};

  //March over the volume
  for(x[2]=0; x[2]<dims[2]-1; ++x[2], n+=dims[0])
  for(x[1]=0; x[1]<dims[1]-1; ++x[1], ++n)
  for(x[0]=0; x[0]<dims[0]-1; ++x[0], ++n) {
    //For each cell, compute cube mask
    int cube_index = 0;
    for(int i=0; i<8; ++i) {
      int *v = cubeVerts[i];
      float s = getPotential(x[0]+v[0], x[1]+v[1], x[2]+v[2]);
      grid[i] = s;
      cube_index |= (s > 0) ? 1 << i : 0;
    }
    //Compute vertices
    int edge_mask = edgeTable[cube_index];
    if(edge_mask == 0) {
      continue;
    }
    for(int i=0; i<12; ++i) {
      if((edge_mask & (1<<i)) == 0) {
        continue;
      }
      int *e = edgeIndex[i];
      int *p0 = cubeVerts[e[0]];
      int *p1 = cubeVerts[e[1]];
      float a = grid[e[0]];
      float b = grid[e[1]];
      float d = a - b;
      float t = a / d;
      std::array<float, 3> &v = edges[i];
      for(int j=0; j<3; ++j) {
        v[j] = (x[j] + p0[j]) + t * (p1[j] - p0[j]);
      }
    }
    //Add faces
    int *f = triTable[cube_index];
    for(int i=0;f[i]!=-1;i+=3) {
      std::array<float, 3> &a = edges[f[i]];
      std::array<float, 3> &b = edges[f[i+2]];
      std::array<float, 3> &c = edges[f[i+1]];

      if (!transparent) {
        setLights(a, heightfield, skyLights, lightIndex, dims);
        setLights(a, lightfield, torchLights, lightIndex, dims);
        lightIndex++;
        setLights(b, heightfield, skyLights, lightIndex, dims);
        setLights(b, lightfield, torchLights, lightIndex, dims);
        lightIndex++;
        setLights(c, heightfield, skyLights, lightIndex, dims);
        setLights(c, lightfield, torchLights, lightIndex, dims);
        lightIndex++;
      } else {
        constexpr float skyLight = 8.0f;
        constexpr float torchLight = 0.0f;
        skyLights[lightIndex] = skyLight;
        torchLights[lightIndex] = torchLight;
        lightIndex++;
        skyLights[lightIndex] = skyLight;
        torchLights[lightIndex] = torchLight;
        lightIndex++;
        skyLights[lightIndex] = skyLight;
        torchLights[lightIndex] = torchLight;
        lightIndex++;
      }
      {
        Tri tri(
          Vec(a[0], a[1], a[2]),
          Vec(b[0], b[1], b[2]),
          Vec(c[0], c[1], c[2])
        );
        Vec center = tri.midpoint();
        // Vec normal = tri.normal();
        // Vec point = center;// - normal;
        int x = (int)center.x;
        int y = (int)center.y;
        int z = (int)center.z;
        // Vec center(std::min({a[0], b[0], c[0]}), std::min({a[1], b[1], c[1]}), std::min({a[2], b[2], c[2]}));
        int biomeIndex = x +
          (z * dims[0]);
        int biome = (int)getBiome(biomeIndex);
        const std::tuple<float, float> &color = groundColors[biome];

        setUvs(color, uvs, uvIndex);
        // setUvs(a, biomes, groundNormals, uvs, uvIndex, dims);
        uvIndex += 2;
        setUvs(color, uvs, uvIndex);
        // setUvs(b, biomes, groundNormals, uvs, uvIndex, dims);
        uvIndex += 2;
        setUvs(color, uvs, uvIndex);
        // setUvs(c, biomes, groundNormals, uvs, uvIndex, dims);
        uvIndex += 2;
      }
      {
        aos[aoIndex++] = getAo(
          (int)std::round(a[0]),
          (int)std::round(a[1]),
          (int)std::round(a[2]),
          getPotential
        );
        aos[aoIndex++] = getAo(
          (int)std::round(b[0]),
          (int)std::round(b[1]),
          (int)std::round(b[2]),
          getPotential
        );
        aos[aoIndex++] = getAo(
          (int)std::round(c[0]),
          (int)std::round(c[1]),
          (int)std::round(c[2]),
          getPotential
        );
      }
    }
    for (int i = 0; i < 12; i++) {
      std::array<float, 3> &v = edges[i];
      for(int j=0; j<3; ++j) {
        v[j] = (v[j] + shift[j]) * scale[j];
      }
    }
    for(int i=0;f[i]!=-1;i+=3) {
      std::array<float, 3> &a = edges[f[i]];
      std::array<float, 3> &b = edges[f[i+2]];
      std::array<float, 3> &c = edges[f[i+1]];

      if (transparent) {
        a[1] = std::min(a[1], yLimit);
        b[1] = std::min(b[1], yLimit);
        c[1] = std::min(c[1], yLimit);
      }

      positions[positionIndex++] = a[0];
      positions[positionIndex++] = a[1];
      positions[positionIndex++] = a[2];
      positions[positionIndex++] = b[0];
      positions[positionIndex++] = b[1];
      positions[positionIndex++] = b[2];
      positions[positionIndex++] = c[0];
      positions[positionIndex++] = c[1];
      positions[positionIndex++] = c[2];

      Tri tri{
        Vec{a[0], a[1], a[2]},
        Vec{b[0], b[1], b[2]},
        Vec{c[0], c[1], c[2]},
      };
      Vec normal = tri.normal();
      normals[normalIndex++] = normal.x;
      normals[normalIndex++] = normal.y;
      normals[normalIndex++] = normal.z;
      normals[normalIndex++] = normal.x;
      normals[normalIndex++] = normal.y;
      normals[normalIndex++] = normal.z;
      normals[normalIndex++] = normal.x;
      normals[normalIndex++] = normal.y;
      normals[normalIndex++] = normal.z;

      barycentrics[barycentricIndex++] = 1;
      barycentrics[barycentricIndex++] = 0;
      barycentrics[barycentricIndex++] = 0;
      barycentrics[barycentricIndex++] = 0;
      barycentrics[barycentricIndex++] = 1;
      barycentrics[barycentricIndex++] = 0;
      barycentrics[barycentricIndex++] = 0;
      barycentrics[barycentricIndex++] = 0;
      barycentrics[barycentricIndex++] = 1;
    }
  }
}

void marchingCubes2(int dims[3], float *potential, unsigned char *biomes, unsigned char *heightfield, unsigned char *lightfield, float shift[3], float scale[3], float *positions, float *normals, float *uvs, float *barycentrics, unsigned char *aos, unsigned int &positionIndex, unsigned int &normalIndex, unsigned int &uvIndex, unsigned int &barycentricIndex, unsigned int &aoIndex, unsigned char *skyLights, unsigned char *torchLights, unsigned int &numOpaquePositions, unsigned int &numTransparentPositions) {
  positionIndex = 0;
  normalIndex = 0;
  uvIndex = 0;
  barycentricIndex = 0;
  aoIndex = 0;
  numOpaquePositions = 0;
  numTransparentPositions = 0;
  unsigned int lightIndex = 0;

  int dimsP1[3] = {
    dims[0]+1,
    dims[1]+1,
    dims[2]+1,
  };
  int dimsP3[3] = {
    dims[0]+3,
    dims[1]+3,
    dims[2]+3,
  };

  marchingCubesRaw<false>(dimsP1, [&](int x, int y, int z) -> float {
    int index = getPotentialIndex(x, y, z, dimsP3);
    return potential[index];
  }, [&](int index) -> unsigned char {
    return biomes[index];
  }, heightfield, lightfield, shift, scale, 0.0f, positions, normals, uvs, barycentrics, aos, positionIndex, normalIndex, uvIndex, barycentricIndex, aoIndex, skyLights, torchLights, lightIndex);
  numOpaquePositions = positionIndex;

  marchingCubesRaw<true>(dimsP1, [&](int x, int y, int z) -> float {
    int ay = shift[1] + y;
    if (ay < 5) {
      int index = getPotentialIndex(x, y, z, dimsP3);
      return -potential[index];
    } else {
      return -0.5f;
    }
  }, [&](int index) -> unsigned char {
    unsigned char biome = biomes[index];
    switch (biome) {
      case (unsigned char)BIOME::biOcean:
      case (unsigned char)BIOME::biRiver:
        return (unsigned char)BIOME::waterOcean;
      case (unsigned char)BIOME::biFrozenOcean:
      case (unsigned char)BIOME::biFrozenRiver:
        return (unsigned char)BIOME::waterOceanFrozen;
      default: return (unsigned char)BIOME::waterOcean;
    }
  }, heightfield, lightfield, shift, scale, 4.0f, positions, normals, uvs, barycentrics, aos, positionIndex, normalIndex, uvIndex, barycentricIndex, aoIndex, skyLights, torchLights, lightIndex);
  numTransparentPositions = positionIndex - numOpaquePositions;
}