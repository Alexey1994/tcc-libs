#ifndef TTF_FONT_GRAPHICS_INCLUDED
#define TTF_FONT_GRAPHICS_INCLUDED


#include <file.c>
#include <reader.c>
#include <data-structures/stack.c>
#include <memory.c>


typedef enum {
	POINT_ON_CURVE = 0b00000001,
	SHORT_X        = 0b00000010,
	SHORT_Y        = 0b00000100,
	REPEAT_FLAG    = 0b00001000,
	X_IS_SAME      = 0b00010000,
	Y_IS_SAME      = 0b00100000,
	X_IS_POSITIVE  = 0b00010000,
	Y_IS_POSITIVE  = 0b00100000
}
TTF_Glyph_Attribute;

typedef enum {
	ARG_1_AND_2_ARE_WORDS    = 0b00000001,
	ARGS_ARE_XY_VALUES       = 0b00000010,
	ROUND_XY_TO_GRID         = 0b00000100,
	WE_HAVE_A_SCALE          = 0b00001000,
	MORE_COMPONENTS          = 0b00100000,
	WE_HAVE_AN_X_AND_Y_SCALE = 0b01000000,
	WE_HAVE_A_TWO_BY_TWO     = 0b10000000,
	WE_HAVE_INSTRUCTIONS     = 0b100000000,
	USE_MY_METRICS           = 0b1000000000,
	OVERLAP_COMPOUND         = 0b10000000000
}
TTF_Composite_Glyph_Attribute;

typedef struct {
	Signed_Number16 x;
	Signed_Number16 y;
	Boolean         on_curve;
}
TTF_Glyph_Point;

typedef struct {
	Number16         number_of_points;
	TTF_Glyph_Point* points;
}
TTF_Glyph_Contour;

typedef struct {
	Signed_Number16    min_x;
	Signed_Number16    min_y;
	Signed_Number16    max_x;
	Signed_Number16    max_y;
	Signed_Number16    number_of_contours;
	TTF_Glyph_Contour* contours;
}
TTF_Glyph;

typedef struct {
	TTF_Glyph* glyphs;
	Number16   number_of_glyphs;

	Signed_Number16 min_x;
	Signed_Number16 min_y;
	Signed_Number16 max_x;
	Signed_Number16 max_y;
}
TTF;


