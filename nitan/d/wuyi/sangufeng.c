// Room: /d/wuyi/sangufeng.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "三姑峰");
        set("long", @LONG
三姑峰為一座上方開裂為三塊巨巖的峰叢，狀如三個站立的仙姑。
山下有一深潭，名叫龍潭。從潭中流下的泉水，就叫三姑泉。相傳遠古
大旱，禾苗幹枯，百姓萬般焦苦，百般求雨而蒼天充耳不聞。三個仙姑
在百姓幾近絕望之時，挺身施助，終致甘霖。但三位仙女也不能再還仙
身，化石成山，用留人間。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "northdown" : __DIR__"path5",
                "southdown" : __DIR__"path4",
                "southwest" : __DIR__"huanguyan",
        ]));
        set("objects", ([
                "/d/taishan/npc/jian-ke" : 1,
        ]));
        set("coor/x", 1400);
        set("coor/y", -4950);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
