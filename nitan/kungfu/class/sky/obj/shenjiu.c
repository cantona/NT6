#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "天乙神酒" NOR, ({"tianyi shenjiu", "jiu", "shenjiu", "tianyi"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "這是一瓶天乙神酒，便是只聞聞也讓你昏昏欲醉。\n" NOR);
                set("unit", "瓶");
                set("no_sell", 1);
                set("value", 50000);
        }
        setup();
}

void init()
{
        add_action("do_eat", "drink");
}

int do_eat(string arg)
{
        object ob;
        object me = this_player();

        if (! id(arg) && arg != "tianyi shenjiu"
           && arg != "jiu" && arg != "shenjiu"
           && arg != "tianyi")
                return notify_fail("你要喝什麼東西？\n");

        if (me->is_busy())
                return notify_fail("急什麼，小心別噎著了。\n");

        if (random(30) > 1)
        {
                message_vision(WHT "$N" WHT "喝了幾口，卻發現瓶內所裝不"
                               "過是普通的女兒紅。\n" NOR, me);
                destruct(this_object());
                return 1;
        }

        message_vision(HIW "$N" HIW "一仰頭，將天乙神酒喝了下去，精神頓"
                       "時為之一振。\n" NOR, me);

        me->set("jingli", me->query("max_jingli"));
        me->set("neili", me->query("max_neili"));
        me->set("jing", me->query("max_jing"));
        me->set("qi", me->query("max_qi"));
        me->set("eff_jing", me->query("max_jing"));
        me->set("eff_qi", me->query("max_qi"));
        me->improve_skill("force", 300000);

        me->affect_by("drunk", ([
                "level" : 500 + random(500),
                "id"    : me->query("id"),
                "duration" : 500 + random(500)
        ]));

        me->start_busy(6);
        destruct(this_object());
        return 1;
}

