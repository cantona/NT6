// Room: /yangzhou/shuixie.c
// Last Modified by Winder on Jul. 20 2000

#include <ansi.h>;
inherit ROOM;
void create()
{
        set("short","花界水榭");
        set("long",@LONG
玲瓏花界水榭為面南一楹，方形，花脊，歇山板瓦頂，南設台階，
北置平台，並設白石欄板。上懸著名書法家歐陽中石手書匾。兩柱懸掛
宋之問盧照鄰集句楹聯(lian)。坐欄觀景，熙春台、望春樓、二十四橋
諸勝盡收眼底。面南兩柱懸掛王維李端集句楹聯(lian1)。
LONG );
        set("outdoors", "shouxihu");
        set("item_desc", ([
                "lian" : HIR"
        花        樓
        柳        台
        含        繞
        丹        曲
        日        池
\n"NOR,
                "lian1" : HIG"
        紅        碧
        桃        石
        綠        青
        柳        苔
        垂        滿
        檐        樹
        向        蔭
\n"NOR,
        ]));
        set("exits", ([
                "northwest" : __DIR__"guanshaoting",
                "southeast" : __DIR__"lianxingsi",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -30);
        set("coor/y", 70);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}