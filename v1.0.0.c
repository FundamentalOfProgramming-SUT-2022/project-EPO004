#include <io.h>
#include <process.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <dirent.h>
#include <windows.h>
#define MAX 1000
#define ll long long
ll G=1;
ll sign_rf;
ll tree_epo=0;
ll cat_epo=0;
void mk_folder(char name[], int length){
    char dirname[1000] = "E:\\C\\home";
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
    free(name);
    mkdir(dirname);
    //free(dirname);
}
void makefile(char name[], int length){
    char dirname[1000] = "E:\\C\\home";
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
    free(name);
    FILE *mkptr;
    mkptr = fopen(dirname, "r");
    if(mkptr!=NULL) {
        result = 1;
        printf("The file already exists!\n");
    }
    if(result==0){
        mkptr = fopen(dirname, "w");
        fclose(mkptr);
    }
    fclose(mkptr);
    //free(dirname);
}
int exist_check(char name[], int length){
    char *dir = (char *)calloc(1000, sizeof(char *));
    ll dir_num;
    for(ll i=length;1;i--){

        if(name[i]=='\\') {
            dir_num=i;
            break;
        }
    }
    for(ll i=0;i<dir_num;i++){
        dir[i]=name[i];
       // printf("\n%c", name[i]);
    }
    DIR *folder;
   // printf("\n%s", name);
    folder = opendir(dir);
    if(folder == NULL)
    {
        printf("Directory doesn't exist!\n");
        closedir(folder);
        return 0;
    }


    FILE *mkptr;
    mkptr = fopen(name, "r");
    if(mkptr==NULL) {
        printf("The file doesn't exist!\n");
        fclose(mkptr);
        return 0;
    }
    fclose(mkptr);
    //free(name);
   // free(dir);
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
    char filename[100];
    sprintf(filename, "%lld.txt", G);
    G++;
    wchar_t *und=filename;
//    int attr = GetFileAttributes(und);
//    if ((attr & FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN) {
//                                SetFileAttributes(und , attr | FILE_ATTRIBUTE_HIDDEN);
//                            }
    unptr = fopen(filename, "w");
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
        if((i+1)%MAX==0) {
            string=(char*) realloc(string, (volume*MAX)* sizeof(char));
            volume++;
        }
    }
                       // if ((attr & FILE_ATTRIBUTE_HIDDEN) == 0) {
                       //     SetFileAttributes(und , attr | FILE_ATTRIBUTE_HIDDEN);
                       // }
    fclose(unptr);
    fclose(remptr);
    if(size>length){
        printf("Invalid size!\n");
        //free(string);
        return;
    }
    if(count_line<line){
        printf("Invalid position!\n");
       // free(string);
        return;
    }
    if(count_in<in){
        printf("Invalid position!\n");
        free(string);
        //return;
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
       // free(string);
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
        if(j>length) {
            if(how=='c') count++;
            if(how=='n') printf("%s : ", address);
            exist=1;
            for(ll k=till; 1; k++){
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

    if(exist==0) {
        return -1;
        //free(mid);
        //free(string);
    }
    if(how=='c') {
    return count;
        //free(mid);
        //free(string);
        }
    if(how=='i') {
        if(exist!=0) printf("%s\n", address);
        //free(mid);
        //free(string);
        return 1;
    }
    return -2;
}

int find(char input[], ll in_length, char text[], ll text_length){
    ll pos=0, count_ss=0, now=0;
    ll fin_pos=-1;
    ll maybe=-1;
    for(ll i=0; i<=in_length;i++){
        if(input[i]=='\\'&&input[i+1]=='*') {
            count_ss++;
        }
    }
    if(input[in_length]=='*'){
        for(ll i=0, j=0;1;i++){
            if(i>text_length) break;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) j=0;
            if(text[i]==input[j]){
                pos++;
                j++;
            }
            if(j>=in_length){
                maybe=-2;
                for(ll k=i; 1; k++){
                    if(k>text_length){
                        break;
                    }
                    if(text[k]==' '||text[k]=='\n') {
                        i=k-1;
                        break;
                    }
                }
                fin_pos=i-pos;
                break;
            }
        }
    }
    if(input[0]=='*'){
        for(ll i=0, j=1;1;i++){
            if(i>text_length) break;
            if(text[i]=='\n') pos=i+1;
            if(i==0) pos=i;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) j=1;
            if(text[i]==' '&& j==1) {
                pos=i+1;
            }
            if(text[i]==input[j]) j++;
            if(j>in_length){
                maybe=-2;
            fin_pos=pos;
            }
        }
    }
    if(input[0]!='*'&&input[in_length]!='*'){
        for(ll i=0, j=0;1; i++){
        if(i>text_length) break;

        if(text[i]=='\n') {
            now=0;

        }
        if(input[j]=='*') {
            now=1;
            j++;
            maybe=-2;
        }
        if(text[i]!=input[j]&&now==0) j=0;
        if(now==1){
            pos++;
        }
        if(text[i]==input[j]) {
            j++;
        }
        if(now==1&&sign_rf==1){
            if(text[i]==' '&& text[i]!=input[j-1]){
              fin_pos=-1;
              break;
            }
        }
        if(sign_rf==0&&text[i]==' '){
            j=0;
            pos=0;
            now=0;
        }
        if(j>in_length){
            if(maybe!=-2) maybe=i-in_length;
            if(maybe==-2) fin_pos=i - pos+1;
            break;
        }
    }
    }
   // free(input);
  //  free(text);
    if(maybe==-2) return fin_pos;
    else return maybe;
}
int c_find(char input[], ll in_length, char text[], ll text_length){
        ll pos, count_ss=0, now=0, si_count=0, count=0;
        for(ll i=0; i<=in_length;i++){
            if(input[i]=='\\'&&input[i+1]=='*') {
                count_ss++;
            }
        }
        if(input[in_length]=='*'){
            for(ll i=0, j=0;1;i++){
                if(i>text_length) break;
            if(text[i]=='\n') pos=i+1;
            if(i==0) pos=i;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) j=0;
            if(text[i]==' '&&j==0) pos=i+1;
            if(text[i]==input[j]) j++;
                if(j>=in_length){
                    pos=i-in_length+count_ss+1;
                    count++;
                    j=0;
                    for(ll k=i; 1; k++){
                        if(k>text_length) break;
                        if(text[k]==' '||text[k]=='\n') {
                            i=k;
                            pos=k+1;
                            break;
                        }
                    }
                }
            }
        }
        if(input[0]=='*'){
            for(ll i=0, j=1;1;i++){
                if(i>text_length) break;
            if(text[i]=='\n') pos=i+1;
            if(i==0) pos=i;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) j=1;
            if((text[i]==' '||i==text_length)&& j==1) {
                pos=i+1;
                if(si_count==1){
                    count++;
                    si_count=0;
                }
            }
            if(text[i]==input[j]) j++;
            if(j>in_length){

            }
                if(j>in_length){
                    si_count=1;
                    j=1;

                }
            }
        }
        if(input[0]!='*'&&input[in_length]!='*'){
        for(ll i=0, j=0;1; i++){
        if(i>text_length) break;
        if(text[i]=='\n') {
            now=0;
            pos=0;

        }
        if(input[j]=='*') {
            now=1;
            j++;
           // maybe=-2;
        }
        if(text[i]!=input[j]&&now==0) {j=0;
            pos=0;
        }
        if(now==1){
            pos++;
        }
        if(text[i]==input[j]) {
                if(now==0) pos++;
            j++;
        }
        if(now==1&&sign_rf==1){
            if(text[i]==' '&& text[i]!=input[j-1]){
              break;
            }
        }
        if(sign_rf==0&&text[i]==' '){
            j=0;
            pos=0;
            now=0;
        }
        if(j>in_length){
            count++;
            j=0;
        }
    }
    }
  //  free(input);
 //   free(text);
        return count;
}
int at_find(char input[], ll in_length, char text[], ll text_length, ll at){
    ll pos = 0, count_ss=0, now=0, si_count=0, count=0, maybe=-1;
    ll fin_pos=-1;
    for(ll i=0; i<=in_length;i++){
        if(input[i]=='\\'&&input[i+1]=='*') {
            count_ss++;
        }
    }
    if(input[in_length]=='*'){
        for(ll i=0, j=0;1;i++){
            if(i>text_length) break;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) j=0;
            if(text[i]==' '&&j==0) {
                j=0;
            }
            if(text[i]==input[j]) {
                pos++;
                j++;
            }
            if(j>=in_length){
                maybe=-2;
                fin_pos=i-pos;
               count++;
                for(ll k=i+1; 1; k++){
                    if(k>text_length) break;
                    if(text[k]==' '||text[k]=='\n') {
                        i=k;
                        break;
                    }
                }
                if(count==at) break;
            }
        }
    }
    if(input[0]=='*'){
        for(ll i=0, j=1;1;i++){
            if(i>text_length) break;
            if(text[i]=='\n') pos=i+1;
            if(i==0) pos=i;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) j=1;
            if((text[i]==' '||i==text_length)&& j==1) {
                pos=i+1;
                if(si_count==1){
                    count++;
                    si_count=0;
                }
            }
            if(text[i]==input[j]) j++;
            if(j>in_length){
                maybe=-2;
                    fin_pos=pos;
                si_count=1;
                if(count==at) break;
                j=1;
            }
        }
    }
    if(input[0]!='*'&&input[in_length]!='*'){
        for(ll i=0, j=0;1; i++){
            if(i>text_length) break;
        if(text[i]=='\n') {
            now=0;

        }
        if(input[j]=='*') {
            now=1;
            j++;
            maybe=-2;
        }
        if(text[i]!=input[j]&&now==0) j=0;
            if(text[i]==' '){

                j=0;
            }
            if(now==1) pos++;
        if(text[i]==input[j]) {
            j++;
        }
        if(now==1&&sign_rf==1){
            if(text[i]==' '&& text[i]!=input[j-1]){
              fin_pos=-1;
              break;
            }
        }
        if(sign_rf==0&&text[i]==' '){
            j=0;
            pos=0;
            now=0;
        }
            if(j>in_length){
                if(maybe!=-2) maybe=i-in_length;
                    fin_pos=i-pos+1;
                count++;
                if(count==at) break;
                j=0;
                pos=0;
            }
        }
    }
   // free(input);
  //  free(text);
    if(maybe==-2) return fin_pos;
    else return maybe;
}

