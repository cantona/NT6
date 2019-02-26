//hua.c 百香花
//
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIG"百香花"NOR, ({"hua", "baixiang"}));
        set("unit", "朵");
        set("long", "這是一朵鮮豔的花，花香濃郁異常。\n");
        setup();
}

int do_eat(string arg)
{
        int force_limit, neili_limit, force_skill, add_skill, improve;
        object me = this_player();
        force_limit = me->query_skill("force")*10;
        neili_limit=query("max_neili", me);
        force_skill = me->query_skill("force", 1);

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");
        if ( neili_limit <= force_limit  )
                addn("max_neili", 1, me);
        me->unconcious();
        destruct(this_object());
        return 1;
}