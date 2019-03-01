inherit ROOM;

void create()
{
        set("short",  "東走廊" );
        set("long", @LONG
這裡是一條幹凈的走廊，從兩面看去，可以欣賞到花園裡
的風景，只見各種假山怪石，奇花異草，足見王府之氣派。
LONG);
        set("exits", ([
                "west"   :__DIR__"dongzoulang",
                "east"   :__DIR__"xiangfan"
        ]));
        set("objects", ([
                "/d/zhongzhou/npc/jiading" : 1,
        ]));
	set("coor/x", -16820);
	set("coor/y", -7180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);         
}