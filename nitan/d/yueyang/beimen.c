// Room: /d/yueyang/beimen.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "岳陽北門");
        set("long", @LONG
這裡是岳陽城的北門。青石築成兩層樓台堅固異常，巍峨寬闊的拱
形城門上方，鏤著「岳陽」兩個紅漆大字。北面是一條黃土路，直通江
陵。
LONG );
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
        set("exits", ([
                "south"     : __DIR__"beijie",
                "northwest" : "/d/jingzhou/tulu2",
        ]));
        set("objects", ([
                CLASS_D("gaibang")+"/bangzhong" : 1,
        ]));
	set("coor/x", -6200);
	set("coor/y", -2990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}