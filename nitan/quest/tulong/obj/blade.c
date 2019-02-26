#include <weapon.h>
#include <ansi.h> 
inherit BLADE;

void create()
{
        set_name(HIY"精靈刀"NOR, ({ "spirit blade", "blade" })); 
        set("long", "精靈的寶物，擁有精靈的力量。\n");
        set("no_get",1);
        set("no_give",1);
        set("no_steal",1);
        set("no_sell",1);
        set("no_put",1);
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 0);
                set("material", "iron");
                set("wield_msg", HIC"$N"+HIC"右手結印，垂目默唸咒語。一點光芒在$N"+HIC"掌中逐漸亮起，$n"NOR+HIC"漸漸成形。\n"NOR);
                set("unwield_msg", "$n"+HIC"從$N"+HIC"手中一躍而起，化為一道清風。\n"NOR); 
            set("skill", ([
                "name": "spirit-blade",    // name of the skill
                "exp_required": 1000,    // minimum combat experience required
                "jing_cost":    2,    // jing cost every time study this
                "difficulty":   10,    // the base int to learn this skill
                "max_skill":   160,    // the maximum level you can learn to
            ]) );
        }
        init_blade(120);
        setup();
}

void owner_is_killed()
{
        write(HIY"只覺一陣清風吹過，好像是……\n"NOR);
       destruct(this_object());
}
/*
int query_autoload()
{
        write(HIG"一陣清風拂過身側，彷彿在呢喃什麼咒語。\n"NOR);
       return 1;
}
*/
void init()
{
    add_action("do_back","back"); 
    add_action("do_nopoison","nopoison"); 
    add_action("do_change","change");    add_action("do_summons","summons");
}
 
int do_back(string arg)
{
    string name;
    name=query("name", this_player());
    if( query("jing", this_player())<20 )
                return notify_fail("你的精神無法集中！\n");
    if( !arg ) return notify_fail("你要回哪裏? \n");
    {
        if ( arg == "spirit" )
        {
            message_vision(HIG"$N默唸咒語，手中"NOR+HIY"精靈刀"NOR+HIG"化為一陣清風，盤旋飛舞。\n"NOR,this_player() );
            this_player()->receive_damage("jing",10);
            tell_room(environment(this_player()),
                 name+"的身影消失在清風中。\n",this_player() );
            tell_room("/d/city/spirit",
                 name+"的身影出現在一陣清風中。\n",this_player() );
            this_player()->move("/d/city/spirit");
         }
     }
     return 1;
}
 
int do_nopoison(string arg)
{     
        object me;
        me = this_player(); 
        if( query("jing", me)<20 )
                return notify_fail("你的精神無法集中！\n");
        if( !arg )
                return notify_fail("你要為誰療毒？\n");
        if ( arg == "spirit" )
          {        me->receive_damage("jing",10);
                        message_vision(HIC"$N雙掌合十，捧着"NOR+HIY"精靈刀"NOR+HIC"，默唸咒語。\n"NOR, me);
        me->clear_condition();  
               write("你成功驅除了體內毒素！\n");
        return 1;  
          }
}
 
int do_summons(string arg)
{
  object me = this_player ();
        object ob;
 
        if( !me->is_fighting() )
                return notify_fail("只有戰鬥中才能召喚精靈！\n");
        if( query("jing", me)<40 )
                return notify_fail("你的精神無法集中！\n");

        message_vision(HIY"$N"+HIY"將精靈刀一揮，喃喃地念了幾句咒語。\n"NOR, me);

         me->receive_damage("jing", 30);
        ob = new("/quest/tulong/npc/spirit");
        ob->move(environment(me));
        ob->invocation(me); 
                return 1;
} 

int do_change(string arg)
{     
        object me = this_player();   
        object ob = this_object();
        object obj;
        if( query("jing", me)<20 )
                return notify_fail("你的精神無法集中！\n");
        if( arg == "sword")
        { 
       me->receive_damage("jing",10);
                        message_vision(HIC"$N手中"NOR+HIY"精靈刀"NOR+HIC"輕輕一晃，變出了一把劍。\n"NOR, me); 
        obj=new("quest/tulong/obj/sword");
        obj->move(me);   
        destruct(ob);
        return 1;  
        }
      return 0;
}
