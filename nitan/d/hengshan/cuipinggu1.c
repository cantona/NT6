// Room: /d/hengshan/cuipinggu1.c
// Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
        set("short", "翠屏谷");
        set("long", @LONG
渾河在谷中沖刷而過，天峰嶺和翠屏山分列峽谷兩側，絕壁千仞，
猶如刀削斧劈，高聳入雲，這裡自古就是塞外通往內地的嚥喉要道，真
有一夫當關萬夫莫開之勢。
LONG
        );
        set("exits", ([
                "southeast"  : __DIR__"cuipinggu2",
                "northwest"  : __DIR__"jinlongxia",
        ]));
        set("objects", ([
                CLASS_D("hengshan")+"/wen" : 1,
        ]));
        set("outdoors", "hengshan");
//        set("no_clean_up", 0);
        set("coor/x", -10);
        set("coor/y", 3190);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
