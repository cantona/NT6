// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "碧波池");
        set("long", @LONG
繞過如同石屏風一般的涵碧峯，是一汪晶瑩剔透，碧玉般的池水。池
底有兩眼活泉，一為寒泉，一為温泉，所以池水冬暖夏涼，四季不涸，且
水質特佳，不亞於天下任何名泉。池養魚鼈，大多是罕見異種，其中五色
錦鯉嘻遊嘬花，池中大黿壽齡已達五百餘歲。更傳説池中有可克百毒的“
金娃娃”出現。北面隱隱約約有一座精舍，東面靠近池中心處有一塊奇形
大石。
LONG );
         set("exits", ([
                "southwest" : __DIR__"hanbi",
                "east"      : __DIR__"tingyu",
                "north"     : __DIR__"jingshe",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 8990);
        set("coor/y", -2960);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}