// Room: /d/huanggong/longzongmen.c

inherit ROOM;

void create()
{
        set("short", "隆宗門");
        set("long", @LONG
此門是通往宮外西路的大門. 外西路是太後的居所. 隆宗門外就是
慈寧宮了.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 6 */
                 "northeast" : __DIR__"qianqingmen",
                 "southeast" : __DIR__"baohedian",
                 "south"     : __DIR__"yongxiang1",
                 "west"      : __DIR__"ciningmen",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2820);
	set("coor/y", 7731);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}