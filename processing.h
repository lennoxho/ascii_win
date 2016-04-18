// processing.h
// Written by      "Lennox" Shou Hao Ho     
// https://ca.linkedin.com/in/lennoxho
// February 2016

#pragma once

#include "ascii_win.h"

const float inverse_scale_width{ 9 };
const float inverse_scale_height{ 16 };

void create_div(std::ofstream &css_file, Gdiplus::Color &bgr_colour, std::unordered_map<unsigned, unsigned> &colour_map);
void write_html_header(std::ofstream &html_file, std::string &filename);
void write_css_header(std::ofstream &css_file);
void process(std::wstring wfilename);

static inline unsigned serialize(Gdiplus::Color &bgr_colour){
	return bgr_colour.GetB() + bgr_colour.GetG() * 256 + bgr_colour.GetR() * 256 * 256;
}