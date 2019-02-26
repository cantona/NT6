// /guanwai/muqiao.c

inherit ROOM;

void create()
{
        set("short", "木橋");
        set("long", @LONG
這是一座年久失修的破木橋，由幾根樹幹捆紮而成。下面的河水早以結
成堅冰。這裏本是赫圖阿拉城的護城河，現已廢棄不用了。河岸北面是用黃
土堆成的城牆，很多處都已坍塌。由此向北就是赫圖阿拉城了。
LONG );
        set("exits", ([
                "north" : __DIR__"nancheng",
                "south" : __DIR__"road8",
        ]));
        set("objects", ([
                __DIR__"npc/yuzhenzi" : 1,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "guanwai");
        set("coor/x", 3990);
	set("coor/y", 9220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
