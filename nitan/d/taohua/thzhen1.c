// This program is a part of NT MudLIB

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
你一走進桃林，看見東一簇桃花，西一叢桃樹，你頓時目眩神迷，迷
失了方向。你慌亂中剛想退出，回頭一瞧，來路已在花叢中消失得無影無
蹤，看來只有硬著頭皮往前走了。
LONG );

        set("exits", ([
                "east"      : __DIR__"thzhen1",
                "south"     : __DIR__"thzhen1",
                "west"      : __DIR__"thzhen1",
                "north"     : __DIR__"thzhen1",
                "northeast" : __DIR__"thzhen3",
                "southeast" : __DIR__"thzhen3",
                "southwest" : __DIR__"thzhen3",
                "northwest" : __DIR__"thzhen3",
        ]));

        set("objects", ([
                // CLASS_D("taohua") + "/feng" : 1,
        ]) );

        set("outdoors", "taohua");

        set("coor/x", 9000);
        set("coor/y", -2500);
        set("coor/z", 0);
        setup();

}
/*
void init()
{
        set_temp("die_reason", "誤入桃花迷陣被桃花瓣射死", this_player());
        this_player()->receive_damage("qi", 15);
        this_player()->receive_wound("qi",  15);
        message_vision(HIR "突然一陣桃花瓣象雨點般疾射$N！\n" NOR, this_player());
}
*/

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
                me->move("/d/taohua/thzhen2");
                if (! myfam || myfam["family_name"] == "桃花島")
                {
                        if( query("combat_exp", me)<20000+random(10000) )
                        {
                                addn("combat_exp", gain, me);
                        }
                }
                  me->start_busy(random(3));
                return 1;
          }
          return ::valid_leave(me, dir);
}
