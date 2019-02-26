// Room: /d/yanping/dongta.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "東塔");
        set("long", @LONG
東塔竣於明萬曆三十五年六月，矗立於鯉魚山頂，高九丈，同西塔
式樣裝飾完全一樣，是七層八角實心青石塔。相傳當時有妖作怪，毀寶
山，污靈水，有人便以妖怪怕火，正好建、西二溪在此交會如“人”字，
便建此雙塔構築成“火”字形，以火驅邪鎮妖。
LONG );
        set("exits", ([
                "northdown" : __DIR__"liyuding",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yanping");
        setup();
        replace_program(ROOM);
}