#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <chrono>
#include <iostream>
#include "catch.hpp"
#include "geometry.hpp"

using namespace std;

TEST_CASE("Testing EuclideanDistance()")
{
    Point a = {2, 3};
    Point b = {3, 3};

    Point c(7, 8);
    Point d(13, 4000);

    REQUIRE(getEuclideanDistance(a, b) == 1);
    REQUIRE(getEuclideanDistance(d, c) ==
            Approx(3992.004509).epsilon(0.0001));  // Epsilon is tolerance
}

TEST_CASE("Testing Segment::getLength()")
{
    Point c(7, 8);
    Point d(13, 4000);

    Segment line1(c, d);

    REQUIRE(line1.getLength() == Approx(3992.004509).epsilon(0.0001));  // Epsilon is tolerance
}

TEST_CASE("Testing compareSegments()")
{
    Point a1;
    Point a2(2, 0);

    Point b1;
    Point b2(3, 0);

    Segment begin(a1, a2);
    Segment other(b1, b2);

    Segment ans = compareSegments(begin, other);

    REQUIRE(ans.getLength() == other.getLength());
}

TEST_CASE("Testing generateDiagonals()")
{
    std::vector<Point> square   = {{7, 4}, {29, 4}, {29, 26}, {7, 26}};
    std::vector<Point> pentagon = {{7, 4}, {29, 4}, {29, 26}, {22, 30}, {7, 26}};

    vector<Segment> diagonals1 = generateDiagonals(pentagon);
    vector<Segment> answer1    = {{{7, 4}, {29, 26}},
                               {{7, 4}, {22, 30}},
                               {{29, 4}, {22, 30}},
                               {{29, 4}, {7, 26}},
                               {{29, 26}, {7, 26}}};

    vector<Segment> diagonals2 = generateDiagonals(square);
    vector<Segment> answer2    = {{{7, 4}, {29, 26}}, {{29, 4}, {7, 26}}};

    REQUIRE(diagonals1 == answer1);
    REQUIRE(diagonals2 == answer2);
}

TEST_CASE("Checking intersection methods")
{
    vector<Point> pentagon    = {{7, 4}, {29, 4}, {29, 26}, {22, 30}, {7, 26}};
    vector<Segment> edges     = generateEdges(pentagon);
    vector<Segment> diagonals = generateDiagonals(pentagon);

    Segment dummy = {{0, 5}, {0, 10}};

    Segment single1 = {{-1, -2}, {3, 2}};
    Segment single2 = {{-3, -2}, {1, -2}};

    REQUIRE(doIntersect(single1, single2) == true);
    REQUIRE(isGoodDiagonal(edges.front(), diagonals, pentagon) == false);
    REQUIRE(isGoodDiagonal(dummy, diagonals, pentagon) == false);
}

TEST_CASE("Testing generateEdges()")
{
    std::vector<Point> input1 = {{0, 20}, {40, 0}, {40, 20}, {70, 50}, {50, 70}, {30, 50}, {0, 50}};
    vector<Segment> testing   = generateEdges(input1);
    vector<Segment> answer    = {{{0, 20}, {40, 0}},   {{40, 0}, {40, 20}},  {{40, 20}, {70, 50}},
                              {{70, 50}, {50, 70}}, {{50, 70}, {30, 50}}, {{30, 50}, {0, 50}},
                              {{0, 50}, {0, 20}}};

    REQUIRE(testing == answer);
}

TEST_CASE("Testing to see of the point is inside or outside the polygon")
{
    Point test2(10, 7);
    Point test1(0, 0);
    vector<Point> pentagon = {{7, 4}, {29, 4}, {29, 26}, {22, 30}, {7, 26}};
    vector<Point> square   = {{7, 4}, {29, 4}, {29, 26}, {7, 26}};

    bool ans1 = pointIsOutside(test2, square);
    bool ans2 = pointIsOutside(test1, pentagon);

    REQUIRE(ans2 == true);
    REQUIRE(ans1 == false);
}

