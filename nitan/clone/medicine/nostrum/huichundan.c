// huichundan.c 回春丹
// Last Modified by Winder on Mar. 5 2001

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIG"回春丹"NOR, ({"huichun dan", "dan"}));
        set("unit", "粒");
        set("vegetable", 0);
        set("nostrum", 0);
        set("level", 300);
        set("long", "這是一粒清綠剔透的回春丹。\n");
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        object me=this_player();

        if (!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if (!id(arg)) return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢喝，小心別嗆著了。\n");

        if( query("age", me) <= 39 )
        {
                message_vision("$N沒必要吃回春丹。\n",me);
        }
        else
        {
                addn("mud_age", -86400, me);
                addn("vegetable/huichun", 1, me);
                delete("last_slp", me);
                delete("jingzuo_time", me);
                message_vision("$N吃下一粒回春丹，伸了個懶腰，覺得身子骨靈便了許多。\n",me);
                destruct(this_object());
        }
        return 1;
}