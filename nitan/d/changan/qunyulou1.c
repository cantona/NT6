//Room: qunyulou1.c

inherit ROOM;

void create()
{
        set("short", "羣玉樓大廳");
        set("long", @LONG
羣玉樓大廳。三面都糊着紗窗，窗櫺縱橫交錯，分成大小格式的
花紋，每一格都有一方小玻璃鑲嵌着，顯得甚為雅緻，玻璃內燈光流
映生輝，案頭所供養的梅花，疏影橫斜，也貼在玻璃窗上。炫目的朝
陽從琉璃窗格透入，微風輕拂，縷縷幽香，沁人心脾。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "north" : "/d/changan/qunyulou",
                "up"   : "/d/changan/qunyulou2",
        ]));
        set("objects", ([
                "/d/changan/npc/lingfeixue" : 1,
        ]) );

        set("coor/x", -10710);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}