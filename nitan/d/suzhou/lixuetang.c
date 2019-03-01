// Room: /d/suzhou/lixuetang.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "立雪堂");
        set("long", @LONG
立雪堂名自“程門立雪”和“斷臂立雪”之典。堂前小院中的湖石、
形似牛、蟹、獅、蛙，謂“獅子靜觀牛吃蟹”，頗生動有趣。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "north"  : __DIR__"wenmeige",
        ]));
	set("coor/x", 1150);
	set("coor/y", -1090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}