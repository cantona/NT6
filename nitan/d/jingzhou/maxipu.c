//Edited by fandog, 02/18/2000

inherit ROOM;
void create()
{
        set("short", "麻溪鋪");
        set("long", @LONG
這是在湘西沅陵南郊的麻溪鄉下，在小溪旁、柳樹邊的三間小屋之
前，是一個曬穀場。屋前矮凳上坐着一個老頭兒，嘴裏咬着一根短短的
旱煙管，手中正在打草鞋。淡淡陽光穿過他口中噴出來的一縷縷青煙，
照在他滿頭白髮、滿臉皺紋之上，但他向你瞥上一眼時，眼中神光炯然，
凜凜有威，看來他的年紀其實也並不很老，似乎五十歲也還不到。
LONG );
        set("exits", ([
                "east"   : __DIR__"caidi1",
                "north"  : __DIR__"tiandi",
                "westup" : __DIR__"tulu4",
        ]));
        set("objects", ([
                __DIR__"npc/qichangfa" : 1,
        ]));
        set("outdoors", "jingzhou");
        set("coor/x", -7120);
	set("coor/y", -2180);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}