#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIC"醉仙樓菜譜" NOR, ({ "cai pu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "本");
            set("material", "stone");
            set("long", "一本醉仙樓菜譜\n");
          }
    set("owner", "冼老闆");
    setup();
}
