// Room: /d/wuyi/baiyunyan.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "白雲巖");
        set("long", @LONG
白雲巖位于九曲盡頭。山上白雲寺，距今已經一千五百年了。全寺
分為四層依巖而建，紅牆雕欄，氣勢宏偉。登上白雲巖頂，只見古木參
天，翠竹竟秀。俯看山下，九曲清溪，竹筏悠悠，真有仙凡感覺。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "northeast"  : __DIR__"path9",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1350);
        set("coor/y", -4960);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
