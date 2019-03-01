// Room: /d/yanping/fuqiao1.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "水東浮橋");
        set("long", @LONG
延平府城山環水繞，詩譽“山圍八面綠，水繞二江青”，建溪和西
溪分從北、西兩面環繞城郭，再匯集東去。此浮橋便是架設在建溪上的
行旅必經之處了。整列浮橋由幾十條小船串接鐵鏈而成，上面再覆以木
板，方便人馬通行。
LONG );
        set("exits", ([
                "eastup" : __DIR__"mazhan",
                "westup" : __DIR__"dongmen",
        ]));
        set("outdoors", "yanping");
        set("coor/x", 1530);
        set("coor/y", -6170);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}