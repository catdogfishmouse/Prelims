// 'outlet_on_small', 39x33px
const unsigned char epd_bitmap_ONE_OUTLET [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 
	0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xc7, 0xff, 0xcf, 0xfe, 0xff, 0xc7, 
	0xff, 0xc7, 0xfe, 0xff, 0xc7, 0xff, 0xc7, 0xfe, 0xff, 0xc7, 0xff, 0xc7, 0xfe, 0xff, 0xc7, 0xff, 
	0xc7, 0xfe, 0xff, 0xc7, 0xff, 0xc7, 0xfe, 0xff, 0xc7, 0xff, 0xc7, 0xfe, 0xff, 0xc7, 0xff, 0xc7, 
	0xfe, 0xff, 0xc7, 0xff, 0xc7, 0xfe, 0xff, 0xc7, 0xff, 0xc7, 0xfe, 0xff, 0xe7, 0xff, 0xcf, 0xfe, 
	0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 
	0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 
	0x83, 0xff, 0xfe, 0xff, 0xff, 0x01, 0xff, 0xfe, 0xff, 0xff, 0x01, 0xff, 0xfe, 0xff, 0xff, 0x01, 
	0xff, 0xfe, 0xff, 0xff, 0x01, 0xff, 0xfe, 0xff, 0xff, 0x01, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 
	0xff, 0xff, 0xff, 0xff, 0xfe
};
// 'outlet_on_small', 39x33px
const unsigned char epd_bitmap_outlet_off [] PROGMEM = {
	0xfe, 0x00, 0x00, 0x00, 0xfe, 0xfc, 0x00, 0x00, 0x00, 0x7e, 0xf8, 0x00, 0x00, 0x00, 0x3e, 0xf0, 
	0x00, 0x00, 0x00, 0x3e, 0xf0, 0x00, 0x00, 0x00, 0x1e, 0xe0, 0x38, 0x00, 0x30, 0x0e, 0xe0, 0x38, 
	0x00, 0x38, 0x0e, 0xe0, 0x38, 0x00, 0x38, 0x0e, 0xc0, 0x38, 0x00, 0x38, 0x06, 0xc0, 0x38, 0x00, 
	0x38, 0x06, 0xc0, 0x38, 0x00, 0x38, 0x06, 0x80, 0x38, 0x00, 0x38, 0x02, 0x80, 0x38, 0x00, 0x38, 
	0x02, 0x80, 0x38, 0x00, 0x38, 0x02, 0x80, 0x38, 0x00, 0x38, 0x02, 0x80, 0x18, 0x00, 0x30, 0x02, 
	0x80, 0x00, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x00, 0x02, 0x80, 
	0x00, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x00, 0x02, 0xc0, 0x00, 
	0x7c, 0x00, 0x06, 0xc0, 0x00, 0xfe, 0x00, 0x06, 0xc0, 0x00, 0xfe, 0x00, 0x06, 0xe0, 0x00, 0xfe, 
	0x00, 0x0e, 0xe0, 0x00, 0xfe, 0x00, 0x0e, 0xf0, 0x00, 0xfe, 0x00, 0x1e, 0xf0, 0x00, 0x00, 0x00, 
	0x1e, 0xf8, 0x00, 0x00, 0x00, 0x3e, 0xfc, 0x00, 0x00, 0x00, 0x7e, 0xfc, 0x00, 0x00, 0x00, 0x7e, 
	0xff, 0xff, 0xff, 0xff, 0xfe
};

// 'outlet_dead_small', 39x41px
const unsigned char epd_bitmap_horizontal__dead_outlet [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0x01, 0xff, 0xfe, 0xff, 0xf0, 0x7e, 0x0f, 0xfe, 0xff, 
	0x87, 0xff, 0xe3, 0xfe, 0xff, 0x3f, 0xff, 0xfb, 0xfe, 0xfc, 0x7f, 0xff, 0xff, 0xfe, 0xf9, 0xff, 
	0xff, 0xff, 0xfe, 0xf3, 0xff, 0xff, 0xff, 0xfe, 0xe7, 0xff, 0xfc, 0x03, 0xfe, 0xcf, 0xff, 0xe0, 
	0x00, 0xde, 0xcf, 0xff, 0x80, 0x00, 0x6e, 0x9f, 0xfe, 0x00, 0x00, 0x3e, 0x9f, 0xfc, 0x00, 0x00, 
	0x16, 0x3f, 0xf8, 0x00, 0x00, 0x0e, 0x3f, 0xf8, 0x00, 0x63, 0x0a, 0x7f, 0xf3, 0x80, 0xff, 0x02, 
	0x7f, 0xff, 0x80, 0x7f, 0x04, 0x7f, 0xff, 0x00, 0x3e, 0x04, 0x7f, 0xfe, 0x00, 0x7e, 0x04, 0xff, 
	0xdf, 0x00, 0x7f, 0x02, 0xff, 0xbf, 0x80, 0xf7, 0x82, 0xff, 0xfb, 0x80, 0x63, 0x00, 0xff, 0x70, 
	0x80, 0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0x02, 0x7f, 0x00, 0x00, 0x00, 0x20, 0x7f, 0x00, 0x3f, 
	0x00, 0x04, 0x3f, 0x00, 0x7f, 0x80, 0x04, 0x3f, 0x00, 0x7f, 0x80, 0x04, 0x3f, 0x00, 0xff, 0xc0, 
	0x00, 0x1f, 0x00, 0xff, 0xc0, 0x08, 0x9f, 0x80, 0xe0, 0xc0, 0x02, 0xcf, 0x80, 0x00, 0x00, 0x16, 
	0xc7, 0x80, 0x00, 0x00, 0x06, 0xe3, 0xc0, 0x00, 0x00, 0x0e, 0xf1, 0xc0, 0x08, 0x00, 0x1e, 0xfc, 
	0xe0, 0x3a, 0x00, 0x3e, 0xfe, 0x38, 0x3c, 0x00, 0xfe, 0xff, 0x8c, 0x3c, 0x03, 0xfe, 0xff, 0xf1, 
	0x7d, 0x1f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xfe
};


// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 192)
const int epd_bitmap_allArray_LEN = 3;
const unsigned char* epd_bitmap_allArray[3] = {
	epd_bitmap_ONE_OUTLET ,epd_bitmap_outlet_off,epd_bitmap_horizontal__dead_outlet
};
