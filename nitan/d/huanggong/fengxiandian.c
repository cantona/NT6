// Room: /d/huanggong/fengxiandian.c

inherit ROOM;

void create()
{
        set("short", "奉先殿");
        set("long", @LONG
奉先殿是皇宮中至要之所. 殿裏供奉着歷代皇帝的圖像. 一旦有何
重大決策, 皇帝都會親自來此, 奉告列祖列宗. 擒拿敖拜之策就是在這
裏定下的.
LONG
        );
        set("exits", ([
                "south"     : __DIR__"fengxianmen",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2800);
	set("coor/y", 7761);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}