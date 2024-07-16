
#include "../gui/gui_engine.h"



void scroll_down(t_menu *menu)
{
    menu->selected = menu->selected->next;

}

void scroll_up(t_menu *menu)
{
    menu->selected = menu->selected->prev;

}
