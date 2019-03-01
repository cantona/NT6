// huochan.c
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
        remove_call_out("destguo");
        call_out("destguo", 10);
}
void destguo()
{
        message_vision("$N全身慢慢變黑，一會就歪頭死掉了。\n",this_object());
        destruct(this_object());
}

void create()
{
        set_name(HIR"火蟾"NOR, ({"huo chan", "chan"}));
        set("unit", "只");
        set("long", "這是一只生長在昆侖山頂的火蟾，兩眼投射出奪目的紅光。\n");
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        int force_limit, neili_limit;
        object me = this_player();
        force_limit = me->query_skill("force")*10;
        neili_limit=query("max_neili", me);
        
        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");
        if( neili_limit <= force_limit)addn("max_neili", 5, me);
        set("neili",query("max_neili",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("eff_qi",  me), me);
        message_vision(HIY "$N吃下一只火蟾，只覺一股熱線自嚥而下，沿督脈直沖玄關，一股真力源源不絕匯入丹田。\n"NOR,me);
        destruct(this_object());
        return 1;
}