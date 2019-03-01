// Room: /d/suzhou/zhenquting.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "真趣亭");
        set("long", @LONG
真趣亭內高高懸掛御筆題寫的“真趣”匾一塊。亭內裝飾精致金碧
輝煌。樑架、圍屏、裙板上雕刻的人物、花鳥圖案惟妙惟肖。在此可以
環覽全園景色。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"wenmeige",
                "northwest" : __DIR__"yanyutang",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
	set("coor/x", 1140);
	set("coor/y", -1080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}