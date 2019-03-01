// bicanfeng.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(GRN "碧蠶粉" NOR, ({"bican fen", "fen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一袋劇毒的毒藥，如果用來煉暗器有見血封喉之效。\n");
                set("unit", "袋");
                set("value", 20000);
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 200,
                        "id"    : "...",
                        "name"  : "劇毒",
                        "duration": 15,
                ]));
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$N仰頭把一小袋" + name() + "都嚥了下去。\n", me);
        set_temp("die_reason", "吞了碧蠶粉，莫名其妙的見了閻王", me);
        me->die();
        destruct(this_object());
        return 1;
}