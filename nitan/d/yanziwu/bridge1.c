// Room: /d/yanziwu/bridge1.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "回望橋");
        set("long", @LONG
出了林中小路，就是蓮韻塘。行人到此，每每回望來路，看青泥小
徑在林中曲折隱沒，別有一般韻味。看橋下蓮韻塘中荷葉田田，蛙鳴魚
躍，生機無限。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "south"  : __DIR__"path10",
                "north"  : __DIR__"path11",
        ]));
        set("coor/x", 1240);
        set("coor/y", -1230);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}