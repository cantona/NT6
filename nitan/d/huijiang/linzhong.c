// Room: /d/huijiang/linzhong.c
// Last Modified by winder on Sep. 12 2001
inherit ROOM;

void create()
{
        set ("short", "樹林中");
        set ("long", @LONG
這是樹林中的一片空地，給人為的打掃整理過，空地的中央一堆篝
火已經熄滅，邊上散落着一些牛羊的骨頭，幾塊大石塊散落在篝火的四
周。草地上留下許多人踐踏過的痕跡。
LONG);
        set("outdoors", "huijiang");
        set("exits", ([ /* sizeof() == 2 */
                "east"  : __DIR__"shulin2",
                "north" : __DIR__"shulin1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50060);
        set("coor/y", 9030);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}