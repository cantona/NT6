#include <ansi.h>

inherit ITEM;
void dest();



void init()
{
       remove_call_out("dest");
       call_out("dest", 100);
}

void create()
{
        set_name("用過的百花腹蛇膏", ({"usedgao", "used gao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", "這是一張用過的百花腹蛇膏。\n");
                set("value", 1000);
        }
        setup();
}


void dest()
{
    destruct(this_object());
}
