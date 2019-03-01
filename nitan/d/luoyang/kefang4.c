// Room: /u/a/agah/kefang4.c

inherit ROOM;

void create()
{
        set("short", "北客房");
        set("long", @LONG
這是一間很大的客房，陳設雖然簡單，但十分幹凈整潔。靠牆放了十
幾張小木床，不少客人正和衣而臥，滿屋子都是呼呼的打酣聲。不時的還
有客人進來睡覺，而睡好的人很自覺的悄悄爬起，走出客房。
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"kezhan2",
]));

	set("coor/x", -6980);
	set("coor/y", 2180);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}