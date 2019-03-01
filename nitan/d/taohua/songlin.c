// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "鬆柏林");
        set("long", @LONG
這座鬆柏林每株樹木之間錯落有致，枝條交互掩映，抬頭望去，鬆針
柏葉密密重重，遮雲蔽日，但林中卻光線充足，纖毫畢現。真不知是天然
生就，還是妙手偶得。林中一條小徑鬥折蛇行，指向北方。東北面似乎有
一排竹林。
LONG );
         set("exits", ([
                "south" : __DIR__"caodi",
                "west"  : __DIR__"songlin2",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 8990);
        set("coor/y", -2990);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}