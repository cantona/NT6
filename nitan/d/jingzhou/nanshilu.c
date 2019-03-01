inherit ROOM;
void create()
{
        set("short", "碎石路" );
        set("long", @LONG
這是一條由碎石舖成的路，雖然有些顛簸，卻很寬闊，再往南去
就是長江了。
LONG );
        set("exits", ([
                  "north" :__DIR__"jznanmen",
                  "south" :__DIR__"nanshilu1",
                "west" : __DIR__"qingshilu1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");

        set("coor/x", -7100);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}