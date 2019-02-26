#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "苗家大門");
        set("long",
"這是一座頗為巨大的宅院，看樣子是富人的居所。門前擺
着兩座石獅，甚是威嚴。紅漆大門上懸掛着塊匾，上面寫着有

          " YEL "※※※※※※※※※※※※※※※※※
          ※                              ※
          ※  " HIR "打  遍  天  下  無  敵  手" NOR YEL "  ※
          ※                              ※
          ※※※※※※※※※※※※※※※※※" NOR "

七個鑲金大字。大門中央站着一位四十來歲的瘦高個子，手裏
持着一副鐵靈牌，冷冷地望着你。\n");

        set("exits", ([
                  "east"  : __DIR__"miaojia_dayuan",
                  "west"  : __DIR__"wendingbei4",
        ]));

        set("no_clean_up", 0);
        set("objects", ([
                CLASS_D("miao") + "/wen" : 1,
        ]));

        set("coor/x", -9030);
	set("coor/y", -960);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        object wen;

        if (dir != "east" ||
            ! objectp(wen = present("zhong zhaowen", this_object())))
                return ::valid_leave(me, dir);

        return wen->permit_pass(me, dir);
}