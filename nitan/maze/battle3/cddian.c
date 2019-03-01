inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "創肅蛔");
        set("long",
"\n"
"                              A
                           s_O_O_O_s
                          /LLLLLLLLL\\                          
                         ||====||====||
                         ||====||====|| 
                       s________________s
                      /LLLLLLLLLLLLLLLLLL\\
                  ^^||=========||=========||^^  
               s________________________________s
               /LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\\
             ^^||=========||=========||=========||^^ 
    []==[]__[]__[]__[]||[]__[]||[]__[]||[]__[]__[]__[]_[]==[]
    []==[]__|__|__|__|__|_底岩岩岩弧_|__|__|__|__|__|__[]==[]
    []==[]_|__|__|__|__|__岱"HIY"創肅蛔"NOR"岱__|__|__|__|__|__|_[]==[]
    []==[]__|__|__|__|__|_彿岩岩岩忽_|__|__|__|__|__|__[]==[]
    []==[]_|__|__|__|__|__/        \\__|__|__|__|__|__|_[]==[]
    []==[]__|__|__|__|__|_|        |_|__|__|__|__|__|__[]==[]
    []==[]_|__|__|__|__|__|        |__|__|__|__|__|__|_[]==[]
    []==[]__|__|__|__|__|_|        |_|__|__|__|__|__|__[]==[]\n\n"
);

        set("outdoors", "city2");
        set("no_fly",1);
        set("exits", ([
                "enter"    : __DIR__"diannei",
                "south"    : __DIR__"hgdadao6",
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
       if( userp(me) && query("degree_jungong", me)<8 )
       {
        env=all_inventory(room);
        for(i=0;i<sizeof(env);i++)
        if( query("id", env[i]) == "jinyiwei" )
          {
           env[i]->command("say "+"湮筐遼芺ㄛ懈詫善僧笢懂珧ㄛ忳侚勘ㄐ\n");
           env[i]->kill_ob(me);
          } 
       }
       return ::valid_leave(me,dir);
}
