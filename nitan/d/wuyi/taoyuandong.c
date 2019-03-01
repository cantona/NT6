// Room: /d/wuyi/taoyuandong.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "桃源洞");
        set("long", @LONG
“喜無樵子復觀弈，怕有漁郎來問津”。曲徑通幽，翠竹掩映，山
門洞開，豁然開朗。這裡就是六曲北岸鬆鼠澗盡頭的小桃源。巨石相倚
的小洞，僅容一人通過。輾轉進入石門，門上鐫刻“桃源洞”三字。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "enter"  : __DIR__"taohuayuan",
                "south"  : __DIR__"path7",
                "north"  : __DIR__"path8",
                "eastup" : __DIR__"tianyoupath2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1370);
        set("coor/y", -4970);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
