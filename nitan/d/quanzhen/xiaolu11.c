// xiaolu11.c 後山小路
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "後山小路");
        set("long", @LONG
這裡是後山上的小路。這條小路好象不是人工刻意修出來的，
也許只是以前的採藥人踩多了，現出這樣一條小路來。走到這裡，
你好象迷路了。
LONG
        );
        set("outdoors", "chongyang");
        set("exits", ([
                "east"  : __FILE__,
                "west"  : __DIR__"xiaolu10",
                "north" : __FILE__,
                "south" : __FILE__,
        ]));
        set("no_clean_up", 0);

        set("coor/x", -2660);
        set("coor/y", 140);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}