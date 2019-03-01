// Room: /d/yanping/yidao1.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "閩浙驛道");
        set("long", @LONG
自古入閩無敞途。往來貨運全靠肩挑背扛，逶迤入閩，車馬不通。
古驛道沿建溪溪流南下，山巖交疊，茅草相簇，飛蠓毛蟲一路陪同，艱
苦萬狀。好在山該青處皆清，碧水清澈爽口，巨樹修竹插天，雖然一路
而來，口音漸變，倒也另有一番情趣。
LONG );
        set("exits", ([
                "northdown" : __DIR__"shandao1",
                "southup"   : __DIR__"yidao2",
        ]));
        set("objects", ([
                "/d/taishan/npc/tiao-fu" : 2,
        ]));
        set("outdoors", "yanping");
        set("coor/x", 1500);
        set("coor/y", -6000);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}