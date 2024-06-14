#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "komut.h"

#define MAX_FILENAME_LENGTH 100

int main() 
{
    system("cls");
    char input_filename[MAX_FILENAME_LENGTH];
    char output_filename[MAX_FILENAME_LENGTH];
    IS input_file;
    FILE *output_file;
    Dllist list;

    while (1) {
        printf("Giris dosyasinin adini giriniz: ");
        scanf("%s", input_filename);

        input_file = new_inputstruct(input_filename);
        if (komut_kontrol(input_file)) {
            break;
        }
    }

    printf("Cikis dosyasinin adini giriniz: ");
    scanf("%s", output_filename);

    output_file = fopen(output_filename, "w");
    if (output_file == NULL) 
    {
        fprintf(stderr, "Hata: Cikis dosyasi olusturulamadi.\n");
        jettison_inputstruct(input_file);
        return 1;
    }

    list = new_dllist();

    while (get_line(input_file) > 0) 
    {
        if (strcmp(input_file->fields[0], "yaz:") == 0) 
        {
            komut_yaz(list, input_file->fields, input_file->NF);
        } 
        else if (strcmp(input_file->fields[0], "sil:") == 0) 
        {
            komut_sil(list, input_file->fields, input_file->NF);
        } 
        else if (strcmp(input_file->fields[0], "sonagit:") == 0) 
        {
            komut_sonagit(list);
        } 
        else if (strcmp(input_file->fields[0], "dur:") == 0) 
        {
            jettison_inputstruct(input_file);
            komut_dur(list, output_file);
         
        } 
    }
}