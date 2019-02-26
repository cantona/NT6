// Room: /city/biaoju.c

inherit ROOM;

void create()
{
        set("short", "福威鏢局");
        set("long", @LONG
朱漆大門上茶杯大小的銅釘閃閃發光，門頂匾額寫着“福威鏢局”
四個金漆大字，下面橫書“總號”兩個小字。進門處兩排長凳，分坐八
名勁裝漢子，個個腰板筆挺，顯出一股英悍之氣。
LONG );

        set("exits", ([
                "south" : __DIR__"xidajie",
                "enter" : __DIR__"biaojudy",
        ]));
        set("objects", ([
                __DIR__"npc/chenqi" : 1,
                __DIR__"npc/baier" : 1,
        ]));
	set("coor/x", -100);
	set("coor/y", -6170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}