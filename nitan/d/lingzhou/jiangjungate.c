// Room: /lingzhou/jiangjungate.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "大將軍府");
        set("long", @LONG
這裏是徵東大將軍赫連鐵樹的府第，在東大街的正中，對面就是衙
門。一色高檐大屋，兩個校尉看上去彪悍驍勇，此刻正神氣活現的挎着
彎刀守在門前。
LONG );
        set("exits", ([
                "north" : __DIR__"dongdajie",
                "south" : __DIR__"jjdayuan",
        ]));
        set("objects", ([
                __DIR__"npc/xiaowei" : 2,
        ]));
        set("coor/x", -6265);
        set("coor/y", 2915);
        set("coor/z", 0);
        setup();
        create_door("south" , "油木大門", "north" , DOOR_CLOSED);
}

int valid_leave(object me, string dir)
{
        int i;
        object wei;

        wei = present("xiao wei", environment(me));
        if (dir != "south" || ! objectp(wei) || ! living(wei))
                return ::valid_leave(me, dir);

        if( query("weiwang", me) >= 10000 )
        {
                message_vision("$N笑道：“" + RANK_D->query_respect(me) +
                               "，請進，請進！這就去讓人通報。”\n", wei, me);
                return ::valid_leave(me, dir);
        }

        if( query("special_skill/trick", me) )
        {
                message_vision("$N看見$n走了過來，剛想攔住，"
                               "卻聽$n一聲斷喝：“散開！”\n"
                               "不由得嚇了一跳，訕訕的不敢説話。\n", wei, me);
                return ::valid_leave(me, dir);
        }

        return notify_fail("校尉上前擋住你，朗聲説道：這位"  +
                           RANK_D->query_respect(me) + "請回吧。老爺不見客。\n");
}