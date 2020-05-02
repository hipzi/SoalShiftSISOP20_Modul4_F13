#define FUSE_USE_VERSION 28

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h> 
#include <sys/time.h>
#include <pwd.h> 

static  const  char *dirpath = "/home/hipzi/Documents"; 
static  const  char *logpath = "/home/hipzi/fs.log";
static  const  char *enkripsilog = "/home/hipzi/enkripsi.log";

char ekstensi[50];
char cwd[1000];
char msg[1000]="9(ku@AW1[Lmvgax6q`5Y2Ry?+sF!^HKQiBXCUSe&0M.b%rI'7d)o4~VfZ*{#:}ETt$3J-zpc]lnh8,GwP_ND|jO";
int key = 10;

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

static  int  xmp_getattr(const char *path, struct stat *stbuf)
{
    int res;
    char fpath[1000];
    char temp_path[1000];
 
    sprintf(temp_path,"%s",path);
    sprintf(fpath, "%s%s",dirpath,temp_path); 

    res = lstat(fpath, stbuf);
    
    if (res == -1)
    return -errno;
    
    return 0;
}

//belum
static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
off_t offset, struct fuse_file_info *fi)
{
    char fpath[1000];
    char temp_path[1000];

    // char gantinama[1000];
    // char namalama[1000];
    // char temp[1000];

    // char path_enkripsi[1000];
    // char rev_temp_path[1000];
    // char temp[1000];
    // char nama[1000];

    // char from[1000];
    // char to[1000];

    // char rev_temp_path[1000];
    char command[10]="READDIR";
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

    if (strcmp(path, "/") == 0){ 
        sprintf(fpath, "%s", dirpath); 
    } else { 
        sprintf(temp_path,"%s",path); 
        sprintf(fpath, "%s%s",dirpath,temp_path); 
    } 

    // printf("%s\n", fpath);

    int res = 0;  

    DIR *dp;
    struct dirent *de;  

    (void) offset;
    (void) fi;  

    dp = opendir(fpath);

    if (dp == NULL)
    return -errno;

    // if(strncmp("/encv1_", temp_path, 7) == 0){
    //     while ((de = readdir(dp)) != NULL && strncmp("/encv1_", temp_path, 7) == 0) {

    //         struct stat st;
    //         memset(&st, 0, sizeof(st));

    //         st.st_ino = de->d_ino;
    //         st.st_mode = de->d_type << 12;

    //         if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
    //         {
                // if(strncmp("/encv1_", temp_path, 7) == 0){
                    // strcpy(temp,de->d_name);
                    // enkripsi(temp);

                    // sprintf(path_enkripsi,"%s%s",dirpath,temp_path); 

                    // sprintf(namalama,"%s/%s", path_enkripsi,de->d_name);
                    // sprintf(gantinama,"%s/%s", path_enkripsi,temp);
                    // rename(namalama, gantinama);
                //     printf("%s %s\n",namalama,gantinama);

                    // res = (filler(buf, temp, &st, 0));

                //     if(res!=0) break;
                // }
                // else {
                    // res = (filler(buf, de->d_name, &st, 0));

                    // if(res!=0) break;
                // }
                
    //         }
    //     }
    // }
    //     else {
            while ((de = readdir(dp)) != NULL) {

            struct stat st;
            memset(&st, 0, sizeof(st));

            st.st_ino = de->d_ino;
            st.st_mode = de->d_type << 12;

            if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
            {
                // if(strncmp("/encv1_", temp_path, 7) == 0){
                //     strcpy(temp,de->d_name);
                //     enkripsi(temp);

                //     sprintf(path_enkripsi,"%s%s",dirpath,temp_path); 

                //     sprintf(namalama,"%s/%s", path_enkripsi,de->d_name);
                //     sprintf(gantinama,"%s/%s", path_enkripsi,temp);
                //     rename(namalama, gantinama);
                //     printf("%s %s\n",namalama,gantinama);

                //     res = (filler(buf, temp, &st, 0));

                //     if(res!=0) break;
                // }
                // else {
                    res = (filler(buf, de->d_name, &st, 0));

                    if(res!=0) break;
                // }
                
            }
        }

        // }

closedir(dp);
return 0;
}  

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
struct fuse_file_info *fi)
{

    char fpath[1000];
    char temp_path[1000];
    // char rev_temp_path[1000];

    char command[10]="READ";
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

