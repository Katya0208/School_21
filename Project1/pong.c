#include <stdio.h>

#define base_ball_y 12
#define base_ball_x1 2
#define base_ball_x2 77
#define base_racket_y 12

void start_screen();
void clear_screen(void);
void draw_winner(int a);
void display(int racket1_x, int racket1_y, int racket2_x, int racket2_y,
             int ball_x, int ball_y, int screen1, int screen2);

int main() {
  int racket1_x = 1, racket1_y = 12, racket2_x = 78, racket2_y = 12;
  int ball_x = 2, ball_y = 12;
  int screen1 = 0, screen2 = 0;
  int flag_of_win = 0;
  int move_ball_x = 1, move_ball_y = 1;
  int goalF = 0;
  clear_screen();
  start_screen();
  char tap;
  tap = getchar();

  if (tap == ' ' || tap == '\n') {
    clear_screen();
    display(racket1_x, racket1_y, racket2_x, racket2_y, ball_x, ball_y, screen1,
            screen2);
  }

  while (1) {
    char comd;
    comd = getchar();
    printf("\033[2k");
    if ((comd == 'A' || comd == 'a' || comd == 'z' || comd == 'Z' ||
         comd == 'K' || comd == 'k' || comd == 'M' || comd == 'm' ||
         comd == ' ') &&
        comd != '\n') {
      if (ball_y == 1 || ball_y == 23) {
        move_ball_y *= -1;
      }
      ball_x += move_ball_x;
      ball_y += move_ball_y;

      if (goalF != 1) {
        if ((comd == 'A' || comd == 'a') && racket1_y - 2 > 0) {
          racket1_y--;
        } else if ((comd == 'Z' || comd == 'z') && racket1_y + 2 < 24) {
          racket1_y++;
        } else if ((comd == 'K' || comd == 'k') && racket2_y - 2 > 0) {
          racket2_y--;
        } else if ((comd == 'M' || comd == 'm') && racket2_y + 2 < 24) {
          racket2_y++;
        }
      }

      if ((((ball_y == racket1_y - 1) || (ball_y == racket1_y) ||
            (ball_y == racket1_y + 1)) &&
           ball_x == 2) ||
          (((ball_y == racket2_y - 1) || (ball_y == racket2_y) ||
            (ball_y == racket2_y + 1)) &&
           ball_x == 77)) {
        move_ball_x *= -1;
      } else if (ball_x == 1) {
        screen2++;
        ball_x = base_ball_x1;
        ball_y = base_ball_y;
        racket1_y = base_racket_y, racket2_y = base_racket_y;
        move_ball_x = 1;
        goalF = 1;
      } else if (ball_x == 78) {
        screen1++;
        ball_x = base_ball_x2;
        ball_y = base_ball_y;
        racket1_y = base_racket_y, racket2_y = base_racket_y;
        move_ball_x = -1;
        goalF = 1;
      }

      if (screen1 == 21) {
        flag_of_win = 1;
      }
      if (screen2 == 21) {
        flag_of_win = 2;
      }
      if (flag_of_win == 1) {
        clear_screen();
        draw_winner(flag_of_win);
        return 0;
      } else if (flag_of_win == 2) {
        clear_screen();
        draw_winner(flag_of_win);
        return 0;
      }
      clear_screen();
      display(racket1_x, racket1_y, racket2_x, racket2_y, ball_x, ball_y,
              screen1, screen2);
    } else {
      continue;
    }
  }
  return 0;
}

void display(int racket1_x, int racket1_y, int racket2_x, int racket2_y,
             int ball_x, int ball_y, int screen1, int screen2) {
  char vertical = '|';
  char horizontal = '-';
  char space = ' ';
  char racket1 = '$', racket2 = '$';
  char ball = '0';

  printf("              Player 1                 ");
  printf("                  Player 2\n");

  if (screen1 < 10) {
    for (int i = 0; i < 80; i++) {
      if (i == 35) {
        printf("%d", screen1);
      } else if (i == 45) {
        printf("%d", screen2);
      } else if (i == 40) {
        printf(":");
      } else {
        printf("%c", space);
      }
    }
  } else {
    for (int i = 0; i < 80; i++) {
      if (i == 34) {
        printf("%d", screen1);
      } else if (i == 44) {
        printf("%d", screen2);
      } else if (i == 39) {
        printf(":");
      } else {
        printf("%c", space);
      }
    }
  }
  printf("\n");
  for (int y = 0; y <= 24; y++) {
    for (int x = 0; x <= 79; x++) {
      if (y == 0 || y == 24) {
        printf("%c", horizontal);
      } else if (x == ball_x && y == ball_y) {
        printf("%c", ball);
      } else if (x == 0 || x == 40 || x == 79) {
        printf("%c", vertical);
      } else if ((x == racket1_x && y == racket1_y) ||
                 (x == racket1_x && y - 1 == racket1_y) ||
                 (x == racket1_x && y + 1 == racket1_y)) {
        printf("%c", racket1);
      } else if ((x == racket2_x && y == racket2_y) ||
                 (x == racket2_x && y - 1 == racket2_y) ||
                 (x == racket2_x && y + 1 == racket2_y)) {
        printf("%c", racket2);
      } else {
        printf("%c", space);
      }
    }
    printf("\n");
  }
}

