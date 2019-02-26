// Room: /d/huijiang/xiaoxi2.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "湖泊");
        set("long", @LONG
轉了幾個彎，從一排參天青松中穿了出去，眼前一片大湖，湖的南
端又是一條大瀑布，水花四濺，日光映照，現出一條彩虹，湖周花樹參
差，雜花紅白相間，倒映在碧綠的湖水之中，奇麗莫名。遠處是大片青
草平原無邊無際，的延伸出去，與天相接，草地上幾百只白羊在奔跑吃
草。
LONG );
        set("outdoors", "huijiang");
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/xiangxiang" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 2 */
                "eastdown" : __DIR__"xiaoxi1",
                "north"    : __DIR__"byriver",
        ]));
        set("coor/x", -50030);
        set("coor/y", 9010);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}