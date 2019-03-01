#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "分解卷軸" NOR, ({ "resolve scroll", "scroll" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "分解卷軸用來分解動態裝備中各種魔法屬性元素。\n" NOR);
                set("unit", "張");
                set("value", 500000);
                set("no_sell", 1);
        }
        setup();
}

