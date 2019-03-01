#include <ansi.h>
inherit TASK;
void create()
{
    set_name(MAG"祖傳秘方"NOR, ({ "zuchuan mifang" }) );
    set_weight(10);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "張");
            set("material", "paper");
            set("long", "一張非常陳舊的黃紙片。\n");
          }
    set("owner", "姚春");
    setup();
}
