// Room: /d/yanping/fengguanyan.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "鳳冠巖");
        set("long", @LONG
鳳冠巖佇立在建溪之畔，如刃立起，下臨深水。巖上懸空支起一座
禪林，號明翠閣。日日晨鐘暮鼓，全城皆沐佛號，檀香佛唱，斯民盡惠
春霖。憑閣下瞰，溪水流碧，百筏爭遊。真可謂“不出城廓而獲山水之
怡，身居鬧市而有林泉之致”。
    對岸便是馬站，有官道前往福州。
LONG );
        set("exits", ([
                "up"        : __DIR__"mingcuige",
                "south"     : __DIR__"dongmen",
                "northwest" : __DIR__"yidao3",
        ]));
        set("outdoors", "yanping");
        set("no_clean_up", 0);
        set("coor/x", 1520);
        set("coor/y", -6160);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}