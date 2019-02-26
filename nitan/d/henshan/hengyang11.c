inherit ROOM;

void create()
{
        set("short", "衡陽西街");
        set("long", @LONG
這裏是衡陽城西街，這見路人匆匆向東而行，南邊是有一個馬廄，
北面是一家裝飾很典雅的店鋪，店鋪入門處掛滿了風鈴。
LONG );
        set("outdoors", "henshan");

        set("exits", ([
                "east"   : __DIR__"hengyang1",
                "west"   : __DIR__"hsroad4",
                "south"  : __DIR__"majiu",
                "north"  : __DIR__"lingyinge",
        ]));

	set("coor/x", -6910);
	set("coor/y", -5700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}