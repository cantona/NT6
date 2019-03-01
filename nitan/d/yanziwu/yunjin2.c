// Room: /d/yanziwu/yunjin2.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "雲錦二樓");
        set("long", @LONG
雲錦樓上陳設富麗，一幅中堂繪的是孔雀開屏，兩旁一副木聯，寫
的是：“漆葉雲差密，茶花雪妒妍”。往樓外望去，湖天一線，煙波浩
渺，窮極目外。近處柳條搖曳，就在眼前。
LONG );
        set("exits", ([
                "down"     : __DIR__"yunjin1",
        ]));
        set("objects", ([
                "/d/dali/obj/chahua12" :1,
        ]));
        set("coor/x", 1230);
        set("coor/y", -1260);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}