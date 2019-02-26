// Room: /d/xiangyang/westjie1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
這是一條寬闊的青石板街道，向東西兩頭延伸。西邊是一個大十
字街口。東面是襄陽的中央廣場，北邊是人稱郭大俠郭靖的府邸大門，
不時地有人從那裏進進出出。南面是一家當鋪，聽説裏面常能買到你
所需的東西。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "east"  : __DIR__"guangchang",
                "west"  : __DIR__"westjie2",
                "south" : __DIR__"dangpu",
                "north" : "/d/wuguan/guofu_gate",
        ]));
        set("objects", ([
                __DIR__"npc/poorman" : 1,
        ]));
        set("coor/x", -7830);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
