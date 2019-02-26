#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", NOR + WHT "【奈河橋】" NOR);
        set("long", NOR + WHT @LONG

                    奈         河         橋

    這裏就是著名的陰間通道「奈河橋」，在你面前矗立著一座長長的
石制拱橋，許多亡魂正哭哭啼啼地列隊上橋，橋頭一位白髮蒼蒼的老婦
人，正為每一個上橋的亡魂舀着湯。


LONG NOR );
        set("exits", ([
                "north" : __DIR__"qiao2",
                // "south" : __DIR__"road6",
        ]) );
        set("objects", ([
                __DIR__"npc/mengpo":1,
                __DIR__"npc/ghost":1,
        ]) );
        
        set("outdoors", 1);

        set("no_fight", 1);
        set("no_sleep_room", 1);

       
        setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        me = this_player();

        if (dir == "north")
        {
                /*
                if( !query("reborn_offer", me) || query("reborn_offer", me) != "finish" )
                        return notify_fail(BLU "你無法通過這裏！\n" NOR);

                if( !query_temp("last_eat/mengpo_tang", me )
                   && objectp(present("meng po", environment(me))) )
                        return notify_fail(CYN "孟婆説道：這位" +
                                           RANK_D->query_respect(me) +
                                           CYN "，喝碗湯再走吧。\n" NOR);
                */
        }
        return ::valid_leave(me, dir);
}

void init()
{
        add_action("do_move", "jump");
        add_action("do_move", "tiao");
}

int do_move(string arg)
{
        object paper,
        me = this_player();

        if (! arg || arg == "")
                return 0;

        if (arg == "qiao" || arg == "橋" || arg == "奈河橋")
        {
                /*
                if( !query("hell_quest/鎖陽丹", me )
                   && objectp(present("meng po", environment(me))))
                {
                        write(CYN "只見孟婆一把攔住你，説道：這位"
                              + RANK_D->query_respect(me) + CYN
                              "，這橋下不得，下不得！下了可就回不"
                              "來了。\n" NOR);
                        return 1;
                }
                */
                message_vision(HIC "\n只見$N" HIC "咬了咬牙，一縱"
                               "身從奈河橋上跳了下去……\n" NOR,
                               this_player());
                me->move("/d/death/hantan1");
                message_vision(HIC "\n只聽“撲通”一聲，$N" HIC
                               "從上面奈河橋跳了下來。\n" NOR,
                               this_player());
                return 1;
        }
        return 0;
}