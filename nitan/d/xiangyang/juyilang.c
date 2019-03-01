// Room: /d/xiangyang/juyilang.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "水上走廊");
        set("long", @LONG
這時一條筆直的走廊，廊下是一湖池水。湖水映著長長垂柳，碧
綠清澈，你能看見一些魚在遊來遊去。南面就是一個大花園，圓內東
西兩側各有一排廂房。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "south" : __DIR__"juyihuayuan",
                "north" : __DIR__"juyiyuan",
        ]));
        set("coor/x", -7840);
	set("coor/y", -790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}