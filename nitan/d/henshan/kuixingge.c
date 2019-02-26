inherit ROOM;

void create()
{
        set("short", "奎星閣");
        set("long", @LONG
奎星閣是南嶽大廟的第二進。閣為一個大舞台，閣左為鼓亭，右
是鍾亭。鄉俗年節唱戲，這裏總是熱鬧非凡。
LONG );
        set("exits", ([
               "south"  : __DIR__"lingxingmen",
               "east"   : __DIR__"zhongting",
               "north"  : __DIR__"zhengchuan",
        ]));
        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6890);
	set("coor/y", -5680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}