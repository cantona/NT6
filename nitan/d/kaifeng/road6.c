inherit ROOM;

void create()
{
        set("short", "御街");
        set("long", @LONG
御街是橫貫開封的主要街道，也是皇上出巡的要道。街道兩邊店
鋪亭台不斷，小販叫賣，行人來往，車馬喧譁，一派繁華，東面一座
高的鐵塔就是有名的開封鐵塔。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"jieying",
                  "south" : __DIR__"road5",
                  "north" : __DIR__"xuandemen",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5060);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}