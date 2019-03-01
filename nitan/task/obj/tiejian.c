#include <ansi.h>
inherit TASK;
void create()
{
    set_name(WHT"鐵劍"NOR, ({ "tie jian", "sword" }) );
    set_weight(100);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "柄");
            set("material", "iron");
            set("long", "這是一柄非常鋒利的鐵劍。\n");
          }
    set("owner", "獨臂神尼");
    setup();
}
