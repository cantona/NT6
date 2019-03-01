// Room: /d/wuxi/eastroad1.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "東林路");
        set("long", @LONG
寬闊的青石板街道打掃得幹幹凈凈，西邊就是城中心的三陽廣場了，
人聲鼎沸，十分熱鬧。相比起來這裡就顯得冷清了許多，這是因為北面
正是無錫的知府衙門，漆紅的官門八字敞開，一面大紅鼓正對路中心，
一股威嚴之氣讓人不由地放輕聲音，加快腳步。南邊是駐軍練兵的練兵
場，一直通向軍營。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"yamen",
                "south" : __DIR__"zhengbing",
                "east"  : __DIR__"eastroad2",
                "west"  : __DIR__"guangchang",
        ]));
        set("coor/x", 1050);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}