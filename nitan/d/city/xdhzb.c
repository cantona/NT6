#include <ansi.h>

inherit ROOM;

#define PLACE "yz"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "小刀會揚州總部");
        set("long", @LONG
這裏是小刀會揚州總部，外面的房間裏傳出來吆五喝六的賭博聲。
小刀會是揚州本地的一個黑幫勢力，幫主鞠老大擅長飛刀絕技，在打
敗了揚州所有地痞流氓之後，創立了小刀會，乃遠近赫赫有名的地頭
蛇。在房間的牆上有一塊牌子(look paizi)。加入小刀會的玩家，可
以在這裏選擇任務去完成。
LONG );

        set("objects", ([
               "/d/city/npc/boss-ju" : 1,
               "/d/city/npc/toumu"   : 2,
        ]));

      set("no_fight",1);

        set("exits", ([
                "out" : "/d/city/shulin1",
        ]));

        setup();
}
#include <bang_bad.h>