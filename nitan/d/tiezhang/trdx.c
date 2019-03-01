// Room: /d/tiezhang/trdx.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;
#include <ansi.h>
string look_bei();

void create()
{
        object ob;
        set("short", HIR"天然洞穴"NOR);
        set("long", @LONG
這石洞系天然生成，較之外面人工開鑿的石室大了十來倍。放眼望
去，洞內共有十余具骸骨，或做或臥，神態各有不同，有的骸骨散開在
地，有的卻仍具完好人形，更有些骨壇靈位之屬。每具骸骨之旁都放著
兵刃，暗器，用具，珍寶等物。洞口處立著一座石碑(bei)。
LONG );
        set("exits", ([
                "out" : __DIR__"dong3",
        ]));
        set("item_desc",([
                "bei"         :       (: look_bei :),
        ]));
        set("objects", ([
                __DIR__"obj/haigu" : 1,  
//                WEAPON_DIR"treasure/yuchang-jian" : 1,      
//                WEAPON_DIR"treasure/liquan-qiang" : 1,      
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2040);
        set("coor/y", -1800);
        set("coor/z", 70);
        setup();
        ob=new(WEAPON_DIR"treasure/yuchang-jian");
        if (ob->violate_unique())
         destruct(ob);
        else
          ob->move(this_object());
        ob=new(WEAPON_DIR"treasure/liquan-qiang");
        if (ob->violate_unique())
         destruct(ob);
        else
          ob->move(this_object());
  
}
string look_bei()
{
        return
        "\n      擅動室內物品者\n"    
        "\n"RED"        死傷莫怪！    \n"NOR
        "\n";
}