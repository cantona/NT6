// Room: /d/suzhou/baodaiqiao.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "寶帶橋");
        set("long", @LONG
寶帶橋橫跨于蘇州的運河之上，又因橋形宛若長帶，被稱為長橋。
橋面寬闊，行人在橋上來往，橋邊有城裡的小販吆喝、叫賣著，熙熙攘
攘，熱鬧非凡。寶帶橋臥于碧波之上，相應生輝，分外多嬌。這裡是中
秋賞月的一處絕佳之地。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "northeast" : __DIR__"dongdajie1",
                "northwest" : __DIR__"xidajie1",
                "north"     : __DIR__"canlangting",
                "south"     : __DIR__"nandajie1",
                "west"      : __DIR__"yingbin-lou1",
        ]));
        set("objects", ([
                __DIR__"npc/seller": 1,
                "/clone/npc/walker"  : 1,
        ]));
	set("coor/x", 1110);
	set("coor/y", -1060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}