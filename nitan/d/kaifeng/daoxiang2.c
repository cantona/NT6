inherit ROOM;

void create()
{
        set("short", "稻香居二樓");
        set("long", @LONG
老大一個大廳內相互間用屏風隔成十多個小間。穿戴厲索的小二
端著菜來往奔走，如果你分量夠的話，還可以撈到個窗邊的位置。邊
喝酒邊看看下面的繁華街景，人生一樂。
LONG );
        set("objects", ([
                  __DIR__"npc/gaoyanei" : 1,
                  __DIR__"npc/luyuhou" : 1,
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                  "down" : __DIR__"daoxiang",
        ]));

	set("coor/x", -5040);
	set("coor/y", 2250);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}