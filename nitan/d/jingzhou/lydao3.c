inherit ROOM;

void create()
{
        set("short", "林蔭道");
        set("long", @LONG
這是一條安靜的林蔭道，地上舖著奇奇怪怪五顏六色的石子，向
東西兩頭延伸。東面是一條林蔭道。徑直通南大街。西邊好像有一眼
溫泉。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "east" : __DIR__"lydao4",
                "westdown" : __DIR__"wenquan",
        ]));
        set("coor/x", -7120);
	set("coor/y", -2070);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}