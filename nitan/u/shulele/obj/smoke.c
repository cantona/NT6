//by djx
inherit ITEM;
#include <ansi.h>
void smoked(object obj);
void init()
{
        add_action("do_smoke", "xiyan");
}

void create()
{
        string *order = ({HIC"中華"NOR, HIC"大前門"NOR, HIR"柔和"+HIW"七星"NOR, HIM"紅塔山"NOR, HIM"萬寶路"NOR, HIB"希爾頓"NOR, 
HIW"雲煙"NOR, HIY"聖羅蘭"NOR, HIY"駱駝"NOR, HIG"三五"NOR, HIG"玉溪"NOR, HIR"紅雙喜"NOR});
        set_name( (order[random(sizeof(order))]), ({ "xiang yan", "yan" }) );
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一盒香煙，可以 "+HIR"(xiyan) \n"NOR);
                set("unit", "盒");
                set("no_give", 1);
                set("no_sell", 1);
                set("no_get", 1);
                set("count",8);
        }
}


int do_smoke()
{
        object me = this_player();
        object obj = this_object();

        if(environment(obj) != me)
                return notify_fail("你是在看煙吧？\n");
        if(query("master") && query("master") != me->query("id"))
                return notify_fail("這煙已經點燃了，而且不是你的煙。\n");
        add("count",-1);
        me->add("food", -20);
        me->add("water", -20);
        switch(query("count")) {
                case 1: message_vision("$N猛吸了一口剩下的"+YEL"煙屁股"+NOR"，兩根手指夾住一彈，扔掉了煙頭。\n", me);
                        break; 
                case 2: message_vision("$N吐出一串"+HIC"煙圈"+NOR"，看著它悠閒地散開。\n", me);
                        break;
                case 3: message_vision("$N閉上眼睛，深深地吸了一口$n，又從鼻孔中噴出來：“爽啊！爽啊！”\n", me, obj);
                        break;
                case 4: message_vision("$N狠狠的吸了一口$n，大概是吸得太猛了，一張臉漲的通紅。\n", me, obj);
                        break;
                case 5: message_vision("$N吸了一口$n，搖頭晃腦地說道：“飯後一支煙，賽過"+HIM"活神仙。”\n"NOR, me, obj );
                        break;
                case 6: message_vision("$N翹起二郎腿，眯上眼睛，猛吸了一口$n，自言自語道：“這東西害人又害己，為啥我還那麼喜歡？”\n", me, obj);
                        break;
                case 7: set("master", me->query("id"));
                        message_vision("$N抽出一支$n，點著了"BLINK HIR"火"+NOR" 美滋滋地吸了起來。\n", me, obj);
                        break;
                default:
                        break;
        }        
        if(query("count") > 1) call_out("do_smoke", 10);
        else {
		obj->set_name(HIR+me->query("name")+"抽過的煙屁股"NOR,({"yan pi gu"}));
		obj->set("long",HIC"被"+me->query("name")+"抽過的煙屁股"NOR);
		obj->set("no_get",1);
		obj->unequip();
		obj->move(environment(me));
		call_out("smoked",random(60),obj);
		}
        return 1;
}

void smoked(object obj)
{
  if(obj && environment(obj)) {
    tell_object(environment(obj),
      "一陣微風吹過，"+obj->name()+"化為片片塵土，消失不見了。\n");
    destruct(obj);
  }
}
