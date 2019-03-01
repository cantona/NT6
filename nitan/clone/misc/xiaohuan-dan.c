// xiaohuan-dan.c 小還丹

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("小還丹", ({"xiaohuan dan", "xiaohuan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "這是一顆瑩白溜圓的小還丹。此丹乃少林奇"
                            "藥，助長內力，靈效無比。\n");
                set("value", 10000);
                set("only_do_effect", 1);
        }

        setup();
}

int do_effect(object me)
{
        if( query("neili", me) >= query("max_neili", me)*2-200 )
                return notify_fail("你現在沒必要吃小還丹。\n");

        me->start_busy(2);

        addn("neili", 200, me);
        message_vision(HIY "$N" HIY "吃下一顆小還丹，只覺得身輕如燕，"
                       "四肢百骸真氣充盈無比，幾欲奔騰而出！\n" NOR, me);

        destruct(this_object());
        return 1;
}
