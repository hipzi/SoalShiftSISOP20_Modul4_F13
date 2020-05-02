# MODUL 4

 - Soal 1 :
	 * <a href="#soal-1">soal 1</a>
 - Soal 4 :
	 * <a href="#soal-4">soal 4</a>


<a id="soal-1"> </a> 
## SOAL 1
<justify>
Mount source (root) filesystem adalah direktori /home/[user]/Documents
<p></p>

    static  const  char *dirpath = "/home/hipzi/Documents"; 
<p></p>
key caesar cipher dengan shift 10
<p></p>

    char msg[1000]="9(ku@AW1[Lmvgax6q`5Y2Ry?+sF!^HKQiBXCUSe&0M.b%rI'7d)o4~VfZ*{#:}ETt$3J-zpc]lnh8,GwP_ND|jO";
    int key = 10;
<p></p>

<p></p>
fungsi enkripsi caesar cipher :
<p></p>

    char *enkripsi(char filename[1000])
    {
        int posisi;
        int len = strlen(filename);
        int M = strlen(msg); 

        for (int i = 0; i < len ; i++)
        {
            if (filename[i] != '/')
            {
                posisi = strchr(msg, filename[i]) - msg;
                filename[i] = msg[(posisi + key) % M];
            }    
        }
        return filename;
    }
<p></p>
fungsi dekripsi caesar cipher :
<p></p>

    char *dekripsi(char name[1000])
    {    
        int posisi;
        int len = strlen(name);
        int M = strlen(msg); 
        int key_d = M - key; 

        for (int i = 0; i < len ; i++)
        {
            if (name[i] != '/')
            {
                posisi = strchr(msg, name[i]) - msg;
                name[i] = msg[(posisi + key_d) % M];
            }    
        }
        return name;
    }
<p></p>
fungsi untuk mengambil ekstensi file :
<p></p>

    const char *get_filename_ext(const char *filename) {

        const char *dot = strrchr(filename, '.');
        if(!dot || dot == filename){
            strcpy(ekstensi, "\0");
            return ekstensi;
        }
        else{
            strcpy(ekstensi, dot);
            return ekstensi;
        }
    }
<p></p>
<p></p>
Setiap pembuatan direktori terenkripsi baru (mkdir ataupun rename) akan
tercatat ke sebuah database/log berupa file :
<p></p>

    static  const  char *enkripsilog = "/home/hipzi/enkripsi.log";

    if(strncmp("/encv1_", temp_path, 7) == 0){
        fp = fopen(enkripsilog, "a");
        fputs(temp_path, fp);
        fputs("\n", fp);
        fclose(fp);
    }
    else if(strncmp("/encv2_", temp_path, 7) == 0){
        fp = fopen(enkripsilog, "a");
        fputs(temp_path, fp);
        fputs("\n", fp);
        fclose(fp);
    }
<p></p> 
Keterangan : </br>
- pada fungsi <code>mkdir</code> dan <code>rename</code></br>
<p></p>
<p></p>
untuk melakukan dekripsi pada direktori terenkripsi yang​ rename ​ menjadi tidak terenkripsi
<p></p>

    DIR *dp;
    struct dirent *de;  

    if(strncmp("/encv1_", s_from, 7) == 0){
    dp = opendir(ganti);

    if (dp == NULL)
    return -errno;

            while ((de = readdir(dp)) != NULL) {

                struct stat st;
                memset(&st, 0, sizeof(st));

                st.st_ino = de->d_ino;
                st.st_mode = de->d_type << 12;

                if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
                {
                        memset(&temp, 0, sizeof(temp));

                        get_filename_ext(de->d_name);
                        memmove(temp, de->d_name, strlen(de->d_name)-strlen(ekstensi));
                        dekripsi(temp);
                        strcat(temp, ekstensi);

                        sprintf(namalama,"%s/%s", ganti,de->d_name);
                        sprintf(gantinama,"%s/%s", ganti,temp);
                        rename(namalama, gantinama);
                        printf("%s %s\n", namalama, gantinama);
                }
            }

        closedir(dp);
    }
<p></p>
Fungsi yang saja yang dipakai pada pada fuse :
<p></p>

    static struct fuse_operations xmp_oper = {
        .getattr    = xmp_getattr,
        .readdir    = xmp_readdir,
        .read       = xmp_read,
        .write		= xmp_write,
        .rename		= xmp_rename,
        .mkdir	    = xmp_mkdir,
        .rmdir      = xmp_rmdir,
        .create     = xmp_create,
        .unlink     = xmp_unlink,
        .truncate   = xmp_truncate,
        .utimens    = xmp_utimens,
        .chmod      = xmp_chmod,
        .chown      = xmp_chown,
        .open		= xmp_open,
        .mknod      = xmp_mknod,
        .statfs     = xmp_statfs,
    };
<p></p>

<a id="soal-4"></a>
## SOAL 4
<justify>
Log system :
<p></p>
Sebuah berkas nantinya akan terbentuk bernama "fs.log" di direktori *home*
pengguna (/home/[user]/fs.log) yang berguna menyimpan daftar perintah system
call yang telah dijalankan.
<p></p>

    static  const  char *logpath = "/home/hipzi/fs.log";

<p></p> 
Format untuk logging yaitu : </br>

    [LEVEL]::[yy][mm][dd]-[HH]:[MM]:[SS]::[CMD]::[DESC ...]
<p></p> 
<p></p> 
Log level WARNING, merupakan pencatatan log untuk syscall ​ rmdir​ dan
unlink​. Sisanya, akan dicatat dengan level INFO.
<p></p> 

    char command[10]="UNLINK";
    char level[10]="WARNING";
    char waktu[1000];
    char satu[1000];
    char dua[1000];
    char tiga[1000];

    time_t t = time(NULL); 
    struct tm tm = *localtime(&t);

    sprintf(waktu, "%02d%02d%02d-%02d:%02d:%02d", (tm.tm_year + 1900) % 100, 
    tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec); 

    sprintf(satu, "%s::%s", level, waktu); 
    sprintf(dua, "%s::%s", satu, command);
    sprintf(tiga, "%s::%s\n", dua, path);

    FILE *fp;
    fp = fopen(logpath, "a");
    fputs(tiga, fp);
    fclose(fp);
<p></p> 
Keterangan : </br>
- contoh untuk format logging <code>rmdir</code> dan <code>unlink</code></br>
  
    char command[10]="TRUNCATE";
    char level[10]="INFO";
    char waktu[1000];
    char satu[1000];
    char dua[1000];
    char tiga[1000];

    time_t t = time(NULL); 
    struct tm tm = *localtime(&t);

    sprintf(waktu, "%02d%02d%02d-%02d:%02d:%02d", (tm.tm_year + 1900) % 100, 
    tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec); 

    sprintf(satu, "%s::%s", level, waktu); 
    sprintf(dua, "%s::%s", satu, command);
    sprintf(tiga, "%s::%s\n", dua, path);

    FILE *fp;
    fp = fopen(logpath, "a");
    fputs(tiga, fp);
    fclose(fp);
<p></p>
Keterangan : </br>
- contoh untuk format logging selain <code>rmdir</code> dan <code>unlink</code></br>




