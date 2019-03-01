inherit ROOM;

void create()
{
        set("short", "馬莊正廳");
        set("long", @LONG
這裡是馬莊的正廳，廳內非常寬敞明亮。正中擺放著一張
八仙桌，四周牆壁上掛著一些字畫。幾個年齡較大的乞丐正坐
在大廳的中央，大聲談論著些什麼。
LONG);
        set("region", "yangzhou");
        set("exits", ([
                "west"  : __DIR__"ma_yantingw",
                "east"  : __DIR__"ma_yantinge",
                "south" : __DIR__"ma_zoulang1",
                "north" : __DIR__"ma_houyuan",
        ]));
        set("objects", ([
                CLASS_D("gaibang") + "/ma" : 1,
                CLASS_D("gaibang") + "/xi" : 1,
                CLASS_D("gaibang") + "/wu-changfeng" : 1,
                "/d/gaibang/npc/6dai" : 1 + random(2),
                "/d/gaibang/npc/7dai" : 1 + random(2),
        ]));
        set("no_clean_up", 0);
	set("coor/x", 30);
	set("coor/y", -40);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}