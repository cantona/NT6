// Room: /d/quanzhou/yuetai.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "月台廣場");
        set("long", @LONG
這是平坦光滑的石面廣場，中間凸起一台面，面放置一焚吊爐。台
座邊嵌着七十二幅獅身人面青石浮雕，有着濃厚的異國風味。東西各有
一座恢宏的石塔。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"dongta",
                "west"  : __DIR__"xita",
                "south" : __DIR__"dxbaodian",
                "north" : __DIR__"jietang",
        ]));
	set("coor/x", -920);
	set("coor/y", -7630);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}