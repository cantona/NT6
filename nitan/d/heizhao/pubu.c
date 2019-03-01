// Room: /heizhao/pubu.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "瀑布");
        set("long", @LONG
你快步走近瀑布，只見柳樹下那人頭戴鬥笠，身披蓑衣，坐在
一塊石上，正自垂釣。這瀑布水勢湍急異常，一瀉如注，水中哪裡
有魚？縱然有魚，又哪有余暇吞餌？看那人時，見他雙目一動不動
的凝視水中。
LONG );
        set("outdoors", "taoyuan");
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("resource/water", 1);
        set("objects", ([
                CLASS_D("dali")+"/yideng/yu" : 1,
        ]));
        set("exits", ([
                "southup" : __DIR__"shanlu9",
                "enter"   : __DIR__"xiaowu",
        ]));
        set("coor/x", -5020);
        set("coor/y", -1280);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}