TEST_CASE("Integration test")  // TODO change pow to **
{
    std::vector<Point> input1 = {{0, 20},  {40, 0},  {40, 20}, {70, 50},
                                 {50, 70}, {30, 50}, {0, 50}};           // 7
    std::vector<Point> input2 = {{0, 2017}, {-2017, -2017}, {2017, 0}};  // 3

    // https://www.mathsisfun.com/geometry/polygons-interactive.html
    std::vector<Point> input3 = {{3, 0}, {3, 3}, {8, 5}, {2, 6}, {1, 4}};  // 5
    // (2.00,6.00), (1.00,4.00), (3.00,0.00), (3.00,3.00), (8.00,5.00)

    std::vector<Point> input4 = {{4, 8}, {2, 6}, {1, 4}, {1, 2}, {2, 0},
                                 {4, 1}, {5, 0}, {7, 4}, {7, 6}};
    // 4.00,8.00), (2.00,6.00), (1.00,4.00), (1.00,2.00), (2.00,0.00),
    // (4.00,1.00), (5.00,0.00), (7.00,4.00), (7.00,6.00)

    std::vector<Point> input5 = {{6, 5}, {4, 5}, {2, 5}, {1, 4}, {1, 3}, {1, 1}, {2, 0},
                                 {3, 0}, {5, 0}, {7, 0}, {9, 2}, {6, 3}, {8, 5}};  // 13

    std::vector<Point> input6 = {
        {18467, 31115}, {17421, 23655}, {16827, 19072}, {18756, 26418},
        {17035, 18007}, {19169, 22704}, {23805, 30836}, {22190, 27624},
        {25667, 31107}, {23281, 26924}, {26962, 31673}, {26299, 30191},
        {26500, 29658}, {22648, 24350}, {28145, 28745}, {24626, 24648},
        {22929, 22813}, {27644, 24946}, {31322, 27753}, {24464, 22386},
        {32662, 27506}, {28253, 24221}, {32391, 23986}, {31101, 23199},
        {24393, 19668}, {27529, 18762}, {20037, 16413}, {28703, 15457},
        {32439, 14893}, {18716, 15574}, {32757, 13030}, {30333, 10383},
        {23811, 12287}, {27446, 10291}, {30106, 6483},  {17673, 14945},
        {25547, 6422},  {29358, 2306},  {19895, 12052}, {24370, 4596},
        {26308, 467},   {24084, 53},    {19629, 8281},  {21538, 2421},
        {21726, 1150},  {19912, 3430},  {19718, 4031},  {19954, 1999},
        {19264, 3602},  {16944, 3728},  {16541, 9514},  {15890, 9374},
        {16118, 14310}, {15724, 9930},  {12623, 4734},  {8723, 900},
        {14604, 13290}, {8942, 4041},   {9961, 6270},   {7376, 3788},
        {6334, 4639},   {5705, 5021},   {4827, 5097},   {778, 1655},
        {4966, 6900},   {9894, 11337},  {7711, 9758},   {3035, 6359},
        {41, 4833},     {2082, 6617},   {491, 5829},    {4664, 8909},
        {3902, 9161},   {6729, 11020},  {11478, 13977}, {1869, 13966},
        {11942, 15573}, {5436, 16512},  {153, 18636},   {5537, 17807},
        {6868, 18588},  {1842, 20537},  {288, 21548},   {12316, 17410},
        {292, 22355},   {14771, 16941}, {3548, 24484},  {2995, 26777},
        {13931, 18127}, {5447, 27350},  {11538, 21724}, {11323, 22483},
        {9040, 27595},  {12382, 24767}, {9741, 32591},  {11840, 27938},
        {12859, 29168}, {15350, 24021}, {15006, 27348}, {15141, 32209}};  // 100 points

    std::vector<Point> input7 = {
        {16827, 32609}, {16944, 27088}, {18588, 27756}, {19912, 27157}, {21538, 30932},
        {17035, 18538}, {24464, 30303}, {21724, 25734}, {23199, 28022}, {23805, 28476},
        {24626, 28617}, {22929, 25721}, {19169, 20600}, {16541, 17189}, {27753, 31185},
        {22190, 23844}, {29358, 31556}, {30106, 31998}, {19718, 20580}, {31115, 31329},
        {31107, 31316}, {23811, 24179}, {20037, 20328}, {30333, 29657}, {32439, 31426},
        {24648, 24372}, {29658, 28692}, {30836, 29510}, {32391, 30523}, {27595, 26292},
        {19895, 19796}, {24767, 23195}, {23986, 22549}, {22704, 21425}, {27350, 24488},
        {26299, 23622}, {27506, 23646}, {26962, 22798}, {22483, 20159}, {24393, 21003},
        {26924, 21718}, {32662, 24272}, {24350, 20024}, {25667, 20472}, {19629, 17861},
        {24946, 19558}, {30191, 20671}, {32591, 20222}, {28253, 19156}, {32757, 20055},
        {27529, 18875}, {28745, 18060}, {31322, 18190}, {26500, 17451}, {26777, 16279},
        {25547, 16202}, {21726, 15281}, {24484, 14018}, {24084, 13401}, {28145, 11008},
        {27624, 11173}, {18756, 15255}, {31673, 7441},  {26308, 10285}, {26418, 10202},
        {28703, 6038},  {21548, 12044}, {32209, 1832},  {31101, 2510},  {29168, 4144},
        {24021, 8313},  {27348, 4474},  {27938, 3625},  {22386, 9512},  {27446, 3557},
        {27644, 2634},  {22813, 7518},  {20537, 10466}, {24370, 5075},  {18636, 12949},
        {23281, 5844},  {24221, 4313},  {22648, 5699},  {23655, 3297},  {19954, 9789},
        {19264, 10021}, {17421, 13458}, {22355, 193},   {17807, 11833}, {18762, 7129},
        {18127, 9314},  {18467, 7616},  {18716, 6618},  {19668, 2168},  {19072, 3753},
        {16941, 12455}, {17673, 7958},  {18007, 5786},  {17410, 5535},  {16512, 12529},
        {16413, 481},   {16118, 4169},  {15724, 5249},  {15457, 4313},  {14945, 912},
        {15006, 2600},  {14604, 1587},  {15350, 10712}, {13977, 3434},  {14310, 7487},
        {9741, 4886},   {9374, 4745},   {9514, 8177},   {4639, 2368},   {4827, 3093},
        {1842, 1416},   {4966, 5002},   {2082, 2154},   {2995, 3195},   {1655, 2161},
        {5705, 6224},   {3788, 4414},   {9930, 10555},  {11337, 12263}, {4664, 6191},
        {9040, 10322},  {8909, 10808},  {9894, 12292},  {7376, 10585},  {1999, 7391},
        {5537, 9832},   {4734, 9905},   {292, 7448},    {12623, 14688}, {6868, 11511},
        {153, 9503},    {5829, 12423},  {3430, 11701},  {4596, 13186},  {9961, 14989},
        {5436, 14343},  {5447, 14798},  {41, 14309},    {12052, 16105}, {11840, 16423},
        {6270, 16139},  {11478, 16519}, {1150, 16282},  {2306, 16549},  {5097, 16687},
        {3602, 17253},  {53, 17958},    {6334, 18935},  {3035, 20142},  {8281, 18787},
        {8942, 18651},  {13290, 17437}, {4833, 19976},  {288, 21881},   {6359, 20450},
        {900, 23196},   {9161, 19866},  {6483, 21659},  {467, 25824},   {10383, 20053},
        {9758, 20945},  {13966, 18114}, {7711, 22888},  {778, 28433},   {11020, 20649},
        {1869, 28009},  {4041, 26439},  {3548, 26869},  {6729, 24389},  {2421, 28070},
        {11538, 20798}, {11942, 20485}, {4031, 28286},  {3728, 29334},  {491, 32702},
        {3902, 29314},  {6900, 26477},  {6422, 28321},  {5021, 30145},  {6617, 28297},
        {8723, 26362},  {11323, 23757}, {10291, 26154}, {12859, 22646}, {12287, 24355},
        {14771, 19589}, {12382, 25200}, {15141, 19815}, {13931, 24182}, {12316, 29869},
        {13030, 27982}, {15574, 20416}, {14893, 25874}, {15573, 25996}, {15890, 27892}};

    Segment answer1 = getBiggestSegmentPossible(input1);
    Segment answer2 = getBiggestSegmentPossible(input2);
    Segment answer3 = getBiggestSegmentPossible(input3);
    Segment answer4 = getBiggestSegmentPossible(input4);
    Segment answer5 = getBiggestSegmentPossible(input5);
    Segment answer6 = getBiggestSegmentPossible(input6);
    Segment answer8 = getBiggestSegmentPossible(input8);

    auto start                       = chrono::high_resolution_clock::now();  // Start clock
    Segment answer7                  = getBiggestSegmentPossible(input7);
    auto finish                      = chrono::high_resolution_clock::now();  // Stop clock
    chrono::duration<double> elapsed = finish - start;                        // Mesure time elapsed
    cout << "\n------ Elapsed time: " << elapsed.count() << " s ------\n";

    Segment ans3 = {{8, 5}, {1, 4}};
    Segment ans4 = {{2, 0}, {4, 8}};
    Segment ans5 = {{1, 4}, {9, 2}};

    vector<Segment> edges = generateEdges(input7);
    writeToFile(edges, answer7);
    draw();

    REQUIRE(answer1.getLength() == Approx(76.157731059));
    REQUIRE(answer2.getLength() == Approx(4510.149110617));
    REQUIRE(answer3.getLength() == Approx(ans3.getLength()));
    REQUIRE(answer4.getLength() == Approx(ans4.getLength()));
    REQUIRE(answer5.getLength() == Approx(ans5.getLength()));
}