int b_find(char input[], ll in_length, char text[], ll text_length){
    ll pos,  count_ss=0, now=0, word=1;
    for(ll i=0; i<=in_length;i++){
        if(input[i]=='\\'&&input[i+1]=='*') {
            count_ss++;
        }
    }
    if(input[in_length]=='*'){
        for(ll i=0, j=0;1;i++){
            if(i>text_length) break;
            if(text[i]=='\n') pos=i+1;
            if(i==0) pos=i;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) j=0;
            if(text[i]==' '&&j==0) {
                if(i>text_length) break;
            if(text[i]=='\n') {
                    if(text[i+1]!=' '){
                            if(text[i+1]!='\n') word++;
                    }
            }
            if(text[i]==' '){
                    if(text[i+1]!=' '){
                        if(text[i+1]!='\n') word++;
                    }
            }
                pos=i+1;
            }
            if(text[i]==input[j]) j++;
            if(j>=in_length){
                break;
            }
        }
    }
    if(input[0]=='*'){
        for(ll i=0, j=1;1;i++){
            if(i>text_length) break;
            if(text[i]=='\n') pos=i+1;
            if(i==0) pos=i;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) j=1;
            if(text[i]==' '&& j==1) {
                pos=i+1;
            }
            if(i>text_length) break;
            if(text[i]=='\n') {
                    if(text[i+1]!=' '){
                            if(text[i+1]!='\n') word++;
                    }
            }
            if(text[i]==' '){
                    if(text[i+1]!=' '){
                        if(text[i+1]!='\n') word++;
                    }
            }
            if(text[i]==input[j]) j++;
            if(j>in_length){
                    break;
            }
        }
    }
    if(input[0]!='*'&&input[in_length]!='*'){
        for(ll i=0, j=0;1; i++){
            if(i>text_length) break;
            if(i==0) pos=i;
            if(i>text_length) break;
            if(text[i]=='\n') {
                    if(text[i+1]!=' '){
                            if(text[i+1]!='\n') word++;
                    }
            }
            if(text[i]==' '){
                    if(text[i+1]!=' '){
                        if(text[i+1]!='\n') word++;
                    }
            }
            if(text[i]=='\n') {
                now=0;
                pos=i+1;
            }
            if(input[j]=='*') {
                now=1;
                j++;
            }
            if(text[i]!=input[j]&&now==0) j=0;
            if(text[i]==' '&&now==0){
                if(j==0) pos=i+1;
            }
            if(text[i]==input[j]) {
                j++;
            }
            if(sign_rf==0&&text[i]==' '){
            j=0;
            pos=0;
        }
            if(j>in_length){
                break;
            }
        }
    }
   // free(input);
   // free(text);
    return word;
}
int all_find(char input[], ll in_length, char text[], ll text_length){
    ll pos=0, till=0, count_ss=0, now=0, z=0, may=-1;
    ll fin_pos[1000], maybe[1000];
    for(ll i=0; i<=in_length;i++){
        if(input[i]=='\\'&&input[i+1]=='*') {
            count_ss++;
        }
    }
    if(input[in_length]=='*'){
        for(ll i=0, j=0;1;i++){
            if(i>text_length) break;
            if(text[i]=='\n') pos=i+1;
            if(i==0) pos=i;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) j=0;
            if(text[i]==' '&&j==0) {
                pos=i+1;
            }
            if(text[i]==input[j]) j++;
            if(j>=in_length){
                may=-2;
                fin_pos[z]=pos;
                z++;
                for(ll k=i; 1; k++){
                    if(k>text_length){
                        break;
                    }
                    if(text[k]==' '||text[k]=='\n') {
                        i=k;
                        pos=k+1;
                        break;
                    }
                }

            }
        }
    }
    if(input[0]=='*'){
        for(ll i=0, j=1;1;i++){
            if(i>text_length) break;
            if(text[i]=='\n') pos=i+1;
            if(i==0) pos=i;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) j=1;
            if(text[i]==' '&& j==1) {
                pos=i+1;
            }
            if(text[i]==input[j]) j++;
            if(j>in_length){
                may=-2;
                fin_pos[z]=pos;
                z++;
                for(ll k=i; 1; k++){
                    if(k>text_length){
                        break;
                    }
                    if(text[k]==' '||text[k]=='\n') {
                        i=k;
                        pos=k+1;
                        break;
                    }
                }
            }
        }
    }
    if(input[0]!='*'&&input[in_length]!='*'){
        for(ll i=0, j=0;1; i++){
            if(i>text_length) break;
            if(text[i]=='\n') {
                now=0;
            }
            if(input[j]=='*') {
                now=1;
                j++;
                may=-2;
            }
            if(text[i]!=input[j]&&now==0) j=0;
            if(now==1) pos++;
            if(text[i]==input[j]) {
                j++;
            }
            if(sign_rf==0&&text[i]==' '){
            j=0;
            pos=0;
            now=0;
        }
            if(now==1&&sign_rf==1){
            if(text[i]==' '&& text[i]!=input[j-1]){
              z=0;
              break;
            }
        }
            if(j>in_length){
                if(may!=-2) maybe[z]=i-in_length;
                fin_pos[z]=i-pos+1;
                z++;
                j=0;
                pos=0;
            }
        }
    }
  //  free(input);
  //  free(text);
    if(z==0) return 0;
    if(may==-2){
    for(ll i=0; 1; i++){
        if(i==z-1) {
            printf("%lld\n", fin_pos[i]);
            return 1;
        }
        printf("%lld, ", fin_pos[i]);

    }
    }
    else{
        for(ll i=0; 1; i++){
        if(i==z-1) {
            printf("%lld\n", maybe[i]);
            return 1;
        }
        printf("%lld, ", maybe[i]);

    }
    }
}
int allb_find(char input[], ll in_length, char text[], ll text_length){
    ll pos=0, till=0, count_ss=0, now=0, z=0, may=-1, word=1;
    ll fin_pos[1000], maybe[1000];
    for(ll i=0; i<=in_length;i++){
        if(input[i]=='\\'&&input[i+1]=='*') {
            count_ss++;
        }
    }
    if(input[in_length]=='*'){
        for(ll i=0, j=0;1;i++){
            if(i>text_length) break;
            if(text[i]=='\n') {
                    if(text[i+1]!=' '){
                            if(text[i+1]!='\n') word++;
                    }
            }
            if(text[i]==' '){
                    if(text[i+1]!=' '){
                        if(text[i+1]!='\n') word++;
                    }
            }
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(i==0) pos=i;
            if(text[i]!=input[j]) j=0;
            if(text[i]==input[j]) j++;
            if(j>=in_length){
                may=-2;
                fin_pos[z]=word;
                z++;
                for(ll k=i; 1; k++){
                    if(k>text_length){
                        break;
                    }
                    if(text[k]==' '||text[k]=='\n') {
                        i=k-1;
                        pos=k+1;
                        break;
                    }
                }

            }
        }
    } 
    if(input[0]=='*'){
        for(ll i=0, j=1;1;i++){
            if(i>text_length) break;
            if(text[i]==' ') {
                    if(text[i+1]!=' '){
                            if(text[i+1]!='\n') word++;
                    }
            }
            if(text[i]=='\n') {
                    if(text[i+1]!=' '){
                            if(text[i+1]!='\n') word++;
                    }
            }
            if(i==0) pos=i;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) j=1;
            if(text[i]==' '&& j==1) {
                pos=i+1;
            }
            if(text[i]==input[j]){
                j++;
            }

            if(j>in_length){
                may=-2;
                fin_pos[z]=word;
                z++;
                j=1;
            }
        }
    }
    if(input[0]!='*'&&input[in_length]!='*'){
        for(ll i=0, j=0;1; i++){
            if(i>text_length) break;
            if(text[i]=='\n') {
                now=0;
            }
            if(input[j]=='*') {
                now=1;
                j++;
                may=-2;
            }
            if(text[i]==' ') {
                    if(text[i+1]!=' '){
                            if(text[i+1]!='\n') word++;
                    }
            }
            if(text[i]=='\n') {
                    if(text[i+1]!=' '){
                            if(text[i+1]!='\n') word++;
                    }
            }
            if(text[i]!=input[j]&&now==0) j=0;
            if(now==1) pos++;
            if(text[i]==input[j]) {
                j++;
            }
            if(sign_rf==0&&text[i]==' '){
            j=0;
            pos=0;
        }
            if(j>in_length){
                fin_pos[z]=word;
                z++;
                j=0;
                pos=0;
            }
        }
    }
  //  free(input);
  //  free(text);
    if(z==0) return 0;

    for(ll i=0; 1; i++){
        if(i==z-1) {
            printf("%lld\n", fin_pos[i]);
            return 1;
        }
        printf("%lld, ", fin_pos[i]);

    }

}
void compare(char add[], char add2[]){
    char *string=(char *)calloc(MAX, sizeof(char *));
    char *string2=(char *)calloc(MAX, sizeof(char *));
    FILE *a1=fopen(add, "r");
    FILE *a2=fopen(add2, "r");
    int longer=0;
    ll size1=0, size2=0;
    ll sign1=0, sign2=0;
    for(ll i=0;1;){
        if(feof(a1)&&feof(a2)){
            break;
        }
        if(feof(a1)){
            longer = 1;
            sign1=1;
        }
        if(feof(a2)){
            longer = -1;
            sign2=1;
        }
            if(sign1==0) {
                    fgets(string + strlen(string), MAX, a1);
                    size1++;
            }
            if(sign2==0){
                fgets(string2 + strlen(string2), MAX, a2);
                size2++;
            }
    }
    ll nu1=0, nu2=0, line=1;
    ll temp1=0, temp2=0;
    //printf("%lld\n", size2);
    for(ll i=1;1;i++){
            if(longer==1&&i==size1+1){
            printf(">>>>>>>>>>>> #%lld - #%lld >>>>>>>>>>>> File 2\n", size1+1, size2);
            for(ll k =0;1;k++){
                    if(string2[k]=='\0') break;
                    if(string2[k]=='\n'&&line<size1+1) {
                            line++;
                            continue;
                    }
                    if(line>=size1+1) printf("%c", string2[k]);
                }
                printf("\n");
                break;
        }
        else if(longer==-1&&i==size2+1){
            printf(">>>>>>>>>>>> #%lld - #%lld >>>>>>>>>>>> File 1\n", size2+1, size1);
            for(ll k =0;1;k++){
                    if(string[k]=='\0') break;
                    if(string[k]=='\n'&&line<size2+1) {
                            line++;
                            continue;
                    }
                    if(line>=size2+1) printf("%c", string[k]);
                }
                printf("\n");
                break;
        }
        else if(longer==0&&i==size1+1) break;
        for(ll j1=temp1, j2=temp2;1;j1++, j2++){
            if(string2[j2]=='\n'&&string[j1]=='\n') {
                    temp1=j1+1;
                    temp2=j2+1;
                    break;
            }
            if(string2[j2]=='\n'||string[j1]=='\n'){
                if(string2[j2]=='\0'||string[j1]=='\0') break;
            if(string2[j2]!=string[j1]){

                   // if(string2[j2==''])
                printf("============ #%lld ============\n", i);
                for(ll k =temp1;1;k++){
                    if(string[k]=='\n') {
                            temp1=k+1;
                            break;
                    }
                    printf("%c", string[k]);
                    if(string[k]=='\0') break;
                }
                printf("\n");
                for(ll k =temp2;1;k++){
                    if(string2[k]=='\n') {
                            temp2=k+1;
                            break;
                    }
                    printf("%c", string2[k]);
                    if(string2[k]=='\0') break;
                }
                printf("\n");
                break;
            }
            }
        }

    }
  //  free(string);
  //  free(string2);

}

