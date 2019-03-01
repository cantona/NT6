#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIR"刺殺令" NOR, ({ "csl" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "塊");
            set("material", "stone");
            set("long", "一塊血跡斑斑的令牌。\n");
    }
    set("owner", "全冠清");
    setup();
}
