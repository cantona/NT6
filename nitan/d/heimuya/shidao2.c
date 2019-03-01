// shidao1.c

inherit ROOM;

void create()
{
        set("short", "石道");
        set("long", @LONG
一路上日月教教眾把守嚴密，經過三處山道，來到一處水灘之前，
西面有一道石階通往水灘。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
            "westdown" : __DIR__"xingxingtan",
            "south" : __DIR__"shidao1",
        ]));
        set("objects", ([
            __DIR__"npc/wangcheng" : 1,
            __DIR__"npc/heiyiren" : 2,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}