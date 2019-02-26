#include <ansi.h>
inherit TASK;
void create()
{
    set_name( WHT "國姓爺遺詔" NOR, ({ "yi zhao" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "張");
            set("material", "paper");
            set("long", "果姓爺臨死前寫下的遺詔。\n");
          }
    set("owner", "鄭克爽");
    setup();
}
