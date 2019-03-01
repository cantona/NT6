// guiyuandan.c
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW"歸元丹"NOR, ({"guiyuan dan", "dan"}));
        if (clonep())
        {
                set_default_object(__FILE__);
        }
        else {
                set("unit", "粒");
                set("long", "歸元丹是峨嵋弟子一身精血所化，珍貴無比，有生死
肉骨之功，為武林至寶。\n");
                set("value", 0);
        }
        set("pour_type", "1");
        seteuid(query("id", this_player()));
        setup();
}

int init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

int do_eat(string arg)
{
        object me = this_player();

        if( !query("dietime", me) || time()-query("dietime", me)>480 )
                return notify_fail("你現在不宜吃歸元丹了。\n");
        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if (!present(this_object(), this_player()))
                return notify_fail("你要吃什麼？\n");
        if( me->query_skill("linji-zhuang", 1) < 180 )
                return notify_fail("你未曾修成幽冥莊，恐怕吃不得此丹。\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");
        message_vision("$N吃下一粒" + name() + "。\n", me);
        log_file("eat_dan", sprintf("[%s] %s eat guiyuan \n", ctime(time()), geteuid(me)));
        delete("dietime", me);
        me->reincarnate();
        addn("combat_exp",query("combat_exp",  me)/49, me);
//        me->add("potential", 50);
        addn("max_neili", 2, me);
        me->skillreincarnate();
        me->start_busy(2);
        destruct(this_object());
        return 1;
}
