// hedinghong.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(RED"鶴頂紅"NOR, ({"heding hong", "hong"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一瓶劇毒的毒藥, 如果用來煉暗器有見血封喉之效. \n");
                set("unit", "瓶");
                set("value", 20000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$N仰頭咕嘟咕嘟灌下一瓶" + name() + "。\n", me);
        set_temp("die_reason", "喝了鶴頂紅，中毒死了", me);
        me->die();
        destruct(this_object());
        return 1;
}