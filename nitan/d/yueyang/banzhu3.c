// Room: /d/yueyang/banzhu1.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "斑竹林");
        set("long", @LONG
這裡是一片斑竹林。湖風吹來，一陣葉響。斑竹又叫湘妃竹，在君
山，它多長在斑竹山上。清初施閨章在《江行雜詠》中寫有《見斑竹》
的觀感： “碧玉森森綠水灣，風鳴環佩滿湘山。遊人自洒離愁淚，不
是當年舊淚斑”。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"erfeimu",
                "west"  : __DIR__"banzhu3",
                "south" : __DIR__"banzhu1",
                "north" : __DIR__"banzhu2",
        ]));
        set("coor/x", -1680);
        set("coor/y", 2300);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}