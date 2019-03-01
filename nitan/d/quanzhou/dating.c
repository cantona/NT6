// Room: /d/quanzhou/dating.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "武館大廳");
        set("long", @LONG
泉州武館是專為初出江湖的少年設立的。由于江湖叛師是十分為人
不齒的，初出道的少年可以在此學習一些基本的防身武功，一來不會光
陰虛度，二來也好為今後選定一個心慕的門派。
    牆上貼著個貼子(tiezi)。
LONG );
        set("objects", ([
                __DIR__"npc/lin" : 1,
        ]));
        set("no_fight",1);
        set("no_steal",1);
        set("no_beg",1);
        set("item_desc", ([
                "tiezi" : @TEXT
揚州武館敬啟者：不須把所有的基本武功學全。必要的基本武功是：

□ 基本內功
□ 基本輕功
□ 基本招架
□ 基本拳腳：由基本爪法、基本手法、基本掌法、基本指法、基
             本爪法以及基本拳法任選一種。
□ 基本兵器：由基本刀法、基本棍法、基本劍法、基本杖法、基
             本棒法以及基本暗器任選一種。

─────────────────────────────
「揚州武館」所傳授基本武功
─────────────────────────────
１）基本輕功 (dodge)              ８）基本拳法 (cuff)
２）基本內功 (force)              ９）基本刀法 (blade)
３）基本招架 (parry)            １０）基本棒法 (stick)
４）基本爪法 (claw)             １１）基本棍法 (club)
５）基本手法 (hand)             １２）基本杖法 (staff)
６）基本掌法 (strike)           １３）基本劍法 (sword)
７）基本指法 (finger)           １４）基本暗器 (throwing)
─────────────────────────────
「揚州武館」所傳授高級武功
─────────────────────────────
１）太祖長拳 (changquan)          ２）岳家散手 (sanshou)
─────────────────────────────
學習命令是: xue 師傅名 武功技能 次數
TEXT
        ]) );
        set("exits", ([
                "east" : __DIR__"kaojiaochang",
        ]));
	set("coor/x", -940);
	set("coor/y", -7690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}