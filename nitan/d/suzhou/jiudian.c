// Room: /d/suzhou/jiudai.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "春在樓");
        set("long", @LONG
這是一座蘇州城裏有名的酒樓，整個樓面以雕刻為特色，磚雕，木
雕，石雕。走進樓內，一眼便看到一副八仙上壽圖，八仙人被描畫的惟
妙惟肖。樓內許多南北來往的門客正在聊天品茶，只見店小二忙的不亦
樂乎。
LONG );
        set("outdoors", "suzhou");
//        set("no_clean_up", 0);
        set("exits", ([
                "west"      : __DIR__"beidajie2",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer2": 1,
        ]));
	set("coor/x", 1120);
	set("coor/y", -1030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}