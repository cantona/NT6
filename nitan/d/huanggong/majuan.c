// majuan.c.c 馬圈

inherit ROOM;

void create()
{
        set("short", "馬圈");
        set("long", @LONG
皇家馬圈, 自然是好馬雲集. 一排排齊整的馬廄, 一匹匹英挺高頭
俊馬, 讓你不由想起大草原上萬馬奔騰的壯偉景象.
LONG
        );
        set("exits", ([
                "east" : __DIR__"yuhuayuan2",
        ]) );
        set("objects", ([
                "/d/beijing/npc/yucongma" : 1,
        ]) );
	set("coor/x", -2830);
	set("coor/y", 7731);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}