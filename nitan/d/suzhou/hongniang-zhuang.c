//Room: /d/suzhou/hongniang-zhaung.c
// by llm 99/06/12

#include <ansi.h>

inherit ROOM;

string look_sign(object me);

void create()
{
        set("short", "紅娘堂");
        set("long", @LONG
這裡就是天下夫婦定約結緣的紅娘堂，只有在這裡締結婚約或是
解除婚約才能得到世人的承認。這裡是一個不大的門廳，但是經過一
番修整之後，顯得十分地氣派。廳堂正中掛著一塊雕著字的烏木匾牌
(sign)。
LONG );
        set("exits", ([
                "west" : "/d/suzhou/hong-zoulang",
                "east" : "/d/suzhou/yinyuan-tang",
   ]) );

   set("item_desc", ([
           "sign": (: look_sign :),
   ]) );

   set("objects", ([
        "/d/city/npc/meipo" : 1,
      ]) );
   set("coor/x", 230);
        set("coor/y", -200);
        set("coor/z", 0);
        setup();
}

string look_sign(object me)
{
        return HIM"勸和不勸分\n"
   "求緣更求份\n"
   "紅線前生系\n"
   "姻結一世人\n"NOR;
}

int valid_leave(object me, string dir)
{
         if( dir == "west" && query_temp("pending/pro", me) )
      delete_temp("pending/pro", me);
      return ::valid_leave(me, dir);
}
