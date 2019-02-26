#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","船上");
        set("long", @LONG
這些大船，想是巨鯨幫、海沙派一干人的座船。
LONG );
        set("exits",([
                //"northup":"/d/tulong/tulong/daobian",
                "south":"/d/binghuo/wangpanshan",
        ]));

        set("objects",([
                 "/d/tulong/tulong/obj/stone": 1,
        ]));

setup();
}

void init()
{
        add_action("do_break","break");
}

int do_break(string arg)
{
        object me=this_player(),inv;
        if (arg!="boat" && arg!="船") return notify_fail("你要打碎什麼？\n");
        inv=present("stone",me);
        if (query("dao")) return notify_fail("船上的桅杆早就倒了，還砸什麼？\n");
        if (!objectp(inv)) return notify_fail("你準備拿什麼砸船呀？\n");
        else 
        {
        message_vision("$N舉起手中"+query("name", inv)+"，向船上的桅杆砸去。\n",me);
        remove_call_out("do_dao");
        call_out("do_dao",3,me);
        return 1;
        }
}

int do_dao(object me)
{
        message_vision( WHT "\n只聽得喀喇、喀喇之聲不絕，聳立的船桅一根根倒將下來。\n砰嘭之聲不絕，頃刻之間，眾桅杆或倒或斜，無一得免。\n" NOR,me);
        set("dao",1);
        set("long","這些大船，想是巨鯨幫、海沙派一干人的座船。只是桅杆都被砸斷了。\n");
        set_temp("dao", 1, me);
        return 1;
}
