inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "永定門");
        set("long",
"\n"
"                         s________________s
                        /LLLLLLLLLLLLLLLLLL\\
    []__[]             ^^||======||======||^^             []__[]
    []==[]_[]__[]__[]__[]||[]__[]||[]__[]||[]__[]__[]__[]_[]==[]
    []==[]|__|__|__|__|__|__|┏━━━┓_|__|__|__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|_┃"HIW"永定門"NOR"┃__|__|__|__|__|__|_[]==[]
    []==[]|__|__|__|__|__|__|┗━━━┛_|__|__|__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|_/        \\__|__|__|__|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__|        |_|__|__|__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|_|        |__|__|__|__|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__|        |_|__|__|__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|_|        |__|__|__|__|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__|        |_|__|__|__|__|__|__[]==[]\n\n" 
);
        set("outdoors", "city2");
        set("no_fly",1);

        set("exits", ([
                "north"    : __DIR__"hgdadao1",
                "south"    : __DIR__"center",
                "east" : __DIR__"ssfmen",
        ]));

        set("objects", ([
                __DIR__"npc/jinyiwei" : 3,   
        ]));
        setup();
}

int valid_leave(object me,string dir)
{
       object *env,room;
       int i;

       room=this_object();
       if( userp(me) && query("degree_jungong", me)<8 && dir == "north" )
       {
        addn_temp("voilet_hg", 1, me);
        if( query_temp("voilet_hg", me)<3 )
        {
         if( query("degree_jungong", me) )
         return notify_fail(
         "錦衣衞一把攔住你道：大人官低位卑，如何能夠進宮面聖！\n");
         else
         return notify_fail(
         "錦衣衞一把攔住你道：那裏來的刁民，還不速速離去，否則休怪刀下無情！\n");
        } else
        {
         if( query_temp("voilet_hg", me) == 3 )
         { 
          env=all_inventory(room);
          for(i=0;i<sizeof(env);i++)
          {
           if( query("id", env[i]) == "jinyiwei" )
           env[i]->kill_ob(me);
          }
          return notify_fail(HIR"你把心一橫，決心力闖皇宮！\n"NOR); 
         }
        }
      }
      return ::valid_leave(me,dir);
}
