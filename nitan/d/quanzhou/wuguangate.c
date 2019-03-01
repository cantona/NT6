// Room: /d/quanzhou/wuguangate.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "武館大門");
        set("long", @LONG
一所氣派輝煌的武館。朱漆大門旁邊擺鎮了兩頭高大威猛，栩栩如
生的石獅子。門上掛著一塊黑底大匾額，四個刷金的大字「揚威武館」
閃閃生光。左邊插著一根兩丈多高的旗桿，繡著“武”字的紅旗隨風飄
揚。這便是城裡招牌最老，威信最著的武館，好多城中的子弟都在此學
些拳腳兵器功夫。館主馬五德豪富好客，頗有孟嘗之風。所聘教頭都是
一等一身具真功夫的好手。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "west" : __DIR__"kaojiaochang",
                "east" : __DIR__"zhaiqu2",
        ]));
        set("objects", ([
                __DIR__"npc/mengding" : 2,
        ]));
	set("coor/x", -920);
	set("coor/y", -7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}