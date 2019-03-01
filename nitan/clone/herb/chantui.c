#include "herb.h"

void create()
{
        set_name(YEL "蟬蛻" NOR, ({"chan tui"}));
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("long", "蟬蛻：蟬由幼蟲蛻變至成蟲所遺的殼，有去風濕的效果。\n");
                set("base_unit", "個");
                set("base_value", 4000);
                set("base_weight", 60);
                set("cure_s", 3);
                set("cure_d", 0);
                set("cure_n", 0);        
        }
        setup();
}