inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR"朱睛"HIW"冰"HIR"蟾"NOR, ({"chan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("value", 40000);
                set("long", "這是一千年難得一見的朱睛冰蟾，通體透明，惟眼呈赤"
                            "色，能解百毒。\n");
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision(HIR "$N" HIG "服下一隻朱睛冰蟾，只覺一股丹田一片火熱，"
                       "內息運轉無比順暢！\n" NOR, me);
        set_temp("nopoison", 3);
        destruct(this_object());
        return 1;
}
