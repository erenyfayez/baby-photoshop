
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include "Image_Class.h"

using namespace std;

// Helper function for safe integer input
int getValidInteger(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        }
        else {
            cout << "Invalid input. Please enter an integer.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

// Function Declarations
void filter1_Grayscale(Image& img);
void filter2_BlackAndWhite(Image& img);
void filter3_Invert(Image& img);
void filter4_Frame(Image& img);
void filter5_Flip(Image& img);
void filter6_Rotate(Image& img);
void filter7_DarkenLighten(Image& img);
void filter8_Resize(Image& img);
void filter9_Merge(Image& img);
void filter10_EdgeDetect(Image& img);
void filter11_Crop(Image& img);
void filter12_Blur(Image& img);
void Blur_Level1(Image& image);
void Blur_Level2(Image& image);
void Blur_Level3(Image& image);
void filter13_Sunlight(Image& img);
void filter14_OldTV(Image& img);
void filter15_Purple(Image& img);
void filter16_Infrared(Image& img);
void filter17_Skew(Image& img);
void filter18_OilPainting(Image& img);

bool loadImageSafely(Image& img, const string& promptMsg);
void saveImageSafely(Image& img);

// ------------------------------------------------------------
// keeps asking for a filename until an image loads successfully
// ------------------------------------------------------------
bool loadImageSafely(Image& img, const string& promptMsg) {
    string filename;
    while (true) {
        cout << promptMsg;
        cin >> filename;

        try {
            img.loadNewImage(filename);
            cout << "Loaded successfully! Size: " << img.width
                << " x " << img.height << endl;
            return true;
        }
        catch (const exception& e) {
            cout << "Could not load that file (" << e.what() << ")." << endl;
            cout << "Try again? (y/n): ";
            char retry;
            cin >> retry;
            if (retry == 'n' || retry == 'N') {
                return false;
            }
        }
    }
}

// ------------------------------------------------------------
// asks for an output filename and saves
// ------------------------------------------------------------
void saveImageSafely(Image& img) {
    string filename;
    while (true) {
        cout << "Enter filename to save as (e.g. output.jpg, output.png, output.bmp): ";
        cin >> filename;

        try {
            img.saveImage(filename);
            cout << "Saved successfully as " << filename << endl;
            return;
        }
        catch (const exception& e) {
            cout << "Could not save (" << e.what() << "). Please try a valid extension." << endl;
        }
    }
}

// ------------------------------------------------------------
// prints the menu options
// ------------------------------------------------------------
void displayMenu() {
    cout << "\n=================== MENU ===================\n";
    cout << " 1. Load a new image\n";
    cout << " 2. Grayscale\n";
    cout << " 3. Black & White\n";
    cout << " 4. Invert Colors\n";
    cout << " 5. Add Frame\n";
    cout << " 6. Flip (horizontal/vertical)\n";
    cout << " 7. Rotate (90/180/270)\n";
    cout << " 8. Darken/Lighten\n";
    cout << " 9. Resize\n";
    cout << "10. Merge with another image\n";
    cout << "11. Edge Detection\n";
    cout << "12. Crop\n";
    cout << "13. Blur\n";
    cout << "14. Fix Sunlight (brightness/warmth)\n";
    cout << "15. Old TV Effect\n";
    cout << "16. Make it Purple\n";
    cout << "17. Infrared Effect\n";
    cout << "18. Skew Image\n";
    cout << "19. Oil Painting Effect\n";
    cout << "20. Save current image\n";
    cout << "21. Exit\n";
    cout << "==============================================\n";
    cout << "Enter your choice: ";
}

int main() {
    Image currentImage;
    bool imageLoaded = false;

    cout << "Welcome to Baby Photoshop!\n";
    imageLoaded = loadImageSafely(currentImage, "Enter the image filename to load: ");

    if (!imageLoaded) {
        cout << "No image loaded. Exiting program." << endl;
        return 0;
    }

    bool running = true;
    while (running) {
        displayMenu();

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            char saveFirst;
            cout << "Save current image before loading a new one? (y/n): ";
            cin >> saveFirst;
            if (saveFirst == 'y' || saveFirst == 'Y') {
                saveImageSafely(currentImage);
            }
            loadImageSafely(currentImage, "Enter the new image filename to load: ");
            break;
        }
        case 2:  filter1_Grayscale(currentImage);     break;
        case 3:  filter2_BlackAndWhite(currentImage); break;
        case 4:  filter3_Invert(currentImage);        break;
        case 5:  filter4_Frame(currentImage);         break;
        case 6:  filter5_Flip(currentImage);          break;
        case 7:  filter6_Rotate(currentImage);        break;
        case 8:  filter7_DarkenLighten(currentImage); break;
        case 9:  filter8_Resize(currentImage);        break;
        case 10: filter9_Merge(currentImage);         break;
        case 11: filter10_EdgeDetect(currentImage);   break;
        case 12: filter11_Crop(currentImage);         break;
        case 13: filter12_Blur(currentImage);         break;
        case 14: filter13_Sunlight(currentImage);     break;
        case 15: filter14_OldTV(currentImage);        break;
        case 16: filter15_Purple(currentImage);       break;
        case 17: filter16_Infrared(currentImage);     break;
        case 18: filter17_Skew(currentImage);         break;
        case 19: filter18_OilPainting(currentImage);  break;
        case 20:
            saveImageSafely(currentImage);
            break;
        case 21: {
            char saveFirst;
            cout << "Save current image before exiting? (y/n): ";
            cin >> saveFirst;
            if (saveFirst == 'y' || saveFirst == 'Y') {
                saveImageSafely(currentImage);
            }
            running = false;
            cout << "Goodbye!" << endl;
            break;
        }
        default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }
    }

    return 0;
}

