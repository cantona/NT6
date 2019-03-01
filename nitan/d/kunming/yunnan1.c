inherit ROOM;

void create()
{
        set("short", "紅土路");
        set("long", @LONG
進入雲貴高原，泥土變為了紅色，空氣變得更清新，放眼
看去，只見周圍那綿綿的原始森林不見邊際，你頓時覺得心高
志遠，一股豪起湧了上來，想要做一方大事業。
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "south" : __DIR__"yunnan2", 
               "northeast"  : "/d/jingzhou/tulu2",
                "west" : __DIR__"zhaoze",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -16760);
	set("coor/y", -7160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}