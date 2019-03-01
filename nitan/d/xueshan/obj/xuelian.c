// medicine: xuelian.c
// Jay 3/18/96

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("雪蓮", ({"xuelian", "lian", "lotus"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("long", "這是一支只有在寒冷的地方才能生長的雪蓮。\n");
                set("value", 100);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
       if( query("eff_qi", me) >= query("max_qi", me) )
                return notify_fail("你現在不用吃這寶貝！\n");

       me->receive_curing("qi", 200);
       message_vision("$N小心地吃下一株雪蓮，頓時覺得神清氣爽了不少！\n",
                      me);

       destruct(this_object());
       return 1;
}