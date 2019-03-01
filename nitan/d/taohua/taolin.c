// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "桃林");
        set("long", @LONG
這是一片燦若雲霞的桃林，繁花似錦，五色繽紛，比起島上其它地方
的桃林要茂盛許多，地下的泥土也十分新鮮，像有人剛剛整理過。
LONG );
        
        set("exits", ([
                "west" : __DIR__"mudi",
                "east" : __DIR__"jingshe",
        ]));
        
        set("objects", ([
                __DIR__"obj/taoshu" : 1,
        ]));
        
        set("outdoors", "taohua");

        set("coor/x", 8980);
        set("coor/y", -2950);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

/*
void init()
{
        object ob = this_player();
        if( query_temp("th_tomb_thief", ob)){
                tell_object(ob,CYN"你似乎覺得桃林中有點異樣，但又說不上來。\n"NOR);
                delete("exits/east");
                set("exits/east", __DIR__"hyjuchu");
                    remove_call_out("close_door");
                    call_out("close_door",random(20),ob);

        }
}


void close_door()
{
        delete("exits/east");
        set("exits/east", __DIR__"jingshe");
}


int valid_leave(object me, string dir)
{
        if( query_temp("th_tomb_thief", me) && dir == "east"){
                me->move("/d/taohua/hyjuchu");
                 return 1;
        }

            return ::valid_leave(me, dir);
}
*/