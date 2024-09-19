#include <stdio.h>
#include <string.h>

#define BLUE "\e[44m"
#define YELLOW "\e[103m"
#define GREEN "\e[42m"
#define RESET "\e[0m"

int main()
{
    printf(GREEN "                              " YELLOW "     " GREEN "                              \n");
    printf("                           " YELLOW "           " GREEN "                           \n");
    printf("                        " YELLOW "                 " GREEN "                        \n");
    printf("                     " YELLOW "                       " GREEN "                     \n");
    printf("                  " YELLOW "                             " GREEN "                  \n");
    printf("               " YELLOW "             " BLUE "         " YELLOW "             " GREEN "               \n");
    printf("            " YELLOW "             " BLUE "               " YELLOW "             " GREEN "            \n");
    printf("         " YELLOW "              " BLUE "                   " YELLOW "              " GREEN "         \n");
    printf("      " YELLOW "                " BLUE "                     " YELLOW "                " GREEN "      \n");
    printf("   " YELLOW "                  " BLUE "                       " YELLOW "                  " GREEN "   \n");
    printf(YELLOW "                     " BLUE "                       " YELLOW "                     \n");
    printf(GREEN "   " YELLOW "                  " BLUE "                       " YELLOW "                  " GREEN "   \n");
    printf("      " YELLOW "                " BLUE "                     " YELLOW "                " GREEN "      \n");
    printf("         " YELLOW "              " BLUE "                   " YELLOW "              " GREEN "         \n");
    printf("            " YELLOW "             " BLUE "               " YELLOW "             " GREEN "            \n");
    printf("               " YELLOW "             " BLUE "         " YELLOW "             " GREEN "               \n");
    printf("                  " YELLOW "                             " GREEN "                  \n");
    printf("                     " YELLOW "                       " GREEN "                     \n");
    printf("                        " YELLOW "                 " GREEN "                        \n");
    printf("                           " YELLOW "           " GREEN "                           \n");
    printf("                              " YELLOW "     " GREEN "                              ");

    return 0;
}
