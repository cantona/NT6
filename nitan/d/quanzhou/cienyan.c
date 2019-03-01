// Room: /d/quanzhou/cienyan.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "賜恩巖");
        set("long", @LONG
這裡巨石綿綿，相連成片。寺宇成排，有佛殿、功德堂、許氏宗祠
等。巨石群中有兩塊大巖石昂然伸出，使底下形成一個天然石室，上刻
「高山仰止」。據稱是唐中葉泉州的進士與韓癒、陸贄等同登「龍虎榜
」的歐陽詹的讀書的書室。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "southdown" : __DIR__"shanlu5",
                "northdown" : __DIR__"shanlu4",
        ]));
	set("coor/x", -900);
	set("coor/y", -7600);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}