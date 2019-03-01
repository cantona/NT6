// ghoster.h
// Modified by haiyan

int accept_object(object who, object ob);  
int do_shou(string arg);
void wildghost(object me);
void course(object me, object weapon);

void init()
{
    object me; 
    ::init(); 
    me = this_player(); 
    if( query_temp("gui/shougui", me) )
    {
        if( query_temp("player") == query("id", me) )
        {
            tell_object(me, comeon);
            call_out("wildghost", 1, me);
            add_action("do_shou", "shoufu");
        }
    }
}

int do_shou(string arg)
{
    object weapon, me, ob; 
    me = this_player(); 

    if (me->is_busy())
       return notify_fail("你上一個動作還沒有完成。\n");

    if (!present("fu zhi", me))
        return notify_fail("你沒符紙就想收鬼，當心鬼把你收了！\n");

    if (!present("taomu jian", me))
        return notify_fail("你沒有桃木劍，還想收鬼？當心鬼把你收了！\n");

    weapon=query_temp("weapon", me);
    if (!objectp(weapon))
         return notify_fail("你沒有裝備桃木劍，鬼也不怕你！\n");

    if (weapon->name() == "桃木劍")
         return notify_fail("這種桃木劍只能練了玩玩，不能驅鬼！\n");

    if (weapon->name() != HIM"桃木劍"NOR)
         return notify_fail("你沒有裝備桃木劍，鬼也不怕你！\n");

    if( !objectp(ob=query_temp("handing", me)) || 
         ob->name() != HIY"符紙"NOR)
         return notify_fail("你手裡沒有拿符紙，無法讓鬼魂現身！\n");

    me->start_busy(2);
    if (query("env/invisible"))
    {
        message_vision(HIY"$N將手中" + ob->name() + HIY"向上一舉，剎時發出"
                       "耀眼的金光。$N大喝一聲“妖魔，還不快快現身？”\n"NOR, me);
        if (random(3) < 1)
        {
            message_vision(HIR"$N忽然看見一個$n正張牙舞爪向$N撲來。\n"NOR, me, this_object());
            delete("env/invisible"); 
        }
    }
    else
    {
        message_vision(styb[random(sizeof(styb))], me, this_object());
        call_out("course", 1, me, weapon);
    }
    return 1;
}

void wildghost(object me)
{
    int damage;
    damage = query_temp("damage");
    if( random(10) == 0)command("grin"+query("id", me));
    if (present(this_object(), environment(me)))
    {
       if (random(10) < 5)
       {
           message_vision(stya[random(sizeof(stya))], me, this_object());
           me->receive_damage("qi", damage, this_object());
           me->receive_wound("qi", damage/3, this_object());
       }
       call_out("wildghost", 1, me);
    }
}

void course(object me, object weapon)
{
    int ap, dp, dam;
    object dan;
    ap = me->query_skill("taoism", 1);
    dp = query_skill("claw", 1);
    if (ap < 300)   dam = 160;
    if (ap < 200)   dam = 120;
    if (ap < 100)   dam = 80;
    if ( ap / 2 + random(ap) > dp )
    {
       message_vision(HIR "$N突然發出一聲凄厲的慘叫，令人毛骨悚然。\n"NOR, this_object());
       if (random(10) < 3)
       {
          message_vision(HIY"\n" + weapon->name() +
                         HIY "突然脫手而出，劃出一道金光，刺入了$n的嚥喉。\n\n"
                         HIR "只聽一聲凄厲的尖叫，$n倒在地下扭動了幾下，"
                         HIR "慢慢化成了一灘黑水，消失了。\n\n", me, this_object());
          weapon->move(environment(this_object()));
          set_temp("gui/finish", 1, me);
          dam += random(80);
          set_temp("gui/base", dam, me);
          if (random(5) == 0)
          {
              message_vision(HIG "$N突然看到地上有一顆發著綠光的丹丸，小心地撿了起來。\n"NOR, me);
              dan = new("/d/wudang/quest/obj/rendan");
              dan->move(me);
          }
          destruct(this_object());
       }
    }
}

void check_time()
{
     if (time() - query_temp("born_time") > 1200) 
     {
         message_vision(HIB "一陣陰風吹過，四周又恢復了平靜。\n"NOR, this_object());
         destruct(this_object());
     }
}

int accept_fight(object ob)  
{ 
    return notify_fail("你不能跟鬼魂較量。\n");  
} 
int accept_hit(object ob)  
{ 
    tell_object(ob,"你不能跟鬼魂打架。\n");
    return 0; 
} 
int accept_kill(object ob)  
{ 
    return notify_fail("你不能跟鬼魂打架。\n");  
} 
int accept_touxi(object ob)  
{  
    tell_object(ob,"你不能偷襲鬼魂。\n");
    return 1;  
}  
int accept_ansuan(object ob)  
{
    return notify_fail("你不能暗算鬼魂。\n"); 
}
