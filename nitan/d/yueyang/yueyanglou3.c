// Room: /d/yueyang/yueyanglou1.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "岳陽樓三樓");
        set("long", @LONG
洞庭山水撫慰了落魄的人生，人生的苦難也鑄就了岳陽的靈魂。一
撥撥朝廷的棄兒，將一掛熱淚拋洒在岳陽樓頭時，巴陵的山捧著它，洞
庭的波含著它，分明就鑄成了岳陽城頭一塊塊苦澀的磚石，從屈夫子一
直壘砌到今天。站在此處，楚天遠闊。樓匾高書“不以己悲”，誰能識
之？滕子京謫守岳州三年，《宋史》定評：“宗諒尚氣，倜儻自任，好
施與，及卒，無余財。”真千秋風骨。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "down"  : __DIR__"yueyanglou2",
        ]));
	set("coor/x", -6240);
	set("coor/y", -3000);
	set("coor/z", 40);
	setup();
        replace_program(ROOM);
}