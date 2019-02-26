inherit ROOM;

void create()
{
        set("short", "北城");
        set("long", @LONG
這裏是用黃土鋪就的街道，街上的行人不多，看起來很冷清。偶爾有幾
個身着異域服飾的行人走過，看起來是滿族，鮮祖的居民。西面有一條幽深
的小巷，不知通向何處。
LONG );
        set("exits", ([
                "south" : __DIR__"jishi",
                "west"  : __DIR__"xiaoxiang",
        ]));
        set("objects", ([
                __DIR__"npc/xiucai" : 1,
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "guanwai");
        set("coor/x", 3990);
	set("coor/y", 9250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}