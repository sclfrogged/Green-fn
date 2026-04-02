#include "data.h"
#include <stdio.h>

static void pechat_menyu(void) {
    printf("1.Pokazat vse kvartiry\n");
    printf("2.Dobavit kvartiru v konec\n");
    printf("3.Zapolnit N kvartir\n");
    printf("4.Redaktirovat kvartiru\n");
    printf("5.Poisk\n");
    printf("6.Udalit poslednyuyu\n");
    printf("7.Udalit po indexu\n");
    printf("8.Vstavit na poziciu\n");
    printf("9.Sortirovat\n");
    printf("10.Rasshirit massiv\n");
    printf("11.Info o pamyati\n");
    printf("12.Ochistit spisok\n");
    printf("13.Sohranit v fayl\n");
    printf("14.Zagruzit iz fayla\n");
    printf("0.Vyhod (s avtosohraneniem)\n");
    printf("Vash vybor: ");
}

int main(void) {
    MassivKvartir m;
    massiv_init(&m);

    /* Avtomaticheskaya zagruzka pri zapuske */
    zagruzit_iz_fayla(&m, IMY_FAYLA);

    int vybor;
    do {
        pechat_menyu();
        vybor = vvod_int("");

        switch (vybor) {
            case 1:  vivesti_vse(&m);break;
            case 2:  menyu_dobavit_v_konec(&m);break;
            case 3:  menyu_zapolnit_n(&m);break;
            case 4:  menyu_redaktirovat(&m);break;
            case 5:  menyu_poisk(&m);break;
            case 6:  menyu_udalit_posledniy(&m);break;
            case 7:  menyu_udalit_po_indexu(&m);break;
            case 8:  menyu_vstavit(&m);break;
            case 9:  menyu_sortirovka(&m);break;
            case 10: menyu_rasshirit(&m);break;
            case 11: menyu_info_pamyati(&m);break;
            case 12: menyu_ochistit(&m);break;
            case 13: menyu_sohranit(&m);break;
            case 14: menyu_zagruzit(&m);break;
            case 0:
                printf("\nAvtosohranenie pered vyhodom...\n");
                sohranit_v_fayl(&m, IMY_FAYLA);
                massiv_ochistit(&m);
                printf("Do svidaniya!\n");
                break;
            default:
                printf("Nevernyy vybor. Povtorite.\n");
        }

    } while (vybor != 0);

    return 0;
}
