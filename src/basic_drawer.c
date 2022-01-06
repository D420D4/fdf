//
// Created by plefevre on 1/6/22.
//

#include "basic_drawer.h"

static int draw_inter_row(t_data *data, t_m4 mat, t_linemap line, int y) {
	int i;
	t_point t1;
	t_point t2;

	i = 0;
	while (i < line.size) {
		t1 = point_new(i- line.size/2, y - line.size_tot/2, line.line[i]);
		t2 = point_new(i- line.size/2, y + 1- line.size_tot/2, line.next->line[i]);
		drawline(data, t1, t2, mat);
		i++;
	}
	return (0);
}

int draw_row(t_data *data, t_m4 mat, t_linemap line, int y) {
	int i;
	t_point t1;
	t_point t2;

	i = 0;
	while (i < line.size - 1) {
		t1 = point_new(i - line.size/2, y - line.size_tot/2, line.line[i]);
		t2 = point_new(i + 1 - line.size/2, y- line.size_tot/2, line.line[i + 1]);
		drawline(data, t1, t2, mat);
		i++;
	}
	if (line.next)
		draw_inter_row(data, mat, line, y);
	return (0);
}