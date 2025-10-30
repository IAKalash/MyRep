#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "BitmapPlusPlus.hpp"

using namespace std;

namespace nikita_lox {
    bmp::Pixel median(const vector <bmp::Pixel> &pixels, int edge) {

        int r_res, g_res, b_res;
        vector <int> r, g, b;
        int med = pixels.size() / 2;

        for (bmp::Pixel p : pixels) {
            r.push_back(p.r);
            g.push_back(p.g);
            b.push_back(p.b);
        }

        sort(r.begin(), r.end());
        sort(g.begin(), g.end());
        sort(b.begin(), b.end());

        r_res = pixels[0].r;
        g_res = pixels[0].g;
        b_res = pixels[0].b;

        r_res = r_res > r[med + edge] || r_res < r[med - edge] ? r[med] : r_res;
        g_res = g_res > g[med + edge] || g_res < g[med - edge] ? g[med] : g_res;
        b_res = b_res > b[med + edge] || b_res < b[med - edge] ? b[med] : b_res;

        return bmp::Pixel(r_res, g_res, b_res);
    }

    bmp::Bitmap median_filter(bmp::Bitmap image, int neighbourhood, int edge) {
        if (neighbourhood < 1) neighbourhood = 1;
        if (edge < 0) edge = 0;
        neighbourhood += neighbourhood % 2 == 0 ? 1 : 0;
        int height = image.height();
        int width = image.width();

        int radius = (neighbourhood - 1) / 2;
        vector <bmp::Pixel> matrix;

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {

                matrix.clear();

                matrix.push_back(image.get(i, j));
                for (int di = 0; di <= radius; ++di) {
                    for (int dj = 1; dj <= radius; ++dj) {

                        if (i + di < width && j + dj < height) matrix.push_back(image.get(i + di, j + dj));
                        if (i + di < width && j - dj >= 0) matrix.push_back(image.get(i + di, j - dj));
                        if (i - di >= 0 && j + dj < height) matrix.push_back(image.get(i - di, j + dj));
                        if (i - di >= 0 && j - dj >= 0) matrix.push_back(image.get(i - di, j - dj));

                    }
                }
                image.set(i, j, median(matrix, edge));

            }
        }

        return image;
    }
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream in1(argv[1]);
    if (!in1.is_open()) {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    string in2, out, line;
    int neighbourhood, edge;

    if (!(in1 >> in2 >> neighbourhood >> edge >> out)) {
        cerr << "Wrong arguments!" << endl;
        return 2;
    }

    in1.close();

    bmp::Bitmap image;
    try {
        image.load(in2);
    } catch (const bmp::Exception& e) {
        cerr << "Error loading image: " << e.what() << endl;
        return 1;
    }

    bmp::Bitmap res = nikita_lox::median_filter(image, neighbourhood, edge);

    try {
        res.save(out);
    } catch (const bmp::Exception& e) {
        cerr << "Error saving image: " << e.what() << endl;
        return 1;
    }

    return 0;
}