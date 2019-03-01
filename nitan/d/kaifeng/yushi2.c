inherit ROOM;

void create()
{
        set("short", "小浴室");
        set("long", @LONG
這些小浴室經過專門裝修，而且有專人伺候打掃，所以很幹凈，
牆角落中還供奉著鮮花，樑柱上供奉著小佛像。房間正中當然是浴盆，
有些人為示對佛誠心，拜佛之前定要沐浴。
LONG );
        set("objects", ([
                __DIR__"npc/obj/zaopeng" : 1,
        ]));
        set("exits", ([
                "east" : __DIR__"yushi",
        ]));

	set("coor/x", -5060);
	set("coor/y", 2200);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}