// ------------------------------------------------------------
// FILTER IMPLEMENTATIONS
// ------------------------------------------------------------

void filter1_Grayscale(Image& img) {
    for (int x = 0; x < img.width; ++x) {
        for (int y = 0; y < img.height; ++y) {
            unsigned char red = img.getPixel(x, y, 0);
            unsigned char green = img.getPixel(x, y, 1);
            unsigned char blue = img.getPixel(x, y, 2);

            unsigned char avg = (red + green + blue) / 3;

            img.setPixel(x, y, 0, avg);
            img.setPixel(x, y, 1, avg);
            img.setPixel(x, y, 2, avg);
        }
    }
    cout << "Grayscale filter applied successfully!\n";
}

void filter2_BlackAndWhite(Image& img) {
    const int threshold = 127;

    for (int x = 0; x < img.width; ++x) {
        for (int y = 0; y < img.height; ++y) {
            unsigned char red = img.getPixel(x, y, 0);
            unsigned char green = img.getPixel(x, y, 1);
            unsigned char blue = img.getPixel(x, y, 2);

            unsigned int avg = (red + green + blue) / 3;
            unsigned char bwValue = (avg >= threshold) ? 255 : 0;

            img.setPixel(x, y, 0, bwValue);
            img.setPixel(x, y, 1, bwValue);
            img.setPixel(x, y, 2, bwValue);
        }
    }
    cout << "Black & White filter applied successfully!\n";
}

void filter3_Invert(Image& img) {
    for (int x = 0; x < img.width; ++x) {
        for (int y = 0; y < img.height; ++y) {
            for (int c = 0; c < 3; ++c) {
                unsigned char originalVal = img.getPixel(x, y, c);
                img.setPixel(x, y, c, 255 - originalVal);
            }
        }
    }
    cout << "Invert filter applied successfully!\n";
}

