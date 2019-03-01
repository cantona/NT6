// Room: /d/suzhou/zhipoxuan.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "揖峰指柏軒");
        set("long", @LONG
這裡曾是為園主接待賓客和親友的地方，有時也作為演戲說書或寫
詩作畫之處。軒名取朱熹“前揖廬山，一峰獨秀”和高啟的“笑指庭前
柏”句詩意。軒內擺設古香古色。憑軒眺望，滿目石峰嶙峋，古柏虯枝
盤繞，舊有桃源“十八景”之稱。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "southwest"  : __DIR__"shizilin",
        ]));
	set("coor/x", 1130);
	set("coor/y", -1060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}