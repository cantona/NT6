// Room: /d/wuxi/zhengtang.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "衙門正廳");
        set("long", @LONG
堂上的氣氛十分肅穆。幾根紅漆楹住更是給這裏增添了幾分莊重。
正牆上懸掛一個橫匾，上書“正大光明”四個金光閃閃的大字。現在
不是升堂之時，知府正坐在雕花方案後批閲文書，師爺隨侍在後。
LONG
        );
        set("exits", ([
                "south" : __DIR__"yamen",
        ]));
        set("objects", ([
                __DIR__"npc/xia": 1,
                __DIR__"npc/shiye": 1,
        ]));
        set("coor/x", 1050);
	set("coor/y", -710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}