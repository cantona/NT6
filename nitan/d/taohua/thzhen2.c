// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

#include <ansi.h>
inherit ROOM;
#include <localtime.h>

string* dirs = ({
        "east", "southeast", "southeast", "southwest", "northeast", "northeast",
        "west", "south", "south", "northwest", "north", "north",
});

string* dirs2 = ({
        "e", "se", "se", "sw", "ne", "ne",
        "w", "s", "s", "nw", "n", "n",
});

void create()
{

        set("short", "桃花林");
        set("long", @LONG
這桃林似乎無窮無盡一般，其中小徑更卻是縱橫交錯，匪夷所思。你
拼命想離開原地，但幾個轉折又回到了原地。一連幾次，似乎只是在同一
個地方兜圈子。
LONG );

        set("exits", ([
                "east"      : __DIR__"thzhen2",
                "south"     : __DIR__"thzhen2",
                "west"      : __DIR__"thzhen2",
                "north"     : __DIR__"thzhen2",
                "northeast" : __DIR__"thzhen2",
                "southeast" : __DIR__"thzhen2",
                "southwest" : __DIR__"thzhen2",
                "northwest" : __DIR__"thzhen2",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 9000);
        set("coor/y", -2600);
        set("coor/z", 0);
        setup();

}

void init()
{
        set_temp("die_reason", "誤入桃花迷陣被桃花瓣射死", this_player());
        this_player()->receive_damage("qi", 15);
        this_player()->receive_wound("qi",  15);
        message_vision(HIR "突然一陣桃花瓣象雨點般疾射$N！\n" NOR, this_player());
}

int valid_leave(object me, string dir)
{
        mixed local;
          int   count, gain;
          mapping myfam;

        myfam=query("family", me);

          local = localtime(time()*60);

          count = ((local[LT_HOUR] + 1) % 24) / 2;
          gain = random((me->query_skill("qimen-wuxing", 1)) / 30) + 1;
          if (dirs[count] == dir || dirs2[count] == dir)
          {
                me->move("/d/taohua/thzhen3");
                if (! myfam || myfam["family_name"] == "桃花島")
                {
                        if( query("combat_exp", me)<20000+random(10000) )
                        {
                                    addn("combat_exp", gain, me);
                          }
                }

                me->start_busy(random(3));
                // return notify_fail("\n");
                return 1;
          }
          return ::valid_leave(me, dir);
}

