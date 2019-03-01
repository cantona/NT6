// Room: /d/yueyang/beijie.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "北街");
        set("long", @LONG
這是一條又長又寬的青石大道，由于地處城北，因此也顯得清凈一
些。街西面，有一家藥舖，打著一個膏藥旗，大書“同仁堂”三字，下
面很不起眼地添上“分號”二字。東邊是個小雜貨舖。
LONG );
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"zahuopu",
                "west"  : __DIR__"yaopu",
                "south" : __DIR__"zhongxin",
                "north" : __DIR__"beimen",
        ]));
        set("objects", ([
                __DIR__"npc/xingren" : 1,
                CLASS_D("gaibang")+"/bangzhong" : 1,
        ]));
	set("coor/x", -6200);
	set("coor/y", -3000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}