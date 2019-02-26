//Room: qunyuys4.c

inherit ROOM;

void create()
{
        set("short", "羣玉樓雅室");
        set("long", @LONG
一間雅室。房中放着一張大牀，牀上鋪着繡花的錦被和枕頭。湘
繡馳名天下，大紅錦被上繡的是一對戲水鴛鴦，顏色燦爛，栩栩欲活。
几上點着一根紅燭，紅燭旁是一面明鏡，一隻梳粧箱子。牀前地下兩
對繡花拖鞋，一對男的，一對女的，並排而置。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "west" : "/d/changan/qunyulou2",
        ]));
        set("objects", ([
                        "/d/changan/npc/qingyi" : 1,
        ]) );

        set("coor/x", -10700);
	set("coor/y", 1950);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}