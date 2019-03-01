// Room: /d/fuzhou/zhongzhou.c
// Date: May 12 1998 Java

inherit ROOM;

void create()
{
        set("short", "中洲橋");
        set("long", @LONG
中洲橋橫越閩江，橋面平整，橋下水花喧鬧。中洲為一小島，盡是
水上人家。西邊是一個碼頭。
LONG );
        set("exits", ([
                "west"  : __DIR__"matou",
                "north" : __DIR__"nanmen",
                "south" : __DIR__"puxian",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "fuzhou");
	set("coor/x", -80);
	set("coor/y", -6220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}