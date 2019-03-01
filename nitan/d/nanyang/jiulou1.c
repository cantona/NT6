// Room: /d/nanyang/jiulou1.c
// Last Modified by winder on Nov. 20 2001

inherit ROOM;

void create()
{
        set("short", "迎賓樓");
        set("long", @LONG
方圓數百裡內提起迎賓樓可以說是無人不知，無人不曉。當年蘇
學士雲遊到此，對迎賓樓的素齊讚不絕口，欣然為其題匾，流下一段
傳遍海內的佳話，從此迎賓樓名聲大震。樓下布置簡易，顧客多是匆
匆的行人，買點包子，雞腿、米酒就趕路去了。樓上是雅座。
LONG );
        set("region", "nanyang");
        set("exits", ([
                "east" : __DIR__"nanyang",
                "up"   : __DIR__"jiulou2",
        ]));
        set("objects", ([
                __DIR__"npc/xiao-er2" : 1,
        ]));
        set("no_clean_up", 0);
        set("no_fight", "1");
	set("coor/x", -6950);
	set("coor/y", 770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}