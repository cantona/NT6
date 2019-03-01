#include <ansi.h>
inherit TASK;
void create()
{
    set_name(BLU"武當錄"NOR, ({ "wudanglu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "長勤武當錄。\n");
          } 
    set("owner", "宋青書");
        setup();
}  
