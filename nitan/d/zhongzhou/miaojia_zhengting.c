inherit ROOM;

void create()
{
        set("short", "苗家正廳");
        set("long", @LONG
這裏是苗家的正廳，廳內非常的寬敞明亮。正中擺放着張八仙桌，
四周牆壁上掛着一些字畫。兩個中年男子坐在大廳的中央，用着鄂北
方言大聲談論着些什麼。
LONG );
        set("exits", ([
                "west"  : __DIR__"miaojia_dayuan",
                "east"  : __DIR__"miaojia_zoulang1",
                "north" : __DIR__"miaojia_xiangfang1",
                "south" : __DIR__"miaojia_xiangfang2",
        ]));
        set("objects", ([
                CLASS_D("miao") + "/ying" : 1,
                CLASS_D("miao") + "/neng" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -9010);
	set("coor/y", -960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}