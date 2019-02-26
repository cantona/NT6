// dongmen.c 東門
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "東門");
        set("long", @LONG
這裏是漢中鎮的東門，眼前城牆高聳，牆上的箭垛裏好像還有
人走來走去。陽光照來，城牆上閃過幾道白光，似乎是兵器反射出
的光。城門上題着‘東門’兩個大字，門口站着一些官兵，正手持
兵刃盤問着來往的行人們。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "east" : __DIR__"guandao2",
                "west" : __DIR__"dongjie",
        ]));
        set("objects", ([
                __DIR__"npc/wujiang" : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -12230);
	set("coor/y", 810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}