void filter4_Frame(Image& image) {
    int width = 30;
    int r, g, b;

    while (true) {
        r = getValidInteger("Enter Red value (0-255): ");
        if (r >= 0 && r <= 255) break;
        cout << "Invalid Red value! Enter a number from 0 to 255.\n";
    }
    while (true) {
        g = getValidInteger("Enter Green value (0-255): ");
        if (g >= 0 && g <= 255) break;
        cout << "Invalid Green value! Enter a number from 0 to 255.\n";
    }
    while (true) {
        b = getValidInteger("Enter Blue value (0-255): ");
        if (b >= 0 && b <= 255) break;
        cout << "Invalid Blue value! Enter a number from 0 to 255.\n";
    }
    int type;
    while (true) {
        type = getValidInteger("Frame type (1=Simple, 2=Fancy): ");
        if (type == 1 || type == 2) break;
        cout << "Invalid frame type! Please enter 1 or 2.\n";
    }

    int w = image.width;
    int h = image.height;
    Image image2(w + 2 * width, h + 2 * width);
    for (int i = 0; i < image2.height; i++) {
        for (int j = 0; j < image2.width; j++) {
            if (j >= width && j < w + width && i >= width && i < h + width) {
                for (int k = 0; k < 3; k++) {
                    image2.setPixel(j, i, k, image.getPixel(j - width, i - width, k));
                }
            }
            else {
                if (type == 2 && (j % 20 < 10 || i % 20 < 10)) {
                    image2.setPixel(j, i, 0, 255 - r);
                    image2.setPixel(j, i, 1, 255 - g);
                    image2.setPixel(j, i, 2, 255 - b);
                }
                else {
                    image2.setPixel(j, i, 0, r);
                    image2.setPixel(j, i, 1, g);
                    image2.setPixel(j, i, 2, b);
                }
            }
        }
    }
    image = image2;
    cout << "Frame filter done!\n";
}

void filter5_Flip(Image& image) {
    int choice;
    cout << "Enter 1 for horizontal flip, 2 for vertical flip: ";
    cin >> choice;
    if (choice == 1) {
        for (int i = 0; i < image.width / 2; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < image.channels; k++) {
                    swap(image(i, j, k), image(image.width - 1 - i, j, k));
                }
            }
        }
        cout << "Horizontal flip done!\n";
    }
    else if (choice == 2) {
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height / 2; j++) {
                for (int k = 0; k < image.channels; k++) {
                    swap(image(i, j, k), image(i, image.height - 1 - j, k));
                }
            }
        }
        cout << "Vertical flip done!\n";
    }
    else {
        cout << "Invalid choice!\n";
    }
}

void filter6_Rotate(Image& img) {
    cout << "Choose rotation angle (clockwise):\n";
    cout << "1. 90 degrees\n";
    cout << "2. 180 degrees\n";
    cout << "3. 270 degrees\n";
    cout << "Enter choice (1, 2, or 3): ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        Image temp(img.height, img.width);
        for (int x = 0; x < img.width; ++x) {
            for (int y = 0; y < img.height; ++y) {
                for (int c = 0; c < 3; ++c) {
                    temp.setPixel(img.height - 1 - y, x, c, img.getPixel(x, y, c));
                }
            }
        }
        img = temp;
    }
    else if (choice == 2) {
        Image temp(img.width, img.height);
        for (int x = 0; x < img.width; ++x) {
            for (int y = 0; y < img.height; ++y) {
                for (int c = 0; c < 3; ++c) {
                    temp.setPixel(img.width - 1 - x, img.height - 1 - y, c, img.getPixel(x, y, c));
                }
            }
        }
        img = temp;
    }
    else if (choice == 3) {
        Image temp(img.height, img.width);
        for (int x = 0; x < img.width; ++x) {
            for (int y = 0; y < img.height; ++y) {
                for (int c = 0; c < 3; ++c) {
                    temp.setPixel(y, img.width - 1 - x, c, img.getPixel(x, y, c));
                }
            }
        }
        img = temp;
    }
    else {
        cout << "Invalid choice! Returning to menu.\n";
        return;
    }

    cout << "Rotate filter applied successfully!\n";
}

void filter7_DarkenLighten(Image& img) {
    cout << "Choose option:\n";
    cout << "1. Lighten image (by 50%)\n";
    cout << "2. Darken image (by 50%)\n";
    cout << "Enter choice (1 or 2): ";

    int choice;
    cin >> choice;

    if (choice != 1 && choice != 2) {
        cout << "Invalid choice! Returning to menu.\n";
        return;
    }

    for (int x = 0; x < img.width; ++x) {
        for (int y = 0; y < img.height; ++y) {
            for (int c = 0; c < 3; ++c) {
                unsigned char val = img.getPixel(x, y, c);

                if (choice == 1) {
                    int newVal = val + (255 - val) / 2;
                    img.setPixel(x, y, c, (unsigned char)newVal);
                }
                else if (choice == 2) {
                    int newVal = val / 2;
                    img.setPixel(x, y, c, (unsigned char)newVal);
                }
            }
        }
    }

    cout << (choice == 1 ? "Lighten" : "Darken") << " filter applied successfully!\n";
}

