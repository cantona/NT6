inherit ROOM;

void create()
{
        set("short", "州橋");
        set("long", @LONG
這座高高的橋如同彩虹初降人間，三十六道石階直通橋面橋下就
是水流奔湧的大運河。橋上人來如梭河中巨舟橫過。切然在橋下看去，
人行於高波之上，令人心顫不已。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "southdown" : __DIR__"road3",
                  "northdown" : __DIR__"road5",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5060);
	set("coor/y", 2230);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}