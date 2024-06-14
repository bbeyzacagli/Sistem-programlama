#include "komut.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

void komut_yaz(Dllist list, char *karakter[], int rakam) 
{
    int i = 1;
    Dllist current_node = dll_next(dll_last(list));
    while (i < rakam) 
    {
        if (atoi(karakter[i]) > 0) 
        {
            int count = atoi(karakter[i]);
            char *char_str = karakter[i + 1];
            for (int k = 0; k < count; k++) 
            {
                if (strcmp(char_str, "\\b") == 0) 
                {
                     dll_append(list, new_jval_s(" ")); 
                } 
                else if (strcmp(char_str, "\\n") == 0) 
                {
                    dll_append(list, new_jval_s("\n"));
                } 
                else 
                {
                    for (int m = 0; m < strlen(char_str); m++) 
                    {
                        char *temp = (char *)malloc(2 * sizeof(char));
                        sprintf(temp, "%c", char_str[m]);
                        dll_append(current_node, new_jval_s(temp));
                    }
                }
            }
            i += 2;
        } 
        else 
        {
            break;
        }
    }
}

void komut_sil(Dllist list, char *karakter[], int rakam) 
{
    int i = 1;
    Dllist current_node = dll_prev(dll_last(list));
    while (i < rakam) 
    {
        if (atoi(karakter[i]) > 0) 
        {
            int count = atoi(karakter[i]);
            char *char_str = karakter[i + 1];
            while (count > 0 && current_node != dll_nil(list)) 
            {
                char *value = jval_s(dll_val(current_node));
                if (strcmp(char_str, "\\b") == 0 && strcmp(value, " ") == 0) 
                {
                    Dllist temp = current_node;
                    current_node = dll_prev(current_node);
                    dll_delete_node(temp);
                    count--;
                } 
                else if (strcmp(char_str, "\\n") == 0 && strcmp(value, "\n") == 0) 
                {
                    Dllist temp = current_node;
                    current_node = dll_prev(current_node);
                    dll_delete_node(temp);
                    count--;
                } 
                else if (strcmp(value, char_str) == 0) 
                {
                    Dllist temp = current_node;
                    current_node = dll_prev(current_node);
                    dll_delete_node(temp);
                    count--;
                } 
                else 
                {
                    current_node = dll_prev(current_node);
                }
            }
            i += 2;
        } 
        else 
        {
            break;
        }
    }
}

void komut_sonagit(Dllist list) 
{
    if (dll_empty(list)) 
    {
        return;
    }
    
    Dllist current_node = dll_last(list);
}

void komut_dur(Dllist list, FILE *output_file) 
{
    if (output_file == NULL) 
    {
        return;
    }


    Dllist node;
    for (node = dll_first(list); node != dll_nil(list); node = dll_next(node)) 
    {
        fprintf(output_file, "%s", jval_s(dll_val(node)));
    }

    fclose(output_file);
    free_dllist(list);
    exit(0);
}

int komut_kontrol(IS input_file) {
    int last_line = -1;
    if (input_file != NULL) {
        while (get_line(input_file) > 0) {
            if (!(strcmp(input_file->fields[0], "yaz:") == 0 ||
                  strcmp(input_file->fields[0], "sil:") == 0 ||
                  strcmp(input_file->fields[0], "sonagit:") == 0 ||
                  strcmp(input_file->fields[0], "dur:") == 0)) {
                fprintf(stderr, "Hata: Giris dosyasi uygun formatta degil.(%d. Satir)\n", input_file->line);
                return 0;
            }
            if (strcmp(input_file->fields[0], "yaz:") == 0 || strcmp(input_file->fields[0], "sil:") == 0) {
                if (input_file->NF == 1 || (input_file->NF == 2 && strlen(input_file->fields[1]) == 0)) {
                    fprintf(stderr, "Hata: Giris dosyasi uygun formatta degil.(%d. Satir: Komutun isleneni olmali.)\n", input_file->line);
                    return 0;
                }
            }
            for (int i = 1; i < input_file->NF; i++) {
                if (i < input_file->NF - 1 && input_file->fields[i][strlen(input_file->fields[i])-1] == ':' && input_file->fields[i+1][0] != ' ') {
                    fprintf(stderr, "Hata: Giris dosyasi uygun formatta degil.(%d. Satir: ':' karakterinden sonra bosluk bulunmali.)\n", input_file->line);
                    return 0;
                }    
            }    
            last_line = input_file->line;
        }
        if (last_line == -1 || strcmp(input_file->fields[0], "dur:") != 0) {
            fprintf(stderr, "Hata: Giris dosyasi son satir 'dur:' ile bitmiyor.\n");
            return 0;
        }
        rewind(input_file->f); // Dosyanın başına dön
        return 1;
    }
    fprintf(stderr, "Hata: Giris dosyasi bulunamadi.\n");
    return 0;
}