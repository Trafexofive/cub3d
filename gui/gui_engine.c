
#include "gui_engine.h"
#include "../inc/struct.h"
#include "../inc/macros.h"
#include "../inc/draw.h"


void    element_init(t_elem *element)
{
    element->async_priority = 0;
    element->selected = NIL;
    element->visibility = NIL;
    element->dimensions.width = DEFAULT_WIDTH;
    element->dimensions.height = DEFAULT_HEIGHT;
    element->position.x = 10;
    element->position.y = 10;
    element->next = NULL;
}


bool render_ui(t_elem *elements, t_mlx *mlx)
{

    clear_window(mlx);
    instantiate_element()


}

