// Room: /d/huijiang/xiaoxi.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set ("short", "小溪流");
        set ("long", @LONG
在差刺交錯的巖石之間流淌的一條小溪流。清澈的河底是光滑的鵝
卵石。流淌的溪水微微帶着香氣，溪水中無數小塊碎冰互相撞擊，發出
清脆聲音，叮叮咚咚，宛如仙樂。
LONG);
        set("exits", ([ /* sizeof() == 2 */
                "northup" : __DIR__"xiaoxi1",
                "east"    : __DIR__"gebi2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huijiang");
        set("coor/x", -50020);
        set("coor/y", 9000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}