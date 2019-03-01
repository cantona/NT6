inherit ROOM;

void create()
{
        set("short", "一線牽");
        set("long", @LONG
你現在正地方叫一線牽，這裡是專門替人締結婚約和解除婚約的地方，
洛陽城裡所有的夫婦都是在這裡喜結良緣的，就連附近鎮子也有許多慕名
而來的年青人。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"eroad2",
        ]));
        set("objects", ([
                "/adm/npc/hongniang" : 1,
        ]));
	set("coor/x", -6970);
	set("coor/y", 2140);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}