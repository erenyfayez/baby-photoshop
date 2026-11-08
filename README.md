# Baby Photoshop

A console image-processing application in C++ with a menu of image filters and editing operations. Built for the CS213 Object-Oriented Programming course at FCAI, Cairo University.

## Features
- **Basic:** Grayscale, Black & White, Invert
- **Editing:** Crop, Resize, Flip (horizontal/vertical), Rotate (90°/180°/270°), Skew, Add Frame (simple/fancy, custom color), Merge two images
- **Adjustments:** Darken/Lighten, Blur (3 levels), Sunlight
- **Effects:** Edge Detection, Old TV, Purple, Infrared, Oil Painting
- Load, save, and exit, with input validation and error messages

## About
A CS213 course project. The team members of the assignment are listed in the header of the source file. I implemented the application's filters and menu (Ereny Fayez).

## How to Run
Requires a C++ compiler (for example g++). All required files are in this repository.

```bash
g++ -std=c++17 CS213_Assignment1.cpp -o baby_photoshop
./baby_photoshop
```

Enter an image filename (`.jpg`, `.png`, `.bmp`, or `.tga`), then choose a filter from the menu. Use option 20 to save the result.

## Project Files
| File | Purpose |
|------|---------|
| `CS213_Assignment1.cpp` | Main program: menu and all filters |
| `Image_Class.h` | Image class provided by the course (FCAI, Cairo University) |
| `stb_image.h`, `stb_image_write.h` | Open-source image loading and saving libraries by Sean Barrett |
