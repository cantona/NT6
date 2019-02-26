// redbag.c 紅包

inherit ITEM;
#include <ansi.h>;
void create()
{
        set_name(HIR"紅包"NOR, ({ "redbag", "bag" }));
        set_weight(500);
        set_max_encumbrance(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "一個裝着壓歲錢的紅包，鼓鼓囊囊地不知包着什麼好東西。\n\n    "HIR"過年好！！\n\n"NOR); 
                set("value", 0);
        }
}

int is_container() { return 1; }