void filter8_Resize(Image& image) {
    int width2 = getValidInteger("Enter the new width: ");
    int height2 = getValidInteger("Enter the new height: ");

    if (width2 <= 0 || height2 <= 0) {
        cout << "Invalid dimensions!\n";
        return;
    }

    Image image2(width2, height2);
    double x_ratio = (double)image.width / width2;
    double y_ratio = (double)image.height / height2;
    for (int i = 0; i < width2; ++i) {
        for (int j = 0; j < height2; ++j) {
            int x = i * x_ratio;
            int y = j * y_ratio;
            for (int k = 0; k < image.channels; ++k) {
                image2(i, j, k) = image(x, y, k);
            }
        }
    }

    image = image2;
    cout << "Resize filter done!\n";
}

void filter9_Merge(Image& img) {
    Image secondImg;
    if (!loadImageSafely(secondImg, "Enter second image filename to merge: ")) {
        return;
    }

    // Resize second image to match first image dimensions
    Image resizedSecond(img.width, img.height);
    double x_ratio = (double)secondImg.width / img.width;
    double y_ratio = (double)secondImg.height / img.height;

    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            int x = i * x_ratio;
            int y = j * y_ratio;
            for (int k = 0; k < img.channels; ++k) {
                resizedSecond(i, j, k) = secondImg(x, y, k);
            }
        }
    }

    // Average the pixel values
    for (int x = 0; x < img.width; ++x) {
        for (int y = 0; y < img.height; ++y) {
            for (int c = 0; c < img.channels; ++c) {
                unsigned char val1 = img.getPixel(x, y, c);
                unsigned char val2 = resizedSecond.getPixel(x, y, c);
                img.setPixel(x, y, c, (val1 + val2) / 2);
            }
        }
    }
    cout << "Merge filter applied successfully!\n";
}

void filter10_EdgeDetect(Image& image) {
    int _width = image.width;
    int _height = image.height;
    int _channels = image.channels;

    Image _temp = image;

    for (int _y = 0; _y < _height; ++_y) {
        for (int _x = 0; _x < _width; ++_x) {
            unsigned int _sum = 0;
            for (int c = 0; c < _channels; ++c) {
                _sum += image.getPixel(_x, _y, c);
            }
            unsigned char _gray = _sum / _channels;
            for (int c = 0; c < _channels; ++c) {
                _temp.setPixel(_x, _y, c, _gray);
            }
        }
    }

    int _threshold = 30;
    for (int _y = 0; _y < _height - 1; ++_y) {
        for (int _x = 0; _x < _width - 1; ++_x) {
            unsigned char _current = _temp.getPixel(_x, _y, 0);
            unsigned char _right = _temp.getPixel(_x + 1, _y, 0);
            unsigned char _down = _temp.getPixel(_x, _y + 1, 0);

            if (abs(_current - _right) > _threshold || abs(_current - _down) > _threshold) {
                for (int c = 0; c < _channels; ++c) {
                    image.setPixel(_x, _y, c, 0);
                }
            }
            else {
                for (int c = 0; c < _channels; ++c) {
                    image.setPixel(_x, _y, c, 255);
                }
            }
        }
    }
    cout << "Edge detection applied successfully! \n";
}

void filter11_Crop(Image& img) {
    int x, y, w, h;
    cout << "Enter starting point (x y): ";
    cin >> x >> y;
    cout << "Enter crop dimensions (width height): ";
    cin >> w >> h;

    if (x < 0 || y < 0 || x + w > img.width || y + h > img.height) {
        cout << "Invalid crop dimensions!\n";
        return;
    }

    Image croppedImg(w, h);
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            for (int c = 0; c < img.channels; ++c) {
                croppedImg(i, j, c) = img(x + i, y + j, c);
            }
        }
    }

    img = croppedImg;
    cout << "Image cropped successfully!\n";
}

void Blur_Level1(Image& image) {
    Image temp = image;
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                int sum = 0, count = 0;
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < image.width && nj >= 0 && nj < image.height) {
                            sum += temp(ni, nj, k);
                            count++;
                        }
                    }
                }
                image(i, j, k) = sum / count;
            }
        }
    }
}

