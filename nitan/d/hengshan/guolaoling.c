// Room: /d/hengshan/guolaoling.c
// Date: Oct. 2 1997 by That

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "果老嶺");
        set("long", @LONG
光滑的巖面上斷續分布著行行馬蹄形凹坑，坑徑三四寸，深寸許。
傳說這就是當年八仙中的張果老在恆山修道時，騎小毛驢由此登天。由
于路陡坡滑，他不得不牽驢步行，留下這些腳印。後人詩雲：“盤跚雲
路嶺頭那，凹石相傳果老過，想是婆心來度世，故留遺跡使人摩。”
LONG);
        set("exits", ([ /* sizeof() == 4 */
                "northup"   : __DIR__"beiyuemiao",
                "westdown"  : __DIR__"tongyuangu",
                "southwest" : __DIR__"hufengkou",
        ]));
        set("outdoors", "hengshan");
        set("no_clean_up", 0);
        set("coor/x", 30);
        set("coor/y", 3160);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}
