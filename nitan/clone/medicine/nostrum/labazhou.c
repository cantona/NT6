// labazou.c 臘八粥

#include <ansi.h>
inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(GRN"臘八粥"NOR, ({"laba zhou", "zhou", "laba"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "碗");
                set("long","這是一碗熱粥，其中蒸氣上冒，兀自有一個個氣泡從粥底沖將上來，一碗粥盡作深綠之色，看上去說不出的詭異。聞著藥氣刺鼻，其毒可知。\n");
                set("value", 50000);
        }
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

        if ( (int)me->query_condition("labazhou_drug" ) > 0 )
        {
                addn("max_neili", -100, me);
                message_vision(HIR "$N又喝下一碗"GRN"臘八粥"HIR"，只覺得肝腸寸斷，五臟欲裂，原來喝得太急太多，藥效適得其反！\n" NOR, me);
        }
                        
        else if ( neili_limit <= force_limit  )
        {
                addn("max_neili", 50, me);
                addn("neili", 50, me);
                message_vision(HIY "$N喝下一碗"GRN"臘八粥"HIY"，頓然間只覺一股浩盪無比的真氣直沖頂門...\n" NOR, this_player());
                me->apply_condition("labazhou_drug", 500);
        }
        me->start_busy(50);
        destruct(this_object());
        return 1;
}
