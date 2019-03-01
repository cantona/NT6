// Room: /d/taishan/shenxian.c
// Last Modified by Winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "升仙坊");
        set("long", @LONG
這裡是十八盤的中間，從這裡直上南天門的一段就是緊十八盤了。
由此刻攀石而上，後面的人可以看到前面的人的鞋底，前面的人回頭則
可見到後面的人的發頂。在這裡一般人每走十來步便要稍一休息。
LONG );
        set("exits", ([
                "northup"   : __DIR__"jin18",
                "southdown" : __DIR__"jinman18",
        ]));
        set("objects", ([
                __DIR__"npc/jianchu" : 1,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 30);
	set("coor/y", 280);
	set("coor/z", 180);
	setup();
        replace_program(ROOM);
}