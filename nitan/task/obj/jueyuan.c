#include <ansi.h>
inherit TASK;
void create()
{
    set_name(WHT"鐵水桶"NOR, ({ "tie shuitong", "shui tong" }) );
    set_weight(100);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "個");
            set("material", "iron");
            set("long", "一個普通的鐵水桶，桶身刻著“少林寺”的字樣，看來是少林寺之物。\n");
          }
    set("owner", "覺遠");
    setup();
}