static Boolean read_TTF_glyph(Reader* reader, TTF_Glyph* glyph)
{
	Number16        number_of_points;
	Number          previouse_points_index;
	Number16        instructions_size;
	Number          i;
	Number          j;
	Number          k;
	Stack           attributes;
	Byte            attribute;
	Number8         number_of_repeatable_attributes;
	Signed_Number16 coord;
	Signed_Number16 long_coord;
	Number          bytes_readed;
	Number          align;

	glyph->number_of_contours = read_binary_Signed_Number16(reader);
	revert_bytes_order(&glyph->number_of_contours, sizeof(glyph->number_of_contours));

	glyph->min_x = read_binary_Number16(reader);
	glyph->min_y = read_binary_Number16(reader);
	glyph->max_x = read_binary_Number16(reader);
	glyph->max_y = read_binary_Number16(reader);
	revert_bytes_order(&glyph->min_x, sizeof(glyph->min_x));
	revert_bytes_order(&glyph->min_y, sizeof(glyph->min_y));
	revert_bytes_order(&glyph->max_x, sizeof(glyph->max_x));
	revert_bytes_order(&glyph->max_y, sizeof(glyph->max_y));

	if(!glyph->number_of_contours) {
		return 0;
	}

	bytes_readed = 0;

	if(glyph->number_of_contours < 0) {
		//не реализованы

		Number16 attribute2;
		Number16 glyph_index;
		Number16 argument1;
		Number16 argument2;

		Number16 a;
		Number16 b;
		Number16 c;
		Number16 d;

		do {
			attribute2 = read_binary_Number16(reader);
			glyph_index = read_binary_Number16(reader);
			revert_bytes_order(&attribute2, sizeof(attribute2));
			revert_bytes_order(&glyph_index, sizeof(glyph_index));
			bytes_readed += 2;

			if(attribute2 & ARGS_ARE_XY_VALUES) {
				if(attribute2 & ARG_1_AND_2_ARE_WORDS) {
					argument1 = read_binary_Number16(reader);
					argument2 = read_binary_Number16(reader);
					bytes_readed += 2;
				}
				else {
					argument1 = read_binary_Number8(reader);
					argument2 = read_binary_Number8(reader);
					bytes_readed += 2;
				}
			}

			if(attribute2 & WE_HAVE_A_SCALE) {
				d = a = read_binary_Number16(reader);
				++bytes_readed;
			}
			else if(attribute2 & WE_HAVE_AN_X_AND_Y_SCALE) {
				a = read_binary_Number16(reader);
				d = read_binary_Number16(reader);
				bytes_readed += 2;
			}
			else if(attribute2 & WE_HAVE_A_TWO_BY_TWO) {
				a = read_binary_Number16(reader);
				b = read_binary_Number16(reader);
				c = read_binary_Number16(reader);
				d = read_binary_Number16(reader);
				bytes_readed += 4;
			}
		}
		while(attribute2 & MORE_COMPONENTS);

		if(attribute2 & WE_HAVE_INSTRUCTIONS) {
			Number16 number_of_instructions;

			number_of_instructions = read_binary_Number16(reader);
			revert_bytes_order(&number_of_instructions, sizeof(number_of_instructions));
			bytes_readed += 2 + number_of_instructions;

			for(i = 0; i < number_of_instructions; ++i) {
				read_binary_Number8(reader);
			}
		}
	}
	else {
		glyph->contours = allocate_memory(glyph->number_of_contours * sizeof(TTF_Glyph_Contour));

		previouse_points_index = -1;
		for(i = 0; i < glyph->number_of_contours; ++i) {
			number_of_points = read_binary_Number16(reader);
			revert_bytes_order(&number_of_points, sizeof(number_of_points));
			bytes_readed += 2;
			glyph->contours[i].number_of_points = number_of_points - previouse_points_index;
			previouse_points_index = number_of_points;
		}
		++number_of_points;

		instructions_size = read_binary_Number16(reader);
		revert_bytes_order(&instructions_size, sizeof(instructions_size));
		bytes_readed += instructions_size;
		for(i = 0; i < instructions_size; ++i) {
			read_binary_Number8(reader);
		}

		initialize_stack(&attributes, 128);
		{
			for(i = 0; i < number_of_points; ++i) {
				attribute = read_binary_Number8(reader);
				++bytes_readed;

				if(attribute & REPEAT_FLAG) {
					number_of_repeatable_attributes = read_binary_Number8(reader);
					++bytes_readed;
					add_bytes_in_stack(&attributes, &attribute, sizeof(attribute));

					for(j = 0; j < number_of_repeatable_attributes; ++j) {
						add_bytes_in_stack(&attributes, &attribute, sizeof(attribute));
					}

					i += number_of_repeatable_attributes;
				}
				else {
					add_bytes_in_stack(&attributes, &attribute, sizeof(attribute));
				}
			}

			for(i = 0; i < glyph->number_of_contours; ++i) {
				glyph->contours[i].points = allocate_memory(glyph->contours[i].number_of_points * sizeof(TTF_Glyph_Point));
			}
		
			coord = 0;
			k = 0;
			for(i = 0; i < glyph->number_of_contours; ++i) {
				for(j = 0; j < glyph->contours[i].number_of_points; ++j) {
					attribute = attributes.data[k];

					if(attribute & SHORT_X) {
						if(attribute & X_IS_POSITIVE)
							coord += read_binary_Number8(reader);
						else
							coord -= read_binary_Number8(reader);
						++bytes_readed;
					}
					else if(!(attribute & X_IS_SAME)) {
						long_coord = read_binary_Number16(reader);
						revert_bytes_order(&long_coord, sizeof(long_coord));
						bytes_readed += 2;
						coord += long_coord;
					}

					glyph->contours[i].points[j].x = coord;
					++k;
				}
			}

			coord = 0;
			k = 0;
			for(i = 0; i < glyph->number_of_contours; ++i) {
				for(j = 0; j < glyph->contours[i].number_of_points; ++j) {
					attribute = attributes.data[k];

					if(attribute & SHORT_Y) {
						if(attribute & Y_IS_POSITIVE) {
							coord += read_binary_Number8(reader);
						}
						else {
							coord -= read_binary_Number8(reader);
						}
						
						++bytes_readed;
					}
					else if(!(attribute & Y_IS_SAME)) {
						long_coord = read_binary_Number16(reader);
						revert_bytes_order(&long_coord, sizeof(long_coord));
						bytes_readed += 2;
						coord += long_coord;
					}

					glyph->contours[i].points[j].y = coord;
					glyph->contours[i].points[j].on_curve = attribute & POINT_ON_CURVE;
					++k;
				}
			}
		}
		deinitialize_stack(&attributes);
	}

	align = (2 - (bytes_readed) % 2) % 2;
	while(align) {
		read_binary_Number8(reader);
		--align;
	}

/*
	printf("(%d, %d, %d, %d)\n", glyph->min_x, glyph->min_y, glyph->max_x, glyph->max_y);
	for(i = 0; i < glyph->number_of_contours; ++i) {
		printf("contour %d\n", i);

		for(j = 0; j < glyph->contours[i].number_of_points; ++j) {
			if(glyph->contours[i].points[j].on_curve)
				printf("(%d, %d)\n", glyph->contours[i].points[j].x, glyph->contours[i].points[j].y);
			else
				printf("C(%d, %d)\n", glyph->contours[i].points[j].x, glyph->contours[i].points[j].y);
		}

		printf("\n");
	}*/

	return 1;
}


