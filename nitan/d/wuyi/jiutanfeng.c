// Room: /d/wuyi/jiutanfeng.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "酒壇峰");
        set("long", @LONG
酒壇峰位于五曲以南的更衣台西側，又名天柱峰。巖峰峻峭挺立，
宛如倒立的酒壇。相傳這是鐵拐李在此一怒踢翻的酒壇，流淌的瓊漿至
今余香不斷。不過，女士們卻寧可叫它醋壇峰。
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
