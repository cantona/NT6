// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "卧房");
        set("long", @LONG
你走進了一間卧房。一股若有若無的甜香撲鼻而來。琴劍書畫，掛在
牆上。錦籠紗罩，金彩珠光。小几上汝窯美人瓶內的桃花正自盛開。右首
一張牀，牀頭放着五彩鸞紋被。
LONG );
        set("exits", ([
                "north" :__DIR__"hyjuchu",
        ]));
        set("objects", ([
                __DIR__"npc/binu" : 2,
        ]) );
        
        set("coor/x", 8970);
        set("coor/y", -2960);
        set("coor/z", 0);
        setup();
}