void tree(char *basePath, const int root, int sign, int depth)
{
    if(depth<=0) return;
    int i;
    char path[1000];
    FILE *t;
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    if (!dir)
        return;
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            for (i=0; i<root; i++)
            {
                if(tree_epo==0)
                    printf("   ");
                    else{
                        t = fopen("tree.txt", "a+");
                        fputs("   ", t);
                        fclose(t);
                    }
            }
            if(sign>0)
            if(tree_epo==0)
            printf("%c%c%s\n", 448, 452, dp->d_name);
            else{
                t=fopen("tree.txt", "a+");
                fputc(448, t);
                fputc(452, t);
                fputs(dp->d_name, t);
                fputc('\n', t);
                fclose(t);
            }
            else {
                    FILE *f;
                    if (f= fopen(dp->d_name, "r")) {
                        if(tree_epo==0)
                        printf("%s\n", dp->d_name);
                        else{
                            t=fopen("tree.txt", "a+");
                            fputs(dp->d_name, t);
                            fputc('\n', t);
                fclose(t);
                        }
                        
                        }
                    else{
                        if(tree_epo==0)
                        printf("%s:\n", dp->d_name);
                        else{
                            t=fopen("tree.txt", "a+");
                            fputs(dp->d_name, t);
                            fputc(':', t);
                            fputc('\n', t);
                fclose(t);
                        }
                    }
            }
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            tree(path, root+1, sign+1, depth-1);
        }
    }
    closedir(dir);
}
int atb_find(char input[], ll in_length, char text[], ll text_length, ll at){
    ll pos = 0, till=0, count_ss=0, now=0, si_count=0, count=0, maybe=-1, word=1;
    ll fin_pos=-1, sign=0;
    for(ll i=0; i<=in_length;i++){
        if(input[i]=='\\'&&input[i+1]=='*') {
            count_ss++;
        }
    }
    if(input[in_length]=='*'){
        for(ll i=0, j=0;1;i++){
            if(i>text_length) break;
            if(i==0) pos=i;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) j=0;
            if(text[i]==' '&&j==0) {
                j=0;
            }
              if(text[i]==' ') {
                    if(text[i+1]!=' '){
                            if(text[i+1]!='\n') word++;
                    }
            }
            if(text[i]=='\n') {
                    if(text[i+1]!=' '){
                            if(text[i+1]!='\n') word++;
                    }
            }
            if(text[i]==input[j]) j++;
            if(sign_rf==0&&text[i]==' '){
            j=0;
            pos=0;
        }
            if(j>=in_length){
                    sign=1;
                maybe=-2;
                fin_pos=word;
               count++;
                for(ll k=i+1; 1; k++){
                    if(k>text_length) break;
                    if(text[k]==' '||text[k]=='\n') {
                        i=k-1;
                        break;
                    }
                }
                if(count==at) break;
            }
        }
    }
    if(input[0]=='*'){
        for(ll i=0, j=1;1;i++){
            if(i>text_length) break;
            if(i==0) pos=i;
            if(text[i]==' ') {
                    if(text[i+1]!=' '){
                            if(text[i+1]!='\n') word++;
                    }
            }
            if(text[i]=='\n') {
                    if(text[i+1]!=' '){
                            if(text[i+1]!='\n') word++;
                    }
            }
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) j=1;
            if((text[i]==' '||i==text_length)&& j==1) {
                pos=i+1;
                if(si_count==1){
                    count++;
                    si_count=0;
                }
            }
            if(text[i]==input[j]) j++;
            if(j>in_length){
                sign=1;
                    fin_pos=word;
                si_count=1;
                if(count==at) break;
                j=1;
            }
        }
    }
    if(input[0]!='*'&&input[in_length]!='*'){
        for(ll i=0, j=0;1; i++){
            if(i>text_length) break;
        if(text[i]=='\n') {
            now=0;

        }
        if(text[i]==' ') {
                    if(text[i+1]!=' '){
                            if(text[i+1]!='\n') word++;
                    }
            }
            if(text[i]=='\n') {
                    if(text[i+1]!=' '){
                            if(text[i+1]!='\n') word++;
                    }
            }
        if(input[j]=='*') {
            now=1;
            j++;
            maybe=-2;
        }
        if(text[i]!=input[j]&&now==0) j=0;
            if(text[i]==' '){

                j=0;
            }
            if(now==1) pos++;
        if(text[i]==input[j]) {
            j++;
        }
            if(j>in_length){
                sign=1;
                    fin_pos=word;
                count++;
                if(count==at) break;
                j=0;
                pos=0;
            }
        }
    }
  //  free(input);
  //  free(text);
    if(sign==1) return fin_pos;
    else return 0;
}
int replace(char input[], ll in_length, char rep[], ll rep_length, char text[], ll text_length, char address[]){
    ll pos=0, till=0, count_ss=0, now=0, pos_f=0;
    ll fin_pos=-1, temp_pos=-1;
    ll maybe=-1;
    //printf("%s", input);
    for(ll i=0; i<=in_length;i++){
        if(input[i]=='\\'&&input[i+1]=='*') {
            count_ss++;
        }
    }
    if(input[in_length]=='*'){
        for(ll i=0, j=0;1;i++){
            if(i>text_length) break;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) {j=0;
            pos=0;
            }
            if(text[i]==input[j]){
                pos++;
                j++;
            }
            if(j>=in_length){
                maybe=-2;
                fin_pos=i-pos+1;
                for(ll k=i; 1; k++){
                    if(k>text_length){
                            pos_f=k-1;
                        break;
                    }
                        pos++;
                    if(text[k]==' '||text[k]=='\n') {
                        i=k;
                        pos_f=k;
                        break;
                    }
                }
                pos=0;
                break;
            }
        }
    }
    if(input[0]=='*'){
        for(ll i=0, j=1;1;i++){
            if(i>text_length) break;
            if(text[i]==' '&&temp_pos!=-1){
                fin_pos=temp_pos;
                break;
            }
            if(i+1>text_length&&temp_pos!=-1){
                fin_pos=temp_pos;
                break;
            }
            if(text[i]=='\n') pos=i+1;
            if(i==0) pos=i;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) j=1;
            if(text[i]==' '&& j==1) {
                pos=i+1;
            }
            if(text[i]==input[j]) j++;
            if(j>in_length){
                maybe=-2;
            temp_pos=pos;
            j=1;
           // printf("%lld\n", temp_pos);
                pos_f=i+1;
            }
        }
    }
    if(input[0]!='*'&&input[in_length]!='*'){
        for(ll i=0, j=0;1; i++){
        if(i>text_length) break;
        if(text[i]=='\n') {
            now=0;
            pos=0;

        }
        if(input[j]=='*') {
            now=1;
            j++;
            maybe=-2;
        }
        if(text[i]!=input[j]&&now==0) {j=0;
            pos=0;
        }
        if(now==1){
            pos++;
        }
        if(text[i]==input[j]) {
                if(now==0) pos++;
            j++;
        }
        if(now==1&&sign_rf==1){
            if(text[i]==' '&& text[i]!=input[j-1]){
              fin_pos=-1;
              break;
            }
        }
        if(sign_rf==0&&text[i]==' '){
            j=0;
            pos=0;
            now=0;
        }
        if(j>in_length){
            if(maybe!=-2) fin_pos=i - in_length;
            if(maybe==-2) fin_pos=i - pos+1;
            pos_f=i+1;
            break;
        }
    }
    }
  //  free(input);
    if(fin_pos==-1) {
        return -1;
    //free(text);
        }
    FILE* f= fopen(address, "w");
    for(ll i=0, j=0; i<text_length;){
        if(i == fin_pos){
            fputc(rep[j], f);
            j++;
            if(j>=rep_length) i=pos_f;
            if(i>=text_length) break;
        }
        else{
        fputc(text[i], f);
        i++;
        }
    }
   fclose(f);
   //free(input);
   // free(text);
    return 0;
}

