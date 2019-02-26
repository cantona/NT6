// Room: /yangzhou/lunlian.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "綠筱淪漣");
        set("long", @LONG
綠筱淪漣在湖上草堂之西，面西三楹，三面廊兩山各開方窗。館內
懸陳重慶題書“綠筱淪漣”匾，跋曰：“此處舊名綠蔭館，二分竹，三
分水，至佳境也。取康樂詩句，改題此額。”館門外懸“綠蔭館”匾。
外柱懸有一楹聯(lian)。
    館前平台圍以石欄，台中植一對黑松，虯曲蒼勁。鬆間置一方石壺，
上刻“小蓬壺”，並有篆文：“借山疊石因成趣，種竹依花為有香”。
由綠柳堤西行逕達吹台。
LONG );
        set("outdoors", "shouxihu");
        set("item_desc", ([
                "lian" : HIG"
        四        三
        面        更
        綠        畫
        蔭        船
        少        穿
        紅        藕
        日        花
\n"NOR
        ]));
        set("exits", ([
                "east"  : __DIR__"caotang",
                "south" : __DIR__"pingtai2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 10);
        set("coor/y", 140);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}