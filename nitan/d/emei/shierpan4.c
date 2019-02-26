#include <ansi.h>
inherit ROOM;

void create()
{
      set("short", "十二盤");
        set("long", @LONG
這裏石階陡折多彎，號稱「十二盤」。由此西上可達華嚴頂，東
下則到萬年庵。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "northeast" : __DIR__"shierpan3",
          "westup"    : __DIR__"huayanding",
      ]));
        set("coor/x", -510);
        set("coor/y", -240);
        set("coor/z", 110);
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

                        tell_object(me, HIC "你爬上華嚴頂，有些累了。\n" NOR);
                } else
                {
                        set("qi", 0, me);
                        tell_object(me, HIR "你太累了，再也走不動了。\n" NOR);
                        return -1;
                }
      }
      return 1;
}