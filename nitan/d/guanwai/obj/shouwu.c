// shouwu.c 何首烏

inherit ITEM;

void create()
{
        set_name("何首烏", ({"heshou wu", "wu"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "棵");
                set("long", "這是一棵初具人形的何首烏。\n");
                set("value", 10000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        addn("max_neili", 1, me);
        if( query("max_neili", me)>me->query_neili_limit() )
                set("max_neili", me->query_neili_limit(), me);

        message_vision("$N吃下一棵何首烏，頓時間覺得全身充滿了活力！\n", me);
        destruct(this_object());
        return 1;
}