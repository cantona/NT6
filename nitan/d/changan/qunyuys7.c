//Room: qunyuys6.c

inherit ROOM;

void create()
{
        set("short", "群玉樓雅室");
        set("long", @LONG
一間雅室。房中放著一張大床，床上舖著繡花的錦被和枕頭。湘
繡馳名天下，大紅錦被上繡的是一對戲水鴛鴦，顏色燦爛，栩栩欲活。
幾上點著一根紅燭，紅燭旁是一面明鏡，一只梳妝箱子。床前地下兩
對繡花拖鞋，一對男的，一對女的，並排而置。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "east" : "/d/changan/qunyulou3",
        ]));
        set("objects", ([
                "/d/changan/npc/fenyi" : 1,
        ]) );

        set("coor/x", -10720);
	set("coor/y", 1950);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}