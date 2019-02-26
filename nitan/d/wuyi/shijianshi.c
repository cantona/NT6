// Room: /d/wuyi/shijianshi.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "試劍石");
        set("long", @LONG
四曲溪北的試劍石，相傳是當年控鶴仙人試劍時劈開的。石上留下
的裂痕，平直而整齊。宋朝李綱題字道：“煉氣為金鑄成劍，且將玩石
試青萍。”這裏附近的溪流叫小九曲。曲折蜿蜒，簡直就是九曲溪的縮
影一般。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"xiandiaotai",
                "south" : __DIR__"4qu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1370);
        set("coor/y", -5000);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
