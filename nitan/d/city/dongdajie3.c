// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "東大街");
        set("long", @LONG
這裏是東大街的盡頭，向東便可到揚州城的東大門了。遠處傳來
官兵的吆喝聲，不言而知官兵正在那裏盤問來來往往的行人。北邊是
一家花店，南邊是個小市場。
LONG );
        set("outdoors", "city");
        set("exits", ([
                "east"  : __DIR__"dongmen",
                "west"  : __DIR__"dongdajie2",
                "south" : __DIR__"ma_damen",
                "north" : __DIR__"huadian",
        ]));

	set("coor/x", 30);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}