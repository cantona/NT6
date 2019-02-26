// shanlu6.c
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這條山路盤着終南山主峯而上，山路貼着石璧鑿出，只容許一人得
過，形勢極為險峻。往遠處望去。羣山環繞，列於腳下，百里美景盡收
眼底，頓時令人豪氣陡聲，想要長嘯一聲。往東下和北上各是一條山路。
往南下是白馬潭。
LONG        );
        set("outdoors", "gumu");
        set("exits", ([
                "northup"   : __DIR__"shanlu5",
                "eastdown"  : "/d/quanzhen/shanlu13",
                "southdown" : __DIR__"baimatang",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3190);
        set("coor/y", 110);
        set("coor/z", 140);
        setup();
        replace_program(ROOM);
}