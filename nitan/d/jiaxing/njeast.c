// Room: /d/taohua/njeast.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "牛家村口");
        set("long", @LONG
這是一座小村落的東村口。村子很小，籠罩在一片寂靜中。南邊隱
約可以看到一條大江。
LONG
        );
        set("no_clean_up", 0);
        set("outdoors","jiaxing");
        set("exits", ([
                "west": __DIR__"njroad3",
        ]) );
        set("objects", ([
                "/d/village/npc/kid" : 1,
        ]) );

	set("coor/x", 1280);
	set("coor/y", -1820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}