void start_screen() {
  printf(
      "------------------------------------------------------------------------"
      "--------\n");
  printf(
      "|                                                                       "
      "       |\n");
  printf(
      "|                      ____     ____              ______                "
      "       |\n");
  printf(
      "|                     |    |   |    |   |\\    |  |      |              "
      "        |\n");
  printf(
      "|                     |    |   |    |   | \\   |  |      |              "
      "        |\n");
  printf(
      "|                     |____|   |    |   |  \\  |  |   ___               "
      "        |\n");
  printf(
      "|                     |        |    |   |   \\ |  |      |              "
      "        |\n");
  printf(
      "|                     |        |____|   |    \\|  |______|              "
      "        |\n");
  printf(
      "|                                                                       "
      "       |\n");
  printf(
      "|                                                                       "
      "       |\n");
  printf(
      "|                            TWO PLAYERS ONE WINNER                     "
      "       |\n");
  printf(
      "|                                                                       "
      "       |\n");
  printf(
      "|                                    RULES:                             "
      "       |\n");
  printf(
      "|                                                                       "
      "       |\n");
  printf(
      "|                      1. each player must move                         "
      "       |\n");
  printf(
      "|                         his racket to catch the ball                  "
      "       |\n");
  printf(
      "|                                                                       "
      "       |\n");
  printf(
      "|                      2. if the ball does not hit                      "
      "       |\n");
  printf(
      "|                         the racket, the opponent gets                 "
      "       |\n");
  printf(
      "|                         a point and a new round begins                "
      "       |\n");
  printf(
      "|                                                                       "
      "       |\n");
  printf(
      "|                      3. the game ends when the score                  "
      "       |\n");
  printf(
      "|                         becomes 21 points                             "
      "       |\n");
  printf(
      "|                                                                       "
      "       |\n");
  printf(
      "|                           PRESS ENTER OR SPACE                        "
      "       |\n");
  printf(
      "------------------------------------------------------------------------"
      "--------\n");
}

void draw_winner(int a) {
  if (a == 1) {
    printf(
        "----------------------------------------------------------------------"
        "----------\n");
    printf(
        "|                                                                     "
        "         |\n");
    printf(
        "|                                                                     "
        "         |\n");
    printf(
        "|                                                                     "
        "         |\n");
    printf(
        "|                       |       |        |   |    |\\     |           "
        "          |\n");
    printf(
        "|                       |       |        |   |    | \\    |           "
        "          |\n");
    printf(
        "|                       |       |        |   |    |  \\   |           "
        "          |\n");
    printf(
        "|                       |       |        |   |    |   \\  |           "
        "          |\n");
    printf(
        "|                       |        \\  /\\  /    |    |    \\ |         "
        "            |\n");
    printf(
        "|                       |         \\/  \\/     |    |     \\|         "
        "            |\n");
    printf(
        "|                                                                     "
        "         |\n");
    printf(
        "|                                                                     "
        "         |\n");
    printf(
        "|                                                                     "
        "         |\n");
    printf(
        "|                                CONGRATULATIONS!                     "
        "         |\n");
    printf(
        "|                                ---------------                      "
        "         |\n");
    printf(
        "|                                                                     "
        "         |\n");
    printf(
        "----------------------------------------------------------------------"
        "----------\n");

  } else if (a == 2) {
    printf(
        "----------------------------------------------------------------------"
        "----------\n");
    printf(
        "|                                                                     "
        "         |\n");
    printf(
        "|                                                                     "
        "         |\n");
    printf(
        "|                     ____                                            "
        "         |\n");
    printf(
        "|                    |    |      |        |   |    |\\     |          "
        "          |\n");
    printf(
        "|                    |    |      |        |   |    | \\    |          "
        "          |\n");
    printf(
        "|                        /       |        |   |    |  \\   |          "
        "          |\n");
    printf(
        "|                       /        |        |   |    |   \\  |          "
        "          |\n");
    printf(
        "|                      /          \\  /\\  /    |    |    \\ |        "
        "            |\n");
    printf(
        "|                     /____        \\/  \\/     |    |     \\|        "
        "            |\n");
    printf(
        "|                                                                     "
        "         |\n");
    printf(
        "|                                                                     "
        "         |\n");
    printf(
        "|                                                                     "
        "         |\n");
    printf(
        "|                                CONGRATULATIONS!                     "
        "         |\n");
    printf(
        "|                                ---------------                      "
        "         |\n");
    printf(
        "|                                                                     "
        "         |\n");
    printf(
        "----------------------------------------------------------------------"
        "----------\n");
  }
}

void clear_screen() { printf("\33c\e[3J"); }