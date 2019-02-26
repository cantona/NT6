// Room: /d/huangshan/shisun.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "石筍槓");
        set("long", @LONG
這裏石柱林立，形同竹筍，千姿百態。每當黎明破曉，旭日東昇，
朝霞遍染羣峯，煙雲迷漫深壑，這種神奇瑰麗的畫面使得慕名而來的人
心悦誠服。
LONG
        );
        set("exits", ([ 
                "southwest" : __DIR__"sanhua",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huangshan");
        set("coor/x", -585);
        set("coor/y", -1010);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}