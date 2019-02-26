inherit ROOM;

void create()
{
        set("short", "衡陽東街");
        set("long", @LONG
這裏是衡陽東街，再往東走便出衡陽城了，北面是一家雜貨鋪，
南邊是一條偏僻的小巷。
LONG );
        set("outdoors", "henshan");

        set("exits", ([
               "east"   : __DIR__"hsroad3",
               "west"   : __DIR__"hengyang",
               "south"  : __DIR__"xiaoxiang1",
               "north"  : __DIR__"zahuopu",
        ]));

        set("no_clean_up", 0);

	set("coor/x", -6880);
	set("coor/y", -5700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}