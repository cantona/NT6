// Room: /u/a/agah/kefang1.c

inherit ROOM;

void create()
{
        set("short", "東客房");
        set("long", @LONG
這是一間很大的客房，陳設雖然簡單，但十分幹凈整潔。靠牆放了十
幾張小木床，不少客人正和衣而臥，滿屋子都是呼呼的打酣聲。不時的還
有客人進來睡覺，而睡好的人很自覺的悄悄爬起，走出客房。
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"kezhan2",
]));

	set("coor/x", -6970);
	set("coor/y", 2170);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}