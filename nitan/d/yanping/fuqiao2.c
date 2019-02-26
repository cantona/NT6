// Room: /d/yanping/fuqiao2.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "水南浮橋");
        set("long", @LONG
延平府城山環水繞，詩譽“山圍八面綠，水繞二江青”，建溪和西
溪分從北、西兩面環繞城郭，再彙集東去。此浮橋便是架設在西溪上通
往南岸九峯山的必經之處。整列浮橋由幾十條小船串接鐵鏈而成，上面
覆以木板，方便通行。
LONG );
        set("exits", ([
                "southup" : __DIR__"9fengshan",
                "northup" : __DIR__"yanshoumen",
        ]));
        set("outdoors", "yanping");
        set("coor/x", 1480);
        set("coor/y", -6210);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}