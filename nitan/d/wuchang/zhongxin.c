inherit ROOM;

void create ()
{
        set("short","中心廣場");
        set("long", @LONG
這裡是武漢最繁華的地帶了。這裡匯集了五湖四海的商人、遊客。
熙熙攘攘，好不熱鬧。雖然近來動亂不住，但是這裡仍然熱鬧非凡。
LONG);

        set("exits", ([
                "west": __DIR__"hzjie4",
                "east": __DIR__"dongmen",
                "south" : __DIR__"hzjie3",
                "north" : __DIR__"hzjie2",
        ]));
        set("objects",([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "wuchang");

	set("coor/x", -5090);
	set("coor/y", -1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}