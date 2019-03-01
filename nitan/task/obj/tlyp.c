#include <ansi.h>
inherit TASK;
void create()
{
    set_name(YEL"統領腰牌"NOR, ({ "tongling yaopai", "yao pai", "pai"}));
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "面");
            set("material", "iron");
            set("long", "這是一面滿清帝國的御林軍統領腰牌。\n");
          }
    set("owner", "多隆");
    setup();
}
