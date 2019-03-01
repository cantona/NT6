#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIY"黃馬甲"NOR, ({ "huang majia", "majia" }) );
    set_weight(10);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "件");
            set("material", "cloth");
            set("long", "這是一件皇上御賜給鰲拜的黃馬甲。\n");
          }
    set("owner", "鰲拜");
    setup();
}
