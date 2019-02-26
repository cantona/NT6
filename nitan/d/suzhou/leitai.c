// Room: /d/suzhou/leitai.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "擂台前廣場");
        set("long", @LONG
這裏是蘇州擂台前面的一個大廣場，有許多人正在擂台上比武，到
處是人山人海，如果你也想試試身手，那麼就請跳上擂台比試比試吧。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "south"  : __DIR__"hutong2",
        ]));
	set("coor/x", 1130);
	set("coor/y", -1030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}