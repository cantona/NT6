// ganmao.c 感冒藥

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIW"特效感冒藥"NOR, ({"texiao yao", "ganmao yao","yao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("long", "這是一包特效感冒藥，用的是平一指的獨家配方。\n"+
                "對各種感冒病症都有顯著療效。\n");
                set("value", 20000);
        }
        setup();
}

int do_eat(string arg)
{
        object me = this_player();
        if (!id(arg))
                return 0;
        if (me->is_busy() )
                return notify_fail("別急，慢慢來。\n");
        if (! me->query_condition("ill_kesou") && 
        ! me->query_condition("ill_shanghan") &&
        ! me->query_condition("ill_fashao") &&
        ! me->query_condition("ill_dongshang") &&
        ! me->query_condition("ill_zhongshu") )
        {
                write("你現在又沒有感冒，別亂吃藥。\n");
                return 1;
        } 
        else 
        {
                me->clear_condition("ill_kesou");
                me->clear_condition("ill_shanghan");
                me->clear_condition("ill_fashao");
                me->clear_condition("ill_dongshang");
                me->clear_condition("ill_zhongshu");
                message_vision(HIY"$N服下一包特效感冒藥，感冒症狀緩解了許多。\n"NOR, me);
                me->start_busy(3);
                destruct(this_object());
                return 1;
        }
}