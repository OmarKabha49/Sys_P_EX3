#include <stdio.h>
#include "StrList.h"

int StrList_CountTheCharacters(StrList* strList);

int main() {

    StrList* p1 = StrList_alloc();
    int c = -1;

    while (c != 0){
        scanf("%d",&c);
        switch (c) {

            case 1: {
                int length;
                scanf("%d", &length);
                char input[100];
                for (int i = 0; i < length; ++i) {
                    scanf("%s", input);
                    StrList_insertLast(p1, input);
                }
                break;
            }

            case 2: {
                int index;
                char str[100];
                scanf("%d", &index);
                scanf("%s", str);
                StrList_insertAt(p1,str,index);
                break;
            }

            case 3:{
                StrList_print(p1);
                printf("\n");
                break;
            }

            case 4:{
                printf("%zu\n", StrList_size(p1));
                break;
            }

            case 5:{
                int index;
                scanf("%d",&index);
                StrList_printAt(p1,index);
                printf("\n");
                break;
            }

            case 6:{
                int numOfCharacters = StrList_CountTheCharacters(p1);
                printf("%d\n",numOfCharacters);
                break;
            }

            case 7:{
                char str[100];
                scanf("%s",str);
                int count = StrList_count(p1,str);
                printf("%d\n",count);
                break;
            }

            case 8:{
                char str[100];
                scanf("%s",str);
                StrList_remove(p1,str);
                break;
            }

            case 9:{
                int index;
                scanf("%d",&index);
                StrList_removeAt(p1,index);
                break;
            }

            case 10:{
                StrList_reverse(p1);
                break;
            }

            case 11:{
                while (StrList_size(p1) > 0){
                    StrList_removeAt(p1,0);
                }
                break;
            }

            case 12:{
                StrList_sort(p1);
                break;
            }

            case 13:{
                int isSorted = StrList_isSorted(p1);
                printf("%s\n",isSorted == 1 ? "true" : "false");
                break;
            }

            case 0:{
                exit(0);
            }

        }
    }






    StrList_free(p1);
    return 0;
}
