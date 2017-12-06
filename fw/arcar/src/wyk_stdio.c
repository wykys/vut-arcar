#include "wyk_stdio.h"

char nible2hex(uint8_t nible)
{
    if (nible < 10)
        return '0' + nible;
    else
        return 'A' + nible - 10;
}

// vytiskne číslo int 2B
void print_hex(uint16_t cislo)
{
    uint16_t i;
    uint16_t nible;

    for (i=0; i < 4; i++)
    {
        nible = (uint8_t) ((cislo >> 12) & 0x000F);
        cislo <<= 4;
        putc(nible2hex(nible));
    }
}

// vytiskne číslo int 2B
void print_int(int cislo, char znaminko, char nula, int pocet_mist)
{
    int poc_cislo = cislo;
    int8_t i, len = 16, state = 1;
    char buf[16];

    // pokud máme vypsat před číslo znamínko
    if (znaminko)
    {
        putc((cislo >= 0) ? '+' : '-');
    }

    // pokud je vypnutá predikce nul
    if (nula)
        state = 0;


    // když je zadána délka čísla
    if (pocet_mist >= 0)
        len = pocet_mist;

    // absolutní hodnota čísla
    cislo = (cislo >= 0) ? cislo : -1 * cislo;

    // převod čísla na řětězec
    for (i=0; i < len; i++)
    {
        buf[i] = '0' + cislo % 10;
        cislo /= 10;
    }
    // výpis řetězce
    for (i--; i >= 0; i--)
    {
        if (buf[i] == '0' && state)
        {
            if (pocet_mist != -1 && (poc_cislo || (i+1) != len))
            {
                putc(' ');
            }
        }
        else
        {
            state = 0;
            putc(buf[i]);
        }

    }
    if (state)
    {
        putc('0');
    }
}

// vytiskne double
void print_double(double cislo, char znaminko, char nula, int mista_pred_carkou, int mista_za_carkou)
{
    int i, cela, desetinna;
    char znam = '+';

    if (mista_za_carkou == -1)
        mista_za_carkou = 3;

    if (cislo < 0)
    {
        cislo *= -1;
        znam = '-';
    }

    cela = (int) cislo;
    cislo -= cela;

    for (i=0; i < mista_za_carkou; i++)
        cislo *= 10;

    desetinna = (int) cislo;
    cela = (znam == '-') ? -1 * cela : cela;

    print_int(cela, znaminko, nula, mista_pred_carkou);
    if (mista_za_carkou)
    {
        putc(',');
        print_int(desetinna, '\0', '0', mista_za_carkou);
    }
}

// printf funkce
void printf(char str[], ...)
{
    uint8_t i, j;
    char *str_p;
    int tmp_int;

    char znaminko = '\0';
    char nula = '\0';
    char desetina_carka = '\0';
    int mista_pred_carkou = -1;
    int mista_za_carkou = -1;



     __gnuc_va_list ap;
     va_start(ap, str);



    for (i=0; str[i] != '\0'; i++)
    {
        if (str[i] == '%')
        {
            // pokud jde o znak %
            if (str[i+1] == '%')
            {
                i++;
                putc('%');
            }
            // když jde o proměnnou
            else
            {
                // zjistáme jakého typu jsou data
                for (j=i+1;                         \
                    str[j] != 'c' &&                \
                    str[j] != 'H' &&                \
                    str[j] != 'd' &&                \
                    str[j] != 'f' &&                \
                    str[j] != 's';                  \
                    j++)
                {
                    if (str[j] == '+' || str[j] == '-')
                    {
                        znaminko = '+';
                    }
                    else if (str[j] == '.')
                    {
                        desetina_carka = ',';
                    }
                    else if (str[j] == '0')
                    {
                        if (desetina_carka == '\0')
                        {
                            if (nula == '0')
                                mista_pred_carkou *= 10;
                            else
                                nula = '0';
                        }
                        else
                        {
                            mista_za_carkou = 0;
                        }

                    }
                    else if (str[j] >= '1' && str[j] <= '9')
                    {
                        if (desetina_carka == ',')
                        {
                            if (mista_za_carkou == -1)
                                mista_za_carkou = 0;

                            mista_za_carkou *= 10;
                            mista_za_carkou += str[j] - '0';
                        }
                        else
                        {
                            if (mista_pred_carkou == -1)
                                mista_pred_carkou = 0;

                            mista_pred_carkou *= 10;
                            mista_pred_carkou += str[j] - '0';
                        }
                    }
                }

                // posuneme index procházení pole
                i = j;

                // podle typu s nimi naložíme
                if (str[j] == 'c')
                {
                    putc(va_arg(ap, int));
                }
                else if (str[j] == 'H')
                {
                    print_hex(va_arg(ap, uint16_t));
                }
                else if (str[j] == 'd')
                {
                    tmp_int = va_arg(ap, int);
                    print_int(tmp_int, znaminko, nula, mista_pred_carkou);
                }
                else if (str[j] == 'f')
                {
                    print_double(va_arg(ap, double), znaminko, nula, mista_pred_carkou, mista_za_carkou);
                }
                else if (str[j] == 's')
                {
                    str_p = va_arg(ap, char *);
                    for (j=0; *(str_p + j) != '\0'; j++)
                        putc(*(str_p + j));
                }

                // vynulovní formátovacích proměnných
                znaminko = '\0';
                nula = '\0';
                desetina_carka = '\0';
                mista_pred_carkou = -1;
                mista_za_carkou = -1;
            }
        }
        else
        {
            putc(str[i]);
        }
    }
    va_end(ap);
}
