// Room: /yangzhou/fengting.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "風亭");
        set("long", @LONG
風亭高處巔頂，為重檐四角亭，花崗巖石柱，板瓦頂，白石地坪，
井藻繪鳳吹牡丹，四周畫百鳥朝鳳圖案，檐間懸道光太傅阮元所題“風
亭”匾，兩柱懸掛王茂如所撰楹聯(lian)。上山沿嶺脊兩側栽有百年古
柏數十株。登上此亭，南望市廛，北眺蜀岡，左右湖山盡收眼底。
LONG );
        set("outdoors", "shouxihu");
        set("exits", ([
                "westdown"   : __DIR__"pingtai1",
                "southdown"  : __DIR__"yueguan",
        ]));
        set("item_desc", ([
                "lian" : HIY"
        風        亭
        月        台
        無        依
        邊        舊

        到        羨
        此        他
        胸        煙
        懷        水
        何        全
        似        收
\n"NOR,
        ]));
        set("no_clean_up", 0);
        set("coor/x", 30);
        set("coor/y", 120);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}