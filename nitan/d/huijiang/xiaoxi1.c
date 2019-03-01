// Room: /d/huijiang/xiaoxi1.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "小溪流");
        set("long", @LONG
在差刺交錯的巖石之間流淌的一條小溪流。清澈的河底是光滑的鵝
卵石。溪流兩邊的樹木開始多了起來，溪水轉彎繞過一塊高地，忽然眼
前一片銀瀑，水聲轟轟不絕，匹練有如自天而降，飛珠濺玉，頓成奇觀。
LONG
        );
        set("outdoors", "huijiang");
        set("exits", ([ /* sizeof() == 2 */
                "southdown" : __DIR__"xiaoxi",
                "westup"    : __DIR__"xiaoxi2",
        ]));
        set("objects", ([ /* sizeof() == 1 */
        ]));
        set("coor/x", -50020);
        set("coor/y", 9010);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}