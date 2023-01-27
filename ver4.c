#include <conio.h>
#include <dir.h>
#include <process.h>
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
#define ll long long

void mk_folder(char name[], int length){
    int check;
    char dirname[10000] = "E:\\C\\home";
    ll update = 9;
    for (int j = -1; j < length; j++) {
        if(j>=0) {
            dirname[update] += name[j];
            update++;
        } else{
            dirname[update] += '\\';
            update++;
        }
    }
    check = mkdir(dirname);
}
void makefile(char name[], int length){
    char dirname[10000] = "E:\\C\\home";
    ll update = 9;
    for (int j = -1; j < length; j++) {
        if(j>=0) {
            dirname[update] += name[j];
            update++;
        } else{
            dirname[update] += '\\';
            update++;
        }
    }
    int result=0;
    FILE *mkptr;
    mkptr = fopen(dirname, "r");
    if(mkptr!=NULL) {
        result = 1;
        printf("The file already exists!\n");
    }
    fclose(mkptr);
    if(result==0){
        mkptr = fopen(dirname, "w");
        fclose(mkptr);
    }
}
int exist_check(char name[], int length){
    FILE *mkptr;
    mkptr = fopen(name, "r");
    if(mkptr==NULL) {
        printf("The file doesn't exist!\n");
        fclose(mkptr);
        return 0;
    }
    fclose(mkptr);
    return 1;
}
void removestr(char address[], ll size,
               char direction,
               ll line, ll in){
    FILE *remptr;
    FILE *unptr;
    char *string=(char *)calloc(MAX, sizeof(char *));
    ll length, pos, volume=2;
    ll count_line =1, count_in=0;
    unptr = fopen("undo.txt", "w");
    remptr = fopen(address, "r");
    for(ll i=0;1;i++){
        if(feof(remptr)) break;
        string[i]= fgetc(remptr);
        if(i>=1) fputc(string[i-1], unptr);
        length=i;
        if(count_in==in && count_line==line) pos=i;
        if(count_line==line) count_in++;
        if(string[i]=='\n') {
            count_line++;
        }
        if((i+1)%MAX==0) string=(char*) realloc(string, (volume*MAX)* sizeof(char));
    }
    fclose(unptr);
    fclose(remptr);
    if(size>length){
        printf("Invalid size!\n");
        return;
    }
    if(count_line<line){
        printf("Invalid position!\n");
        return;
    }
    if(count_in<in){
        printf("Invalid position!\n");
        return;
    }

    if(direction=='b') {
        pos -= size;
    }
        FILE *editptr;
        editptr = fopen(address, "w");
        for(int i=0; i<length; i++){
            if(i==pos) i=i+size;
            if(i>=length) break;
            putc(string[i], editptr);
        }

        fclose(editptr);
}

int grep_print(char mid[],
                char string[],char address[],
                ll text_length, ll length,
                char how){
    ll count=0;
    ll till=0, j=0;
    ll exist=0;
    for(ll i=0;1; i++){
        if(i>text_length) break;
        if(mid[i]!=string[j]) j=0;
        if(mid[i]=='\n') till=i+1;
        if(mid[i]==string[j]) j++;
       // printf("%d     %d\n", i, j);
      //  printf("%c\n", mid[till]);
        if(j>length) {
            if(how=='c') count++;
            if(how=='n') printf("%s : ", address);
            exist=1;
            for(ll k=till; 1; k++){
              //  printf("1");
                if(mid[k]=='\n' || k>text_length) {
                    i=k;
                    till=k+1;
                    break;
                }
                if(how=='n') {
                    printf("%c", mid[k]);
                }
            }
            if(how=='n') printf("\n");
        }
    }

    if(exist==0) return -1;
    if(how=='c') return count;
    if(how=='i') {
        printf("%s\n", address);
        return 1;
    }
}

