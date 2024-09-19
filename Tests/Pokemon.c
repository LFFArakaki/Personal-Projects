#include <stdio.h>
#include <string.h>

#define RED "\e[41m"
#define YELLOW "\e[103m"
#define ORANGE "\e[101m"
#define WHITE "\e[107m"
#define RESET "\e[0m"

int main()
{
    printf("      " ORANGE "        " RESET "                  " RED "  \n");
    printf(RESET "    " ORANGE "            " RESET "                " RED "    \n");
    printf(RESET "    " ORANGE "            " RESET "                " RED "    \n");
    printf(RESET "  " ORANGE "                " RESET "            " RED "        \n");
    printf(ORANGE "        " WHITE "  " RESET "  " ORANGE "      " RESET "            " RED "    " YELLOW "  " RED "  \n");
    printf(ORANGE "        " RESET "    " ORANGE "        " RESET "          " RED "  " YELLOW "    " RED "  \n");
    printf(ORANGE "        " RESET "    " ORANGE "        " RESET "            " YELLOW "  \n");
    printf(RESET "  " ORANGE "                    " RESET "          " ORANGE "  \n");
    printf(RESET "      " ORANGE "                  " RESET "      " ORANGE "    \n");
    printf(RESET "            " ORANGE "    " RESET "  " ORANGE "      " RESET "    " ORANGE "    \n");
    printf(RESET "          " YELLOW "    " RESET "  " ORANGE "          " RESET "  " ORANGE "    \n");
    printf(RESET "          " YELLOW "      " RESET "    " ORANGE "      " RESET "  " ORANGE "  \n");
    printf(RESET "        " WHITE "  " RESET "  " YELLOW "      " ORANGE "        \n");
    printf(RESET "              " YELLOW "    " ORANGE "      \n");
    printf(RESET "                    " ORANGE "  \n");
    printf(RESET "                  " WHITE "  " ORANGE "  " WHITE "  \n");
    
    

    return 0;
}
