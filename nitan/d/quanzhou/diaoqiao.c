// Room: /d/quanzhou/diaoqiao.c
// Last Modified by winder on May. 29 2001

inherit ROOM;
string look_gaoshi();

void create()
{
        set("short", "新門吊橋");
        set("long", @LONG
這是泉州西面的一座吊橋，從傍著晉河而建的城樓大門上以兩個滑
輪維系。日出放下吊橋，日落絞起。城樓牆上有張官府告示(gaoshi)。
西出城門便是亂石崗，經常有土匪出沒，沒事還是別出城的好。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("item_desc", ([
                "gaoshi" : (:look_gaoshi:),
        ]));
        set("exits", ([
                "west" : __DIR__"luanshigang",
                "east" : __DIR__"xinmenji",
        ]));
	set("coor/x", -920);
	set("coor/y", -7720);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n靖海將軍\n施琅\n";
}