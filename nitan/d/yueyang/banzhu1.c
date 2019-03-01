// Room: /d/yueyang/banzhu1.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "斑竹林");
        set("long", @LONG
這裡是一片斑竹林。湖風吹來，一陣葉響。斑竹又叫湘妃竹，晉張
曄《博物志》記載：“堯之二女，舜之二妃，曰：‘湘夫人’。帝崩，
二妃啼，以涕揮竹，竹盡斑。”《巴陵縣志》載：“君山出斑竹”。它
秀拔瑩潤，竹竿上點點雅麗的紫色斑點，施肩吾《湘竹詞》雲：“萬古
湘江竹，無窮奈怨何！年年長春筍，只是淚痕多”。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"banzhu2",
                "west"  : __DIR__"banzhu3",
                "south" : __DIR__"banzhu1",
                "north" : __DIR__"erfeimu",
        ]));
        set("coor/x", -1670);
        set("coor/y", 2290);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}