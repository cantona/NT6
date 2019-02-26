// Room: /d/huangshan/guanpu.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "觀瀑亭");
        set("long", @LONG
這是一座六方翹角，頂覆琉璃的小亭，坐在這裏，可以遠觀黃山三
大名瀑之一的“百丈泉”，由此看百丈泉，只見清潭，紫雲二峯有飛泉
傾泄，勢如銀河天降，雨少時，如輕紗薄霧，雨足時則如千匹白練，高
懸天際，實在美不勝收。
LONG
);
        set("exits", ([ 
                "westdown" : __DIR__"wenquan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huangshan");
        set("coor/x", -595);
        set("coor/y", -1100);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}