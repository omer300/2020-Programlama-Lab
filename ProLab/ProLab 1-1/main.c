#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct kayit
{
    int ogrNo;
    int dersKodu;
    int puan;

} ogrenci;      //soruda verilen şekilde struct oluşturma ve onu typedef ile ogrenci olarak tanımlama
void indexe_aktar(ogrenci *s1)              //indexdosyasını sil tekrar oluştur işlemlerinden dolayı
{                                           //önceki kayıtları kaydememe problemini önlemek için
    FILE *dosya_index, *dosya_veri;  //her işlemden önce ve sonra kullanılan verileri indexin içine yazdırma fonksiyonu
    dosya_index = fopen("index.txt", "r+");
    dosya_veri = fopen("veri.bin","rb");
    while(fread(s1, sizeof(*s1), 1, dosya_veri))
    {
        fprintf(dosya_index,"%d\n",s1->ogrNo);
    }
    fclose(dosya_veri);
    fclose(dosya_index);
}
void bin_indexveri_sirala(int n,int array[n],int matris[n][3])
{
    //binary search uygulamak için gereken sıralı verileri sıralamak için kullanılan fonksiyon
    int temp;
    for (int i = 0; i < n - 1; i++) //veri dosyasının içindekileri matrise aktarıldığı
    {                               //için matrisi bubble sort ile sıralama
        for (int j = 0; j < n - i - 1; j++)
        {
            if(matris[j][0] > matris[j+1][0])
            {
                temp=matris[j][0];
                matris[j][0] = matris[j+1][0];
                matris[j+1][0] = temp;

                temp=matris[j][1];
                matris[j][1] = matris[j+1][1];
                matris[j+1][1] = temp;

                temp=matris[j][2];
                matris[j][2] = matris[j+1][2];
                matris[j+1][2] = temp;
            }
            else if((matris[j][0]==matris[j+1][0])&&(matris[j][1]>matris[j+1][1]))
            {
                temp=matris[j][0];
                matris[j][0] = matris[j+1][0];
                matris[j+1][0] = temp;

                temp=matris[j][1];
                matris[j][1] = matris[j+1][1];
                matris[j+1][1] = temp;

                temp=matris[j][2];
                matris[j][2] = matris[j+1][2];
                matris[j+1][2] = temp;
            }
        }
    }
    for (int i = 0; i < n - 1; i++)//aynı sıralama ama index arrayi için
    {
        for (int j = 0; j < n - 1 -i; j++)
        {
            if(array[j] > array[j+1])
            {
                temp=array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}
void index_final_Sirala(int x[],int m,int y[])
{
    //istenilen formatta index dosyasını göstermek için adres ve öğrenci no'yu sıralama
    int i, j, t1,t2;

    for(i = 1; i <= m-1; i++)//bubble sort kullanımı öğrencile no'larını küçükten büyüğe
        for(j = 1; j <= m-i; j++)
            if(x[j-1] > x[j])
            {
                t1 = x[j-1];
                t2 = y[j-1];

                x[j-1] = x[j];
                y[j-1] = y[j];

                x[j] = t1;
                y[j] = t2;
            }
            else if(x[j-1] == x[j] && y[j-1] > y[j])
            {//adresleri ise aynı öğrenci no ları için küçükten büyüğe sıralama

                t1 = x[j-1];
                t2 = y[j-1];

                x[j-1] = x[j];
                y[j-1] = y[j];

                x[j] = t1;
                y[j] = t2;
            }
}

void kayitEkle(ogrenci *s1)
{
    //girilen kayıtları kaydetme fonksiyonu
    FILE *dosya_index, *dosya_veri;

    dosya_index = fopen("index.txt", "r+");
    dosya_veri = fopen("veri.bin", "r+b");
    if(!dosya_veri)
        dosya_veri = fopen("veri.bin", "a+b");

    printf("\n\nOgrenci No: ");
    scanf("%d", &s1->ogrNo);
    printf("\nDers Kodu: ");
    scanf("%d", &s1->dersKodu);
    printf("\nPuan: ");
    scanf("%d", &s1->puan);

    /*veri dosyasında pointerı sona konumlandırma
    böylece yeni kayıt en altta kalıcak*/
    fseek(dosya_veri, 0, SEEK_END);
    /*eğer yazılan bir yazı varsa if 1 oluyor ve koşul
    içine giriyor böylece veri yazılırken indexe de öğrenci no'su yazılıyor.*/
    if (fwrite(s1, sizeof(*s1), 1, dosya_veri))
    {
        fseek(dosya_index, 0, SEEK_END);
        fprintf(dosya_index,"%d",s1->ogrNo);
    }
    else//olası bir kayıt eklenememe durumunu kontrol etmek için
    {   //hata komutu
        printf("\nKayit eklenemedi.");
    }
    rewind(dosya_index);//indexin pointerını en başa tanımlama
    //işlem bitince dosyaları kapatma
    fclose(dosya_index);
    fclose(dosya_veri);
}
void kayitGuncelle(ogrenci *s1,int a,int b)
{
    /*girilen öğrenci no(int a) ve ders kodunun(int b)
    skorunu değiştirme fonksiyonu*/
    int kontrol = 0;
    FILE *dosya_index, *dosya_veri;

    dosya_index = fopen("index.txt", "r+");
    dosya_veri = fopen("veri.bin", "r+b");
    /*dosya pointer tanımlama ve veri dosyasının
    pointerını en başa konumlandırma*/
    fseek(dosya_veri,0, SEEK_SET);
    while (fread(s1, sizeof(*s1), 1, dosya_veri) == 1)//fread değer okuduğu sürece dönecek bir while
    {
        //eğer öğrenci no ve ders kodu sağlanıyorsa koşula girilir
        if(s1->ogrNo==a && s1->dersKodu==b)
        {
            kontrol = 1;//kayıt bulunup bulunmadığını kontrol etmek

            fseek(dosya_veri, (-1) * sizeof(*s1), SEEK_CUR);
            /*veri dosyasının pointerını son okunan
            değer sağladığı için o değerleri tekrar
            okumak amaçlı 1 struct büyüklüğünde
            pointerı geri kaydırma*/
            fread(s1, sizeof(*s1), 1, dosya_veri);//değerleri tekrar okuma

            printf("\nOgrenci No:%d", s1->ogrNo);//bulunan değerleri yazdırma
            printf("\nDers Kodu:%d", s1->dersKodu);
            printf("\nPuan:%d", s1->puan);

            printf("\n\nYeni puan giriniz: ");//puanını değiştirme işlemi
            scanf("%d", &s1->puan);

            fseek(dosya_veri, (-1) * sizeof(*s1), SEEK_CUR);//tekrar 1 struct geri gitme
            fwrite(s1, sizeof(*s1), 1, dosya_veri);//son halini o kaydın üzerine yazma
            break;
        }
    }
//eğer değer bulunduysa kontrol 1 olacağından buraya girilmeyecek
//bulmazsa 0 olduğu için girip bulunamadı yazdıracak
    if (!kontrol)
        printf("\nKayit Bulunamadi.");

    printf("\n");
    fclose(dosya_index);
    fclose(dosya_veri);
}
void kayitBul(ogrenci *s1, int a)
{
    /*binary search kullanarak girilen öğrenci no(int a)
    için tüm kayıtları yazdırma*/
    int kontrol = 0;
    int n=0;
    FILE *dosya_veri;
    int *array_yindex= malloc((n+1) *sizeof(int));//dinamik array tanımlama
    int array_yveri[1000][3];
    dosya_veri = fopen("veri.bin", "r+b");
    fseek(dosya_veri,0,SEEK_SET);
    while(fread(s1, sizeof(*s1), 1, dosya_veri))
    {
        //veri dosyasında her bir değeri oluşturulan index ve veri arraylerine aktarma
        array_yveri[n][0] = s1->ogrNo;
        array_yveri[n][1] = s1->dersKodu;
        array_yveri[n][2] = s1->puan;
        n++;
        array_yindex=realloc(array_yindex,n*sizeof(int));
        array_yindex[n-1]=s1->ogrNo;
    }
    array_yveri[n][3];
    fclose(dosya_veri);
    //iki arraye de bubble sort uygulama fonksiyonu
    bin_indexveri_sirala(n,array_yindex,array_yveri);
    //binary search için değişken tanımlama
    int first, last, middle, search;
    search = a;
    first = 0;
    last = n-1;
    middle = (first+last)/2;
    while (first <= last)
    {
        if (array_yindex[middle] < search)
            first = middle + 1;
        else if (array_yindex[middle] == search)//aradığımız değer bulunduğunda
        {
            int k=1;
            while(array_yindex[middle] == array_yindex[middle-k])
                k++;
/*birden fazla aynı öğrenci no'dan olabileceği için
kendinden önce ve sonraki indisleri kontrol etme
ve kendinden önce eğer varsa o değerleri alttaki
döngü ile yazdırma*/
            while(k>0)
            {
                if(search == array_yveri[middle-k][0])
                {
                    printf("\nOgrenci No:%d", array_yveri[middle-k][0]);
                    printf("\nDers Kodu:%d", array_yveri[middle-k][1]);
                    printf("\nPuan:%d", array_yveri[middle-k][2]);
                    kontrol = 1;
                }
                  k--;
            }
            while(1)
            {//kendinden sonra gelen değerleri yazdırma
                if(search == array_yveri[middle+k][0])
                {
                    printf("\nOgrenci No:%d", array_yveri[middle+k][0]);
                    printf("\nDers Kodu:%d", array_yveri[middle+k][1]);
                    printf("\nPuan:%d", array_yveri[middle+k][2]);
                    kontrol = 1;
                    k++;
                }
                else
                    break;
            }
            break;//tüm değerler yazıldıktan sonra
            //breakler ile döngüden çıkma
        }
        else
            last = middle - 1;

        middle = (first + last)/2;
    }
    if ((first > last)&&kontrol==0)
        printf("Kayit bulunamadi.", search);
    printf("\n");
    free(array_yindex);
    //free(array_yveri);

}
void kayitSil(ogrenci *s1, int a,int b)
{
    //ilgili kaydı arama konusunda kayıt güncelle ile aynı mantık çalışan fonksiyon
    int r, kontrol = 0,file_handler_ind,file_handler_rec,file_size_ind,file_size_rec;
    //char ch;
    FILE *dosya_index, *dosya_veri;

    dosya_index = fopen("index.txt", "r+");
    dosya_veri = fopen("veri.bin", "r+b");

    file_handler_ind=_fileno(dosya_index);
    file_handler_rec=_fileno(dosya_veri);

    file_size_ind=_filelength(file_handler_ind);//dosya boyutlarını öğrenmek ve sonra kullanmak için
    file_size_rec=_filelength(file_handler_rec);//her dosya için filelenght kullanımı

    fseek(dosya_veri,0, SEEK_SET);
    while (fread(s1, sizeof(*s1), 1, dosya_veri) == 1)
    {
        if(s1->ogrNo==a && s1->dersKodu==b)
        {
            kontrol = 1;
            fseek(dosya_veri, (-1) * sizeof(*s1), SEEK_CUR);
            fread(s1, sizeof(*s1), 1, dosya_veri);
            printf("\nOgrenci No:%d", s1->ogrNo);
            printf("\nDers Kodu:%d", s1->dersKodu);
            printf("\nPuan:%d", s1->puan);

            fseek(dosya_index, sizeof(int), SEEK_CUR);
/* değeri bulduktan sonra silinecek değerin arkasındaki değerleri
pointer kullanarak scanleyerek tekrar yazdırma işlemi*/
            while(fscanf(dosya_index,"%d",&r) == 1)
            {
                fseek(dosya_index, (-2) * sizeof(int), SEEK_CUR);
                fprintf(dosya_index,"%d",&r);
                fseek(dosya_index, sizeof(int), SEEK_CUR);
            }

            while (fread(s1, sizeof(*s1), 1, dosya_veri))
            {
                fseek(dosya_veri, (-2) * sizeof(*s1), SEEK_CUR);
                fwrite(s1, sizeof(*s1), 1, dosya_veri);
                fseek(dosya_veri, sizeof(*s1), SEEK_CUR);
            }
            break;
        }
    }
    if (!kontrol)
    {
        printf("\nKayit Bulunamadi.");
    }
    _chsize(file_handler_ind,file_size_ind-sizeof(int));//dosya boyutlarını yeni haline uyması için
    _chsize(file_handler_rec,file_size_rec-sizeof(*s1));//indexten int veriden struct boyutunda azaltma
    //(dosya numarası,boyut- 1 veri çıktığı için -1*veri boyutu);
    printf("\n");
    fclose(dosya_index);
    fclose(dosya_veri);
}

void veriDosyasiniGoster(ogrenci *s1)
{
    //veri dosyasını gösterme işlemi
    FILE *dosya=NULL;
    int kontrol = 1;

    dosya = fopen("veri.bin", "rb");

    while (fread(s1, sizeof(*s1), 1, dosya))
    {
        if ((s1->ogrNo) != 0)
        {
            if (kontrol == 1)
                printf("\n\nOgrenci No  dersKodu    puan");
            kontrol = 0;
            printf("\n%-3d", s1->ogrNo);
            printf("%10d", s1->dersKodu);
            printf("%13d", s1->puan);
        }
    }

    if (kontrol == 1)
        printf("Veri dosyasi bulunamadi.\n\n");
    printf("\n");
    fclose(dosya);
}

void indexDosyasiniGoster(ogrenci *s1)
{
    //index dosyasını ve adreslerini sıralı bir şekilde gösterme
    FILE *dosya_index, *dosya_veri,*dosya_final;
    int kontrol = 1, n = 1, i = 0;
    int *array_adres= malloc(n *sizeof(int)), *array_no= malloc(n *sizeof(int));//2 dinamik dizi tanımlama
    dosya_index = fopen("index.txt", "r+");
    dosya_veri = fopen("veri.bin","rb");
    dosya_final=fopen("index_final.txt","r+");
    //istenilen format için kullanılacak txt indexi index_final

    fseek(dosya_index, 0, SEEK_SET);
    //veri içindeki no ları ve adresleri arraye aktarma
    while(fread(s1, sizeof(*s1), 1, dosya_veri))
    {
        array_adres[n-1]=&s1[n-1];
        array_no[n-1]=s1->ogrNo;
        n++;
        array_adres=realloc(array_adres,n*sizeof(int));
        array_no=realloc(array_no,n*sizeof(int));

    }
    fclose(dosya_veri);
    if(n-1>1)//öğrenci noları kendi aralarında no'ların aynı olduğu adresleri kendi aralarındna sıralama
        index_final_Sirala(array_no,(n-1),array_adres);
    while (fscanf(dosya_index,"%d",&s1->ogrNo)==1)
    {
        if ((s1->ogrNo) != 0)
        {
            if(kontrol==1)
                printf("\n\nOgrenci No    adres");

            kontrol = 0;
            printf("\n%-12d",array_no[i]);
            printf("%d", array_adres[i]);
            fprintf(dosya_final,"%d %d\n",array_no[i],array_adres[i]);
            i++;
            //hem dosyaya hem de ekrana yazdırma işlemi
        }
    }
    if (kontrol == 1)
        printf("Index dosyasi bulunamadi.\n\n");
    printf("\n");
    free(array_adres);
    free(array_no);
    fclose(dosya_index);
    fclose(dosya_final);
}
void indexDosyasiniOlustur()
{
    /*kodda fonksiyonlarda kullanılacak index.txt
    ve adres ve girdileri sıralı göreceğimiz index_final dosyaları oluşturma*/
    FILE *dosya,*dosya_final;
    dosya = fopen("index.txt", "a+");
    dosya_final = fopen("index_final.txt", "a+");
    fclose(dosya);
    fclose(dosya_final);
}
void indexDosyasiniSil()
{
    //remove fonksiyonu kullanarak 2 index dosyasını da silme
    if (remove("index.txt")==0)
        if(remove("index_final.txt")==0)
        {
            printf("Index dosyasi basariyla silindi.\n\n");
        }
        else
        {
            printf("Index dosyasi silinemedi.\n\n");
        }
}
int main()
{
    ogrenci s1;
    int sec, no,derskodu;

    //index dosyaları oluşturma
    indexDosyasiniOlustur();
    //varsa veri dosyasında veri indexe aktarma
    indexe_aktar(&s1);
    //exit komutu verilene kadar dönen ve diğer fonksiyonları kullanmak için while komutu
    while (1)
    {
        printf("\n\n1:kayitEkle\n2:veriDosyasiniGoster\n3:Yeniden indexDosyasiniOlustur\n4:indexDosyasiniSil\n5:indexDosyasiniGoster\n6:kayitGuncelle\n7:kayitSil\n8:kayitBul\n9:Exit \n\n");
        scanf("%d", &sec);
        fflush(stdin);
        switch (sec)
        {
        case 1:
            kayitEkle(&s1);
            indexe_aktar(&s1);

            break;
        case 2:
            veriDosyasiniGoster(&s1);

            break;
        case 3:
            indexDosyasiniOlustur();
            indexe_aktar(&s1);
            printf("Index dosyasi olusturuldu.\n\n");

            break;
        case 4:
            indexDosyasiniSil();

            break;
        case 5:
            indexe_aktar(&s1);
            indexDosyasiniGoster(&s1);

            break;
        case 6:
            indexe_aktar(&s1);
            printf("\nGuncellenecek kaydin ogrenci no'sunu giriniz : ");
            scanf("%d", &no);
            fflush(stdin);
            printf("Guncellenecek kaydin ders kodunu giriniz : ");
            scanf("%d", &derskodu);
            fflush(stdin);

            kayitGuncelle(&s1, no, derskodu);

            break;
        case 7:
            indexe_aktar(&s1);
            printf("\nSilinecek kaydin ogrenci no'sunu giriniz : ");
            scanf("%d", &no);
            fflush(stdin);
            printf("Silinecek kaydin ders kodunu giriniz : ");
            scanf("%d", &derskodu);
            fflush(stdin);

            kayitSil(&s1, no, derskodu);

            break;
        case 8:
            indexe_aktar(&s1);
            printf("\nBulunacak kaydin ogrenci no'sunu giriniz : ");
            scanf("%d", &no);
            fflush(stdin);

            kayitBul(&s1,no);

            break;
        case 9:
            exit(0);
        default:
            printf("\n\nHatali giris.");
        }
    }
    return 0;
}