int main(){
    char cmd[1000];
    ll update;
    char qu_sl, temp;
    char *clipboard=(char *)calloc(MAX, sizeof(char *));
    ll size_clipboard=0;
    FILE *checkptr;
    FILE *unptr;
    while(1){
        char *string=(char *)calloc(MAX, sizeof(char *));
        char *path=(char *)calloc(MAX, sizeof(char *));
        scanf("%s", cmd);
   //===========================================================================
        //createfile
        if(cmd[0]=='c'&&cmd[1]=='r'&&cmd[2]=='e'&&cmd[3]=='a'&&cmd[4]=='t'&&cmd[5]=='e'&&cmd[6]=='f'&&cmd[7]=='i'&&cmd[8]=='l'&&cmd[9]=='e'){
            scanf("%s", cmd);
            if(cmd[0]=='-'&&cmd[1]=='-'&&cmd[2]=='f'&&cmd[3]=='i'&&cmd[4]=='l'&&cmd[5]=='e'){
                int spen=getchar();
                scanf("%c", &qu_sl);

                if(qu_sl=='/'){
                    ll length;
                    for(ll i=0;1;i++){
                        scanf("%c", &path[i]);
                        if(path[i]=='/') {
                            path[i] = '\\';
                            mk_folder(path, i);
                        }
                        if (path[i] == '\n') {
                            makefile(path, i);
                            break;
                        }
                    }

                }
                else if(qu_sl=='"') {

                    scanf("%c", &qu_sl);
                    if (qu_sl == '/') {
                        for(ll i=0;1;i++){
                            scanf("%c", &path[i]);
                            if(path[i]=='/') {
                                path[i] = '\\';
                                mk_folder(path, i);
                            }
                            if (path[i] == '"') {
                                makefile(path, i);
                                break;
                            }
                        }
                    }
                }
            }
            else {
                printf("Invalid command!\n");
                continue;
            }
        }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //insertstr
        else if(cmd[0]=='i'&&cmd[1]=='n'&&cmd[2]=='s'&&cmd[3]=='e'&&cmd[4]=='r'&&cmd[5]=='t'&&cmd[6]=='s'&&cmd[7]=='t'&&cmd[8]=='r') {
            char address[10000]="E:\\C\\home";
            update=9;
            scanf("%s", cmd);

            if (cmd[0] == '-' && cmd[1] == '-' && cmd[2] == 'f' && cmd[3] == 'i' && cmd[4] == 'l' && cmd[5] == 'e') {
                ll in_length;
                char spen = getchar();
                scanf("%c", &qu_sl);
                if (qu_sl == '/') {
                    qu_sl = '\\';
                    path[0] = qu_sl;
                    for (ll i = 1; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == ' ') {
                            in_length = i;
                            break;
                        }
                    }

                    for (int j = 0; j < in_length; j++) {
                        address[update] = path[j];
                        update++;
                    }
                }
                else if(qu_sl=='"') {
                    for (ll i = 0; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == '"') {
                            in_length = i;
                            break;
                        }
                    }
                    for (ll j = 0; j < in_length ; j++) {
                        address[update] = path[j];
                        update++;
                    }
                }

                if(exist_check(address, in_length-1)==0) continue;

                scanf("%s", cmd);
                if (cmd[0] == '-' && cmd[1] == '-' && cmd[2] == 's' && cmd[3] == 't' && cmd[4] == 'r') {
                    char spen = getchar();
                    ll line, in, volume=2;
                    ll in_st_length;
                    char *final=(char *)calloc(MAX, sizeof(char *));
                    char *mid=(char *)calloc(MAX, sizeof(char *));
                    scanf("%c", &temp);
                    if (temp == '"') {
                        for (ll i = 0; 1; i++) {
                            scanf("%c", &string[i]);
                            if ((i + 1) % MAX == 0)
                                string = (char *) realloc(string, (volume * MAX) * sizeof(char));
                            if (string[i] == '"' && string[i - 1] != '\\') {
                                in_st_length = i;
                                break;
                            }
                        }
                        in_st_length--;
                    }
                    else {
                        ll line, in;
                        string[0] = temp;
                        ll volume = 2;
                        for (ll i = 1; 1; i++) {
                            scanf("%c", &string[i]);
                            if ((i + 1) % MAX == 0) string = (char *) realloc(string, (volume * MAX) * sizeof(char));
                            if (string[i] == ' ') {
                                in_st_length = i;
                                break;
                            }
                        }
                        in_st_length--;
                    }
                    scanf("%s", cmd);
                    if (cmd[0] == '-' && cmd[1] == '-' && cmd[2] == 'p' && cmd[3] == 'o' && cmd[4] == 's') {
                        char *name=(char *)calloc(MAX, sizeof(char *));
                        scanf("%lld:%lld", &line, &in);
                        ll in_pos = 0, volume=2, in_length3, in_length2=0;
                        ll in_count_line=1, in_count_in=0;
                        for (ll i = 0, j = 0; j <= in_st_length; i++, j++) {
                            in_length3 = i;
                            if((i+1)%MAX==0) name=(char*) realloc(name, (volume*MAX)* sizeof(char));
                            if (string[j] == '\\') {
                                if (string[j + 1] == 'n') {
                                    name[i] = '\n';
                                    j++;
                                    continue;
                                } else if (string[j + 1] == '\\') {
                                    name[i] = '\\';
                                    j++;
                                    continue;
                                } else if (string[j + 1] == '"') {
                                    name[i] = '"';
                                    j++;
                                    continue;
                                }
                            }
                            name[i] = string[j];
                        }
                        unptr= fopen("undo.txt", "w");
                        checkptr= fopen(address, "r");
                        for(ll i=0;1;i++){
                            if(feof(checkptr)) break;
                            mid[i]= fgetc(checkptr);
                            if(i>=1) fputc(mid[i-1], unptr);
                            in_length2=i;
                            if(in_count_in==in && in_count_line==line) in_pos=i;
                            if(in_count_line==line) in_count_in++;
                            if(mid[i]=='\n') {
                                in_count_line++;
                            }
                            if((i+1)%MAX==0) mid=(char*) realloc(mid, (volume*MAX)* sizeof(char));

                        }
                        fclose(unptr);
                        fclose(checkptr);
                        if(in_count_line<line){
                            printf("Invalid position!\n");
                            continue;
                        }
                        if(in_count_in<in){
                            printf("Invalid position!\n");
                            continue;
                        }
                        volume =2;
                        ll in_length4;
                        for (ll i = 0, j=0, k=0; 1;k++) {
                            if(j>in_length3 && i>in_length2) break;
                            if(i==in_pos && j<=in_length3){
                                final[k]=name[j];
                                j++;
                            }
                                else{
                                final[k]=mid[i];
                                i++;
                            }
                            if((k+1)%MAX==0) final=(char*) realloc(final, (volume*MAX)* sizeof(char));
                            in_length4=k;
                        }
                         checkptr = fopen(address, "w");
                              for(ll i=0; i<in_length4; i++){
                                  putc(final[i], checkptr);
                              }
                          fclose(checkptr);


                    } else {
                                printf("Invalid command!\n");
                                continue;
                            }
                        }


                    } else {
                        printf("Invalid command!\n");
                        continue;
                    }

            }
   //----------------------------------------------------------------------------------------------------
     //cat

        else if(cmd[0]=='c'&&cmd[1]=='a'&&cmd[2]=='t'){
            scanf("%s", cmd);
            if(cmd[0]=='-'&&cmd[1]=='-'&&cmd[2]=='f'&&cmd[3]=='i'&&cmd[4]=='l'&&cmd[5]=='e') {
                char address[100000]="E:\\C\\home";
                update=9;
                ll ca_length;
                int spen = getchar();
                scanf("%c", &temp);
                if (temp == '/') {
                    temp = '\\';
                    path[0] = temp;
                    for (ll i = 1; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == '\n') {
                            ca_length = i;
                            break;
                        }
                    }

                        for (int j = 0; j < ca_length; j++) {
                            address[update] = path[j];
                            update++;
                        }
                    }
                else if(temp=='"'){
                    for (ll i = 0; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == '\n') {
                            ca_length = i;
                            break;
                        }
                    }


                    for (ll j = 0; j < ca_length-1; j++) {
                        address[update] = path[j];
                        update++;
                    }
                }
                    if(exist_check(address, ca_length-1)==0) continue;

                    checkptr= fopen(address, "r");
                    ll volume=2;
                    for (ll i=0; 1; i++){
                        if((i+1)%MAX==0) string=(char*) realloc(string, (volume*MAX)* sizeof(char));
                        if(fgets(string, MAX, checkptr)==NULL) break;
                        printf("%s", string);
                    }
                    fclose(checkptr);
                    printf("\n");

            }
            else{
                printf("Invalid command!\n");
                continue;
            }

        }
  //=======================================================================================
      //remove
        else if(cmd[0]=='r'&&cmd[1]=='e'&&cmd[2]=='m'&&cmd[3]=='o'&&cmd[4]=='v'&&cmd[5]=='e'&&cmd[6]=='s'&&cmd[7]=='t'&&cmd[8]=='r'){
            char address[10000]="E:\\C\\home";
            update=9;
            scanf("%s", cmd);

            if (cmd[0] == '-' && cmd[1] == '-' && cmd[2] == 'f' && cmd[3] == 'i' && cmd[4] == 'l' && cmd[5] == 'e') {
                ll rm_length;
                char spen = getchar();
                scanf("%c", &temp);
                if (temp == '/') {
                    temp = '\\';
                    path[0] = temp;
                    for (ll i = 1; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == ' ') {
                            rm_length = i;
                            break;
                        }
                    }

                    for (int j = 0; j < rm_length; j++) {
                        address[update] = path[j];
                        update++;
                    }
                } else if (temp == '"') {
                    for (ll i = 0; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == '"') {
                            rm_length = i;
                            break;
                        }
                    }

                    for (int j = 0; j < rm_length ; j++) {
                        address[update] = path[j];
                        update++;
                    }
                }
                if(exist_check(address, rm_length-1)==0) continue;

                scanf("%s", cmd);
                if (cmd[0] == '-' && cmd[1] == '-' && cmd[2] == 'p' && cmd[3] == 'o' && cmd[4] == 's') {
                    ll rm_line, rm_in;
                    scanf("%lld:%lld", &rm_line, &rm_in);

                    ll rm_pos, rm_size;

                    scanf("%s", cmd);

                    if(cmd[0] == '-' && cmd[1] == 's' && cmd[2] == 'i' && cmd[3] == 'z' && cmd[4] == 'e'){
                        scanf("%lld", &rm_size);
                        char direction;
                        ll rm_count_line=1, rm_count_in=0;
                        scanf(" -%c", &direction);

                        if(direction=='f' || direction=='b'){
                            removestr(address, rm_size, direction, rm_line, rm_in);

                        } else{
                            printf("Invalid command!\n");
                            continue;
                        }

                    } else{
                        printf("Invalid command!\n");
                        continue;
                    }

                } else{
                    printf("Invalid command!\n");
                    continue;
                }

            }
            else{
                printf("Invalid command!\n");
                continue;
            }
        }
    //=============================================================
       //copy
        else if(cmd[0]=='c'&&cmd[1]=='o'&&cmd[2]=='p'&&cmd[3]=='y'&&cmd[4]=='s'&&cmd[5]=='t'&&cmd[6]=='r'){
            char address[10000]="E:\\C\\home";
            update=9;
            scanf("%s", cmd);

            if (cmd[0] == '-' && cmd[1] == '-' && cmd[2] == 'f' && cmd[3] == 'i' && cmd[4] == 'l' && cmd[5] == 'e') {
                ll co_length;
                int spen = getchar();
                scanf("%c", &temp);
                if (temp == '/') {
                    temp = '\\';
                    path[0] = temp;
                    for (ll i = 1; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == ' ') {
                            co_length = i;
                            break;
                        }
                    }

                    for (int j = 0; j < co_length; j++) {
                        address[update] = path[j];
                        update++;
                    }
                } else if (temp == '"') {
                    for (ll i = 0; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == '"') {
                            co_length = i;
                            break;
                        }
                    }

                    for (int j = 0; j < co_length - 1; j++) {
                        address[update] = path[j];
                        update++;
                    }
                }
                if(exist_check(address, co_length-1)==0) continue;

                scanf("%s", cmd);
                if (cmd[0] == '-' && cmd[1] == '-' && cmd[2] == 'p' && cmd[3] == 'o' && cmd[4] == 's') {
                    ll co_line, co_in;
                    scanf("%lld:%lld", &co_line, &co_in);

                    ll co_pos, co_size;

                    scanf("%s", cmd);
                    if(cmd[0] == '-' && cmd[1] == 's' && cmd[2] == 'i' && cmd[3] == 'z' && cmd[4] == 'e') {
                        scanf("%lld", &co_size);
                        char direction;
                        ll co_count_line = 1, co_count_in = 0;
                        scanf(" -%c", &direction);

                        if(direction=='f' || direction=='b'){
                            FILE *remptr;
                            char *string=(char *)calloc(MAX, sizeof(char *));
                            ll length, pos, volume=2;
                            ll count_line =1, count_in=0;
                            remptr = fopen(address, "r");
                            for(ll i=0;1;i++){
                                if(feof(remptr)) {
                                    break;
                                }
                                string[i]= fgetc(remptr);
                                length=i;
                                if(co_count_in==co_in && co_count_line==co_line) co_pos=i;
                                if(co_count_line==co_line) co_count_in++;
                                if(string[i]=='\n') {
                                    co_count_line++;
                                }
                                if((i+1)%MAX==0) string=(char*) realloc(string, (volume*MAX)* sizeof(char));
                            }
                            fclose(remptr);
                            if(co_size>co_length){
                                printf("Invalid size!\n");
                                continue;
                            }
                            if(co_count_line<co_line){
                                printf("Invalid position!\n");
                                continue;
                            }
                            if(co_count_in<co_in){
                                printf("Invalid position!\n");
                                continue;
                            }

                            if(direction=='b') {
                                co_pos -= co_size;
                            }
                                FILE *editptr;
                                for(ll i=co_pos, j=0; i<co_size+co_pos; i++, j++){
                                    clipboard[j]=string[i];
                                    size_clipboard=j;
                                }
                                editptr = fopen(address, "w");
                                for(ll i=0; i<length; i++){
                                    putc(string[i], editptr);
                                }

                                fclose(editptr);
                            continue;


                        } else{
                            printf("Invalid command!\n");
                            continue;
                        }

                    } else{
                        printf("Invalid command!\n");
                        continue;
                    }

                } else{
                    printf("Invalid command!\n");
                    continue;
                }

            } else{
                printf("Invalid command!\n");
                continue;
            }
        }
    //============================================================================================
     //cut

        else if(cmd[0]=='c'&&cmd[1]=='u'&&cmd[2]=='t'&&cmd[3]=='s'&&cmd[4]=='t'&&cmd[5]=='r'){
            char address[10000]="E:\\C\\home";
            update=9;
            scanf("%s", cmd);

            if (cmd[0] == '-' && cmd[1] == '-' && cmd[2] == 'f' && cmd[3] == 'i' && cmd[4] == 'l' && cmd[5] == 'e') {
                ll cu_length;
                int spen = getchar();
                scanf("%c", &temp);
                if (temp == '/') {
                    temp = '\\';
                    path[0] = temp;
                    for (ll i = 1; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == ' ') {
                            cu_length = i;
                            break;
                        }
                    }

                    for (int j = 0; j < cu_length; j++) {
                        address[update] = path[j];
                        update++;
                    }
                } else if (temp == '"') {
                    for (ll i = 0; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == '"') {
                            cu_length = i;
                            break;
                        }
                    }

                    for (int j = 0; j < cu_length; j++) {
                        address[update] = path[j];
                        update++;
                    }
                }
                if(exist_check(address, cu_length-1)==0) continue;

                scanf("%s", cmd);
                if (cmd[0] == '-' && cmd[1] == '-' && cmd[2] == 'p' && cmd[3] == 'o' && cmd[4] == 's') {
                    ll cu_line, cu_in;
                    scanf("%lld:%lld", &cu_line, &cu_in);

                    ll cu_pos, cu_size;

                    scanf("%s", cmd);
                    if(cmd[0] == '-' && cmd[1] == 's' && cmd[2] == 'i' && cmd[3] == 'z' && cmd[4] == 'e') {
                        scanf("%lld", &cu_size);
                        char direction;
                        ll cu_count_line = 1, cu_count_in = 0;
                        scanf(" -%c", &direction);

                        if(direction=='f' || direction=='b'){

                            FILE *remptr;
                            char *string=(char *)calloc(MAX, sizeof(char *));
                            ll  cu_pos, volume=2;
                            ll cu_count_line =1, cu_count_in=0;
                            unptr = fopen("undo.txt", "w");
                            remptr = fopen(address, "r");
                            for(ll i=0;1;i++){
                                if(feof(remptr)) break;
                                string[i]= fgetc(remptr);
                                if(i>=1) fputc(string[i-1], unptr);
                                cu_length=i;
                                if(cu_count_in==cu_in && cu_count_line==cu_line) cu_pos=i;
                                if(cu_count_line==cu_line) cu_count_in++;
                                if(string[i]=='\n') {
                                    cu_count_line++;
                                }
                                if((i+1)%MAX==0) string=(char*) realloc(string, (volume*MAX)* sizeof(char));
                            }
                            fclose(unptr);
                            fclose(remptr);
                            if(cu_size>cu_length){
                                printf("Invalid size!\n");
                                continue;
                            }
                            if(cu_count_line<cu_line){
                                printf("Invalid position!\n");
                                continue;
                            }
                            if(cu_count_in<cu_in){
                                printf("Invalid position!\n");
                                continue;
                            }
                            if(direction=='b') {
                                cu_pos -= cu_size;
                            }
                                FILE *editptr;
                                for(ll i=cu_pos, j=0; i<cu_size+cu_pos; i++, j++){
                                    clipboard[j]=string[i];
                                    size_clipboard=j;
                                }
                            editptr = fopen(address, "w");
                            for(ll i=0; 1; i++){
                                if(i==cu_pos) i+=cu_size;
                                if(i>cu_length-1) break;
                                  putc(string[i], editptr);
                            }

                            fclose(editptr);

                        } else{
                            printf("Invalid command!\n");
                            continue;
                        }

                    } else{
                        printf("Invalid command!\n");
                        continue;
                    }

                } else{
                    printf("Invalid command!\n");
                    continue;
                }

            } else{
                printf("Invalid command!\n");
                continue;
            }
        }
    //=========================================================================================
      //paste

        else if(cmd[0]=='p'&&cmd[1]=='a'&&cmd[2]=='s'&&cmd[3]=='t'&&cmd[4]=='e'&&cmd[5]=='s'&&cmd[6]=='t'&&cmd[7]=='r'){
            char address[1000]="E:\\C\\home";
            update=9;
            scanf("%s", cmd);

            if (cmd[0] == '-' && cmd[1] == '-' && cmd[2] == 'f' && cmd[3] == 'i' && cmd[4] == 'l' && cmd[5] == 'e') {
                ll pa_length;
                int spen = getchar();
                scanf("%c", &temp);
                if (temp == '/') {
                    temp = '\\';
                    path[0] = temp;
                    for (ll i = 1; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == ' ') {
                            pa_length = i;
                            break;
                        }
                    }

                    for (int j = 0; j < pa_length; j++) {
                        address[update] = path[j];
                        update++;
                    }
                } else if (temp == '"') {
                    for (ll i = 0; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == '"') {
                            pa_length = i;
                            break;
                        }
                    }

                    for (int j = 0; j < pa_length; j++) {
                        address[update] = path[j];
                        update++;
                    }
                }
                if(exist_check(address, pa_length-1)==0) continue;

                scanf("%s", cmd);
                ll pa_line, pa_in;
                if (cmd[0] == '-' && cmd[1] == '-' && cmd[2] == 'p' && cmd[3] == 'o' && cmd[4] == 's') {
                    char *mid=(char *)calloc(MAX, sizeof(char *));
                    char *final=(char *)calloc(MAX, sizeof(char *));
                    scanf("%lld:%lld", &pa_line, &pa_in);
                    ll pa_pos = 0, volume=2, pa_length3, pa_length2=0;
                    ll pa_count_line=1, pa_count_in=0;
                    unptr = fopen("undo.txt", "w");
                    checkptr= fopen(address, "r");
                    for(ll i=0;1;i++){
                        if(feof(checkptr)) break;
                        mid[i]= fgetc(checkptr);
                        if(i>=1) fputc(mid[i-1], unptr);
                        pa_length2=i;
                        if(pa_count_in==pa_in && pa_count_line==pa_line) pa_pos=i;
                        if(pa_count_line==pa_line) pa_count_in++;
                        if(mid[i]=='\n') {
                            pa_count_line++;
                        }
                        if((i+1)%MAX==0) mid=(char*) realloc(mid, (volume*MAX)* sizeof(char));

                    }
                    fclose(unptr);
                    fclose(checkptr);

                    if(pa_count_line<pa_line){
                        printf("Invalid position!\n");
                        continue;
                    }
                    if(pa_count_in<pa_in){
                        printf("Invalid position!\n");
                        continue;
                    }
                    volume =2;
                    ll pa_length4;
                    for (ll i = 0, j=0, k=0; 1;k++) {
                        if(j>size_clipboard && i>pa_length2) break;
                        if(i==pa_pos && j<=size_clipboard){
                            final[k]=clipboard[j];
                            j++;
                        }
                        else{
                            final[k]=mid[i];
                            i++;
                        }
                        if((k+1)%MAX==0) final=(char*) realloc(final, (volume*MAX)* sizeof(char));
                        pa_length4=k;
                    }
                    checkptr = fopen(address, "w");
                    for(ll i=0; i<pa_length4; i++){
                       putc(final[i], checkptr);
                    }
                    fclose(checkptr);


                } else{
                    printf("Invalid command!\n");
                    continue;
                }

            } else{
                printf("Invalid command!\n");
                continue;
            }
        }
     //=========================================================================================================
       //grep
        else if(cmd[0]=='g'&&cmd[1]=='r'&&cmd[2]=='e'&&cmd[3]=='p'){
            char how='n';
            scanf("%s", cmd);
            if(cmd[0]=='-'&&cmd[1]=='c'){
                how='c';
                scanf("%s", cmd);
            }
            if(cmd[0]=='-'&&cmd[1]=='i'){
                how='i';
                scanf("%s", cmd);
            }

            if(cmd[0]=='-'&&cmd[1]=='-'&&cmd[2]=='s'&&cmd[3]=='t'&&cmd[4]=='r'){
                char spen = getchar();
                ll volume=2;
                ll gr_length, gr_count=0;
                char *mid=(char *)calloc(MAX, sizeof(char *));
                scanf("%c", &temp);
                if (temp == '"') {
                    for (ll i = 0; 1; i++) {
                        scanf("%c", &string[i]);
                        if ((i + 1) % MAX == 0)
                            string = (char *) realloc(string, (volume * MAX) * sizeof(char));
                        if (string[i] == '"' && string[i - 1] != '\\') {
                            gr_length = i;
                            break;
                        }
                    }
                    gr_length--;
                }
                else {
                    string[0] = temp;
                    ll volume = 2;
                    for (ll i = 1; 1; i++) {
                        scanf("%c", &string[i]);
                        if ((i + 1) % MAX == 0) string = (char *) realloc(string, (volume * MAX) * sizeof(char));
                        if (string[i] == ' ') {
                            gr_length = i;
                            break;
                        }
                    }
                    gr_length--;
                }
                ll gr_line, gr_in;
                ll gr_length3=0;
                char *name=(char *)calloc(MAX, sizeof(char *));
                for (ll i = 0, j = 0; j <= gr_length; i++, j++) {
                    gr_length3 = i;
                    if((i+1)%MAX==0) name=(char*) realloc(name, (volume*MAX)* sizeof(char));
                    if (string[j] == '\\') {
                        if (string[j + 1] == 'n') {
                            name[i] = '\n';
                            j++;
                            continue;
                        } else if (string[j + 1] == '\\') {
                            name[i] = '\\';
                            j++;
                            continue;
                        } else if (string[j + 1] == '"') {
                            name[i] = '"';
                            j++;
                            continue;
                        }
                    }
                    name[i] = string[j];
                }


                    scanf("%s", cmd);
                    if(cmd[0]=='-'&&cmd[1]=='-'&&cmd[2]=='f'&&cmd[3]=='i'&&cmd[4]=='l'&&cmd[5]=='e'&&cmd[6]=='s'){
                        char spen = getchar();
                        while (1) {
                            if(spen=='\n') break;
                            char address[10000] = "E:\\C\\home";
                            update = 9;
                            ll text_length, add_length, end=0;
                            scanf("%c", &qu_sl);
                            if (qu_sl == '/') {
                                qu_sl = '\\';
                                path[0] = qu_sl;
                                for (ll i = 1; 1; i++) {
                                    scanf("%c", &path[i]);
                                    if (path[i] == '/') path[i] = '\\';
                                    if (path[i] == ' ') {
                                        add_length = i;
                                        break;
                                    }
                                    if(path[i]=='\n') {
                                        add_length=i;
                                        end =1;
                                        break;
                                    }
                                }
                                for (int j = 0; j < add_length; j++) {
                                    address[update] = path[j];
                                    update++;
                                }
                            } else if (qu_sl == '"') {
                                for (ll i = 0; 1; i++) {
                                    scanf("%c", &path[i]);
                                    if (path[i] == '/') path[i] = '\\';
                                    if (path[i] == ' '&&path[i-1]=='"') {
                                        add_length = i-1;
                                        break;
                                    }
                                    if(path[i]=='\n') {
                                        add_length = i-1;
                                        end = 1;
                                        break;
                                    }
                                   // printf("!");
                                }
                                //if(end==1) break;
                                //printf("!");
                                for (ll j = 0; j < add_length; j++) {
                                    address[update] = path[j];
                                    update++;
                                }
                            }
                           // printf("%s", address);
                            if (exist_check(address, add_length - 1) == 0) break;
                            volume = 2;
                            checkptr= fopen(address, "r");
                            for (ll i = 0, j=0; 1; i++, j++) {
                                //printf("1");
                                if ((j + 1) % MAX == 0) mid = (char *) realloc(mid, (volume * MAX) * sizeof(char));
                                if(feof(checkptr)) break;
                                mid[i]= fgetc(checkptr);
                                text_length=i;
                            }
                            fclose(checkptr);
                          //  printf("%s\n", mid);
                            gr_count+=grep_print(mid, name, address, text_length, gr_length3, how);

                            if(end==1) {
                                if(gr_count<=0){
                                    printf("There is no file that contain input str!\n");
                                    break;
                                }
                                if(how=='c') printf("%lld\n", gr_count);
                                break;
                            }


                        }
                        continue;
                    }

                    else {
                        printf("Invalid command!\n");
                        continue;
                    }
                }
            else{
                printf("Invalid command!\n");
                continue;
            }
        }

    //=============================================================================================================
       //undo
        else if(cmd[0]=='u'&&cmd[1]=='n'&&cmd[2]=='d'&&cmd[3]=='o'){
            scanf("%s", cmd);
            if(cmd[0]=='-'&&cmd[1]=='-'&&cmd[2]=='f'&&cmd[3]=='i'&&cmd[4]=='l'&&cmd[5]=='e') {
                char address[1000] = "E:\\C\\home";
                update = 9;
                ll ca_length;
                int spen = getchar();
                scanf("%c", &temp);
                if (temp == '/') {
                    temp = '\\';
                    path[0] = temp;
                    for (ll i = 1; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == '\n') {
                            ca_length = i;
                            break;
                        }
                    }

                    for (int j = 0; j < ca_length; j++) {
                        address[update] = path[j];
                        update++;
                    }
                } else if (temp == '"') {
                    for (ll i = 0; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == '\n') {
                            ca_length = i;
                            break;
                        }
                    }


                    for (ll j = 0; j < ca_length - 1; j++) {
                        address[update] = path[j];
                        update++;
                    }
                }
                if (exist_check(address, ca_length - 1) == 0) continue;
                unptr = fopen("undo.txt", "r");
                checkptr = fopen(address, "w");
                for(ll i=0; 1; i++){
                    if(feof(unptr)) break;
                    string[i]= fgetc(unptr);
                    if(i>=1) fputc(string[i-1], checkptr);
                }
                fclose(unptr);
                fclose(checkptr);
            }
            else {
                printf("Invalid command!\n");
                continue;
            }
        }
    //==============================================================================================================
      //find

        else if(cmd[0]=='f'&&cmd[1]=='i'&&cmd[2]=='n'&&cmd[3]=='d'){
            scanf("%s", cmd);
            if(cmd[0]=='-'&&cmd[1]=='-'&&cmd[2]=='s'&&cmd[3]=='t'&&cmd[4]=='r'){
                char spen = getchar();
                ll volume=2;
                ll fi_length;
                char *mid=(char *)calloc(MAX, sizeof(char *));
                scanf("%c", &temp);
                if (temp == '"') {
                    for (ll i = 0; 1; i++) {
                        scanf("%c", &string[i]);
                        if(string[i]=='*' && string[i-1]=='\\'){
                            string[i-1]='*';
                            i--;
                            continue;
                        }
                        if ((i + 1) % MAX == 0) string = (char *) realloc(string, (volume * MAX) * sizeof(char));
                        if (string[i] == '"' && string[i - 1] != '\\') {
                            fi_length = i;
                            break;
                        }
                    }
                    fi_length--;
                }
                else {
                    string[0] = temp;
                    ll volume = 2;
                    for (ll i = 1; 1; i++) {
                        scanf("%c", &string[i]);
                        if(string[i]=='*' && string[i-1]=='\\'){
                            string[i-1]='*';
                            i--;
                            continue;
                        }
                        if ((i + 1) % MAX == 0) string = (char *) realloc(string, (volume * MAX) * sizeof(char));
                        if (string[i] == ' ') {
                            fi_length = i;
                            break;
                        }
                    }
                    fi_length--;
                }
                scanf("%s", cmd);
                if(cmd[0]=='-'&&cmd[1]=='-'&&cmd[2]=='f'&&cmd[3]=='i'&&cmd[4]=='l'&&cmd[5]=='e'){
                    char address[1000] = "E:\\C\\home";
                update = 9;
                ll ca_length;
                int spen = getchar();
                scanf("%c", &temp);
                if (temp == '/') {
                    temp = '\\';
                    path[0] = temp;
                    for (ll i = 1; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == '\n') {
                            ca_length = i;
                            break;
                        }
                    }

                    for (int j = 0; j < ca_length; j++) {
                        address[update] = path[j];
                        update++;
                    }
                } else if (temp == '"') {
                    for (ll i = 0; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == '\n') {
                            ca_length = i;
                            break;
                        }
                    }


                    for (ll j = 0; j < ca_length - 1; j++) {
                        address[update] = path[j];
                        update++;
                    }
                }
                if (exist_check(address, ca_length - 1) == 0) continue;
                
                }
                else{
                    printf("Invalid command!\n");
                    continue;
                }
            }
            else{
                printf("Invalid command!\n");
                continue;
            }
        }
        else{
            char temp;
            while(1){
                scanf("%c", &temp);
                if(temp=='\n') break;
            }
            printf("Invalid command!\n");
        }
    }
    return 0;
}
