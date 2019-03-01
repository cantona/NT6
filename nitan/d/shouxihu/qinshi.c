// Room: /city/qinshi.c
// Last Modified by Winder on Jul. 15 2000

inherit ROOM;

void create()
{
        set("short", "琴室");
        set("long", @LONG
室內兩後壁，各裝一堂透空雕花罩格，貼牆放琴幾，幾上放置盆景。
兩側布置一式雕花海梅方桌，圍以團凳。南，北，東三面牆壁，安放紅
木雕花幾座，間以瓷凳。一室明凈，一塵不染。琴室前有廊廡一架，臨
水欄檻。檻外疏柳，橫臥水際；水面微波，倒影搖曳。
LONG );
        set("exits", ([
                "southeast" : __DIR__"luqiao",
        ]));
        set("outdoors", "yangzhouw");
        set("no_clean_up", 0);
        set("coor/x", -25);
        set("coor/y", 5);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}