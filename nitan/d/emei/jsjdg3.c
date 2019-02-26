#include <ansi.h>
inherit ROOM;

void create()
{
      set("short","九十九道拐");
        set("long", @LONG
這是著名的「九十九道拐」，道路紆曲陡豎千折百回。據説過去
曾有個百餘歲的瘋僧至此，見一巨蟒擋路，便唸咒驅蟒。但人們得知
此處有巨蟒出沒後，便再也無人敢碰這裏的草木並以「龍居」名之。
由此東可至千佛庵，西達九老洞。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "northeast" : __DIR__"jsjdg2",
          "westup"    : __DIR__"jsjdg4",
      ]));
      set("coor/x", -500);
        set("coor/y", -250);
        set("coor/z", 120);
        set("coor/x", -500);
        set("coor/y", -250);
        set("coor/z", 120);
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

                        tell_object(me, HIC "你爬上九十九道拐，有些累了。\n" NOR);
                } else
                {
                        set("qi", 0, me);
                        tell_object(me, HIR "你太累了，再也走不動了。\n" NOR);
                        return -1;
                }
      }
      return 1;
}