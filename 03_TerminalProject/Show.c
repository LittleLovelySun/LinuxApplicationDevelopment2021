#include <ncurses.h>
#include <stdlib.h>


const int DX = 3;

const int ESCAPE = 27;

const int SPACE = 32;
const int DOWN = 2;
const int UP = 3;

const int RIGHT = 5;
const int LEFT = 4;

const int PAGE_UP = 83;
const int PAGE_DOWN = 82;

void print_info(const char* name, int string_count) {
   printw("Name: %s\tSize: %d", name, string_count);
   refresh();
}

void print_box(WINDOW *win, char** strings, size_t string_count, size_t start_line, size_t lines, size_t start_col, size_t cols) {
   werase(win);
   wprintw(win, "\n");

   for (int i = start_line; i < string_count && i <= start_line + lines; i++) {
      wprintw(win, " %d:   ", i + 1);

      int j = 0;

      while (strings[i][j] && j < start_col)
         j++;

      for (; j >= start_col && strings[i][j] && j <= start_col + cols; j++)
         wprintw(win, "%c", strings[i][j]);

      wprintw(win, "\n");
   }

   box(win, 0, 0);
   wmove(win, 2, 0);
}

void display(char** strings, size_t string_count, size_t max_col_len) {
   size_t lines = LINES - 2 * DX;
   size_t cols = COLS - 2 * DX;

   size_t start_line = 0;
   size_t start_col = 0;

   WINDOW *win = newwin(lines, cols, DX, DX);
   keypad(win, TRUE);
   
   print_box(win, strings, string_count, start_line, lines, start_col, cols);
   lines -= 2;
   cols -= 2;
   
   char c;
   while ((c = wgetch(win)) != ESCAPE) {
      if ((c == SPACE || c == DOWN) && start_line < string_count) {
         start_line++;
      }
      else if (c == UP && start_line > 0) {
         start_line--;
      }
      else if (c == RIGHT && start_col < max_col_len - 1) {
         start_col++;
      }
      else if (c == LEFT && start_col > 0) {
         start_col--;
      }
      else if (c == PAGE_UP) {
         start_line = lines >= start_line ? 0 : start_line - lines;
      }
      else if (c == PAGE_DOWN) {
         start_line = start_line + lines > string_count - 1 ? string_count - 1 : start_line + lines;
      }

      wprintw(win, "%d\n", start_line);
      print_box(win, strings, string_count, start_line, lines, start_col, cols);
   }
}

char* get_string(FILE* f, size_t *len) {
   size_t capacity = 1;
   char* s = (char*)malloc(capacity * sizeof(char));
   *len = 0;

   for (char c = fgetc(f); c != '\n' && c != EOF; c = fgetc(f)) {
      s[(*len)++] = c;

      if (*len >= capacity) {
         capacity *= 2;
         s = (char*)realloc(s, capacity * sizeof(char));
      }
   }

   s[*len] = '\0';
   return s;
}


char** get_file_strings(const char* file_name, size_t *string_count, size_t *max_col_len) {
   FILE *f = fopen(file_name, "r");

   if (!f) {
      endwin();
      fprintf(stderr, "No such file: %s\n", file_name);
      exit(EXIT_FAILURE);
   }

   size_t capacity = 1;
   char** strings = (char**)malloc(capacity * sizeof(char*));
   *string_count = 0;
   *max_col_len = 0;

   while (!feof(f)) {
      size_t len;
      strings[(*string_count)++] = get_string(f, &len);

      if (len > *max_col_len)
         *max_col_len = len;

      if (*string_count >= capacity) {
         capacity *= 2;
         strings = (char**)realloc(strings, capacity * sizeof(char*));
      }
   }

   fclose(f);
   return strings;
}


int main(int argc, char const *argv[]) {
   initscr();
   noecho();
   curs_set(0);
   
   size_t string_count, max_col_len;
   char** strings = get_file_strings(argv[1], &string_count, &max_col_len);

   print_info(argv[1], string_count);

   display(strings, string_count, max_col_len);
   endwin();

   for (int i = 0; i < string_count; i++)
      free(strings[i]);
   free(strings);

   return 0;
}