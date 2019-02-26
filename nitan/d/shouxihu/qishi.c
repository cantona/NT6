// Room: /yangzhou/qishi.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","棋室");
        set("long",@LONG
棋室面東三楹，北側接廊通月觀後門，中間內懸尉天池題“棋室”
匾，外中柱懸掛康殷所書楹聯(lian)。室內陳列瓷繪屏風一樘，十二片，
紅木框，樟木膛。瓷繪青花山水、博古，周飾古錢浮雕，瓷繪精良，裝
飾美觀，四壁懸掛四條彩繪瓷屏，瓷繪八仙人物，亦為稀有之物。
    室內一樘小靠紅木傢俱海梅為框，櫻木為膛，條桌還飾以黃楊木雕
紋飾，做工精美。擺設有“魚紋音石”，敲擊聲聲似編鐘。
LONG );
        set("outdoors", "shouxihu");
        set("item_desc", ([
                "lian" : "
        青        紫
        山        褥
        載        傳
        酒        杯
        呼        近
        棋        笛
        局        休
\n",
        ]));
        set("exits", ([
                "west"  : __DIR__"changchunling",
                "east"  : __DIR__"yueguan",
                "south" : __DIR__"qinshi1",
        ]));
        set("objects", ([
                "/d/changan/obj/chess" : 1,
        ]));
        set("coor/x", 20);
        set("coor/y", 110);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}