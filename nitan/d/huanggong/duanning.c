// Room: /d/huanggong/duangning.c

inherit ROOM;

void create()
{
        set("short", "端凝殿");
        set("long", @LONG
這是皇上貯存冠袍帶履和轎輿的端凝殿.
LONG
        );
        set("exits", ([
                "west" : __DIR__"qianqinggong",
        ]));
        set("objects", ([
                __DIR__"npc/wenyoudao" :1,
        ]));
	set("coor/x", -2800);
	set("coor/y", 7751);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}