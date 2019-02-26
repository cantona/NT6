// Room: /d/yanziwu/qiuyu.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "秋雨齋");
        set("long", @LONG
秋雨齋高居山崖之上，下面十數丈就是太湖的水面了。蔓陀山莊中
秋賞月時光，藉着水音，高揚絲竹，明月當空，萬頃如銀蛇，真是無邊
景緻應時來，恍若人間仙境。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "eastdown"   : __DIR__"path19",
        ]));
        set("coor/x", 1190);
        set("coor/y", -1260);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}