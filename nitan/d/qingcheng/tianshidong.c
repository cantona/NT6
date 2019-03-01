// Room: /qingcheng/tianshidong.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "天師洞");
        set("long", @LONG
天師洞以東漢張陵在此講道修煉而得名，又名古常道觀。洞在
山腰混元頂下峭壁間。中塑天師像，沿巖壁有廊可通。正殿名三皇
殿，重檐回廊，雄踞高台，氣勢宏偉。內供伏羲、神農、軒轅三皇
石刻造像。
LONG );
        set("exits", ([
                "northup"  : __DIR__"gulongqiao",
                "north"    : __DIR__"sanqingdian",
                "eastdown" : __DIR__"path2",
                "west"     : __DIR__"yinxing",
                "east"     : __DIR__"sandaoshi",
        ]));
        set("objects", ([
                __DIR__"npc/dizi" : random(3),
        ]));
        set("coor/x", -8100);
        set("coor/y", -910);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}