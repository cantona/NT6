#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(WHT "虎骨" NOR, ({"hu gu", "hu", "gu"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", WHT "\n一根新鮮的虎骨，從神獸白虎的身體裡取出，可以入藥。\n" NOR);
                set("value", 6000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        mapping my;

        my = me->query_entire_dbase();

        if( me->is_busy() )
                return notify_fail("急什麼，小心別噎著了。\n");

        message_vision(HIR "$N" HIR "將虎骨嚼爛吞下，只感一股真氣直沖頂門。\n" NOR, me);
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