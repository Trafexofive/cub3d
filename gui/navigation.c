
#include "../gui/gui_engine.h"



void scroll_down(t_elem *element, t_menu *menu)
{
    element->selected = false;
    element->next->selected = true;
    menu->selected = element->next;
    

}

void scroll_up(t_elem *element)
{
    element->selected = false;
    element->prev->selected = true;
    menu->selected = element->prev;

}
