// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "刺藤樹叢");
        set("long", @LONG
你走了一陣，前面出現一片無法通過的密林，這林子好不古怪，每株
樹上生滿了長藤鈎刺，難以落腳。走不了兩步，就被長藤纏住，放眼遠望，
前面刺藤樹密密層層，不知道能不能走出去。
LONG );
         set("exits", ([
                "west"  : __DIR__"shulin2",
                "east"  : __DIR__"beach",
                "north" : __DIR__"shanlu1",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 9030);
        set("coor/y", -3000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}