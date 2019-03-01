// Room: wuguan.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "金牛武館");
        set("long", @LONG
「金牛武館」在江湖中很有名聲，很多大俠自小就是從這裡走進
江湖。雖然他們在江湖早已成名立萬，這裡的師傅年紀也都大了，卻
是他們的啟蒙業師，他們也常回來看望師傅們，因此這裡長久得到黑
白兩道的尊重，不容侵犯。這裡是武館大廳。館主馬五德在此請授：
基本輕功，基本內功，基本招架，基本手法，^M基本刀法。  牆上貼
著個貼子(tiezi)。
LONG );
        set("objects", ([
                __DIR__"npc/mawude" : 1,
                __DIR__"npc/zhangfang" : 1,
        ]));
         set("no_fight",0);
        set("no_steal",1);
        set("no_beg",1);
        set("item_desc", ([
            "tiezi" : @TEXT
金牛武館敬啟者：不須把所有的基本武功學全。必要的基本武功是：

□ 基本內功
□ 基本輕功
□ 基本招架
□ 基本拳腳：由基本爪法、基本手法、基本掌法、基本指法、基
             本爪法以及基本拳法任選一種。
□ 基本兵器：由基本刀法、基本棍法、基本劍法、基本杖法、基
             本棒法以及基本暗器任選一種。

─────────────────────────────
「金牛武館」所傳授基本武功
─────────────────────────────
１）基本輕功 (dodge)            ８）基本拳法 (cuff)
２）基本內功 (force)            ９）基本刀法 (blade)
３）基本招架 (parry)            １０）基本棒法 (stick)
４）基本爪法 (claw)             １１）基本棍法 (club)
５）基本手法 (hand)             １２）基本杖法 (staff)
６）基本掌法 (strike)           １３）基本劍法 (sword)
７）基本指法 (finger)           １４）基本暗器 (throwing)
─────────────────────────────
學習命令是: xue 師傅名 武功技能
TEXT
        ]) );
        set("exits", ([
                "southwest" : __DIR__"northroad3",
                "east"      : __DIR__"wuguanchen",
                "south"     : __DIR__"wuguanlong",
                "west"      : __DIR__"wuguanxiao",
                "north"     : __DIR__"wuguanliu",
                "up"        : __DIR__"practice",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15200);
	set("coor/y", -1800);
	set("coor/z", 0);
	setup();
}
int valid_leave(object me, string dir)
{
        if( !query_temp("marks/jinniu_paied", me) && (dir == "up") )
        return notify_fail("馬五德笑道: 那是本館弟子才能進去的。\n");
        else  return 1;
}