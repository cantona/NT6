// Room: /heizhao/pububian.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "瀑布岸邊");
        set("long", @LONG
瀑布日夜奔流，年深月久，在巖石間切了一道深溝，約有二丈
來高。站在岸上，只見那瀑布奔騰而去，水沫四濺，不由得目眩心
驚，瀑布一瀉如注，直衝入下面深淵去。岸邊繫着一隻鐵舟。
LONG );
        set("outdoors", "taoyuan");
        set("resource/water", 1);
        set("exits", ([
                "south" : __DIR__"xiaowu",
                "enter" : __DIR__"ironboat",
        ]));
        set("coor/x", -5020);
        set("coor/y", -1260);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}