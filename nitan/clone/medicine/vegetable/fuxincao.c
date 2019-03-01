// cao.c
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}
void create()
{
        set_name(HIG"腐心草"NOR, ({"fuxin cao","cao"}));
        set("unit", "根");
        set("long", "這是一朵無根小草，長得很小，卻給人一種欣欣向榮的感覺。\n");
        set("pour_type", "1");
        setup();
}
int do_eat(string arg)
{
        int force_limit, neili_limit;
        object me = this_player();

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");

        message_vision(HIG "生吃腐心草還不如熬了粥再喝吧。\n" NOR, me);
        force_limit = me->query_skill("force",1)*10;
        neili_limit=query("max_neili", me);
        if ( neili_limit <= force_limit )
        {
                addn("max_neili", 5, me);
                me->start_busy(20);
        }
        message_vision(HIG "$N吃下一株腐心草，頓然間有點肚子疼...\n" NOR, me);
        destruct(this_object());
        return 1;
}