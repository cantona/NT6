inherit ROOM;

void create()
{
        set("short", "遇真宮");
        set("long", @LONG
這裡是進入武當山的第一道宮宇遇真宮，寬敞無比，可容千人食
宿，是進香客的一大歇腳處。三豐真人曾在此結庵修煉，因此宮中供
著張三豐真人像。由于張真人閉關已久，外人不知其是否仍在人間，
民間傳說他已得道仙逝，立像膜拜。
LONG );
        set("objects", ([
                CLASS_D("wudang") + "/zhixiang": 1,
        ]));
        set("outdoors", "wudang");
        set("exits", ([
                "northdown": __DIR__"shijie1",
                "southup"  : __DIR__"wdbl",
        ]));
        set("coor/x", -370);
        set("coor/y", -200);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}