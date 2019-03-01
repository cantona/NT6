// Room: /d/suzhou/zhengdian.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "正殿");
        set("long", @LONG
一走進正殿，首先你看到的是號稱揚州八怪的畫家羅聘所繪寒山、
拾得寫意畫像石刻和鄭文焯指畫豐幹和尚石刻像。左右碑廊中藏歷代名
人諸如岳飛等題寫得詩文，楹聯碑刻樹方，世傳精品。正殿左右的偏殿
保存著宋代樟木雕塑的金身五百羅漢。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "out"   : __DIR__"hanshansi",
                "east"  : __DIR__"hanshidian",
        ]));
	set("coor/x", 1039);
	set("coor/y", -1051);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}