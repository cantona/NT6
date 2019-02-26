 //yuxiao.c
 //桃花寶物--玉簫
 //PLZW 2003-12-22
 
#include <ansi.h>
#include <weapon.h>

inherit XSWORD;

void create()
{
        set_name(HIW "玉簫" NOR, ({ "yu xiao", "yu", "xiao" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "支");
                set("long", HIW "一支白玉做成的玉簫，看上去晶瑩温潤。武林中人經常以簫代劍。\n" NOR);
                set("value", 800000);
                set("no_sell", 1);
                set("material", "stone");
                set("wield_msg", HIW "$N" HIW "大袖一揮，手中已多了一支晶瑩温潤的玉簫。\n" NOR);
                set("unwield_msg", HIW "$N" HIW "手中玉蕭一轉，眨眼間玉簫已然不見影蹤。\n" NOR);
                set("stable", 100);
        }
        init_xsword(90);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;

        if (me->query_skill_mapped("sword") != "yuxiao-jian" ||
            me->query_skill("yuxiao-jian", 1) < 100)
                return damage_bonus / 2;

        switch (random(10))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(me->query_skill("sword") / 10 + 2);
                return HIW "突然間一陣尖鋭的簫聲至$N" HIW "處傳來，$n" HIW
                       "頓時只覺得太陽穴隱隱刺痛！\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_damage("jing", n / 3, me);
                victim->receive_wound("jing", n / 3, me);
                return HIW "$N" HIW "手中玉簫隨招式激盪出陣陣簫音，$n" HIW
                       "頓時只覺氣血上湧，難受之極！\n" NOR;
        }
        return damage_bonus;
}


void start_borrowing() 
{ 
         remove_call_out("return_to_huang"); 
         call_out("return_to_huang", 7200 + random(600)); 
} 
  
void return_to_huang() 
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
                      call_out("return_to_zhang", 1); 
                      return; 
              } 

              message_vision("忽然一個桃花弟子走了過來，看到$N，忙招呼道：“黃島主讓我來找你拿回" 
                             "玉簫，你現在不用了麼？”\n" 
                             "$N道：“好了，好了，你就拿回去吧。”\n" 
                             "$N將玉簫交給桃花弟子帶走。\n", me); 
      } else 
      { 
              message("visoin", "忽然一個桃花弟子走了過來，撿起玉簫，歎了口氣，搖搖頭走了。\n", 
                      me); 
      } 

      destruct(this_object()); 
} 