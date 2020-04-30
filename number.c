#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

const char slant[90] =
        "/\\ \\ \\ \\/ \\   \\   /\\  /  \\//\\  /\\  / \\ \\/\\   /  \\/\\  //  \\/\\ \\//\\   \\   /\\ \\/\\ \\//\\ \\/\\  /";

const char *
get_font(char c, int i)
{
	return c == ' ' ? "   " : slant + (c - 48) * 9 + i * 3;
}

void
print_number(char *str, int len)
{
	int i;

	int x = (len - 1) * 2, y = 0;
	int width = len * 2 + 2, height = len * 2 + 1;

	char *c = str + len - 1;
	char *buf = malloc(height * width);

	for (i = 0; i < (len == 1 ? 3 : 2); ++i) {
		memset(buf + i * width, ' ', x);
		memcpy(buf + i * width + x, get_font(*c, i), 3);
		buf[i * width + x + 3] = '\0';
	}

	for (c = str + len - 2; c >= str; --c) {
		x -= 2;
		y += 2;

		for (i = 0; i < 3; ++i) {
			memset(buf + (y + i) * width, ' ', x);
			memcpy(buf + (y + i) * width + x, get_font(*c, i), 3);

			if (i) {
				buf[(y + i) * width + x + 3] = '\0';
				continue;
			}

			memcpy(buf + (y + i) * width + x + 2,
			       get_font(*(c + 1), 2), 3);
			buf[(y + i) * width + x + 5] = '\0';
		}
	}

	for (i = 0; i < height ; ++i)
		printf("%s\n", buf + i * width);

	free(buf);
}

void
remove_letters(char *c, int *len)
{
	int i, j;

	for (i = j = 0; i < *len; ++i) {
		if (isdigit(c[i]))
			c[j++] = c[i];
		else if (isspace(c[i]))
			c[j++] = ' ';
	}

	c[j] = '\0';
	*len = j - 1;
}

int
main(void)
{
	int len;
	char str[MAX_LEN];

	fgets(str, MAX_LEN, stdin);
	len = strlen(str);

	remove_letters(str, &len);

	print_number(str, len);

	return 0;
}
