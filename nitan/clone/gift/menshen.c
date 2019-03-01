// menshen.c

#include <ansi.h>
#include <room.h>

inherit ITEM;

void setup() {}

void create()
{
        set_name(HIM "門神" NOR, ({ "men shen", "menshen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一張畫的五顏六色的門神，常常"
                            "被人貼在門上用來驅除妖邪。\n");
                set("unit", "張");
        }

        set("no_get", 1);
        setup();
}

void init()
{
        object env;
        object me;

        if (! objectp(env = environment()))
                return;

        if (! clonep(env) || base_name(env) != CHAT_ROOM)
                return;

        if (! stringp(env->query("owner_id")) ||
            ! stringp(env->query("startroom")))
                return;

        me = this_player();
        if (! interactive(me) || env->welcome(me))
                return;

        message_vision("門神大喝一聲：“何方妖孽，也"
                       "敢來此？”說罷手中銅錘一盪，"
                       "將$N一錘打得飛了出去！\n", me);
        me->move(env->query("startroom"));
        me->start_busy(3);
        message("vision", "只聽“蓬”一聲，" + me->name() +
                "飛了出來，身上青一塊兒紫一塊兒的。\n",
                environment(me), ({ me }));
}
