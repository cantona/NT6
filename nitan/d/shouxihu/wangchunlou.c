// Room: /yangzhou/wangchunlou.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short","望春樓");
        set("long",@LONG
望春樓位於瘦西湖東岸，與熙春台隔湖相望。面西五楹，二層，七
架樑，歇山板瓦頂。樓上下皆為四面廊。下層南北兩間作樓梯過道，分
別綴以水院、山庭，將山水景石引入室內。底層兩側山牆置木刻落地罩
門，雕刻鬆、竹、梅、蘭紋飾。兩柱懸掛韋莊和蘇某人集句楹聯(lian)。
樓四周為青磚鋪砌露台，周以石欄。樓上欄板鑿雲月圖案，雲紋柱頭，
樓頭沿牆疊黃石山子。
LONG );
        set("item_desc", ([
                "lian" : HIM"
        才        更
        看        逢
        早        晴
        春        日
        鶯        柳
        出        含
        谷        煙
\n"NOR,
        ]));
        set("exits", ([
                "north" : __DIR__"changdi3",
                "east"  : __DIR__"baitaqingyun",
                "west"  : __DIR__"ershisiqiao",
                "up"    : __DIR__"wangchunlou2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -30);
        set("coor/y", 100);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}