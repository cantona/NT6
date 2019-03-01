#include <ansi.h> 
inherit ITEM;

void create()
{
        set_name("蛇膽粉", ({ "shedan fen", "shedan", "fen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("long", GRN "這是一包治療外傷的蛇膽粉。\n" NOR);
                set("value", 2000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        if( query("eff_qi", me) >= query("max_qi", me)-20 )
                return notify_fail("你現在氣血充盈，不需要用蛇膽粉。\n");

        if (random(2) == 0)
        {
                message_vision(WHT "$N" WHT "吃下一包蛇膽粉，覺得"
                               "象是土豆粉，連呼上當。\n" NOR, me);
                destruct(this_object());
                return 1;
        }
        addn("qi", 30, me);
        addn("eff_qi", 20, me);
        message_vision(HIY "$N" HIY "吃下一包蛇膽粉，頓覺真氣上湧"
                       "，精神好了些。\n" NOR, me);
        destruct(this_object());
        return 1;
}