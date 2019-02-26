// Room: /u/a/agah/kefang2.c

inherit ROOM;

void create()
{
        set("short", "南客房");
        set("long", @LONG
這是一間很大的客房，陳設雖然簡單，但十分乾淨整潔。靠牆放了十
幾張小木牀，不少客人正和衣而卧，滿屋子都是呼呼的打酣聲。不時的還
有客人進來睡覺，而睡好的人很自覺的悄悄爬起，走出客房。
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"kezhan2",
]));

	set("coor/x", -6980);
	set("coor/y", 2160);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}