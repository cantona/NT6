// Room: /yangzhou/guanshaoting.c
// Last Modified by Winder on Jul. 20 2000

#include <ansi.h>;
inherit ROOM;
void create()
{
        set("short","觀芍亭");
        set("long",@LONG
玲瓏花嬌為芍藥牡丹園，取“洛陽牡丹，揚州芍藥”之意。為瘦西
湖南岸，蓮性寺與熙春台之間，由觀芍亭經由曲廊連接水榭。相傳為乾
隆觀賞芍藥處。觀芍亭單檐方形，立于花壇之中，上懸鄭板橋墨跡“觀
芍亭”匾，兩柱懸掛鮑照謝眺集句楹聯(lian)。亭中頂棚為芍藥彩繪。
LONG );
        set("outdoors", "shouxihu");
        set("item_desc", ([
                "lian" : HIR"
        繁        紅
        華        藥
        及        當
        春        階
        媚        翻
\n"NOR,
        ]));
        set("exits", ([
                "northwest" : __DIR__"chongyanting",
                "southeast" : __DIR__"shuixie",
        ]));
        set("objects", ([
                "/d/village/npc/kid" : 3,
        ]));
        set("coor/x", -40);
        set("coor/y", 80);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}