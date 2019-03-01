// 神話世界﹒西遊記﹒版本（世紀）
/* <SecCrypt CPL V3R05> */

//by night 
string test_name(string);

#include <ansi.h>
inherit ITEM;

string *names = ({
  "法鈴",
  "木魚",
  "經綸",
  "羅衣",
  "禪杖",
  "念珠",
  "袈裟",
});

string *ids = ({
  "fa ling",
  "mu yu",
  "jing lun",
  "luo yi",
  "chan zhang",
  "nian zhu",
  "jia sha",
});

string *units = ({
  "個",
  "個",
  "盤",
  "件",
  "根",
  "串",
  "件",
});

void create()
{
        int i = random(sizeof(names));
        set_name(names[i], ({ids[i],"fa qi"}));
        set("unit", units[i]);   
        if (clonep())
                set_default_object(__FILE__);
        else {      
                set("no_drop","這是佛家法器，不可隨便丟棄。\n");
                set("no_put",1);
                set("long", "這是佛家法器，你可以用它來布道（budao）。\n");
                set("value", 0);
             }
        setup();
}

void init()
{
        add_action("do_budao", "budao");
        add_action("do_check", "kan");
        add_action("do_check", "chakan");                
}

int do_budao(string arg)
{
        object me=this_player();
        int nforce,nmana,skl,i;
        int j = 0;
        string people = "";
        object *obs = all_inventory(environment(me));
        
        nforce=query("force", me)/4;
        nmana=query("mana", me)/4;
        skl = random(60) + 140 - (int)me->query_skill("chanting", 1);
        if(skl>180) skl = 180;
        if(skl<10) skl = 10 + random(5);
        i = sizeof (obs);
        while (i--)
        {
        if (living (obs[i]) && obs[i]!=me && me->visible(obs[i]) )
                {
                j++;
                people = people + obs[i]->name();
                }
        }

        if( query_temp("obj/done", me) >= 1 )
        {
          tell_object(me,"你已經完成布道了，回去報告吧。\n");
          return 1;
        }
        else
        if( query_temp("obj/budao", me)<1 )
        {
          tell_object(me,"現在好像沒有輪到你去布道？\n");
          return 1;
        }
        else
        if( query_temp("obj/where", me) != test_name(base_name(environment(me))) )
        {
          tell_object(me,"你布道的地方不是這裡吧？\n");
          return 1;
        }
        else
        if( query_temp("budao", environment(me)) >= 1 )
        {
          tell_object(me,"這兒不久前有人來布過道，現在恐怕來得不是時候。\n");
          return 1;
        }
        else          
        if( (query("sen", me)<20) )
        {  
          tell_object(me,"你的精力不能集中，不可以布道！\n");
          return 1;
        }
        else
        if( (query("kee", me)<30) )
        {
          tell_object(me,"你的身體狀態太差，不能傳經布道！\n");
          return 1;
        }
        else          
        if (j == 0 || !me)
        {
          tell_object(me,"這兒人都沒有，布什麼道？\n");
          return 1;
        }
        else
        if (me->is_busy())
        {
          tell_object(me,"你現在正忙著呢，沒法布道。\n");
          return 1;
        }
        else
        if (!arg || arg == "" )
        { 
          tell_object(me,"你要用什麼道具進行布道？\n");
          return 1;
        }
        else
        if ( arg == "fa ling" || arg == "mu yu")
        {
          if(!present(arg,me)) return notify_fail("你身上沒有這樣東西。\n");        
          if( nforce<30 || (query("force", me)<nforce) )
            return notify_fail("唱梵曲需要內息悠長，你的內力不足，力不能及。\n");
          
          message_vision(HIW"$N清了清噪子，法像莊嚴，吟出一曲梵唱。\n"NOR,me);          
          me->start_busy(skl);
          addn("force", -nforce, me);
        remove_call_out ("reacting");
        call_out ("reacting",1+random(3),me,people,j);
          remove_call_out("fanchang");             
          call_out("fanchang",skl,me);
          return 1;
        }
        else
        if ( arg == "luo yi" || arg == "jia sha")
        {
          if(!present(arg,me)) return notify_fail("你身上沒有這樣東西。\n");
          if( nmana<30 || (query("mana", me)<nmana) )
            return notify_fail("講經必須法力充盈，你法力不足，神思難以集中。\n");
            
          message_vision(HIW"$N垂目低首，合什于胸，講起了《法華經》。\n"NOR,me);          
          me->start_busy(skl);
          addn("mana", -nmana, me);
        remove_call_out ("reacting");
        call_out ("reacting",1+random(3),me,people,j);
          remove_call_out("jiangjing");                       
          call_out("jiangjing",skl,me);
          return 1;
        }
        else
        if ( arg == "chan zhang" || arg == "jing lun" || arg == "nian zhu")
        {
          if(!present(arg,me)) return notify_fail("你身上沒有這樣東西。\n");        
          if( (nmana<30 || nforce<30) || (query("mana", me)<nmana) || (query("force", me)<nforce) )
            return notify_fail("開設祭壇必須內力法力融而為一，天地交匯，你的狀態還不允許。\n");

          message_vision(HIW"$N開設祭壇，祈天默禱，為百姓降福。\n"NOR,me);          
          me->start_busy(skl); 
          addn("mana", -nmana, me);
          addn("force", -nforce, me);
        remove_call_out ("reacting");
        call_out ("reacting",1+random(3),me,people,j);
          remove_call_out("kaitan");                                         
          call_out("kaitan",skl,me);
          return 1;
        }
}

int fanchang(object me)
{
        message_vision(HIY"$N聲音漸微，曲意不散，圍觀的群眾似乎有所領悟。\n"NOR,me);
        set_temp("obj/done", 1, me);
        set_temp("budao", 1, environment(me));
        return 1;
}

int jiangjing(object me)
{
        message_vision(HIY"$N舌綻蓮花，天花亂墜。周圍的群眾聽得嘖嘖不已。\n"NOR,me);
        set_temp("obj/done", 1, me);
        set_temp("budao", 1, environment(me));
        return 1;
} 

int kaitan(object me)
{
        message_vision(HIY"$N慈悲普渡，寶像莊嚴。周圍的群眾都看得目瞪口呆。\n"NOR,me);
        set_temp("obj/done", 1, me);
        set_temp("budao", 1, environment(me));
        return 1;
}  

string test_name(string arg)
{
  string *temp;
  temp=explode(arg,"/");
  return temp[2];
}

int do_check(string arg)
{
        object me;

        me = this_player();

        if(!arg) return 0;
        if( (arg == "faqi" || arg == "faqi") && query_temp("obj/budao", me)){
                write(
                        "這是一件法器，你布道的目的地是："
                        HIG"「"+query_temp("obj/budaowhere", me)+"」"NOR"。\n"NOR);
        }
        else
        {
        if( (arg == "faqi" || arg == "faqi") && !query_temp("obj/budao", me) )
        write("這是一件法器，隱蘊無上法力。\n");
         }
        return 1;
}

void reacting (object me, string people, int j)
{
  if (j == 0 || !me)
    return;

  if (j == 1)
    message_vision (people+"看見有人在此布道，不禁停了下來，看個究竟。\n",me);
  else
    message_vision (people+"等人見有人在此布道，都圍了過去，看個究竟。\n",me);
}
