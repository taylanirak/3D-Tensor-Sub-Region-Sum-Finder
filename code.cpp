//Taylan Irak 30702

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// We are reading the input from our files
void inpFile(const string &filename, vector<vector<vector<double>>> &tensor, double &goalSum) {
    ifstream inputFile(filename);

    int W, H, D;
    inputFile >> W >> H >> D;

    // Our 3d tensor(everything [width, height, depth] is set to 0)
    tensor = vector<vector<vector<double>>>(W, vector<vector<double>>(H, vector<double>(D, 0.0)));

    // It's reading our target sum.
    inputFile >> goalSum;

    // We are reading the non zero elements
    int non0_count;
    inputFile >> non0_count;

    for (int i = 0; i < non0_count; ++i) {
        int x, y, z;
        double v;
        inputFile >> x >> y >> z >> v;
        tensor[x][y][z] = v;
    }

    inputFile.close();
}

// We are counting the (sub-tensors = target sum)
int subTen(const vector<vector<vector<double>>> &tensor, double goalSum) {
    int W = tensor.size();
    int H = tensor[0].size();
    int D = tensor[0][0].size();
    int count = 0;

    // For all possible sub-tensors(I could have used prefix sums to make the calculation faster but we haven't seen it yet.)
    for (int x1 = 0; x1 < W; ++x1) {
        for (int y1 = 0; y1 < H; ++y1) {
            for (int z1 = 0; z1 < D; ++z1) {
                // For sub-tensors that are starting at x1, y1, z1, we are iterating them to their endings.
                for (int x2 = x1; x2 < W; ++x2) {
                    for (int y2 = y1; y2 < H; ++y2) {
                        for (int z2 = z1; z2 < D; ++z2) {
                            double sum = 0.0;
                            // We are calculating the sum between (x1, y1, z1) and (x2, y2, z2)
                            for (int x = x1; x <= x2; ++x) {
                                for (int y = y1; y <= y2; ++y) {
                                    for (int z = z1; z <= z2; ++z) {
                                        sum += tensor[x][y][z];
                                    }
                                }
                            }
                            // We are checking if sum = target
                            if (sum == goalSum) {
                                ++count;
                            }
                        }
                    }
                }
            }
        }
    }

    return count;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    string filename = argv[1];
    vector<vector<vector<double>>> tensor;
    double goalSum;

    // We are reading the input
    inpFile(filename, tensor, goalSum);

    // We are finding the number of (sub-tensors = target)
    int res = subTen(tensor, goalSum);

    cout << res << endl;

    return 0;
}
