#include <stdio.h>
#include<stdlib.h>
#include<string.h>
int agac_olusur_mu(int length,char sonek[length][100],char onek[length][100])
{
    for(int i=1; i<length; i++)
    {
        if(strcmp(sonek[i],onek[i])==0)
        {
            printf("Sonek %s ve Onek %s nin ayni olmasindan dolayi agac yapisi olusturulamaz.\n",sonek[i],onek[i]);
            return 0;
        }

    }
    printf("\nKelimenin kendisi haricinde ortak olan onek sonek olmadigi icin agac yapisi olusturulabilir.\n");
    return 1;
}
void katar_geciyor_mu(int length,char sonek[length][100],char katar[100])
{
    char yedek[100];
    strcpy(yedek,sonek[0]);
    int sayac=0,q;
    for(int i=0; i<strlen(yedek); i++)
    {
        if(katar[0]==yedek[i])
        {
            q=i;
            for(int k=0; k<strlen(katar); k++,q++)
            {
                if(katar[k]!=yedek[q])
                    break;
                else if(k==(strlen(katar)-1))
                    sayac++;
            }
            i=q-1;
        }
    }

    char *ptr;
    ptr=strstr(sonek[0],katar);
    if(sayac>0)
        printf("%s altkatari %s kelimesinde vardir ve %d kez gecmektedir.\nGectigi ilk yerin adresi:%d\nPozisyonu:%s",katar,sonek[0],sayac,ptr,ptr);
    else
        printf("Aranan katar kelimede bulunamamistir.");
}
void tekrar_eden_en_uzun_altkatar(int length,char sonek[length][100])
{
    char yedek[100],temp[100];
    strcpy(yedek,sonek[0]);
    int j=0,sayac=0,tut=0,max_tekrar=0,max_uzunluk=0;
    char sonek_onek[5050][100];
    while(strlen(yedek)>0)
    {
        for(int i=tut; i<5050; i++)
        {
            if(strlen(yedek)>0)
            {
                strcpy(sonek_onek[i],yedek);
                yedek[strlen(yedek)-1] = '\0';
            }
            else
            {
                tut=i;
                break;
            }

        }
        j++;
        strcpy(yedek,sonek[j]);
    }
    j=0;
    strcpy(yedek,sonek[0]);
    int q;
    while(strlen(sonek_onek[j])>0)
    {
        for(int i=0; i<strlen(yedek); i++)
        {
            if(sonek_onek[j][0]==yedek[i])
            {
                q=i;
                for(int k=0; k<strlen(sonek_onek[j]); k++,q++)
                {
                    if(sonek_onek[j][k]!=yedek[q])
                        break;
                    else if(k==(strlen(sonek_onek[j])-1))
                        sayac++;
                }
                i=q-1;
            }
        }
        if(strlen(sonek_onek[j])>max_uzunluk && sayac>1)
        {
            strcpy(temp,sonek_onek[j]);
            max_tekrar=sayac;
            max_uzunluk=strlen(sonek_onek[j]);
        }
        j++;
        sayac=0;
    }
    if(max_tekrar>1)
        printf("\nTekrar eden en uzun altkatar:%s\nTekrar sayisi:%d\n",temp,max_tekrar);
    else
        printf("\nBirden fazla tekrar eden altkatar bulunamamistir.\n");
}
void en_cok_tekrar_eden_altkatar(int length,char sonek[length][100])
{
    char yedek[100],temp[100];
    strcpy(yedek,sonek[0]);
    int j=0,sayac=0,tut=0,max=0;
    char sonek_onek[5050][100];
    while(strlen(yedek)>0)
    {
        for(int i=tut; i<5050; i++)
        {
            if(strlen(yedek)>0)
            {
                strcpy(sonek_onek[i],yedek);
                yedek[strlen(yedek)-1] = '\0';
            }
            else
            {
                tut=i;
                break;
            }
        }
        j++;
        strcpy(yedek,sonek[j]);
    }
    j=0;
    while(strlen(sonek_onek[j])>0)
    {
        for(int i=0; i<tut; i++)
        {
            if(strcmp(sonek_onek[j],sonek_onek[i])==0)
            {
                sayac++;
            }

        }
        if(sayac>max)
        {
            strcpy(temp,sonek_onek[j]);
            max=sayac;
        }
        j++;
        sayac=0;

    }
    printf("\nEn cok tekrar eden altkatar:%s\nTekrar sayisi:%d\n",temp,max);
}
int main()
{
    char sonek[100][100];
    char onek[100][100];
    char kelime[100],katar[100];
    //printf("Bir kelime giriniz:");
    //scanf("%s",kelime);
    FILE *fileptr;
    fileptr = fopen("input.txt", "r");
    char name;

    if(fileptr == NULL)
    {
        printf("Hata\n");
        return 0;
    }
    fscanf( fileptr, "%s",kelime);
    printf("Girilen kelime:%s", kelime);
    printf("\n");
    fclose(fileptr);
    char yedek[100];
    strcpy(yedek,kelime);

    for(int i=0; i<strlen(kelime); i++)
    {
        strcpy(sonek[i],kelime+i);
        strcpy(onek[i],yedek);
        yedek[strlen(yedek)-1] = '\0';
    }
    int sec;
    while(1)
    {
        printf("\n\n1-)Agac olusturabilir mi?\n2-)Aranan katar kelimede geciyor mu?\n3-)Tekrar eden en uzun altkatar\n4-)En cok tekrar eden altkatar\n5-)Exit\n\n");
        scanf("%d", &sec);
        fflush(stdin);
        switch (sec)
        {
        case 1:
            printf("\n%s kelimesinin sonekleri\n\n",kelime);
            for(int i=0; i<strlen(kelime); i++)
                printf("%s\n",sonek[i]);
            printf("\n%s kelimesinin onekleri\n\n",kelime);
            for(int i=0; i<strlen(kelime); i++)
                printf("%s\n",onek[i]);
            agac_olusur_mu(strlen(kelime),sonek,onek);

            break;
        case 2:
            printf("%s kelimesinde aracanacak katari giriniz:",kelime);
            scanf("%s",katar);
            fflush(stdin);
            printf("\n");
            katar_geciyor_mu(strlen(kelime),sonek,katar);

            break;
        case 3:
            tekrar_eden_en_uzun_altkatar(strlen(kelime),sonek);

            break;
        case 4:
            en_cok_tekrar_eden_altkatar(strlen(kelime),sonek);

            break;
        case 5:
            exit(0);
        }
    }
    return 0;
}
