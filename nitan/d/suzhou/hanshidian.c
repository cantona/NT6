// Room: /d/suzhou/hanshidian.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "寒拾殿");
        set("long", @LONG
這裏供奉着相傳為“和合二仙”化身的寒山，拾得金身塑像，形態
生動，逗人喜愛。寒山寺每年除夕半夜，撞鐘一百零八響，其含義是除
舊迎新和紀念佛門一百零八位高僧。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "out"   : __DIR__"fengqiao",
                "west"  : __DIR__"zhengdian",
        ]));
	set("coor/x", 1049);
	set("coor/y", -1051);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}