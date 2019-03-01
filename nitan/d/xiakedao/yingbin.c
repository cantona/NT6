// yingbin.c 迎賓館

inherit ROOM;

void create()
{
        set("short", "迎賓館");
        set("long", @LONG
這是一個石洞，地下的青石板舖得甚是整齊，兩旁有一些木制家
具，整個房間並無特殊之處，但收拾得幹幹凈凈，一塵不染。東面是
一個小吃部，西面是休息室。
LONG );
        set("exits", ([
               "east" : __DIR__"xiaodian",
               "west" : __DIR__"xiuxis",
               "south" : __DIR__"shidong2",
               "out" : __DIR__"dongmen",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3080);
        set("coor/y", -22080);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}