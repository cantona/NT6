#include <ansi.h>
inherit ROOM;

string look_shibei();

void create()
{
        set("short", "松林小路");
        set("long", @LONG
這是山腳松林中的小路，兩邊長滿參天的紅松樹，只能看見一線
天空。路旁有道士在奮力砍樹。東邊可回大道。路邊有個石碑(shibe
i)，很多遊客在圍那裏。原來西邊上去就是名鎮天下的解劍巖了，
LONG );
        set("outdoors", "wudang");
        set("item_desc", ([
                "shibei" : (: look_shibei :),
        ]));
        set("exits", ([
                "westup" : __DIR__"jiejianyan",
                "east"   : __DIR__"slxl1",
                "south"  : __DIR__"songlin1",
                "north"  : __DIR__"songlin2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -340);
        set("coor/y", -180);
        set("coor/z", 0);
        setup();
}

string look_shibei()
{
        return WHT "\n\n"
        "  ※※※※※※※※※※※※※※※※※※※※※※※※※\n"
        "  ※※※※　        　　　　　　　　　　　　※※※※\n"
        "  ※※※※" HIW "　        　武當派通告" NOR + WHT "    　　　　※※※※\n"
        "  ※※※※　                            　　※※※※\n"
        "  ※※※※" HIW "　    往前就是武當山解劍巖。所有" NOR + WHT "　※※※※\n"
        "  ※※※※" HIW "　外來人客請自覺解劍。邪魔外道到" NOR + WHT "　※※※※\n"
        "  ※※※※" HIW "　此止步。" NOR + WHT "                　　　　※※※※\n"
        "  ※※※※　　　　　                　　　　※※※※\n"
        "  ※※※※※※※※※※※※※※※※※※※※※※※※※\n\n\n" NOR;
}