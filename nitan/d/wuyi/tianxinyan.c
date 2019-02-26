// Room: /d/wuyi/tianxinyan.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "天心巖");
        set("long", @LONG
天心巖在武夷山北部。《武夷山志》載：「全山百二十里度之，是
峯居中央，猶天之樞極也，故曰天心。」
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "west"  : __DIR__"yonglechansi",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1410);
        set("coor/y", -4930);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
