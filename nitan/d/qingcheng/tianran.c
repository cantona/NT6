// Room: /qingcheng/tianran.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "天然圖畫");
        set("long", @LONG
這裏巖壁矗立，綠樹映輝，牌閣在山埡間巍然屹立。四顧峯奇
石異，雲霧縹緲，遠近觀賞，如在畫中。閣左“天生橋”，一石丈
餘飛插石壁之間，十分險峻。
LONG );
        set("outdoors", "qingcheng");
        set("exits", ([
                "eastdown" : __DIR__"path1",
                "westup"   : __DIR__"path2",
                "north"    : __DIR__"zhuhezhuang",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -8080);
        set("coor/y", -910);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}