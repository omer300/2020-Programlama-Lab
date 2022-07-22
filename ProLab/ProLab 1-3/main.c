#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int ucak_id;
    int oncelik_id;
    int talep_edilen_inis_saati;
    int gecikme;

    struct node* next;

} ucak;

struct node *start=NULL;

void kuyruk_olustur()
{
    struct node *new_node,*temp;
    FILE *fp;
    fp = fopen("input.txt", "r");
    int a,b,c;
    new_node = (struct node*)malloc(sizeof(struct node));

    while(fscanf(fp,"%d %d %d", &a,&b,&c)!=EOF)
    {
        new_node->oncelik_id = a;
        new_node->ucak_id = b;
        new_node->talep_edilen_inis_saati = c;
        new_node->gecikme=0;
        if(start==NULL)
        {
            start=new_node;
            new_node->next=NULL;
        }
        else
        {
            temp=start;
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
            temp->next=new_node;
            new_node->next=NULL;
            printf("\nUcak id:%d talep edilen saat:%d\n",new_node->ucak_id,new_node->talep_edilen_inis_saati);
            inis_pisti_kullanim_sirasi();
            guncel_kalkis_pisti_kullanim_sirasi();
        }
        new_node = (struct node*)malloc(sizeof(struct node));
    }
    inis_pisti_kullanim_sirasi();
    printf("\n\n");
    yazdir();
    guncel_kalkis_pisti_kullanim_sirasi();
    fclose(fp);

};

void inis_pisti_kullanim_sirasi()
{
    struct node *i,*j;
    int temp;
    for(i=start; i->next!=NULL; i=i->next)
    {
        for(j=i->next; j!=NULL; j=j->next)
        {
            if((i->talep_edilen_inis_saati) > (j->talep_edilen_inis_saati))
            {
                temp=i->oncelik_id;
                i->oncelik_id=j->oncelik_id;
                j->oncelik_id=temp;

                temp=i->ucak_id;
                i->ucak_id=j->ucak_id;
                j->ucak_id=temp;

                temp=i->talep_edilen_inis_saati;
                i->talep_edilen_inis_saati=j->talep_edilen_inis_saati;
                j->talep_edilen_inis_saati=temp;

                temp=i->gecikme;
                i->gecikme=j->gecikme;
                j->gecikme=temp;
            }

        }
    }
    for(i=start; i->next!=NULL; i=i->next)
    {
        for(j=i->next; j!=NULL; j=j->next)
        {
            if((i->oncelik_id) > (j->oncelik_id) && (i->talep_edilen_inis_saati) == (j->talep_edilen_inis_saati))
            {
                temp=i->oncelik_id;
                i->oncelik_id=j->oncelik_id;
                j->oncelik_id=temp;

                temp=i->ucak_id;
                i->ucak_id=j->ucak_id;
                j->ucak_id=temp;

                temp=i->talep_edilen_inis_saati;
                i->talep_edilen_inis_saati=j->talep_edilen_inis_saati;
                j->talep_edilen_inis_saati=temp;

                temp=i->gecikme;
                i->gecikme=j->gecikme;
                j->gecikme=temp;
            }

        }
    }
    for(i=start; i->next!=NULL; i=i->next)
    {
        for(j=i->next; j!=NULL; j=j->next)
        {
            if((i->talep_edilen_inis_saati + i->gecikme) == (j->talep_edilen_inis_saati + j->gecikme))
            {
                if((i->oncelik_id) > (j->oncelik_id) && i->gecikme <4 && j->gecikme<4)
                {
                    temp=i->oncelik_id;
                    i->oncelik_id=j->oncelik_id;
                    j->oncelik_id=temp;

                    temp=i->ucak_id;
                    i->ucak_id=j->ucak_id;
                    j->ucak_id=temp;

                    temp=i->talep_edilen_inis_saati;
                    i->talep_edilen_inis_saati=j->talep_edilen_inis_saati;
                    j->talep_edilen_inis_saati=temp;

                    temp=i->gecikme+1;
                    i->gecikme=j->gecikme;
                    j->gecikme=temp;
                }
                else if((i->oncelik_id) == (j->oncelik_id) && i->gecikme <4 && j->gecikme<4 && i->ucak_id > j->ucak_id)
                {
                    temp=i->oncelik_id;
                    i->oncelik_id=j->oncelik_id;
                    j->oncelik_id=temp;

                    temp=i->ucak_id;
                    i->ucak_id=j->ucak_id;
                    j->ucak_id=temp;

                    temp=i->talep_edilen_inis_saati;
                    i->talep_edilen_inis_saati=j->talep_edilen_inis_saati;
                    j->talep_edilen_inis_saati=temp;

                    temp=i->gecikme+1;
                    i->gecikme=j->gecikme;
                    j->gecikme=temp;
                }
                else if(i->gecikme<4 && j->gecikme<4)
                    j->gecikme++;

            }

        }
    }
}
void guncel_kalkis_pisti_kullanim_sirasi()
{
    printf("Kalkis pisti kullanim sirasi\n\n");
    FILE *fp;
    if ((fp = fopen ("output.txt", "w+")) == NULL)
    {
        printf("Dosya acilamadi!");
        exit(1);
    }

    struct node *i=start;
    while(i!=NULL)
    {
        if(i->gecikme < 4 && i->talep_edilen_inis_saati+ i->gecikme<11)
        {
            printf("%d %5d %5d %5d %5d %5d\n", i->oncelik_id, i->ucak_id, i->talep_edilen_inis_saati,i->talep_edilen_inis_saati+i->gecikme,
                   i->gecikme,(i->talep_edilen_inis_saati+ i->gecikme+1)%24);
            fprintf(fp,"%d %5d %5d %5d %5d %5d\n", i->oncelik_id, i->ucak_id, i->talep_edilen_inis_saati,i->talep_edilen_inis_saati+i->gecikme,
                    i->gecikme,(i->talep_edilen_inis_saati+ i->gecikme+1)%24);
        }

        i=i->next;
    }
    i=start;
    while(i!=NULL)
    {
        i->gecikme=0;
        i=i->next;
    }
}
void yazdir()
{
    printf("\nInis pisti kullanim sirasi\n");
    struct node *i=start;
    while(i!=NULL)
    {
        if(i->gecikme > 3)
            printf("%d %5d %5d \tseferi %d kez ertelendiginden baska havalimanina yonlendirildi.\n", i->oncelik_id, i->ucak_id, i->talep_edilen_inis_saati, i->gecikme);
        else
            printf("%d %5d %5d %5d \tinis saat:%d\n", i->oncelik_id, i->ucak_id, i->talep_edilen_inis_saati, i->gecikme,(i->talep_edilen_inis_saati+ i->gecikme)%24);
        i=i->next;
    }
}
int main()
{
    kuyruk_olustur();

    return 0;
}

