// xiaolu1.c 後山小路
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "後山小路");
        set("long", @LONG
這裡是後山上的小路。這條小路好象不是人工刻意修出來的，
也許只是以前的採藥人踩多了，現出這樣一條小路來。
LONG
        );
        set("outdoors", "chongyang");
        set("exits", ([
                "northeast" : __DIR__"xiaolu2",
                "southwest" : __DIR__"houshan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2710);
        set("coor/y", 120);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}