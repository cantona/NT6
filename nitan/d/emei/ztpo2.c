#include <ansi.h>
inherit ROOM;

void create()
{
      set("short", "鑽天坡");
        set("long", @LONG
蓮花石與洗象池之間，道路陡絕石棧若齒，直上藍天，石蹬達一
千三百多級，是在陡峭山壁上開鑿出來的坡道。人行其上，前後頂踵
相接，一如登天。這段路叫「鵓鴿鑽天」，這段陡坡也因此而叫「鑽
天坡」。這裡西上坡頂便到洗象池，東下可達蓮花石。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "eastdown"  : __DIR__"ztpo1",
          "westup"    : __DIR__"xixiangchi",  
      ]));
        set("coor/x", -550);
        set("coor/y", -240);
        set("coor/z", 150);
        setup();
}

int valid_leave(object me, string dir)
{
        int c_skill;

        me = this_player();
        if (dir == "westup")
        {
                c_skill = me->query_skill("dodge", 1);
                if( query("qi", me)>40 )
                {
                        me->receive_damage("qi", 20 + random(20));

                        if (me->can_improve_skill("dodge") && c_skill < 100)
                                me->improve_skill("dodge", 1 + c_skill / 15);

                        tell_object(me, HIC "你爬上洗象池，有些累了。\n" NOR);
                } else
                {
                        set("qi", 0, me);
                        tell_object(me, HIR "你太累了，再也走不動了。\n" NOR);
                        return -1;
                }
      }
      return 1;
}