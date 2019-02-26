// Room: /d/wuyi/jiutanfeng.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "酒罈峯");
        set("long", @LONG
酒罈峯位於五曲以南的更衣台西側，又名天柱峯。巖峯峻峭挺立，
宛如倒立的酒罈。相傳這是鐵枴李在此一怒踢翻的酒罈，流淌的瓊漿至
今餘香不斷。不過，女士們卻寧可叫它醋罈峯。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"gengyitai",
        ]));
        set("objects", ([
                "/d/taishan/npc/seng-ren" : 1,
        ]));
        set("coor/x", 1350);
        set("coor/y", -5030);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
