inherit ROOM;

#include <ansi.h>
void create()
{
      set("short", "竹徑");
      set("long",
"這裏是一段落滿青苔的青石板小路，右邊是流水回縈，小橋略陳，左\n"
"邊是竹樹掩映，山花浪漫，真個是幽深靜謐，秀麗清朗。向北是一片草地，\n"
"遠遠地似乎就已經聞到了花香。\n"
);
      set("outdoors", "nightstar");
      set("no_fight", "1");
      set("no_steal", "1");
      set("exits", ([
            "south"   : __DIR__"bamboo",
            "northup": __DIR__"ground",
            "north"   : __DIR__"bamboo1",
      ]));
}

int valid_leave(object me, string dir)
{
      int c_exp,c_skill;
        me = this_player();
      if (dir == "north")
      {
        if( query("qi", me)<50 )
                return notify_fail("悠着點，小心身體。\n");
             c_exp=query("combat_exp", me);
             c_skill=me->query_skill("dodge",1);
             if (((c_skill*c_skill*c_skill/10)< c_exp) && (c_skill<301))
                   me->improve_skill("dodge", (int)me->query_skill("dodge", 1)*10);
            me->receive_damage("qi",30);

             tell_object(me,"你在竹林裏悠閒地漫步，竟對輕功修為有所領悟。\n");
      }
        return 1;
}