int all_replace(char input[], ll in_length, char rep[], ll rep_length, char text[], ll text_length, char address[]){
    ll pos=0, till=0, count_ss=0, now=0, pos_f[1000];
    ll fin_pos[10000];
    ll maybe=-1, z=0, temp_pos=-1;
    fin_pos[0]=-1;
    for(ll i=0; i<=in_length;i++){
        if(input[i]=='\\'&&input[i+1]=='*') {
            count_ss++;
        }
    }
    if(input[in_length]=='*'){
        for(ll i=0, j=0;1;i++){
            if(i>text_length) break;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) {j=0;
            pos=0;
            }
            if(text[i]==input[j]){
                pos++;
                j++;
            }
            if(j>=in_length){
                maybe=-2;
                fin_pos[z]=i-pos+1;
                for(ll k=i; 1; k++){
                    if(k>text_length){
                            pos_f[z]=k-1;
                        break;
                    }
                        pos++;
                    if(text[k]==' '||text[k]=='\n') {
                        i=k;
                        pos_f[z]=k;
                        break;
                    }
                }
                z++;
                pos=0;
            }
        }
    }
    if(input[0]=='*'){
        for(ll i=0, j=1;1;i++){
            if(i>text_length) break;
            if(text[i]==' '&&temp_pos!=-1){
                if(temp_pos!=fin_pos[z-1] || z==0) {
                    fin_pos[z]=temp_pos;
                    z++;
                }
               // printf("%lld\n", fin_pos[z]);
                //z++;
            }
            if(i+1>text_length&&temp_pos!=-1){
                if(temp_pos!=fin_pos[z-1] || z==0) {
                    fin_pos[z]=temp_pos;
                    z++;
                }
            }
            if(text[i]=='\n') pos=i+1;
            if(i==0) pos=i;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) j=1;
            if(text[i]==' '&& j==1) {
                pos=i+1;
            }
            if(text[i]==input[j]) j++;
            if(j>in_length){
                maybe=-2;
            temp_pos=pos;
                pos_f[z]=i+1;
                j=1;
            }
        }
    }
    if(input[0]!='*'&&input[in_length]!='*'){
        for(ll i=0, j=0;1; i++){
        if(i>text_length) break;
        if(text[i]=='\n') {
            now=0;
            pos=0;

        }
        if(input[j]=='*') {
            now=1;
            j++;
            maybe=-2;
        }
        if(text[i]!=input[j]&&now==0) {j=0;
            pos=0;
        }
        if(now==1){
            pos++;
        }
        if(text[i]==input[j]) {
                if(now==0) pos++;
            j++;
        }
        if(now==1&&sign_rf==1){
            if(text[i]==' '&& text[i]!=input[j-1]){
              fin_pos[0]=-1;
              break;
            }
        }
        if(sign_rf==0&&text[i]==' '){
            j=0;
            pos=0;
            now=0;
        }
        if(j>in_length){
            if(maybe!=-2) fin_pos[z]=i - in_length;
            if(maybe==-2) fin_pos[z]=i - pos+1;
            pos_f[z]=i+1;
            z++;
        }
    }
    }
   // free(input);
    if(fin_pos[0]==-1) {
        return -1;
        //free(text);
    }
    z=0;
    FILE* f= fopen(address, "w");
    for(ll i=0, j=0; i<text_length;){
        if(i == fin_pos[z]){
            fputc(rep[j], f);
            j++;
            if(j>rep_length) {
                    i=pos_f[z];
                j=0;
            z++;
            }
            if(i>=text_length) break;
        }
        else{
        fputc(text[i], f);
        i++;
        }
    }
   //fclose(f);
   // free(text);
    return 0;
}
int at_replace(char input[], ll in_length, char rep[], ll rep_length, char text[], ll text_length, char address[], ll at){
    ll pos=0, till=0, count_ss=0, now=0, pos_f=0, count=0;
    ll fin_pos=-1, temp_pos=-1;
    ll maybe=-1;
    //printf("%s", input);
    for(ll i=0; i<=in_length;i++){
        if(input[i]=='\\'&&input[i+1]=='*') {
            count_ss++;
        }
    }
    if(input[in_length]=='*'){
        for(ll i=0, j=0;1;i++){
            if(i>text_length) break;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) {j=0;
            pos=0;
            }
            if(text[i]==input[j]){
                pos++;
                j++;
            }
            if(j>=in_length){
                maybe=-2;
                fin_pos=i-pos+1;
                count++;
                for(ll k=i; 1; k++){
                    if(k>text_length){
                            pos_f=k-1;
                        break;
                    }
                        pos++;
                    if(text[k]==' '||text[k]=='\n') {
                        i=k;
                        pos_f=k;
                        break;
                    }
                }
                pos=0;
                if(count==at) break;
            }
        }
    }
    if(input[0]=='*'){
        for(ll i=0, j=1;1;i++){
            if(i>text_length) break;
            if(text[i]==' '&&temp_pos!=-1){
                if(temp_pos!=fin_pos ) {
                    fin_pos=temp_pos;
                    
                    count++;
                    if(count==at) break;
                }
               // printf("%lld\n", fin_pos[z]);
                //z++;
            }
            if(i+1>text_length&&temp_pos!=-1){
                if(temp_pos!=fin_pos ) {
                    fin_pos=temp_pos;
                    
                    fin_pos=temp_pos;
                    
                    count++;
                    if(count==at) break;
                }
            }
            if(text[i]=='\n') pos=i+1;
            if(i==0) pos=i;
            if(input[j]=='\\'&&input[j+1]=='*') j++;
            if(text[i]!=input[j]) j=1;
            if(text[i]==' '&& j==1) {
                pos=i+1;
            }
            if(text[i]==input[j]) j++;
            if(j>in_length){
                maybe=-2;
            temp_pos=pos;
                pos_f=i+1;
                j=1;
            }
        }
    }
    if(input[0]!='*'&&input[in_length]!='*'){
        for(ll i=0, j=0;1; i++){
        if(i>text_length) break;
        if(text[i]=='\n') {
            now=0;
            pos=0;

        }
        if(input[j]=='*') {
            now=1;
            j++;
            maybe=-2;
        }
        if(text[i]!=input[j]&&now==0) {j=0;
            pos=0;
        }
        if(now==1){
            pos++;
        }
        if(text[i]==input[j]) {
                if(now==0) pos++;
            j++;
        }
        if(now==1&&sign_rf==1){
            if(text[i]==' '&& text[i]!=input[j-1]){
              fin_pos=-1;
              break;
            }
        }
        if(sign_rf==0&&text[i]==' '){
            j=0;
            pos=0;
            now=0;
        }
        if(j>in_length){
                count++;
            if(maybe!=-2) fin_pos=i - in_length;
            if(maybe==-2) fin_pos=i - pos+1;
            pos_f=i+1;
            if(count==at) break;
            j=0;
        }
    }
    }
    if(fin_pos==-1) {
        return -1;
        free(input);
        free(text);
        }
    FILE* f= fopen(address, "w");
    for(ll i=0, j=0; i<text_length;){
        if(i == fin_pos){
            fputc(rep[j], f);
            j++;
            if(j>rep_length) i=pos_f;
            if(i>=text_length) break;
        }
        else{
        fputc(text[i], f);
        i++;
        }
    }
   fclose(f);
   //free(input);
    //free(text);
    return 0;
}


