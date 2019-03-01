// Room: /d/wuxi/sanfengqiao.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "三鳳橋");
        set("long", @LONG
眼前一座單孔拱橋，象一道彩虹跨在南長街上，橋的兩側下方長滿
了青苔，深深的水痕顯示羊雨季時的水位。橋面上古老的青磚和兩旁的
條石都在訴說著它悠久的歷史。從橋上看下去，下面是穿越城市的運河
不少畫舫在運河中遊弋，一到夜幕降臨，河水中星星點點，恰似天上的
繁星。喧鬧之聲從橋的南北兩頭不斷傳來。
LONG );
        set("outdoors", "wuxi");
        set("exits", ([
                "south" : __DIR__"southroad2",
                "north" : __DIR__"southroad1",
        ]));
        set("objects", ([
                "/d/city/npc/liumangtou" : 1,
        ]));
        set("coor/x", 1040);
	set("coor/y", -750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}