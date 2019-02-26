// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

int do_tanzhi();
void create()
{
        set("short", "彈指峯");
        set("long", @LONG
這裏是整個桃花島的最高點，居高臨下，全島景觀盡收眼底。南邊是
海，向西是一些光禿禿的巖石，東面北面都是花樹，五色繽紛，不見盡頭，
只看得人頭昏眼花。峯頂有一塊石碑，上有三個大字“彈指峯”，碑旁有
一個石洞。洞口之上三個大篆，雖然已磨損不少，但仍依稀可辨。細看之
下原來是“清音洞”三字。
LONG );
         set("exits", ([
                "enter" : __DIR__"qingyin",
                "southdown" : __DIR__"shanlu2",
        ]));
        
        set("objects", ([
                __DIR__"obj/taoshu" : 1,
        ]));

        set("outdoors", "taohua");

        set("coor/x", 9030);
        set("coor/y", -2970);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
