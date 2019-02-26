// This program is a part of NT MudLIB

inherit  ROOM;

void create()
{
        set("short",  "遊府後院");
        set("long",  @LONG
這裏是遊府的後院，幾個僕役穿梭奔走，為這次的英雄宴而忙碌着。
後院一角聚坐着一幫乞丐，低聲商談着什麼，旁邊的江湖人士似乎對
他們頗為不屑，甚少有人上前攀談。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east"  :  __DIR__"neitang",
                "west"  :  __DIR__"chaifang",
                "south" :  __DIR__"xiangfang3",
                "north" :  __DIR__"xiangfang2",
        ]));
        /*
        set("objects",([
                __DIR__"npc/gangbang" : 1,
        ]));
        */
        setup();
        //replace_program(ROOM);
}

#include "/maze/juxianzhuang/zhuang.h"

int valid_leave(object me, string dir)
{
        object room, ob;

        if( dir == "west" )
        {
                if( me->query_temp("juxianzhuang_step") == 6
                ||  me->query_temp("juxianzhuang_step") == 10 )
                {
                        room = get_object(__DIR__"chaifang");
                        if( !present("xiao feng", room) )
                        {
                                ob = new(__DIR__"npc/xiaofeng");
                                ob->move(room);
                        }
                        return 1;
                }
        }

        return ::valid_leave(me, dir);
}