int main(){
    char cmd[1000];
    ll update;
    char qu_sl, temp;
   // char filename[1000];
    ll size_clipboard=0;
    FILE *checkptr;
    FILE *unptr;
    while(1){
        char *string=(char *)calloc(MAX, sizeof(char *));
        char *path=(char *)calloc(1000, sizeof(char *));
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
                       // printf("1");
            char address[1000]="E:\\C\\home";
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

                if(exist_check(address, update)==0) continue;
                //free(path);
                    if(tree_epo==1||cat_epo==1){
                    //        printf("%lld", tree_epo);
                            char *final=(char *)calloc(MAX, sizeof(char *));
                    char *mid=(char *)calloc(MAX, sizeof(char *));
                    ll line, in;
                        tree_epo=0;
                        cat_epo=0;
                        scanf("%s", cmd);
                        if (cmd[0] == '-' && cmd[1] == '-' && cmd[2] == 'p' && cmd[3] == 'o' && cmd[4] == 's') {
                        
                        scanf("%lld:%lld", &line, &in);
                        ll in_pos = 0, volume=2, in_length3, in_length2=0;
                        ll in_count_line=1, in_count_in=0;
                        //free(string);
                        char filename[1000];
                        sprintf(filename, "%lld.txt", G);
                        G++;

                        wchar_t *und = filename;
                        int attr = GetFileAttributes(und);
                        
                        unptr= fopen(filename, "w");
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
                            if((i+1)%MAX==0) {
                                mid=(char*) realloc(mid, (volume*MAX)* sizeof(char));
                                volume++;
                            }

                        }
                        fclose(unptr);
                        fclose(checkptr);
                        //printf("%s, %d", filename, G);
                        if(in_count_line<line){
                            printf("Invalid position!\n");
                            continue;
                        }
                        if(in_count_in<in){
                            printf("Invalid position!\n");
                            continue;
                        }
                        FILE *t = fopen("tree.txt", "r");
                        in_length3=0;
                        for(ll i=0; 1; i++){
                            if( feof(t)) break;
                            string[i]=fgetc(t);
                            in_length3=i;
                        }
                        fclose(t);
                        volume =2;

                        ll in_length4;
                        for (ll i = 0, j=0, k=0; 1;k++) {
                            if(j>=in_length3 && i>in_length2) break;
                            if(i==in_pos && j<in_length3){
                                final[k]=string[j];
                                j++;
                            }
                                else{
                                final[k]=mid[i];
                                i++;
                            }
                            if((k+1)%MAX==0) {
                                final=(char*) realloc(final, (volume*MAX)* sizeof(char));
                                volume++;
                            }
                            in_length4=k;
                        }
                       // free(mid);
                         checkptr = fopen(address, "w");
                              for(ll i=0; i<in_length4; i++){
                                  putc(final[i], checkptr);
                              }
                          fclose(checkptr);
                            //free(final);


                    } else {
                                printf("Invalid command!\n");
                                continue;
                            }
                        continue;
                    }
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
                        //free(string);
                        char filename[1000];
                        sprintf(filename, "%lld.txt", G);
                        G++;

                        wchar_t *und = filename;
                        int attr = GetFileAttributes(und);
                      //  if ((attr & FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN) {
                          //      SetFileAttributes(und , attr | FILE_ATTRIBUTE_HIDDEN);
                        //    }
                        unptr= fopen(filename, "w");
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
                            if((i+1)%MAX==0) {
                                mid=(char*) realloc(mid, (volume*MAX)* sizeof(char));
                                volume++;
                            }

                        }
                        fclose(unptr);
                        fclose(checkptr);
                      //  if ((attr & FILE_ATTRIBUTE_HIDDEN) == 0) {
                       //     SetFileAttributes(und , attr | FILE_ATTRIBUTE_HIDDEN);
                    //    }
                        //printf("%s, %d", filename, G);
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
                            if((k+1)%MAX==0) {
                                final=(char*) realloc(final, (volume*MAX)* sizeof(char));
                                volume++;
                            }
                            in_length4=k;
                        }
                       // free(mid);
                         checkptr = fopen(address, "w");
                              for(ll i=0; i<in_length4; i++){
                                  putc(final[i], checkptr);
                              }
                          fclose(checkptr);
                            //free(final);


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
                char address[1000]="E:\\C\\home";
                update=9;
                ll ca_length;
                int ent=0;
                int spen = getchar();
                scanf("%c", &temp);
                if (temp == '/') {
                    temp = '\\';
                    path[0] = temp;
                    for (ll i = 1; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == '\n') {
                            ent=1;
                            ca_length = i;
                            break;
                        }
                        if (path[i] == ' ') {
                            ent=0;
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
                            ent=1;
                            ca_length = i;
                            break;
                        }
                        if (path[i] == ' '&&path[i-1]=='"') {
                            ent=0;
                            ca_length = i;
                            break;
                        }
                    }


                    for (ll j = 0; j < ca_length-1; j++) {
                        address[update] = path[j];
                        update++;
                    }
                }
                    //printf("%s", address);
                    if(exist_check(address, update)==0) continue;
                    //free(path);

                    if(ent==1){
                    checkptr= fopen(address, "r");
                    ll volume=2;
                    for (ll i=0; 1; i++){
                        if((i+1)%MAX==0) {
                            string=(char*) realloc(string, (volume*MAX)* sizeof(char));
                            volume++;
                            
                            }
                        if(fgets(string, MAX, checkptr)==NULL) break;
                        printf("%s", string);
                    }
                    fclose(checkptr);
                    printf("\n");
                    }
                    else{
                        scanf("%s", cmd);
                        if(cmd[0]=='='&&cmd[1]=='>'){
                            cat_epo=1;
                        FILE *t = fopen("tree.txt", "w");
                        checkptr= fopen(address, "r");
                    ll volume=2;
                    for (ll i=0; 1; i++){
                        if((i+1)%MAX==0) {
                            string=(char*) realloc(string, (volume*MAX)* sizeof(char));
                            volume++;
                            
                            }
                        if(fgets(string, MAX, checkptr)==NULL) break;
                        fputs(string, t);
                        fputc('\n', t);
                    }
                    fclose(checkptr);
                        fclose(t);

                        }
                        else{
                            printf("Invalid command!\n");
                            continue;
                        }
                        
                    }
                    //free(string);

            }
            else{
                printf("Invalid command!\n");
                continue;
            }

        }
  //=======================================================================================
      //remove
        else if(cmd[0]=='r'&&cmd[1]=='e'&&cmd[2]=='m'&&cmd[3]=='o'&&cmd[4]=='v'&&cmd[5]=='e'&&cmd[6]=='s'&&cmd[7]=='t'&&cmd[8]=='r'){
            char address[1000]="E:\\C\\home";
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
                if(exist_check(address, update)==0) continue;
               // free(path);

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
            char address[1000]="E:\\C\\home";
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
                if(exist_check(address, update)==0) continue;
                //free(path);

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
                                if((i+1)%MAX==0) {
                                    string=(char*) realloc(string, (volume*MAX)* sizeof(char));
                                    volume++;
                                }
                            }
                            fclose(remptr);
                            if(co_size>co_length){
                                printf("Invalid size!\n");
                                free(string);
                                continue;
                            }
                            if(co_count_line<co_line){
                                printf("Invalid position!\n");
                                free(string);
                                continue;
                            }
                            if(co_count_in<co_in){
                                printf("Invalid position!\n");
                                free(string);
                                continue;
                            }

                            if(direction=='b') {
                                co_pos -= co_size;
                            }
                            FILE *clip;
                            wchar_t * clPCWSTR = "clipboard.txt";
                            int attr = GetFileAttributes(clPCWSTR);
                            if ((attr & FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN) {
                                SetFileAttributes(clPCWSTR , attr | FILE_ATTRIBUTE_HIDDEN);
                            }
                            clip = fopen("clipboard.txt", "w");
                                FILE *editptr;
                                for(ll i=co_pos, j=0; i<co_size+co_pos; i++, j++){
                                    fputc(string[i], clip);
                                    size_clipboard=j;
                                }
                                fclose(clip);
                                if ((attr & FILE_ATTRIBUTE_HIDDEN) == 0) {
                                    SetFileAttributes(clPCWSTR , attr | FILE_ATTRIBUTE_HIDDEN);
                                }   
                                editptr = fopen(address, "w");
                                for(ll i=0; i<length; i++){
                                    putc(string[i], editptr);
                                }
                                //free(string);

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
            char address[1000]="E:\\C\\home";
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
                if(exist_check(address, update)==0) continue;
               // free(path);

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
                            char filename[1000];
                        sprintf(filename, "%lld.txt", G);
                        G++;
                        wchar_t *und = filename;
                        int attr = GetFileAttributes(und);
                    //    if ((attr & FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN) {
                    //            SetFileAttributes(und , attr | FILE_ATTRIBUTE_HIDDEN);
                    //        }
                            unptr = fopen(filename, "w");
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
                      //      if ((attr & FILE_ATTRIBUTE_HIDDEN) == 0) {
                      //          SetFileAttributes(und , attr | FILE_ATTRIBUTE_HIDDEN);
                      //      }
                            if(cu_size>cu_length){
                                printf("Invalid size!\n");
                                free(string);
                                continue;
                            }
                            if(cu_count_line<cu_line){
                                printf("Invalid position!\n");
                                free(string);
                                continue;
                            }
                            if(cu_count_in<cu_in){
                                printf("Invalid position!\n");
                                free(string);
                                continue;
                            }
                            if(direction=='b') {
                                cu_pos -= cu_size;
                            }
                                FILE *editptr;
                                wchar_t * clPCWSTR= "clipboard.txt";
                                attr = GetFileAttributes(clPCWSTR);
                                if ((attr & FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN) {
                                SetFileAttributes(clPCWSTR , attr | FILE_ATTRIBUTE_HIDDEN);
                            }
                                FILE* clip=fopen("clipboard.txt", "w");
                                for(ll i=cu_pos, j=0; i<cu_size+cu_pos; i++, j++){
                                    fputc(string[i], clip);
                                    size_clipboard=j;
                                }
                                fclose(clip);
                                if ((attr & FILE_ATTRIBUTE_HIDDEN) == 0) {
                                 SetFileAttributes(clPCWSTR , attr | FILE_ATTRIBUTE_HIDDEN);
                             }
                            editptr = fopen(address, "w");
                            for(ll i=0; 1; i++){
                                if(i==cu_pos) i+=cu_size;
                                if(i>cu_length-1) break;
                                  putc(string[i], editptr);
                            }
                                //free(string);
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
                if(exist_check(address, update)==0) continue;
                //free(path);

                scanf("%s", cmd);
                ll pa_line, pa_in;
                if (cmd[0] == '-' && cmd[1] == '-' && cmd[2] == 'p' && cmd[3] == 'o' && cmd[4] == 's') {
                    char *mid=(char *)calloc(MAX, sizeof(char *));
                    char *final=(char *)calloc(MAX, sizeof(char *));
                    scanf("%lld:%lld", &pa_line, &pa_in);
                    ll pa_pos = 0, volume=2, pa_length3, pa_length2=0;
                    ll pa_count_line=1, pa_count_in=0;
                    char filename[1000];
                        sprintf(filename, "%lld.txt", G);
                        G++;
                        wchar_t *und = filename;
                    //    int attr = GetFileAttributes(und);
                    //    if ((attr & FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN) {
                    //            SetFileAttributes(und , attr | FILE_ATTRIBUTE_HIDDEN);
                    //        }
                            unptr = fopen(filename, "w");
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
                //            if ((attr & FILE_ATTRIBUTE_HIDDEN) == 0) {
                //                SetFileAttributes(und , attr | FILE_ATTRIBUTE_HIDDEN);
                //            }
                    if(pa_count_line<pa_line){
                        printf("Invalid position!\n");
                        //free(mid);
                        continue;
                    }
                    if(pa_count_in<pa_in){
                        printf("Invalid position!\n");
                       // free(mid);
                        continue;
                    }
                    volume =2;
                    ll pa_length4;
                    FILE *cl = fopen("clipboard.txt", "r");
                    for (ll i = 0, j=0, k=0; 1;k++) {
                        if(j>size_clipboard && i>pa_length2) break;
                        if(i==pa_pos && j<=size_clipboard){
                            final[k]=fgetc(cl);
                            j++;
                        }
                        else{
                            final[k]=mid[i];
                            i++;
                        }
                        if((k+1)%MAX==0) {
                            final=(char*) realloc(final, (volume*MAX)* sizeof(char));
                            volume;
                        }
                        pa_length4=k;
                    }
                    fclose(cl);
                    checkptr = fopen(address, "w");
                    for(ll i=0; i<pa_length4; i++){
                       putc(final[i], checkptr);
                    }
                    //free(mid);
                    //free(final);
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
                    //free(string);

                    scanf("%s", cmd);
                    if(cmd[0]=='-'&&cmd[1]=='-'&&cmd[2]=='f'&&cmd[3]=='i'&&cmd[4]=='l'&&cmd[5]=='e'&&cmd[6]=='s'){
                        char spen = getchar();
                        gr_count=0;
                        ll exi;
                        while (1) {
                            if(spen=='\n') break;
                            char address[1000] = "E:\\C\\home";
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
                                }
                                for (ll j = 0; j < add_length; j++) {
                                    address[update] = path[j];
                                    update++;
                                }
                            }
                            if (exist_check(address, update) == 0) break;
                            volume = 2;
                            checkptr= fopen(address, "r");
                            for (ll i = 0, j=0; 1; i++, j++) {
                                if ((j + 1) % MAX == 0) mid = (char *) realloc(mid, (volume * MAX) * sizeof(char));
                                if(feof(checkptr)) break;
                                mid[i]= fgetc(checkptr);
                                text_length=i;
                            }
                            fclose(checkptr);
                            int cou =grep_print(mid, name, address, text_length, gr_length3, how);
                            
                            if(cou>=0) gr_count+=cou;
                            else exi+=cou;

                            if(end==1) {
                                if(exi%2==1){
                                    printf("There is no file that contain input str!\n");
                                    break;
                                }
                                if(how=='c') printf("%lld\n", gr_count);
                                break;
                            }


                        }
                        //free(mid);
                       // free(name);
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
                if (exist_check(address, update) == 0) continue;
               // free(path);
                char filename[1000];
                        G--;
                        sprintf(filename, "%lld.txt", G);
                        wchar_t *und = filename;
                 //       int attr = GetFileAttributes(und);
                 //       
                 //       if ((attr & FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN) {
                 //               SetFileAttributes(und , attr | FILE_ATTRIBUTE_HIDDEN);
                 //           }
                            unptr = fopen(filename, "r");
                checkptr = fopen(address, "w");
                for(ll i=0; 1; i++){
                    if(feof(unptr)) break;
                    string[i]= fgetc(unptr);
                if(i>=1) fputc(string[i-1], checkptr);
                }
                fclose(unptr);
                fclose(checkptr);
   //             if ((attr & FILE_ATTRIBUTE_HIDDEN) == 0) {
   //     SetFileAttributes(und , attr | FILE_ATTRIBUTE_HIDDEN);
   // }
                
                //free(string);
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
                ll fi_length, fi_count=0;
                char *mid=(char *)calloc(MAX, sizeof(char *));
                scanf("%c", &temp);
                if (temp == '"') {
                        sign_rf=1;
                    for (ll i = 0; 1; i++) {
                        scanf("%c", &string[i]);
                        if ((i + 1) % MAX == 0){
                            string = (char *) realloc(string, (volume * MAX) * sizeof(char));
                                volume++;
                            }
                        if (string[i] == '"' && string[i - 1] != '\\') {
                            fi_length = i;
                            break;
                        }
                    }
                    fi_length--;
                }
                else {
                    sign_rf=0;
                    string[0] = temp;
                    ll volume = 2;
                    for (ll i = 1; 1; i++) {
                        scanf("%c", &string[i]);
                        if ((i + 1) % MAX == 0) {
                            string = (char *) realloc(string, (volume * MAX) * sizeof(char));
                            volume++;
                        }
                        if (string[i] == ' ') {
                            fi_length = i;
                            break;
                        }
                    }
                    fi_length--;
                }
                ll gr_line, gr_in;
                ll fi_length3=0;
                char *name=(char *)calloc(MAX, sizeof(char *));
                for (ll i = 0, j = 0; j <= fi_length; i++, j++) {
                    fi_length3 = i;
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
                        } else if(string[j+1]== '*'){
                            name[i]= '*';
                            j++;}
                    }
                    name[i] = string[j];
                }
              //  free(string);
                scanf("%s", cmd);
                if(cmd[0]=='-'&&cmd[1]=='-'&&cmd[2]=='f'&&cmd[3]=='i'&&cmd[4]=='l'&&cmd[5]=='e'){
                    ll sign_cot=0, sign_at=0, sign_by=0, sign_all=0, sign_nor=0;
                    ll space=0, enter=0;
                    char spen = getchar();
                        char address[1000] = "E:\\C\\home";
                        update = 9;
                        ll text_length, add_length;
                        scanf("%c", &qu_sl);
                        if (qu_sl == '/') {
                            qu_sl = '\\';
                            path[0] = qu_sl;
                            for (ll i = 1; 1; i++) {
                                scanf("%c", &path[i]);
                                if (path[i] == '/') path[i] = '\\';
                                if (path[i] == ' ') {
                                    space=1;
                                    add_length = i;
                                    break;
                                }
                                if (path[i] == '\n') {
                                    enter=1;
                                    add_length = i;
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
                                if (path[i] == ' ' && path[i - 1] == '"') {
                                    space=1;
                                    add_length = i - 1;
                                    break;
                                }
                                if (path[i] == '\n') {
                                    enter=1;
                                    add_length = i - 1;
                                    break;
                                }
                            }
                            for (ll j = 0; j < add_length; j++) {
                                address[update] = path[j];
                                update++;
                            }
                        }
                        ll at=0;
                        if (exist_check(address, update) == 0) break;
                       // free(path);
                        char cmd2[1000];
                        if(space==1){
                            scanf("%s", cmd);
                            if(cmd[0]=='-'&&cmd[1]=='c'&&cmd[2]=='o'&&cmd[3]=='u'&&cmd[4]=='n'&&cmd[5]=='t') sign_cot=1;
                            if(cmd[0]=='-'&&cmd[1]=='a'&&cmd[2]=='t') {
                                scanf("%lld", &at);
                                sign_at=1;
                                char te =  getchar();
                                if(te == ' '){
                                    scanf("%s", cmd2);
                            if(cmd2[0]=='-'&&cmd2[1]=='b'&&cmd2[2]=='y'&&cmd2[3]=='w'&&cmd2[4]=='o'&&cmd2[5]=='r'&&cmd2[6]=='d'){
                                sign_by=1;
                            }
                                else{
                                    printf("Invalid command!\n");
                                    free(name);
                                    continue;
                                }
                                }
                            }
                            if(cmd[0]=='-'&&cmd[1]=='b'&&cmd[2]=='y'&&cmd[3]=='w'&&cmd[4]=='o'&&cmd[5]=='r'&&cmd[6]=='d'){
                                sign_by=1;
                                char te =  getchar();
                                if(te == ' '){
                                    scanf("%s", cmd2);
                                    if(cmd2[0]=='-'&&cmd2[1]=='a'&&cmd2[2]=='t'){
                                        sign_at=1;
                                        scanf("%lld", &at);
                                    }
                                    else if(cmd2[0]=='-'&&cmd2[1]=='a'&&cmd2[2]=='l'&&cmd2[3]=='l'){
                                        sign_all=1;
                                    }
                                    else{
                                        printf("Invalid command!\n");
                                      //  free(name);
                                    continue;
                                    }
                                }
                            }
                            if(cmd[0]=='-'&&cmd[1]=='a'&&cmd[2]=='l'&&cmd[3]=='l'){
                                sign_all=1;
                                char te =  getchar();
                                if(te == ' '){
                                    scanf("%s", cmd2);
                            if(cmd2[0]=='-'&&cmd2[1]=='b'&&cmd2[2]=='y'&&cmd2[3]=='w'&&cmd2[4]=='o'&&cmd2[5]=='r'&&cmd2[6]=='d'){
                                sign_by=1;
                            }
                                else{
                                    printf("Invalid command!\n");
                                  //  free(name);
                                    continue;
                                }
                                }
                            }
                        }

                    checkptr = fopen(address, "r");
                    for(ll i=0;1;i++){
                        if(feof(checkptr)) break;
                        string[i]= fgetc(checkptr);
                        text_length=i;
                        if((i+1)%MAX==0) string=(char*) realloc(string, (volume*MAX)* sizeof(char));
                    }
                    fclose(checkptr);
                        if(enter==1) {
                            ll final = find(name, fi_length, string, text_length);
                            if(final==-1){
                                printf("Nothing found!\n");
                             //   free(string);
                           //     free(name);
                                continue;
                            }
                            printf("%lld\n", final);
                      //      free(string);
                        //    free(name);
                            continue;
                        }
                        if(sign_all==1&& sign_by==1){
                            allb_find(name, fi_length, string, text_length);
                            //free(string);
                          //  free(name);
                            continue;
                        }
                        if(sign_at==1 && sign_by==1){
                            if(at>c_find(name, fi_length, string, text_length)||at==0){
                                printf("Input is more than counter of real string!\n");
                       //         free(string);
                         //       free(name);
                                continue;
                            }
                            ll final = atb_find(name, fi_length, string, text_length, at);
                            if(final==0) {
                                printf("Nothing found!\n");
                             //   free(string);
                           //     free(name);
                            continue;
                            }
                            printf("%lld\n", final);
                        //    free(string);
                      //      free(name);
                            continue;
                        }
                        if(sign_cot==1){
                            ll final = c_find(name, fi_length, string, text_length);
                            printf("%lld\n", final);
                            //free(string);
                          //  free(name);
                            continue;
                        }
                        if(sign_at==1){
                            if(at>c_find(name, fi_length, string, text_length)||at==0){
                                printf("Input is more than counter of real string!\n");
                           //     free(string);
                             //   free(name);
                                continue;
                            }
                            ll final = at_find(name, fi_length, string, text_length, at);
                            printf("%lld\n", final);
                           // free(string);
                            //free(name);
                            continue;
                        }
                    if(sign_by==1) {
                        ll final = b_find(name, fi_length, string, text_length);
                        if(final==0) {
                            printf("Nothing found!\n");
                        //    free(string);
                      //      free(name);
                            continue;
                        }
                        printf("%lld\n", final);
                      //  free(string);
                    //    free(name);
                        continue;
                    }
                    if(sign_all==1){
                        ll final = all_find(name, fi_length, string, text_length);
                        if(final==0){
                            printf("Nothing found!\n");
                        //    free(string);
                      //      free(name);
                            continue;
                        }
                    }
                   // free(name);
                 //   free(string);

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
    //=============================================================================================================
      //compare
         else if(cmd[0]=='c'&&cmd[1]=='o'&&cmd[2]=='m'&&cmd[3]=='p'&&cmd[4]=='a'&&cmd[5]=='r'&&cmd[6]=='e'){
            char address[1000]="E:\\C\\home";
            char address2[1000]="E:\\C\\home";
            int spen = getchar();
            for(int k=0; k<2; k++) {
                update = 9;
                ll ca_length;
                scanf("%c", &temp);
                if (temp == '/') {
                    temp = '\\';
                    path[0] = temp;
                    for (ll i = 1; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == ' '||path[i]=='\n') {
                            ca_length = i;
                            break;
                        }
                    }
                    for (int j = 0; j < ca_length; j++) {
                        if(k==0)
                            address[update] = path[j];
                        else
                            address2[update] = path[j];
                        update++;
                    }
                } else if (temp == '"') {
                    for (ll i = 0; 1; i++) {
                        scanf("%c", &path[i]);
                        if (path[i] == '/') path[i] = '\\';
                        if (path[i] == ' '&&path[i]=='"') {
                            ca_length = i;
                            break;
                        }
                    }

            //printf("#");

                    for (ll j = 0; j < ca_length - 1; j++) {
                        if(k==0)
                            address[update] = path[j];
                        else
                            address2[update] = path[j];
                        update++;
                    }
                }
                if(k==1) if (exist_check(address2, update) == 0) continue;
                if(k==0) if (exist_check(address, update) == 0) continue;
                //free(path);
            }
            compare(address, address2);

        }
    //==================================================================================================================
     //tree
        else if(cmd[0]=='t'&&cmd[1]=='r'&&cmd[2]=='e'&&cmd[3]=='e'){
            char address[1000]="E:\\C\\home\\root\\";
            ll depth;
            scanf("%lld", &depth);
            if(depth<-1){
                printf("Invalid depth!\n");
            }
            if(depth==-1) depth=999999999;
            depth++;
            char temp = getchar();
            if(temp == '\n'){
            tree(address, 0, 0, depth);
            continue;
            }
            scanf("%s", cmd);
            if(cmd[0]=='='&&cmd[1]=='>'){
                tree_epo=1;
                FILE *t=fopen("tree.txt", "w");
                fclose(t);
                tree(address, 0, 0, depth);
            }
            else{
                printf("Invalid command!\n");
                continue;
            }
        }
    //================================================================================================================
      //organize
        else if(cmd[0]=='o'&&cmd[1]=='r'&&cmd[2]=='g'&&cmd[3]=='a'&&cmd[4]=='n'&&cmd[5]=='i'&&cmd[6]=='z'&&cmd[7]=='e'){
                char address[1000]="E:\\C\\home";
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
                if(exist_check(address, update)==0) continue;
               // free(path);

                    FILE *remptr;
                    ll length, volume=2;
                    ll open=0;
                    char filename[1000];
                        sprintf(filename, "%lld.txt", G);
                        G++;
                        wchar_t *und = filename;
                      //  printf("%s", filename);
                
                     //   int attr = GetFileAttributes(und);
                     //   if ((attr & FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN) {
                     //           SetFileAttributes(und , attr | FILE_ATTRIBUTE_HIDDEN);
                     //       }
                            unptr = fopen(filename, "w");
                    remptr = fopen(address, "r");
                    for(ll i=0;1;i++){
                    if(feof(remptr)) break;
                    string[i]= fgetc(remptr);
                    if(i>=1) fputc(string[i-1], unptr);
                    length=i;
                    if((i+1)%MAX==0) string=(char*) realloc(string, (volume*MAX)* sizeof(char));
                    }
                    fclose(unptr);
                    fclose(remptr);
 //   if ((attr & FILE_ATTRIBUTE_HIDDEN) == 0) {
 //       SetFileAttributes(und , attr | FILE_ATTRIBUTE_HIDDEN);
 //   }
                    char *mid=(char *)calloc(MAX, sizeof(char *));
                    ll length2=0, e_sign=0;
                    ll ent=0, sign=0;
                    for(ll i =0, j=0; i<=length; i++){
                            length2=j;
                        if(string[i]=='}'){
                            open--;
                            if(string[i+1]!='\n'){
                                mid[j]='\n';
                                j++;
                                if(open>0 && ent>0){
                            ll z=0;
                            ent--;
                            for(;z<open*4;z++){
                                mid[j]=' ';
                                j++;
                            }
                        }
                                mid[j]='}';
                                e_sign=1;
                                j++;
                                continue;
                            }
                            if(string[i+1]=='\n'){
                                mid[j]='\n';
                                j++;
                                ent++;
                                if(open>0 && ent>0){
                            ll z=0;
                            ent--;
                            for(;z<open*4;z++){
                                mid[j]=' ';
                                j++;
                            }
                        }
                                mid[j]='}';
                                j++;
                                e_sign=1;
                                continue;
                            }
                        }
                        if(e_sign==1){
                            mid[j]='\n';
                            j++;
                            e_sign=0;
                        }
                        if(open>0 && ent>0){
                            ll z=0;
                            ent--;
                            for(;z<open*4;z++){
                                mid[j]=' ';
                                j++;
                            }
                        }

                        if(string[i]=='{'){
                            open++;
                            sign=1;
                            if(string[i-1]==' '&&string[i-2]==' '){
                                ll k=i-1, size=0;
                                for(; 1;k--){
                                    size++;
                                    if(string[k]!=' '||k==0){
                                        break;
                                    }
                                }
                                j-=size;
                                mid[j]=string[k];
                                j++;
                                if(string[k]!='{'){
                                mid[j]=' ';
                                j++;
                                }
                                mid[j]='{';
                                j++;
                                if(string[i+1]=='}'){
                                    mid[j]=' ';
                                    j++;
                                }
                                    mid[j]='\n';
                                    ent++;
                                    j++;
                                continue;
                            }
                            if(string[i-1]!=' '&&i-1!=-1){
                                if(mid[j-1]!=' '){
                                mid[j]=' ';
                                j++;
                                }
                                mid[j]='{';
                                j++;
                                if(string[i+1]=='}'){
                                    mid[j]=' ';
                                    j++;
                                }
                                mid[j]='\n';
                                ent++;
                                j++;
                                continue;
                            }
                            mid[j]='{';
                            j++;
                            if(string[i+1]=='}'){
                                mid[j]=' ';
                                j++;
                            }
                                mid[j]='\n';
                                j++;
                                ent++;
                                continue;
                        }
                        if(sign==1){
                            for(ll k=i; 1;k++){
                                if(string[k]!=' '||string[k]=='\0'){
                                    i=k;
                                    sign=0;
                                    break;
                                }
                            }
                        }
                        mid[j]=string[i];
                        j++;
                    }

                    checkptr=fopen(address, "w");
                    for(ll i=0; i<length2; i++){
                        fputc(mid[i], checkptr);
                    }
                //    free(string);
                  //  free(mid);
                    fclose(checkptr);


        }
     //================================================================================
        // replace
        else if(cmd[0]=='r'&&cmd[1]=='e'&&cmd[2]=='p'&&cmd[3]=='l'&&cmd[4]=='a'&&cmd[5]=='c'&&cmd[6]=='e'){
    scanf("%s", cmd);
    if(cmd[0]=='-'&&cmd[1]=='s'&&cmd[2]=='1'){
        char spen = getchar();
                ll volume=2;
                ll r1_length, r1_count=0;
                char *mid=(char *)calloc(MAX, sizeof(char *));
                scanf("%c", &temp);
                if (temp == '"') {
                        sign_rf=1;
                    for (ll i = 0; 1; i++) {
                        scanf("%c", &string[i]);
                        if ((i + 1) % MAX == 0)
                            string = (char *) realloc(string, (volume * MAX) * sizeof(char));
                        if (string[i] == '"' && string[i - 1] != '\\') {
                            r1_length = i;
                            break;
                        }
                    }
                    r1_length--;
                }
                else {
                    sign_rf=0;
                    string[0] = temp;
                    ll volume = 2;
                    for (ll i = 1; 1; i++) {
                        scanf("%c", &string[i]);
                        if ((i + 1) % MAX == 0) string = (char *) realloc(string, (volume * MAX) * sizeof(char));
                        if (string[i] == ' ') {
                            r1_length = i;
                            break;
                        }
                    }
                    r1_length--;
                }
                ll r1_length3=0;
                char *name1=(char *)calloc(MAX, sizeof(char *));
                for (ll i = 0, j = 0; j <= r1_length; i++, j++) {
                    r1_length3 = i;
                    if((i+1)%MAX==0) name1=(char*) realloc(name1, (volume*MAX)* sizeof(char));
                    if (string[j] == '\\') {
                        if (string[j + 1] == 'n') {
                            name1[i] = '\n';
                            j++;
                            continue;
                        } else if (string[j + 1] == '\\') {
                            name1[i] = '\\';
                            j++;
                            continue;
                        } else if (string[j + 1] == '"') {
                            name1[i] = '"';
                            j++;
                            continue;
                        } else if(string[j+1]== '*'){
                            name1[i]= '*';
                            j++;}
                    }
                    name1[i] = string[j];
                }
                scanf("%s", cmd);
                if(cmd[0]=='-'&&cmd[1]=='s'&&cmd[2]=='2'){


                    char spen = getchar();
                ll volume=2;
                ll r2_length, r2_count=0;
                //char *mid=(char *)calloc(MAX, sizeof(char *));
                scanf("%c", &temp);
                if (temp == '"') {
                    for (ll i = 0; 1; i++) {
                        scanf("%c", &string[i]);
                        if ((i + 1) % MAX == 0)
                            string = (char *) realloc(string, (volume * MAX) * sizeof(char));
                        if (string[i] == ' ' && string[i - 1] == '"') {
                            r2_length = i;
                            break;
                        }
                    }
                    r2_length--;
                }
                else {
                    string[0] = temp;
                    ll volume = 2;
                    for (ll i = 1; 1; i++) {
                        scanf("%c", &string[i]);
                        if ((i + 1) % MAX == 0) string = (char *) realloc(string, (volume * MAX) * sizeof(char));
                        if (string[i] == ' ') {
                            r2_length = i;
                            break;
                        }
                    }
                    r2_length--;
                }
                ll r2_length3=0;
                char *name2=(char *)calloc(MAX, sizeof(char *));
                for (ll i = 0, j = 0; j <= r2_length; i++, j++) {
                    r2_length3 = i;
                    if((i+1)%MAX==0) name2=(char*) realloc(name2, (volume*MAX)* sizeof(char));
                    if (string[j] == '\\') {
                        if (string[j + 1] == 'n') {
                            name2[i] = '\n';
                            j++;
                            continue;
                        } else if (string[j + 1] == '\\') {
                            name2[i] = '\\';
                            j++;
                            continue;
                        } else if (string[j + 1] == '"') {
                            name2[i] = '"';
                            j++;
                            continue;
                        }
                    }
                    name2[i] = string[j];
                }


                //printf("%s", name1);
                        char address[1000]="E:\\C\\home";
                update=9;
                ll ca_length;
                ll space=0;
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
                        if (path[i] == ' ') {
                            space=1;
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
                        if (path[i] == ' '&&path[i-1]=='"') {
                                space=1;
                            ca_length = i;
                            break;
                        }
                    }


                    for (ll j = 0; j < ca_length-1; j++) {
                        address[update] = path[j];
                        update++;
                    }
                }
                //printf("%s\n%s\n%s", name1, name2, address);
                if(exist_check(address, update)==0) continue;
                    FILE *remptr;
                    ll length;
                     volume=2;
                    ll open=0;

                    char filename[1000];
                        sprintf(filename, "%lld.txt", G);
                        G++;
                        wchar_t *und = filename;
                        printf("%s\n", filename);
                    //    int attr = GetFileAttributes(und);
                    //    
                    //    if ((attr & FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN) {
                    //            SetFileAttributes(und , attr | FILE_ATTRIBUTE_HIDDEN);
                    //        }
                            unptr = fopen(filename, "w");
                    remptr = fopen(address, "r");
                    for(ll i=0;1;i++){
                    if(feof(remptr)) break;
                    string[i]= fgetc(remptr);
                    if(i>=1) fputc(string[i-1], unptr);
                    length=i;
                    if((i+1)%MAX==0) string=(char*) realloc(string, (volume*MAX)* sizeof(char));
                    }
                    fclose(unptr);
                    fclose(remptr);
   // if ((attr & FILE_ATTRIBUTE_HIDDEN) == 0) {
   //     SetFileAttributes(und , attr | FILE_ATTRIBUTE_HIDDEN);
   // }
                    ll at, sign_at=0, sign_all=0;
                    if(space==1){
                        scanf("%s", cmd);
                        if(cmd[0]=='-'&&cmd[1]=='a'&&cmd[2]=='t') {
                                scanf("%lld", &at);
                                sign_at=1;
                            }
                        else if(cmd[0]=='-'&&cmd[1]=='a'&&cmd[2]=='l'&&cmd[3]=='l'){
                                sign_all=1;
                            }
                        else{
                            printf("Invalid command!\n");
                            continue;
                        }
                    }
                    if(space==0){
                        ll final=replace(name1, r1_length3, name2, r2_length3, string, length, address);
                    //printf("%s\n%s\n%s", name1, name2, string);
                        if(final==-1) printf("Nothing found to be replace!\n");
                        continue;
                    }
                    if(sign_all==1){
                        ll final = all_replace(name1, r1_length3, name2, r2_length3, string, length, address);
                        if(final==-1) printf("Nothing found to be replace!\n");
                        continue;
                    }
                    if(sign_at==1){
                        ll final = c_find(name1, r1_length3,string, length);
                        if(at==0){
                            printf("Invalid input number!\n");
                            continue;
                        }
                        if( at>final) {
                            printf("This is more than limit of input!\n");
                            continue;
                        }
                        final = at_replace(name1, r1_length3, name2, r2_length3, string, length, address, at);

                    }

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

