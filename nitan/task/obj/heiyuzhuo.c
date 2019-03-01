#include <ansi.h>
inherit TASK;
void create()
{
    set_name(BLU"黑玉鐲"NOR, ({ "yu zhuo", "zhuo" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "支");
            set("material", "steel");
            set("long", "這是一支黑玉鐲，相傳是大俠楊過送給郭襄的生日禮物。\n");
          }
    set("owner", "郭芙");
    setup();
}
