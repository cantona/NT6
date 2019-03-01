#include <ansi.h>
inherit ROOM;

void create()
{
      set("short", "雷洞坪");
        set("long", @LONG
雷洞坪一帶道路艱險駭人，路左是蔽日遮天的冷杉林，路右是深
不見底的絕壁峽谷。這裡長年雲遮霧罩空蒙黑暗。巖上建有雷神殿，
旁邊豎一鐵碑。由此往上是「八十四盤」至接引殿，北下到洗象池。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "northdown"  : __DIR__"lingyunti",
          "southup"    : __DIR__"bashisipan1",
          "east"       : __DIR__"lengsl1",
      ]));
        set("coor/x", -560);
        set("coor/y", -260);
        set("coor/z", 180);
        setup();
}

int valid_leave(object me, string dir)
{
        int c_skill;

        me = this_player();
        if (dir == "southup")
        {
                c_skill = me->query_skill("dodge", 1);
                if( query("qi", me)>40 )
                {
                        me->receive_damage("qi", 20 + random(20));

                        if (me->can_improve_skill("dodge") && c_skill < 100)
                                me->improve_skill("dodge", 1 + c_skill / 15);

                        tell_object(me, HIC "你爬上八十四盤，有些累了。\n" NOR);
                } else
                {
                        set("qi", 0, me);
                        tell_object(me, HIR "你太累了，再也走不動了。\n" NOR);
                        return -1;
                }
      }
      return 1;
}