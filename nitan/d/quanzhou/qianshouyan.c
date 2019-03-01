// Room: /d/quanzhou/qianshouyan.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "千手巖");
        set("long", @LONG
沿山路而上，即達千手巖。這裡每交秋冬滿山楓葉，如火如錦，煞
是好看。巖上一寺，內供觀音坐像一尊。寺前蒼鬆挺拔，寺後峰石嶙峋，
別有一番景致。近旁就是著名高僧弘一法師的墓亭，墓亭邊的崖石上刻
著他臨終時寫的「悲欣交集」四個字。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "southeast" : __DIR__"mituoyan",
                "northup"   : __DIR__"laojunyan",
        ]));
	set("coor/x", -930);
	set("coor/y", -7530);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}