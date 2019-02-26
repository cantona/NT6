// Room: /d/wuxi/southroad2.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "南長街");
        set("long", @LONG
南長街上住着許多普通的小市民，裏面三教九流的人都有，顯得十
分地繁華。青磚鋪成的道路向南北兩頭延伸。西邊的吟春書場已有不少
的年頭了，是附近的老百姓們最喜歡去的地方了。東邊一座兩層的樓房
不時地傳來陣陣浪笑，那就是這裏最有名的羣玉院了。北面是跨越運河
的三鳳橋。
LONG );
        set("outdoors", "wuxi");
        set("exits", ([
                "north" : __DIR__"sanfengqiao",
                "south" : __DIR__"southgate",
                "east"  : __DIR__"qunyu",
                "west"  : __DIR__"shuchang",
        ]));
        set("objects", ([
                        __DIR__"npc/lady2" : 1,
        ]));
        set("coor/x", 1040);
	set("coor/y", -760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}