// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "松柏林");
        set("long", @LONG
這座松柏林每株樹木之間錯落有致，枝條交互掩映，抬頭望去，松針
柏葉密密重重，遮雲蔽日，但林中卻光線充足，纖毫畢現。真不知是天然
生就，還是妙手偶得。林中一條小徑斗折蛇行，指向北方。東北面似乎有
一排竹林。
LONG );
         set("exits", ([
                "north" : __DIR__"songlin3",
                "east"  : __DIR__"songlin",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 8980);
        set("coor/y", -2990);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}