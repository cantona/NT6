#include <ansi.h>
inherit ROOM;

void create()
{
      set("short", "千佛庵");
        set("long", @LONG
此處是洪椿坪千佛庵。山間小坪壩，四面層巒疊障，峯環嶺護；
兩側深谷幽嵐，溪澗玲叮。坪上古木扶疏，亭亭如蓋山陰沁透，白霧
飄遊，極為幽靜清涼。此處常見雨霧霏霏，林中迷迷濛濛，乃山中霧
氣所為。正所謂「山行本無雨，空翠濕人衣」。這就是譽為奇觀的「
洪椿曉雨」。此處殿美景幽，氣象新異，令人心醉。沿途南上是「九
十九道拐」，北下經黑龍江棧道至清音閣。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "westup" : __DIR__"jsjdg1",
          "east"   : __DIR__"heilong2",
          "enter"  : __DIR__"qfadadian",
      ]));
      set("coor/x", -470);
        set("coor/y", -240);
        set("coor/z", 100);
        set("coor/x", -470);
        set("coor/y", -240);
        set("coor/z", 100);
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