Boolean set_TTF_header_position(Reader* reader, Number16 number_of_tables, Byte* header_name)
{
	Number32     checksum;
	Number32     offset;
	Number32     size;
	Number       i;
	Byte         tag_name[4];

	set_file_position(reader->source, 12);
	initialize_reader(reader, reader->source, reader->read_bytes, reader->queue.buffer, reader->queue.buffer_size);

	for(i = 0; i < number_of_tables; ++i) {
		read_bytes(reader, tag_name, 4);

		checksum = read_binary_Number32(reader);
		offset   = read_binary_Number32(reader);
		size     = read_binary_Number32(reader);

		if(!compare_bytes(tag_name, 4, header_name, 4)) {
			revert_bytes_order(&offset, sizeof(offset));
			revert_bytes_order(&size, sizeof(size));
			set_file_position(reader->source, offset);
			initialize_reader(reader, reader->source, reader->read_bytes, reader->queue.buffer, reader->queue.buffer_size);
			return 1;
		}
	}

	return 1;

error:
	return 0;
}


Boolean read_TTF(TTF* ttf, Reader* reader)
{
	Number16     number_of_tables;
	Number16     search_range;
	Number16     entry_selector;
	Number16     range_shift;
	Byte         tag_name[4];
	Number32     checksum;
	Number32     offset;
	Number32     size;
	Number       i;
	Number       j;
	Number       align;

	Number16     index_to_location_format;
	Number32*    locations;
	Number       number_of_glyphs_in_table;

	if(!read_if_bytes(reader, "\x00\x01\x00\x00", 4)) {
		goto error;
	}

	number_of_tables = read_binary_Number16(reader);
	search_range     = read_binary_Number16(reader);
	entry_selector   = read_binary_Number16(reader);
	range_shift      = read_binary_Number16(reader);

	revert_bytes_order(&number_of_tables, sizeof(number_of_tables));
	revert_bytes_order(&search_range, sizeof(search_range));
	revert_bytes_order(&entry_selector, sizeof(entry_selector));
	revert_bytes_order(&range_shift, sizeof(range_shift));

	if(!set_TTF_header_position(reader, number_of_tables, "head"))
		goto error;

	read_binary_Number32(reader); //version
	read_binary_Number32(reader); //revision
	read_binary_Number32(reader); //checksum
	read_binary_Number32(reader); //magic number
	read_binary_Number16(reader); //attributes
	read_binary_Number16(reader); //units per em
	read_binary_Number64(reader); //created
	read_binary_Number64(reader); //modified
	ttf->min_x = read_binary_Number16(reader);
	ttf->min_y = read_binary_Number16(reader);
	ttf->max_x = read_binary_Number16(reader);
	ttf->max_y = read_binary_Number16(reader);
	revert_bytes_order(&ttf->min_x, sizeof(ttf->min_x));
	revert_bytes_order(&ttf->min_y, sizeof(ttf->min_y));
	revert_bytes_order(&ttf->max_x, sizeof(ttf->max_x));
	revert_bytes_order(&ttf->max_y, sizeof(ttf->max_y));
	read_binary_Number16(reader); //style
	read_binary_Number16(reader); //smallest readable size in pixels
	read_binary_Number16(reader); //deprecated
	index_to_location_format = read_binary_Number16(reader);
	revert_bytes_order(&index_to_location_format, sizeof(index_to_location_format));

	if(!set_TTF_header_position(reader, number_of_tables, "maxp")) {
		goto error;
	}

	read_binary_Number32(reader);//version
	ttf->number_of_glyphs = read_binary_Number16(reader);
	revert_bytes_order(&ttf->number_of_glyphs, sizeof(ttf->number_of_glyphs));

	if(!set_TTF_header_position(reader, number_of_tables, "loca")) {
		goto error;
	}

	locations = allocate_memory(ttf->number_of_glyphs * sizeof(*locations));

	if(!index_to_location_format) {
		for(i = 0; i < ttf->number_of_glyphs; ++i) {
			Number16 map = read_binary_Number16(reader);
			revert_bytes_order(&map, sizeof(map));
			locations[i] = map * 2;
			//printf("%d -> %d\n", locations[i], i);
		}
	}
	else if(index_to_location_format == 1) {
		for(i = 0; i < ttf->number_of_glyphs; ++i) {
			Number32 map = read_binary_Number32(reader);
			revert_bytes_order(&map, sizeof(map));
			locations[i] = map;
			//printf("%d -> %d\n", locations[i], i);
		}
	}
	else {
		print_error("location format error");
		goto error;
	}

	number_of_glyphs_in_table = 1;
	for(i = 0; i < ttf->number_of_glyphs - 1; ++i) {
		if(locations[i] != locations[i + 1]) {
			++number_of_glyphs_in_table;
		}
	}

	if(!set_TTF_header_position(reader, number_of_tables, "glyf")) {
		goto error;
	}

	ttf->glyphs = allocate_memory(ttf->number_of_glyphs * sizeof(TTF_Glyph));

	for(i = 0; i < number_of_glyphs_in_table; ++i) {
		read_TTF_glyph(reader, ttf->glyphs + i);
	}

	return 1;

	error: {
		print_error("ttf error");
		return 0;
	}
}


