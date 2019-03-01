// Room: gbdixiaoshi.c
// by aji

inherit ROOM;
void create()
{
        set("short", "林間小屋");
        set("long", @LONG
你走進了一間小屋。四周牆壁都由青竹篾編成，窗外是一望無際
的竹林。屋裡的桌椅、床舖均為竹制。但一陣撲鼻而來的狗肉香味，
卻顯得與這清雅的氣紛格格不入。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "west" : "/d/city/gbandao"
        ]));
	set("objects", ([
		"/d/city/obj/zhubang": 1,
		"/d/city/obj/gourou": 1,
		"/d/city/obj/jiudai": 1,
		"/d/city/obj/jitui": 1
	]));

        set("valid_startroom", 1);
        set("sleep_room", 1);
	set("coor/x", 50);
	set("coor/y", 40);
	set("coor/z", 0);
	setup();

        (CLASS_D("gaibang") + "/hong")->come_here();
}

void reset()
{
        ::reset();
        (CLASS_D("gaibang") + "/hong")->come_here();
}