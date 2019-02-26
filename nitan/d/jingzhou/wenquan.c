inherit ROOM;

void create()
{
        set("short", "温泉井");
        set("long", @LONG
你看到一眼温泉呈現在你的面前，汩汩往外冒着熱氣和泉水，温
泉雖不大，但足以使人想到下去泡一泡，據説還可以療傷治病。
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "northup" : __DIR__"lydao2",
                "eastup" : __DIR__"lydao3",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("coor/x", -7130);
	set("coor/y", -2070);
	set("coor/z", -20);
	setup();
        replace_program(ROOM);
}