// Room: /d/shaolin/wuxing1.c
// Date: YZC 96/02/06

#include <ansi.h>

inherit ROOM;

string* dirs = ({"east", "south", "west", "north"});

void create()
{
        set("short", HIG "五行洞" NOR);
        set("long", @LONG
[1；32m這是五行洞。這裏地面相對比較乾燥些，四壁由寬厚的木板嚴嚴
實實的地封了起來，叩上去發出沉悶的篤篤聲，看來不是實心的就是
有幾尺厚，沒有斧鑿等利器休想劈開它們。不過你還是想下手試一試，
希望能從這裏打開缺口。[2；37；0m
LONG );
        set("exits", ([
                "east" : __DIR__"wuxing0",
                "south" : __DIR__"wuxing3",
                "west" : __DIR__"wuxing4",
                "north" : __DIR__"wuxing2",
        ]));
        set("no_clean_up", 0);
        setup();
}

int check_out(object me)
{
        int metal, wood, water, fire, earth;

        metal=query_temp("wuxing/金", me);
        wood=query_temp("wuxing/木", me);
        water=query_temp("wuxing/水", me);
        fire=query_temp("wuxing/火", me);
        earth=query_temp("wuxing/土", me);

        if ( metal > 0 &&
                metal == wood && metal == water &&
                metal == fire && metal == earth )
        {
                delete_temp("wuxing", me);
                me->move(__DIR__"andao2");
                return (1);
        }
        return (0);
}

int valid_leave(object me, string dir)
{
        int count;

        if (member_array(dir, dirs) != -1)
        {
                if (dir == "south")
                {
//                        write("*木生火*\n");
                        count=query_temp("wuxing/火", me);
                        count++;
                        set_temp("wuxing/火", count, me);
                        if (check_out(me))
                        {
                                write("你順利地走出了五行迷宮。\n");
                                return 1;
                        }
                }
                else if (dir == "west")
                {
//                        write("*木克土*\n");
                        delete_temp("wuxing", me);
                        me->move(__DIR__"jianyu1");
                        write("你掉進機關，落入僧監。\n");
                        return 1;
                }
        }
        return ::valid_leave(me, dir);
}
