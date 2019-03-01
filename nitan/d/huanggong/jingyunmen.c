// Room: /d/huanggong/jingyunmen.c

inherit ROOM;

void create()
{
        set("short", "景運門");
        set("long", @LONG
此門是通往宮外東路的大門. 外東路是太上皇的居所. 景運門外空
地上有一座箭亭, 又稱紫金箭亭, 皇上常在這和王公大臣們一齊射箭, 
操練武藝。
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 6 */
                 "northwest" : __DIR__"qianqingmen",
                 "southwest" : __DIR__"baohedian",
                 "south"     : __DIR__"yongxiang4",
                 "east"      : __DIR__"jianting",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2800);
	set("coor/y", 7731);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}