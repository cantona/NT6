//HSQCHANGLANG.C

inherit ROOM;

void create()
{
        set("short", "洪水旗長廊");
        set("long", @LONG
你正走在一條長廊之上， 長廊蜿蜒曲折， 兩旁是如畫景象。 小
河從廊下靜靜流淌， 河面之上飄浮着淡淡的輕煙， 如霧如紗。但河
面上又靜得讓人奇怪， 似乎沒有一點生氣。
LONG );
        set("exits", ([
                "east"  : __DIR__"cangshui",
                "north" : __DIR__"hsqdating",
                "out"   : __DIR__"hsqmen",
        ]));
        set("outdoors", "mingjiao");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}