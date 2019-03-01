inherit ROOM;

void create()
{
        set("short", "朱雀門");
        set("long", @LONG
這是內城的城門，高大的城牆用大青磚彌合米汁而成，時間的沖
刷使得牆磚變為鐵青色。東西兩邊是角樓，南面不遠處就是大相國寺
的八寶琉璃殿。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"road",
                  "north" : __DIR__"road2",
                  "westup" : __DIR__"jiaolou",
                  "eastup" : __DIR__"jiaolou2",
        ]));
        set("objects", ([
                  __DIR__"npc/guanbing" : 2,
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5050);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}