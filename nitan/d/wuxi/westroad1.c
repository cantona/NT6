// Room: /d/wuxi/westroad1.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "西新街");
        set("long", @LONG
這是一條寬闊的青磚街道，與東林路一起成為貫通無錫城東西的要
道。驛馬、商販來往不絕。常有小河穿街而過，人説“三步一橋”也不
為過。智慧的吳裏工匠將橋樑與道路建築巧妙地結合在一起，使人走在
這裏一點也不覺得不便。南邊是一家有名的錢莊，開在這條路上真是既
方便了生意人，又照顧了自己的營生，裏面不時地傳來稀哩嘩啦的數錢
的聲音。北面是一家當鋪，細聽可以聽到裏壓低的討價還價的聲音。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"dangpu",
                "south" : __DIR__"qianzhuang",
                "west"  : __DIR__"westroad2",
                "east"  : __DIR__"guangchang",
        ]));
        set("coor/x", 1030);
	set("coor/y", -730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}