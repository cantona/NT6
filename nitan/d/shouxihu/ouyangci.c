// Room: /yangzhou/ouyangci.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short","歐陽祠");
        set("long",@LONG
歐陽祠又名歐陽文忠公祠，位于谷林堂後，為紀念歐陽修知揚州之
政德而建。光緒間，兩淮鹽運使歐陽正墉集資重建，並題書“六一宗風”
匾，薛時雨撰楹聯(lian)。歐陽修別號“六一居士”，因其自謂家藏書
一萬卷，集錄三代以來金石遺文一千卷，有琴一張，棋一局，常置酒一
壺，加上自己老于此五物之間一老翁，是為“六一”，故歐陽祠又稱六
一祠。
    祠中後壁嵌有歐陽修畫像刻石，畫像傳神，胡須部分刀法精巧，形
成光線折射，產生遠看為白，近看為黑的視覺效果，常使遊人稱奇。
誼。
LONG );
        set("item_desc", ([
                "lian" : "
        遺構溯歐陽，公為文章道德之宗，侑客傳花，也自徜徉詩酒
        名區冠淮海，我從豐樂醉翁而至，攜雲載鶴，更教曠覽江山
\n",
        ]));
        set("exits", ([
                "south" : __DIR__"gulintang",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -40);
        set("coor/y", 180);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}