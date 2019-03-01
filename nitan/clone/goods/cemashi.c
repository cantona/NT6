
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "冊馬石" NOR, ({ "cema shi", "cema", "shi", "stone" }) );
        set_weight(100);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "一塊光滑如玉的石頭，隱約可見其中鑲有一匹駿馬，乃天然形成。\n"
                            "使用 loghorse 命令可使你增加一條騎馬記錄點。\n" 
                            "如果暫時不使用，最好將冊馬石存入倉庫，以免丟失。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "塊");
                set("auto_load", 1);
        }

        setup();
}

void init()
{
        add_action("do_changing", "loghorse");
}

int do_changing(string arg)
{
        object me;
        me = this_player();

        if( query("horse/stone", me) >= 5 )
                return notify_fail("你只能通過冊馬石最多增加到五條騎馬記錄點。\n");

        addn("horse/stone", 1, me);
        write(HIM "冊馬石使用成功，你的騎馬記錄點增加了！\n" NOR);
        me->save();
        destruct(this_object());

        return 1;
}

