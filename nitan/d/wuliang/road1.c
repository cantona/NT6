// Room: /wuliang/road1.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "甬道");
        set("long", @LONG
這裡是劍湖宮內的甬道。前通宮門，後連正廳。自于大宋仁過年
間分為三宗之後，每隔五年，三宗門下弟子便在劍湖宮中比武鬥劍，
獲勝的一宗得在劍湖宮居住五年，至第六年上重行比試。五場鬥劍，
贏得三場者為勝。由于比武關系重大，這正廳自分宗以後就一直是練
武廳。
LONG );
        set("outdoors", "wuliang");
        set("no_clean_up", 0);
        set("valid_startroom", 1);
        set("exits", ([
                "out"     : __DIR__"jianhugate",
                "northup" : __DIR__"zhengting",
        ]));
        set("coor/x", -71000);
        set("coor/y", -79900);
        set("coor/z", 90);
        setup();
        "/clone/board/wuliang_b"->foo();
}