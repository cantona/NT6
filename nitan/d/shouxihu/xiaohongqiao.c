// Room: /yangzhou/xiaohongqiao.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","小紅橋");
        set("long",@LONG
小紅橋是一座木制拱橋，是相對大紅橋而名，此橋南接桃花塢，北
連小金山。瘦西湖原為揚州蜀岡山水流入運河的河道妝點而成。湖面瘦
小清秀，得名瘦西湖。遊程曲折，水樹交映，亭台別致，歷代疏濬治理，
建造園林，遂成秀麗風光一片。
LONG );
        set("outdoors", "shouxihu");

        set("exits", ([
                "northup" : __DIR__"changchunling",
                "south"   : __DIR__"taohuawu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 80);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}