#ifndef KOMUT_H
#define KOMUT_H

#include "dllist.h"
#include "fields.h"
#include <stdio.h>


void komut_yaz(Dllist list, char *karakter[], int rakam);
void komut_sil(Dllist list, char *karakter[], int rakam);
void komut_sonagit(Dllist);
void komut_dur(Dllist, FILE*);
int komut_kontrol(IS input_file);

#endif 