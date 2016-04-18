// processing.cpp
// Written by      "Lennox" Shou Hao Ho     
// https://ca.linkedin.com/in/lennoxho
// February 2016

#include "ascii_win.h"
#include "processing.h"

using namespace std;
using namespace Gdiplus;

void create_div(ofstream &css_file, Color &bgr_colour, unordered_map<unsigned, unsigned> &colour_map){
	css_file << R"(div.c)";
	css_file << colour_map[serialize(bgr_colour)];
	css_file << R"({color: rgb()";
	css_file << static_cast<unsigned>(bgr_colour.GetR()) << ',';
	css_file << static_cast<unsigned>(bgr_colour.GetG()) << ',';
	css_file << static_cast<unsigned>(bgr_colour.GetB());
	css_file << R"();})" << '\n';
}

void write_html_header(ofstream &html_file, string &filename){
	html_file << R"(<!DOCTYPE html><html><head><link rel="stylesheet" type="text/css" href=")";
	html_file << filename << ".css";
	html_file << R"("><title>Page Title</title></head><body>)";
}

void write_css_header(ofstream &css_file){
	css_file << R"(div{display: inline; font-family: monospace;})" << '\n';
	css_file << R"(body{text-rendering: optimizeSpeed; font-size: )";
	css_file << inverse_scale_height;
	css_file << R"(px; line-height: )";
	css_file << inverse_scale_height;
	css_file << R"(px;})" << '\n';
}

void process(wstring wfilename){
	assert(inverse_scale_height > 0);
	assert(inverse_scale_width > 0);
	wcerr << wfilename;
	Bitmap image{ wfilename.c_str() };

	if (image.GetLastStatus() != Ok){
		cerr << "File could not be opened!" << endl;
		exit(E_BAD_FILENAME);
	}

	size_t last_pos{ wfilename.find_last_of('.') };
	if (last_pos != wstring::npos)
		wfilename.erase(last_pos);

	std::ofstream html_file{ wfilename + TEXT(".html"), ios::out };
	if (!html_file.is_open()){
		cerr << "HTML file could not be created!" << endl;
		exit(E_BAD_FILENAME);
	}

	std::ofstream css_file{ wfilename + TEXT(".css"), ios::out };
	if (!css_file.is_open()){
		cerr << "HTML file could not be created!" << endl;
		exit(E_BAD_FILENAME);
	}

	size_t height{ image.GetHeight() };
	size_t width{ image.GetWidth() };

	Bitmap *img;
	
	img = new Bitmap(static_cast<int>(width / inverse_scale_width), static_cast<int>(height / inverse_scale_height));
	Graphics g{ img };
	g.ScaleTransform(1 / inverse_scale_width, 1 / inverse_scale_height);
	g.DrawImage(&image, 0, 0);

	unordered_map<unsigned, unsigned> colour_map{};
	write_html_header(html_file, string(wfilename.begin(), wfilename.end()));
	write_css_header(css_file);

	size_t new_height{ img->GetHeight() };
	size_t new_width{ img->GetWidth() };

	unsigned num{ 0 };
	for (int i = 0; i < new_height; ++i){
		int j{ 0 };
		while (j < new_width){
			Color curr_colour;
			img->GetPixel(j, i, &curr_colour);

			if (colour_map.count(serialize(curr_colour)) == 0){
				colour_map[serialize(curr_colour)] = num++;
				create_div(css_file, curr_colour, colour_map);
			}

			html_file << R"(<div class="c)";
			html_file << colour_map[serialize(curr_colour)];
			html_file << R"("><b>)";

			Color next_colour{ curr_colour };
			while (j < new_width &&
				next_colour.GetB() == curr_colour.GetB() &&
				next_colour.GetG() == curr_colour.GetG() &&
				next_colour.GetR() == curr_colour.GetR()){
				html_file << R"(m)";
				++j;
				if (j < new_width) 
					img->GetPixel(j, i, &curr_colour);
			}

			html_file << R"(</b></div>)";
		}

		html_file << R"(<br>)";
	}

	delete img;

	html_file << R"(</body></html>)";
	html_file.close();
	css_file.close();

}