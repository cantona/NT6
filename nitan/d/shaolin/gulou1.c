// Room: /d/shaolin/gulou1.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "鼓樓一層");
        set("long", @LONG
這裡是塔樓的底層，一縷縷陽光從牆上的花磚縫隙裡透射進來，
在青磚地上投下別致的光影，如同一格格棋盤相似。往上看，長長的
木樓梯盤繞而上，似乎永無盡頭。牆角，梯級都相當潔凈，看來經常
有僧人打掃。
LONG );
        set("exits", ([
                "up" : __DIR__"gulou2",
                "out" : __DIR__"gulou",
        ]));
        set("objects",([
                __DIR__"npc/saodi-seng" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
