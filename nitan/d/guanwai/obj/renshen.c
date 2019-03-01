// renshen.c

inherit ITEM;

void create()
{
        set_name("人參", ({"renshen", "shen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "棵");
                set("long", "這是一棵初具人形的老山參。\n");
                set("value", 10000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        addn("max_neili", 3, me);
        if( query("max_neili", me)>me->query_neili_limit() )
                set("max_neili", me->query_neili_limit(), me);

        message_vision("$N吃下一棵老山參，頓時間覺得全身充滿了活力！\n", me);
        destruct(this_object());
        return 1;
}