#include <ansi.h>
inherit ROOM;

void create()
{
      set("short", "十二盤");
        set("long", @LONG
這裏石階陡折多彎，號稱「十二盤」。你見路邊有個八音池，有
人正在向池中擊掌(clap)。由此西上可達華嚴頂，東下則到萬年庵。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "eastdown"  : __DIR__"shierpan2",
          "southwest" : __DIR__"shierpan4",
      ]));
      set("no_clean_up", 0);
        set("coor/x", -500);
        set("coor/y", -230);
        set("coor/z", 110);
        setup();
}

void init()
{
      add_action("do_clap", "clap");
}

int do_clap()
{
      message_vision(HIC "\n池內忽然有蛙大鳴一聲，接着羣蛙次第相"
                     "合，最後又是一蛙大\n鳴，羣蛙便嘎然而止，其"
                     "數正好為八。\n", this_player());
      return 1;
}

int valid_leave(object me, string dir)
{
        int c_skill;

        me = this_player();
        if (dir == "southwest")
        {
                c_skill = me->query_skill("dodge", 1);
                if( query("qi", me)>40 )
                {
                        me->receive_damage("qi", 20 + random(20));

                        if (me->can_improve_skill("dodge") && c_skill < 100)
                                me->improve_skill("dodge", 1 + c_skill / 15);

                        tell_object(me, HIC "你爬上十二盤，有些累了。\n" NOR);
                } else
                {
                        set("qi", 0, me);
                        tell_object(me, HIR "你太累了，再也走不動了。\n" NOR);
                        return -1;
                }
      }
      return 1;
}