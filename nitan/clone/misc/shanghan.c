// shanghan.c 傷寒愁

inherit ITEM;

#include <ansi.h>

void create()
{
        set_name(HIY"傷寒愁"NOR, ({"shanghan chou", "shanghanchou"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("long", "這是一包專治傷寒的藥，靈驗無比。\n");
                set("value", 1000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        if (!me->query_condition("ill_shanghan"))
        {
                write("你現在又沒有得傷寒，別亂吃藥。\n");
                return 1;
        } else {
                me->clear_condition("ill_shanghan");
                message_vision("$N吃下一包傷寒愁，氣色看起來好多了。\n", me);
                me->start_busy(2);
                destruct(this_object());
                return 1;
        }
}
