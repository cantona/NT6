// Room: /d/huanggong/dafotang.c

inherit ROOM;

void create()
{
        set("short", "大佛堂");
        set("long", @LONG
這是慈寧宮後的大佛堂。堂裡供著一尊如來佛像，佛像前是一張供
桌。桌上點著盞油燈。
LONG );
        set("exits", ([
                  "south" : __DIR__"cininggong",
        ]));
        set("objects", ([
                  __DIR__"npc/maodongzhu": 1,
                  __DIR__"npc/liuyan": 1,
        ]));
	set("coor/x", -2830);
	set("coor/y", 7751);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}