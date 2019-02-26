// xiaolu7.c 後山小路
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "後山小路");
        set("long", @LONG
這裏是後山上的小路。這條小路好像不是人工刻意修出來的，
也許只是以前的採藥人踩多了，現出這樣一條小路來。走到這裏，
你好像迷路了。
LONG
        );
        set("outdoors", "chongyang");
        set("exits", ([
                "east" : __DIR__"xiaolu8",
                "west" : __FILE__,
                "north" : __DIR__"xiaolu3",
                "south" : __FILE__,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2690);
        set("coor/y", 120);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}