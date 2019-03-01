#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "田地");
        set("long", @LONG
這是藥王谷用來種植草藥的田地，你可以拿草藥種籽在這裡種植草藥(zhong)。
等草藥種成了就可以挖(dig)起來。
LONG );
        set("no_clean_up", 1);
        set("yaotian",1);
        set("no_fight", 1);
        set("exits", ([
                "north" : __DIR__"door",
        ]));

        setup();
}

void init()
{
        add_action("do_dig", "dig");
        add_action("do_work", "get");
}

int do_dig(string arg)
{
        object ob, me;
        me = this_player();

        if( query("family/family_name", me) != "藥王谷"
                || me->query_skill("medical",1) < 60 )
                return notify_fail("你不會種植草藥！更不會挖草藥！\n");

        if(me->is_fighting() && me->is_busy())
                return notify_fail("你很忙，沒時間。\n");

        if( !arg || !ob = present(arg, environment(me)) )
                return notify_fail("指令格式：dig <草藥ID> \n");

        if( query("owner", ob) != query("id", me) )
                return notify_fail("這個東西好象不是你的啊？？\n"); 

        message_vision("$N輕輕將$n挖了起來。\n", me, ob);

        delete("no_get", ob);
        ob->move(me);
        delete("dig", ob);
        return 1;
}

int do_work()
{
        return notify_fail("這裡不能使用這個指令！\n");
}
