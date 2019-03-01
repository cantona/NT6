// Room: /d/yueyang/nanmen.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "岳陽南門");
        set("long", @LONG
這裡是岳陽城的南門。青石築成兩層樓台堅固異常，巍峨寬闊的拱
形城門上方，鏤著「岳陽」兩個紅漆大字。南面是一條林蔭大道，通向
衡陽。
LONG );
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
        set("objects", ([
                CLASS_D("gaibang")+"/bangzhong" : 3,
                CLASS_D("gaibang")+"/li-chunlai" : 1,
        ]));
        set("exits", ([
                "north"     : __DIR__"nanjie",
                "southeast" : "/d/henshan/hsroad8",
        ]));
	set("coor/x", -6200);
	set("coor/y", -3030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}