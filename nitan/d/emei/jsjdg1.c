#include <ansi.h>
inherit ROOM;

void create()
{
      set("short", "九十九道拐");
        set("long", @LONG
這是便是著名的「九十九道拐」，道路紆曲陡豎，千折百回。據
說過去曾有個百余歲的瘋僧至此，見一巨蟒擋路，便念咒驅蟒。但人
們得知此處有巨蟒出沒後，便再也無人敢碰這裡的草木，並以「龍居
」名之。東可至千佛庵，西達九老洞。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "westup"   : __DIR__"jsjdg2",
          "eastdown" : __DIR__"qianfoan",
      ]));
      set("coor/x", -480);
        set("coor/y", -240);
        set("coor/z", 110);
        set("coor/x", -480);
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