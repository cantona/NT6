#include <ansi.h>
inherit ROOM;

void create()
{ 
        set("short", "桃花迷陣");
        set("long", @LONG
這是片桃花的海洋。四周一望無際全是盛開的桃花。微風
拂過，落英繽紛。周圍靜悄悄的。遠處偶爾傳來一聲鳥叫。你
心中不禁慌亂起來：還是早點出去的好。
LONG );
        set("outdoors", "taohua");
        set("exits", ([
                "east" :  __FILE__,
                "west" :  __FILE__,
                "south" : __FILE__,
                "north" : __FILE__,
        ]));             
}

int valid_leave(object me, string dir)
{
        int total_steps;

        if( query("family/family_name", me) == "桃花島"
           || me->query_skill("qimen-wuxing") >= 150)
        {
                total_steps = 1; 
        } else
        {
                    me->receive_damage("qi", 15);
                    me->receive_wound("qi", 15);
                    message_vision(HIM "\n突然間一陣桃花瓣象雨點般疾"
                               "射$N" HIM "。\n\n" NOR, me);

                total_steps = 30;
        }

        if (dir == "north")
                    addn_temp("taohua/steps", 1, me);

        if (dir == "south")
                    addn_temp("taohua/steps", -1, me);

        if( query_temp("taohua/steps", me) == total_steps )
        {
                         me->move(__DIR__"tao_in");
                    delete_temp("taohua/steps", me);
                    write(HIC "\n你走了半天，終於走出了桃花迷陣。\n\n" NOR);
                   return -1;
        }  

        if( query_temp("taohua/steps", me) == -total_steps )
        {  
                me->move(__DIR__"tao_out");
                    delete_temp("taohua/steps", me);
                    write(HIC "\n你走了半天，終於走出了桃花迷陣。\n\n" NOR);
                return -1;
             }

        return ::valid_leave(me,dir);
}