void TTF_to_HTML(TTF* ttf)
{
	TTF_Glyph*         glyph;
	TTF_Glyph_Contour* contour;
	TTF_Glyph_Point*   point1;
	TTF_Glyph_Point*   point2;
	Number i;
	Number j;
	Number k;
	
	print("<html><head><meta charset=\"utf8\"></head><body>");
	
	for(i = 0; i < ttf->number_of_glyphs; ++i) {
		glyph = ttf->glyphs + i;
		
		if(glyph->number_of_contours < 0) {
			continue;
		}
		
		print(
			"<svg style=\"transform: scale(1, -1)\" width=\"%d\" height=\"%d\">",
			(ttf->max_x - ttf->min_x)/80,
			(ttf->max_y - ttf->min_y)/80
		);
		print("<path transform=\"scale(0.0125) translate(%d %d)\" d=\"", -ttf->min_x, -ttf->min_y);
		
		for(j = 0; j < glyph->number_of_contours; ++j) {
			contour = glyph->contours + j;

				for(k = 0; k < contour->number_of_points; ++k) {
					if(k == contour->number_of_points - 1) {
						point1 = contour->points + k;
						point2 = contour->points;
					}
					else {
						point1 = contour->points + k;
						point2 = contour->points + k + 1;
					}

					if(!k) {
						print(" M%d,%d", point1->x, point1->y);
					}
					else {
						if(point1->on_curve) {
							print(" L%d,%d", point1->x, point1->y);
						}
						else if(point2->on_curve) {
							print(" Q%d,%d %d,%d", point1->x, point1->y, point2->x, point2->y);

							++k;
						}
						else {
							print(" Q%d,%d %d,%d", point1->x, point1->y, (point1->x + point2->x) / 2, (point1->y + point2->y) / 2);
						}
					}
				}
		}
		
		print("\"></path>");
		print("</svg>");
	}
	
	print("</html></body>");
}


#endif//TTF_FONT_GRAPHICS_INCLUDED


Number main(Number number_of_arguments, Byte** arguments)
{
	TTF ttf;
	
	File file;
	Reader reader;
	Byte reader_buffer[32];
	
	file = open_file("DroidSansMono.ttf");
	initialize_reader(&reader, file, &read_bytes_from_file, reader_buffer, sizeof(reader_buffer));
	read_TTF(&ttf, &reader);
	close_file(file);

	TTF_to_HTML(&ttf);
	
	return 0;
}