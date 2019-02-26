// Room: /d/mobei/lvzhou.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set ("short", "綠洲");
        set ("long", @LONG
一塊沙漠中的綠洲，雖然只有很小的一塊，但對於沙漠中的旅行者
而言卻已足夠。你終於可以停下來歇歇腳了。
LONG);
        set("outdoors","mobei");
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 2 */
                "southeast" : __DIR__"damo2",
                "north"     : __DIR__"damo",
        ]));
        set("coor/x", -210);
        set("coor/y", 5120);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}