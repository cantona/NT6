#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "靈穴再生丹" NOR, ({"zaisheng dan", "zaisheng", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("value", 100000);
                set("only_do_effect", 1);
                set("long", HIY "一顆紫色的藥丸。恢復全部內力。\n" NOR);
        }
        setup();
}

int do_effect(object me)
{
        mapping my;
        int nl, mn;

        if (time() - me->query_temp("last_eat") < 2)
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        me->set_temp("last_eat", time());

        message_vision(HIW "$N吃下一顆靈穴再生丹，感到內力有所補充。\n" NOR, me);

        me->set("neili", me->query("max_neili"));

        destruct(this_object());

        return 1;
}

int query_autoload()
{
        return 1;
}
