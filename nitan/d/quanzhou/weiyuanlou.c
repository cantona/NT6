// Room: /d/quanzhou/weiyuanlou.c
// Last Modified by winder on May. 29 2001

inherit ROOM;
string look_gaoshi();

void create()
{
        set("short", "威遠樓");
        set("long", @LONG
這是泉州的北門城樓，青石築成兩層樓台堅固異常，巍峨寬闊的拱
形城門上方，鏤着「泉州」兩個紅漆大字。城牆上貼着一張泉州官府告
示(gaoshi)。過了此門就是北邊蜿蜒崎嶇的清源山區了。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "south" : __DIR__"northroad3",
                "north" : __DIR__"shanlu6",
        ]));
        set("item_desc", ([
                "gaoshi" : (:look_gaoshi:),
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
	set("coor/x", -900);
	set("coor/y", -7630);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n靖海將軍\n施琅\n";
}