    memset(&temp_path, 0, sizeof(temp_path));
    strcpy(temp_path,path);

    if (strcmp(path, "/") == 0){ 
        sprintf(fpath, "%s", dirpath); 
    } else { 
        sprintf(temp_path,"%s",path); 
        sprintf(fpath, "%s%s",dirpath,temp_path); 
    } 

    printf("read : %s",fpath); 

    int res = 0;
    int fd = 0 ;  

    (void) fi;

    fd = open(fpath, O_RDONLY);
    if (fd == -1)
    return -errno;  

    res = pread(fd, buf, size, offset);
    if (res == -1)

    res = -errno;  

    close(fd);

return res;
}


static int xmp_write(const char *path, const char *buf, size_t size,off_t offset, struct fuse_file_info *fi)
{
	int fd;
	int res;

	char fpath[1000];
	char temp_path[1000];
    // char rev_temp_path[1000];

    char command[10]="WRITE";
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

    if (strcmp(path, "/") == 0){ 
        sprintf(fpath, "%s", dirpath); 
    } else { 
        sprintf(temp_path,"%s",path); 
        sprintf(fpath, "%s%s",dirpath,temp_path); 
    } 

	(void) fi;

	fd = open(fpath, O_WRONLY);
	if (fd == -1)
		return -errno;

	res = pwrite(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static int xmp_rename(const char *from, const char *to)
{
    int res;
    
	char s_from[1000];
	char s_to[1000];
    // char rev_s_from[1000];
    // char rev_s_to[1000];

    char gantinama[1000];
    char namalama[1000];
    char temp[1000];

    char command[10]="RENAME";
    char level[10]="INFO";
    char waktu[1000];
    char satu[1000];
    char dua[1000];
    char tiga[1000];

    // char fpath[1000];

    time_t t = time(NULL); 
    struct tm tm = *localtime(&t);

    sprintf(waktu, "%02d%02d%02d-%02d:%02d:%02d", (tm.tm_year + 1900) % 100, 
    tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec); 

    sprintf(satu, "%s::%s", level, waktu); 
    sprintf(dua, "%s::%s", satu, command);
    sprintf(tiga, "%s::%s::%s\n", dua, from, to);

    FILE *fp;
    fp = fopen(logpath, "a");
    fputs(tiga, fp);
    fclose(fp);

    strcpy(s_from,from);
    strcpy(s_to,to);

    if(strncmp("/encv1_", s_to, 7) == 0){
        fp = fopen(enkripsilog, "a");
        fputs(s_to, fp);
        fputs("\n", fp);
        fclose(fp);
    }
    else if(strncmp("/encv2_", s_to, 7) == 0){
        fp = fopen(enkripsilog, "a");
        fputs(s_to, fp);
        fputs("\n", fp);
        fclose(fp);
    }

	char awal[1000];
	char ganti[1000];

	strcpy(awal,dirpath);
    strcat(awal,s_from);
	strcpy(ganti,dirpath);
    strcat(ganti,s_to);

	res = rename(awal,ganti);
	if (res == -1)
		return -errno;

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

    if(strncmp("/encv2_", s_from, 7) == 0){
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

    return 0;
}

//belum
static int xmp_mkdir(const char *path, mode_t mode)
{
    FILE *fp;
    int res;
    char fpath[1000];
    char temp_path[1000];

    char command[10]="MKDIR";
    char level[10]="INFO";
    char waktu[1000];
    char satu[1000];
    char dua[1000];
    char tiga[1000];

    char path_enkripsi[1000];
    char gantinama[1000];
    char namalama[1000];
    char temp[1000];

    time_t t = time(NULL); 
    struct tm tm = *localtime(&t);

    sprintf(waktu, "%02d%02d%02d-%02d:%02d:%02d", (tm.tm_year + 1900) % 100, 
    tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec); 

    sprintf(satu, "%s::%s", level, waktu); 
    sprintf(dua, "%s::%s", satu, command);
    sprintf(tiga, "%s::%s\n", dua, path);

    fp = fopen(logpath, "a");
    fputs(tiga, fp);
    fclose(fp);

    memset(&temp_path, 0, sizeof(temp_path));
    strcpy(temp_path,path);
    // sprintf(temp_path,"%s",path);
    // dekripsi(temp_path);

    // if(strncmp("encv1_", temp_path, 6) == 0){
    //     fp = fopen("log.txt", "a");
    //     fputs(temp_path, fp);
    //     fclose(fp);
    // }

    if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}

	else sprintf(fpath,"%s%s",dirpath,temp_path);

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


    res = mkdir(fpath, mode);
    if(res == -1)
        return -errno;

        if(strncmp("/encv1_", temp_path, 7) == 0){
    
    DIR *dp;
    struct dirent *de;  

    dp = opendir(fpath);

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

                        strcpy(temp,de->d_name);
                        enkripsi(temp);

                        sprintf(path_enkripsi,"%s%s",dirpath,temp_path); 

                        sprintf(namalama,"%s/%s", path_enkripsi,de->d_name);
                        sprintf(gantinama,"%s/%s", path_enkripsi,temp);
                        rename(namalama, gantinama);
                        printf("%s %s\n", namalama, gantinama);
                }
            }

        closedir(dp);
    }

    return 0;
}  

