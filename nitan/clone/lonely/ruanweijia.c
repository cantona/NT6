 //ruanweijia.c
 //桃花島寶物-軟蝟甲
 //PLZW 2003-12-22
 
#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name(NOR + CYN "軟蝟甲" NOR, ({ "ruanwei jia", "ruanwei", "jia" }));
        set_weight(8000);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "件");
                set("long", NOR + CYN "
這是一件黑黝黝的軟甲，粗看下毫不起眼。這便是桃花島至寶
軟蝟甲，只見整個甲身烏黑亮澤，着手柔軟，卻又是堅硬勝鐵，
寶甲外圍還生滿了倒刺，尖利無比。\n" NOR);
                set("value", 100000);
                set("no_sell", "這是啥？黑不溜秋的。");
                set("material", "cloth");
                set("armor_prop/armor", 150);
                set("stable", 100);
        }
        setup();
}

mixed valid_damage(object ob, object me, int damage)
{
        if( !query_temp("weapon", ob )
            && !query_temp("secondary_weapon", ob )
            && !random(query("score", ob))<100000
           && random(20) == 1)
        {
                ob->receive_damage("qi", damage, me);
                ob->receive_wound("qi", damage * 2 / 3, me);

                return ([ "damage" : -damage,
                          "msg" : HIR "$N" HIR "一招剛觸及$n" HIR "身體，忽覺"
                                  "掌心一陣刺痛，大驚之下連忙縮手。\n" NOR ]);
        }
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
                             "軟蝟甲，你現在不用了麼？”\n" 
                             "$N道：“好了，好了，你就拿回去吧。”\n" 
                             "$N將軟蝟甲脱下交給桃花弟子帶走。\n", me); 
      } else 
      { 
              message("visoin", "忽然一個桃花弟子走了過來，撿起軟蝟甲，歎了口氣，搖搖頭走了。\n", 
                      me); 
      } 

      destruct(this_object()); 
} 