void Blur_Level2(Image& image) {
    Image temp = image;
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                int sum = 0, count = 0;
                for (int di = -3; di <= 3; di++) {
                    for (int dj = -3; dj <= 3; dj++) {
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < image.width && nj >= 0 && nj < image.height) {
                            sum += temp(ni, nj, k);
                            count++;
                        }
                    }
                }
                image(i, j, k) = sum / count;
            }
        }
    }
}

void Blur_Level3(Image& image) {
    Image temp = image;
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                int sum = 0, count = 0;
                for (int di = -5; di <= 5; di++) {
                    for (int dj = -5; dj <= 5; dj++) {
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < image.width && nj >= 0 && nj < image.height) {
                            sum += temp(ni, nj, k);
                            count++;
                        }
                    }
                }
                image(i, j, k) = sum / count;
            }
        }
    }
}

void filter12_Blur(Image& image) {
    int choice;
    while (true) {
        cout << "Choose Blur Level:\n1. Level 1\n2. Level 2\n3. Level 3\n";
        choice = getValidInteger("Enter choice: ");
        if (choice >= 1 && choice <= 3) break;
        cout << "Invalid choice! Please enter 1, 2 or 3 only.\n";
    }

    if (choice == 1) Blur_Level1(image);
    else if (choice == 2) Blur_Level2(image);
    else if (choice == 3) Blur_Level3(image);

    cout << "Blur applied successfully!\n";
}

void filter13_Sunlight(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            img(i, j, 0) = min(255, (int)(img(i, j, 0) * 1.2)); // Increase Red
            img(i, j, 1) = min(255, (int)(img(i, j, 1) * 1.15)); // Increase Green
            img(i, j, 2) = (int)(img(i, j, 2) * 0.85);          // Reduce Blue
        }
    }
    cout << "Sunlight filter applied successfully!\n";
}

void filter14_OldTV(Image& image) {
    int _width = image.width;
    int _height = image.height;
    int _channels = image.channels;

    for (int _y = 0; _y < _height; ++_y) {
        if (_y % 2 == 0) {
            for (int _x = 0; _x < _width; ++_x) {
                for (int c = 0; c < _channels; ++c) {
                    unsigned char _val = image.getPixel(_x, _y, c);
                    image.setPixel(_x, _y, c, _val * 0.5);
                }
            }
        }
    }
    cout << "Old TV effect applied successfully!\n";
}

void filter15_Purple(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            img(i, j, 0) = min(255, (int)(img(i, j, 0) * 1.2));
            img(i, j, 1) = (int)(img(i, j, 1) * 0.7);
            img(i, j, 2) = min(255, (int)(img(i, j, 2) * 1.2));
        }
    }
    cout << "Purple filter applied successfully!\n";
}

void filter16_Infrared(Image& image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int r = image(i, j, 0);
            int g = image(i, j, 1);
            int b = image(i, j, 2);

            int brightness = (r + g + b) / 3;

            image(i, j, 0) = 255;
            image(i, j, 1) = 255 - brightness;
            image(i, j, 2) = 255 - brightness;
        }
    }
    cout << "Infrared filter done!\n";
}

void filter17_Skew(Image& img) {
    double angle;
    cout << "Enter skew angle in degrees: ";
    cin >> angle;

    double rad = angle * 3.141592653589793 / 180.0;
    int skewAmount = tan(rad) * img.width;
    int newHeight = img.height + abs(skewAmount);

    Image skewedImg(img.width, newHeight);
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            for (int c = 0; c < img.channels; ++c) {
                skewedImg(i, j, c) = 255;
            }
        }
    }

    for (int i = 0; i < img.width; ++i) {
        int yOffset = tan(rad) * (img.width - i);
        for (int j = 0; j < img.height; ++j) {
            int newY = j + yOffset;
            if (newY >= 0 && newY < newHeight) {
                for (int c = 0; c < img.channels; ++c) {
                    skewedImg(i, newY, c) = img(i, j, c);
                }
            }
        }
    }

    img = skewedImg;
    cout << "Image skewed successfully!\n";
}

void filter18_OilPainting(Image& img) {
    int levels = 8;
    int step = 256 / levels;

    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int c = 0; c < img.channels; ++c) {
                img(i, j, c) = (img(i, j, c) / step) * step;
            }
        }
    }
    cout << "Oil painting effect applied successfully!\n";
}