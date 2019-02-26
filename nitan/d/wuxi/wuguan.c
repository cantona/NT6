// Room: /d/wuxi/wuguan.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "武館");
        set("long", @LONG
你走進來，立刻就被這裏生機勃勃的景象給吸引住了，大門口正豎
着一根旗杆，懸一幅黑底杏黃邊的大旗，書着一個大大的“武”字。方
圓數百里之內的好武弟子都來這裏學藝，裏面的練武場上喊聲陣陣。館
主秦教頭無門無派，祖傳的十八般武藝，也算這一帶的好手了。
LONG );
        set("exits", ([
                "west" : __DIR__"northroad2",
                "east" : __DIR__"wuchang",
        ]));
        set("objects", ([
                __DIR__"npc/dizi" : 2,
        ]));
        set("coor/x", 1050);
	set("coor/y", -700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}