//belum
static int xmp_rmdir(const char *path)
{
	int res;
	char fpath[1000];
	char temp_path[1000];

    char command[10]="RMDIR";
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
	
    memset(&temp_path, 0, sizeof(temp_path));
    // strcpy(temp_path,path);
    sprintf(temp_path,"%s",path);
	// enkripsi(temp_path);

	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,temp_path);
	res = rmdir(fpath);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_create(const char* path, mode_t mode, struct fuse_file_info* fi)
{

    (void) fi;

    int res;
	char fpath[1000];
	char temp_path[1000];
    // char rev_temp_path[1000];

    char command[10]="CREATE";
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

    memset(&temp_path, 0, sizeof(temp_path));
    // strcpy(temp_path,path);
    sprintf(temp_path,"%s",path);

	// get_filename_ext(temp_path);
    // memmove(rev_temp_path, temp_path, strlen(temp_path)-strlen(ekstensi));
    // dekripsi(rev_temp_path);
    // strcat(rev_temp_path, ekstensi);

	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,temp_path);

    res = creat(fpath, mode);
    if(res == -1)
	return -errno;

    close(res);

    return 0;
}

static int xmp_unlink(const char *path)
{
	int res;
	char fpath[1000];
	char temp_path[1000];

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
	
    memset(&temp_path, 0, sizeof(temp_path));
    // strcpy(temp_path,path);
    sprintf(temp_path,"%s",path);
    // get_filename_ext(temp_path);
    //strtok(temp_path, ekstensi); ganti oi bahaya
    // enkripsi(temp_path);
    // strcat(temp_path, ekstensi);

	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,temp_path);
	res = unlink(fpath);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_truncate(const char *path, off_t size)
{
	char fpath[1000];
	char temp_path[1000];
	int res = 0;

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

	memset(&temp_path, 0, sizeof(temp_path));
	strcpy(temp_path, path);
    // sprintf(temp_path,"%s",path);
    // get_filename_ext(temp_path);
    // strtok(temp_path, ekstensi); ganti oi bahaya
    // enkripsi(temp_path);
    // strcat(temp_path, ekstensi);

	sprintf(fpath, "%s%s", dirpath, temp_path);
	res = truncate(fpath, size);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_utimens(const char *path, const struct timespec ts[2])
{
	int res;
	struct timeval tv[2];

    char fpath[1000];
	char temp_path[1000];

    char command[10]="UTIMENS";
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

	tv[0].tv_sec = ts[0].tv_sec;
	tv[0].tv_usec = ts[0].tv_nsec / 1000;
	tv[1].tv_sec = ts[1].tv_sec;
	tv[1].tv_usec = ts[1].tv_nsec / 1000;

	strcpy(temp_path,path);

	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,temp_path);

	res = utimes(fpath, tv);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_chmod(const char *path, mode_t mode)
{
	int res;

    char fpath[1000];
	char temp_path[1000];
    char s_mode[1000];

    char command[10]="CHMOD";
    char level[10]="INFO";
    char waktu[1000];
    char satu[1000];
    char dua[1000];
    char tiga[1000];

    sprintf(s_mode, "%u", mode);

    time_t t = time(NULL); 
    struct tm tm = *localtime(&t);

    sprintf(waktu, "%02d%02d%02d-%02d:%02d:%02d", (tm.tm_year + 1900) % 100, 
    tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec); 

    sprintf(satu, "%s::%s", level, waktu); 
    sprintf(dua, "%s::%s", satu, command);
    sprintf(tiga, "%s::%s::%s\n", dua, path, s_mode);

    FILE *fp;
    fp = fopen(logpath, "a");
    fputs(tiga, fp);
    fclose(fp);

    strcpy(temp_path,path);

	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,temp_path);

	res = chmod(fpath, mode);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_chown(const char *path, uid_t uid, gid_t gid)
{
	int res;

    char fpath[1000];
	char temp_path[1000];

    char command[10]="CHOWN";
    char level[10]="INFO";
    char waktu[1000];
    char satu[1000];
    char dua[1000];
    char tiga[1000];
    char s_uid[10];

    sprintf(s_uid, "%u", uid);

    time_t t = time(NULL); 
    struct tm tm = *localtime(&t);

    sprintf(waktu, "%02d%02d%02d-%02d:%02d:%02d", (tm.tm_year + 1900) % 100, 
    tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec); 

    sprintf(satu, "%s::%s", level, waktu); 
    sprintf(dua, "%s::%s", satu, command);
    sprintf(tiga, "%s::%s::%s\n", dua, path, s_uid);

    FILE *fp;
    fp = fopen(logpath, "a");
    fputs(tiga, fp);
    fclose(fp);

    strcpy(temp_path,path);

	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,temp_path);

	res = lchown(fpath, uid, gid);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_open(const char *path, struct fuse_file_info *fi)
{
	int res;

    char command[10]="OPEN";
    char level[10]="INFO";
    char waktu[1000];
    char satu[1000];
    char dua[1000];
    char tiga[1000];

    char fpath[1000];
	char temp_path[1000];

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

    memset(&temp_path, 0, sizeof(temp_path));
	strcpy(temp_path, path);
    sprintf(fpath, "%s%s", dirpath, temp_path);

	res = open(fpath, fi->flags);
	if (res == -1)
		return -errno;

	close(res);
	return 0;
}

static int xmp_mknod(const char *path, mode_t mode, dev_t rdev)
{
	int res;

    char fpath[1000];
	char temp_path[1000];

    char gantinama[1000];
    char namalama[1000];
    char temp[1000];

    char command[10]="MKNOD";
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

	memset(&temp_path, 0, sizeof(temp_path));
	strcpy(temp_path, path);
    sprintf(fpath, "%s%s", dirpath, temp_path);
	
	if (S_ISREG(mode)) {
		res = open(fpath, O_CREAT | O_EXCL | O_WRONLY, mode);
		if (res >= 0)
			res = close(res);
	} else if (S_ISFIFO(mode))
		res = mkfifo(fpath, mode);
	else
		res = mknod(fpath, mode, rdev);
	if (res == -1)
		return -errno;

    DIR *dp;
    struct dirent *de;  

    if(strncmp("/encv1_", temp_path, 7) == 0){
        dp = opendir(fpath);

        if (dp == NULL)
        return -errno;

            while ((de = readdir(dp)) != NULL && strncmp("/encv1_", temp_path, 7) == 0) {

                struct stat st;
                memset(&st, 0, sizeof(st));

                st.st_ino = de->d_ino;
                st.st_mode = de->d_type << 12;

                if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
                {       
                        memset(&temp, 0, sizeof(temp));

                        get_filename_ext(de->d_name);
                        memmove(temp, de->d_name, strlen(de->d_name)-strlen(ekstensi));
                        enkripsi(temp);
                        strcat(temp, ekstensi);

                        sprintf(namalama,"%s/%s", fpath,de->d_name);
                        sprintf(gantinama,"%s/%s", fpath,temp);
                        rename(namalama, gantinama);
                        printf("%s %s\n", namalama, gantinama);
                }
            }

        closedir(dp);
    }

	return 0;
}

static int xmp_statfs(const char *path, struct statvfs *stbuf)
{
	int res;

    char fpath[1000];
	char temp_path[1000];

    char command[10]="STATFS";
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

	memset(&temp_path, 0, sizeof(temp_path));
	strcpy(temp_path, path);
    sprintf(fpath, "%s%s", dirpath, temp_path);

	res = statvfs(fpath, stbuf);
	if (res == -1)
		return -errno;

	return 0;
}

//belum
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
    // .fsync      = xmp_fsync,
};

int  main(int  argc, char *argv[])
{
    umask(0);
    return fuse_main(argc, argv, &xmp_oper, NULL);
}
