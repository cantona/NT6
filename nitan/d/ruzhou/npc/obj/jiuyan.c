// Obj /d/ruzhou/npc/obj/jiuxi.c
// llm 99/07/09

inherit ITEM;
#include <ansi.h>

void create()
{
        set_name("酒席", ({ "jiuxi" }));
   if( clonep() )
       set_default_object(__FILE__);
   else
   {
                set("long", "這是一桌五色齊全、香味四溢、豐盛的酒席。\n"
   HIG"八味拼盤(pingpan)  珍品杲羹(guogeng)  紅燒蹄膀(tipang)\n"
      "松子桂魚(guiyu)    香菇菜心(caixing)  清燉甲魚(jiayu)\n"
      "人蔘雞湯(jitang)   翠玉豆腐(doufu)    海蔘青蟹(qingxie)\n"NOR);
                set("unit", "桌");
                set("value",1000);
set("no_drop",1);
      set("no_get","你也太黑心了吧？竟想扛走這一桌的酒席？弄得動嗎？\n");
   }
   setup();
}

void init()
{
        add_action("do_eat", "eat");
}

int do_eat(string arg)
{
        object me=this_player();
   if( me->is_busy() )
      return notify_fail("你上一個動作還沒有完成。\n");
   if( query("food", me) >= me->max_food_capacity() )
           return notify_fail("你已經吃太飽了，還想吃什麼？\n");
        switch(arg)
   {
           case "pingpan":
         message_vision("$N輕輕挑出一塊拼盤冷菜，夾進嘴裏津津有味地嚼起來。\n",me);
                   addn("food", 8, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 1, me);
         break;
      case "guogeng":
              message_vision("$N舀了一勺珍品果羹，“啊！”真是又香又甜。\n",me);
                   addn("food", 2, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 8, me);
         break;
      case "tipang":
              message_vision("$N叉了一大塊的紅燒蹄膀，狼吞虎嚥地吃了下去。\n",me);
                   addn("food", 20, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 2, me);
         break;
      case "guiyu":
              message_vision("$N夾出一塊松子桂魚，只覺入嘴滑嫩，鮮美無比。\n",me);
                   addn("food", 10, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 2, me);
         break;
      case "caixing":
              message_vision("$N細心地挑了一些色香俱全的香菇菜心，慢慢地品味着，真香。\n",me);
                   addn("food", 10, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 2, me);
         break;
      case "jiayu":
              message_vision("$N一下子挖出一塊甲魚，急不可耐地塞進嘴裏。\n",me);
                   addn("food", 20, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 4, me);
         break;
      case "jitang":
              message_vision("$N湊着香味大大地嚐了一口人蔘雞湯，果真是鮮美無比。\n",me);
                   addn("food", 2, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 15, me);
         break;
      case "doufu":
              message_vision("$N夾起一筷翠玉豆腐含在嘴裏，一臉的幸福滿足的神情。\n",me);
                   addn("food", 8, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 1, me);
         break;
      case "qingxie":
              message_vision("$N悶着頭，剝開青蟹殼，一口一口地吮吸裏面鮮美的汁肉。\n",me);
                   addn("food", 10, me);
         if( query("water", me)<me->max_water_capacity() )
                           addn("water", 1, me);
         break;
      default:
              write("你想吃什麼？菜上那麼多菜都不吃？\n");
         break;
   }
        return 1;
}