inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這是馬莊內的一條木制的走廊，紅漆地面很是光滑。整個
走廊被打整得一塵不染。你不時能夠看到幾個丐幫的弟子在此
走動，忙碌個不停。往北是個練武場。
LONG);
        set("region", "yangzhou");
        set("exits", ([
                "south"  : __DIR__"ma_lianwu1",
                "north"  : __DIR__"ma_zoulang1",
        ]));
        set("objects", ([
                "/d/gaibang/npc/2dai" : 1,
        ]));
        set("no_clean_up", 0);
	set("coor/x", 30);
	set("coor/y", -60);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}