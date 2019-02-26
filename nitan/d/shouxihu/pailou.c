// Room: /yangzhou/pailou.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","牌樓");
        set("long",@LONG
大明寺山門前建牌樓，四柱三楹，木皆香材，正上題篆體“棲靈遺
址”，背題“豐樂名區”，極顯雄偉。牌樓斗拱託頂，仰如傘蓋，下置
白玉石礎。牌樓前有一對青石正頭巨型石獅。
    大明寺因始建於南朝劉宋大明年間故名。隋代，因寺在隋宮西側，
故又名西寺。又因在寺內建九層棲靈塔，亦名棲靈寺。
LONG );
        set("outdoors", "shouxihu");
        set("objects", ([
                "/d/village/npc/boy" : 3,
        ]));
        set("exits", ([
                "northup"   : __DIR__"shanmen",
                "southdown" : __DIR__"pingshanwu",
        ]));
        set("coor/x", -30);
        set("coor/y", 130);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}