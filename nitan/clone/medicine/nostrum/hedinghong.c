// Pill: hedinghong.c
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
        }
        set("pour_type", "1");
        setup();
}

int init()
{
        add_action("do_drink", "drink");
        add_action("do_drink", "he");
}

int do_drink(string arg)
{
        object me = this_player();

        if(!id(arg)) return notify_fail("你要喝什麼？\n");
        if(!present(this_object(), this_player()))
                return notify_fail("你要喝什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢喝，小心別嗆着了。\n");

        message_vision("$N仰頭咕嘟咕嘟灌下一瓶" + name() + "。\n", me);
        set_temp("die_reason", "喝下鶴頂紅，自殺身亡了", me);
        me->die();
        destruct(this_object());
        return 1;
}