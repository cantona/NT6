inherit ROOM;

void create()
{
        set("short", "小店");
        set("long", @LONG
這裡是衡陽縣城的一間小店，賣些簡單的飲食，專門賺那些遊客
的錢。
LONG );
        set("exits", ([
                "north" : __DIR__"hengyang1",
                "up"    : __DIR__"huiyan",
        ]));

        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));

	set("coor/x", -6900);
	set("coor/y", -5710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}