// Room: /d/fuzhou/xiangyang.c
// Date: May 12 1998 Java

inherit ROOM;

void create()
{
        set("short", "向陽巷");
        set("long", @LONG
這裡是福州城西向陽巷。北面有一所破敗的宅子。西面有一家雜貨
舖，專賣女人家用的東西，男人不可以進去。
LONG );

        set("exits", ([
                "east"  : __DIR__"shiqiao",
                "north" : __DIR__"laozhai",
                "west"  : __DIR__"zahuopu",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "fuzhou");
	set("coor/x", -100);
	set("coor/y", -6200);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if( dir == "west" && (query("gender", me) == "男性") && !wizardp(me) )
                return notify_fail("你個大老爺們兒去那幹嘛！！\n");
        return 1;
}