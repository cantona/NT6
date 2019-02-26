inherit ROOM;

void create()
{
        set("short", "御街");
        set("long", @LONG
御街是橫貫開封的主要街道，也是皇上出巡的要道。街道兩邊店
鋪亭台不斷，小販叫賣，行人來往，車馬喧譁，一派繁華，南邊的高
橋就是州橋，西面是龍亭寺。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "southup" : __DIR__"road4",
                  "north" : __DIR__"road6",
                  "west" : __DIR__"longting",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5060);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}