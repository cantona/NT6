// xuming8wan.c

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW"續命八丸"NOR, ({"xuming bawan", "bawan", "8wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "粒");
                set("vegetable", 86);
                set("nostrum", 121);
                set("no_sell",1);
                set("level", 160);
                set("long","這是花了一十二年時光，採集千年人參、伏苓、靈芝、鹿茸、首烏、靈脂、熊膽、三七、麝香種種珍貴之極的藥物，九蒸九曬，制成八顆起死回生的“續命八丸”。有的極臭，有的極苦，有的入口如刀割，有的辛辣如火炙。只要吞服了這“續命八丸”，不論多大的內傷外傷，定然起死回生。\n");
                set("value", 0);
        }
        set("pour_type", "1");
        setup();
}

int init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
        remove_call_out("destwan");
        call_out("destwan", 60);
}

int do_eat(string arg)
{
        object me = this_player();

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");

        if( !wizardp(me) &&
                (!query("dietime", me) || time()-query("dietime", me)>600) )
        {
                write("你現在不宜吃續命八丸了。\n");
                return 1;
        }
        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");
        message_vision("$N吃下一粒" + name() + "。\n", me);
        log_file("eat_dan", sprintf("[%s] %s eat xuming8wan \n", ctime(time()), geteuid(me)));
        delete("dietime", me);
        me->reincarnate();
        addn("combat_exp", (query("combat_exp", me)/49), me);
        addn("potential",query("potential",  me)-query("learned_points", me), me);
        //me->add("max_neili", 2);
//        me->set("shen", 0);
//        me->set("score", 0);
//        me->set("meili", 0);
//        me->set("weiwang", 0);
        if( query("score", me)<5000)set("score", 0, me);
        else addn("score", -5000, me);
        me->skillreincarnate();
        me->start_busy(10);
        destruct(this_object());
        return 1;
}

void destwan()
{
        message_vision("$N慢慢幹涸化成灰，一會就飄落地上消失了。\n",this_object());
        destruct(this_object());
}
