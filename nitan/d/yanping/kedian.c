// Room: /d/yanping/kedian.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "山野客店");
        set("long", @LONG
山野客店十分簡陋。一個小二臨台買賣，一片破門扇撲在地上，顯
得相當忙亂。櫃台上貼著個牌子(paizi)。
LONG );
        set("exits", ([
                "east" : __DIR__"erbapu",
        ]));
        set("item_desc", ([
                "paizi" : "即日起只供應吃喝，不留宿。\n",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer2" : 1,
        ]));
        set("coor/x", 1490);
        set("coor/y", -4000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}