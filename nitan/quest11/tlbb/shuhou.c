// shuhou.c
// bbb 1997/06/11
// Modify By River 98/12
// Modify by tangfeng 2004
inherit ROOM;
#define QUESTDIR1 "quest/天龍八部/凌波微步篇/"
#include <ansi.h>
void create()
{
	set("short", "樹叢後");
	set("long", @LONG
這裡光禿禿的一大片石壁，爬滿籐蔓，但見石壁平整異常，宛然一面銅鏡，
只是比湖西的山壁小了許多，再細看那石壁，平整光滑，別無他異。
LONG
	);
        set("exits", ([
		"out" : __DIR__"shulin1",
	]));
        set("outdoors", "大理");
	setup();
}

void init()
{
	  object me;
    me = this_player();
	  if (me->query(QUESTDIR1+"start") 
	     && !me->query(QUESTDIR1+"wuliangover")
	     && me->query_temp(QUESTDIR1+"jianying") 
	     && !me->query_temp(QUESTDIR1+"see_duanyu1"))
	  {
      "/cmds/std/look.c"->look_room(this_player(), this_object());
      tell_object(me,HIY"\n你眼光順著湖面一路伸展出去，突然之間全身一震，只見對面玉壁上赫然有個人影。你定了定神凝神看去，那人影淡淡的看不清楚。\n"
                          "你一怔之下，便即省悟：“是我自己的影子？”身子左幌，壁上人影跟著左幌，身側右，此時已無懷疑。你微一凝思，只覺這迷惑了\n"
                          "“無量劍”數十年的“玉壁仙影”之謎，更無絲毫神奇之處：“當年確有人站在這裡使劍，人影映上玉壁。本來有一男一女，後來那\n"
                          "男的不知是走了還是死了，只剩下一個女的，她在這幽谷中寂寞孤單，過不了兩年也就死了。”一想像佳人失侶，獨處幽谷，終于鬱\n"
                          "鬱而死，不禁黯然。既明白了這個道理，心中先前的狂喜自即無影無蹤，百無聊賴之際，便即手舞足蹈，拳打腳踢，心想：“最好左\n"
                          "子穆、雙清他們這時便在崖頂，見到玉壁上忽現‘仙影’，認定這是仙人在演示神奇武功，于是將我這套‘武功’用心學了去，拼命\n"
                          "鑽研，傳之後世。哈哈，哈哈！”越想越有趣，忍不住縱聲狂笑。\n"NOR);
    }
    add_action("do_down", "tear");
    add_action("do_down", "si");
}

int do_down(string arg)
{
	object me = this_player();
        if (!arg || arg!="teng") return 0;
        message_vision("$N把石壁上的籐蔓撕得幹幹凈凈，走向後面。\n" , me);
        me->move(__DIR__"shibi");
        return 1; 
}
