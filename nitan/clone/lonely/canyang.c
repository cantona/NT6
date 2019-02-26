#include <ansi.h> 
#include <weapon.h> 
 
inherit SWORD; 
 
void create()
{
        set_name(HIY "殘陽寶劍" NOR, ({ "canyang baojian", "canyang", 
                                        "sword" }));
        set_weight(8000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIY "
此劍長五尺，細而長，通體泛出金光。劍柄彎曲，上刻殘陽圖
紋，劍脊之上還鑄有無數密密麻麻的古篆，似乎與武學有關。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIC "$N" CYN "驀地縱聲長嘯，霎時寒"
                                 "芒一閃，一道金光破空劃過，落於$N"
                                 CYN "掌間。\n" NOR);
                set("unwield_msg", HIC "$N" CYN "一聲輕哼，將手中的"
                                   "殘陽寶劍插入劍鞘。\n" NOR);
                set("skill", ([
                        "name"         : "poyang-jian",
                        "exp_required" : 300000,
                        "jing_cost"    : 90,
                        "difficulty"   : 92,
                        "max_skill"    : 129,
                        "min_skill"    : 60
                ]));

                set("stable", 100);
        }
        init_sword(140);
        setup();
} 
 
int query_unique() { return 1; }

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n = me->query_skill("sword");

        if (me->query_skill("sword") < 150)
                return damage_bonus / 2;

        if (me->query_skill_mapped("sword") != "poyang-jian")
                return damage_bonus / 2;

        switch (random(4))
        {
        case 0:
                victim->receive_damage("jing", n / 2 , me);
                victim->receive_wound("jing", n / 4, me);
                return HIW "$N" HIW "長嘯一聲，手中" HIY "殘陽寶劍" HIW 
                           "橫於胸前，猛地揮出，一陣熾熱的劍氣將$n" 
                           HIW "逼得連連後退。\n" NOR;
        case 1:
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                return HIR "$N" HIR "手中" HIY "殘陽寶劍" HIR "突然劍光"
                           "一閃，耀眼奪目，一道熾熱的劍氣划向$n" HIR "。\n" NOR;
        }
        return damage_bonus;
}

void start_borrowing()  
{ 
     remove_call_out("return_to_zuo");  
     call_out("return_to_zuo", 7200+random(600));  
}  
   
void return_to_zuo()  
{  
      object me;  
 
      me = environment();  
      if (! objectp(me))  
              return;  
 
      while (objectp(environment(me)) && ! playerp(me))  
              me = environment(me);  
 
      if (playerp(me))  
      {  
              if (me->is_fight())  
              {  
                      call_out("return_to_zuo", 1);  
                      return;  
              }  
 
              message_vision("忽然一個嵩山派弟子走了過來，看到$N，忙招呼道：“左盟主讓我來找你拿回"  
                             "殘陽寶劍，你現在不用了麼？”\n"  
                             "$N道：“好了，好了，你就拿回去吧。”\n"  
                             "$N將殘陽寶劍交給嵩山派弟子帶走。\n", me);  
      } else  
      {  
              message("vision", "忽然一個嵩山派弟子走了過來，撿起殘陽寶劍，歎了口氣，搖搖頭走了。\n",  
                      me);  
      }  
 
      destruct(this_object()); 
}