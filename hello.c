#include <stdio.h>

int main(int argc, char**argv) {
      if (argc == 1) {
            char name[129];
            printf("What is your name? ");
            scanf("%[^\n]s", name);

            if (name[0] == 0) {
                  return 1;
            }
            printf("Hello, %s\n",name);
            return 0;
      }
      else {
            printf("Hello, %s\n", argv[1]);
            return 0;
      }
}
