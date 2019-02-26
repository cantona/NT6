// Room: /d/wuyi/shuiguishi.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "水龜石");
        set("long", @LONG
七曲北角，有兩塊重疊的巖石，以其獨特的情態和逼真的形狀，把
一對上下水龜嬉戲的靈性舒展得淋漓盡致：一隻潛在水裏，只露出腦袋
和脊背。另一隻爬在它的脊背上，朝水下伸出長長的脖頸。兩塊無識的
石塊騰動着生命的律動，讓人驚歎稱絕。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "northwest" : __DIR__"7qu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1350);
        set("coor/y", -5020);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
