// Room: /yangzhou/xichuntai.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short","熙春台");
        set("long",@LONG
熙春台面東三楹，二層重檐，前加抱廈，七架樑，歇山，上覆鉻綠
琉璃瓦，脊飾龍藻圖案，飛甍反宇。四面廊，樓層四周圍以檻窗，以便
遠眺二十四橋和湖山勝景。底層，上懸康殷手書“春台祝壽”匾額，兩
柱懸掛江湘嵐楹聯(lian)。迎面有巨幅“玉女月夜吹簫圖”，為揚州漆
畫工藝品。漆畫前設置漆器琴桌和圓凳，可演奏古箏。
LONG );
        set("item_desc", ([
                "lian" : HIM"
勝地據淮南，看雲影當空，與水平分秋一色
扁舟過橋下，聞簫聲何處，有人吹到月三更
\n"NOR,
        ]));
        set("exits", ([
                "eastdown" : __DIR__"pingtai5",
                "up"       : __DIR__"xichuntai1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -60);
        set("coor/y", 100);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}