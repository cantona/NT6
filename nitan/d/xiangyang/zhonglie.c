// Room: /d/xiangyang/zhonglie.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "忠烈祠");
        set("long", @LONG
這裡是襄陽城的忠烈祠，十余年來為保衛襄陽而犧牲的烈士遺骨
都安葬在這裡，每個有愛國心的好漢到這都會來祭奠一下忠魂。
LONG );
        set("no_beg", 1);
        set("no_clean_up", 0);

        set("exits", ([
                "west" : __DIR__"eastroad2",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("coor/x", -7790);
	set("coor/y", -750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}