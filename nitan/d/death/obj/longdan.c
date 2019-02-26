#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIR "龍膽" NOR, ({"long dan", "dan", "long"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", HIR "\n一隻血淋淋的新鮮龍膽，從神獸青龍的身體裏取出，可以入藥。\n" NOR);
                set("value", 8000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        mapping my;

        my = me->query_entire_dbase();

        if( me->is_busy() )
                return notify_fail("急什麼，小心別噎着了。\n");

        message_vision(HIR "$N" HIR "生吞下一隻血淋淋的龍膽，只感一股真氣從體內澎湃而出。\n" NOR, me);
        set("jingli",query("max_jingli",  me), me);
        set("neili",query("max_neili",  me), me);
        set("jing",query("max_jing",  me), me);
        set("qi",query("max_qi",  me), me);
        set("eff_jing",query("max_jing",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        me->improve_skill("force", 200000000);

        me->start_busy(6);
        destruct(this_object());
        return 1;
}