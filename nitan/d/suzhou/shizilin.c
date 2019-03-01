// Room: /d/suzhou/shizilin.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "獅子林");
        set("long", @LONG
你一走進獅子林，便不禁為江南蘇州園林的奇妙美景所折服。獅子
林東南多山，西北多水，素有”假山王國“之稱。假山峰巒疊嶂，曲折
盤旋，石洞連綿不斷，幽深莫測。咫尺之間，可望而不可及，變幻無窮
如入迷宮，不由得不為之讚嘆不已。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"yanyutang",
                "west"      : __DIR__"nandajie1",
                "northeast" : __DIR__"zhipoxuan",
        ]));
	set("coor/x", 1120);
	set("coor/y", -1070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}