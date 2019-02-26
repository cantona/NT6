#include <ansi.h>
inherit ITEM;
int query_autoload()
{
        return 1;
}

void create()
{
        set_name(HIW "補藥" NOR, ({ "bu yao", "yao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                                                                set("long", HIY "這是一顆增加內功的補藥。\n" NOR);
                                                                set("unit", "課");
                set("value", 10000);
                set("weight", 300);
                //增加的技能名為force  
                //如果不為force 那後面的force_point表示增加精力
                set("pill_skill", "force");
                // 是否為特殊武功
                set("skill_mapped", 1);

                //增加武功多少技能點
                set("pill_point", 100);

                //增加多少內力或者精力
                set("force_point", 1);
                                                                
                                                                //加武功成功的描述
                set("pill_msg1", HIR "你只覺一股暖氣散佈全身，説不出的舒服受用。\n" NOR);
                //加武功失敗的描述  這兩項僅當pill_point定義時
                set("pill_msg2", HIY "你只覺一股熱流湧上，內息得到了完全的補充。\n" NOR);
                
                // 增加內力或精力的描述，如果有前面兩條信息，則應作缺省
                set("pill_msg3", HIM "你感到內力又雄厚了一些。\n" NOR);
                set("pill_msg4", HIR "你感到內息澎湃，難以吸收藥力。\n" NOR);

        }
        setup();
}

init()
{
        add_action("do_eat","eat");
        }
int do_eat(string arg)
{
  string skill;
  int pot1, pot2, time;
        object me=this_player();
        int jingli_limit=me->query_skill("taoism", 1)*10;
        int neili_limit=me->query_skill("force")*10;
  pot1 = query("pill_point");
  pot2 = query("force_point");
  time = query("pill_point") / 40; 
  //假設20000點熟練度 就是500condition ==187 min ~= 3hour

//非技能型的藥物重新計算效用時間
  if (! query("pill_point"))
     time = 400 + query("force_point") * 10;
        if (!id(arg))
                return 0;
        if ((int)me->query_condition("pill_drug") > 0)
  {
    write("你覺得現在內息未定，經脈隱隱還能感到真氣衝蕩，不敢貿然服食。\n");
    return 1;
  }
  if (me->is_busy())
  {
          write("你正忙着呢。\n");
          return 1;
          }
        me->apply_condition("pill_drug", time);
  message_vision(HIY + "$N"+ HIY+ "服下一" + query("unit")+query("name") + HIY +"，開始運功吸收藥力。\n" NOR, me);
 log_file("gift/eat_skill",sprintf("%-20seat%-10s[%s]\n",query("name", me)+"("+query("id", me)+")",this_object()->name(),ctime(time())));

        // 如果該藥物有增加技能的功能，則加之
  if (query("pill_skill") && query("pill_point"))
    {
       // 判斷增加的技能是否為特殊技能
         if (query("skill_mapped") >= 1)
            skill = me->query_skill_mapped(query("pill_skill"));
         else
            skill = query("pill_skill");
         tell_object(me, query("pill_msg1"));
         me->improve_skill(skill, pot1);
    }
// 如果該藥物有增加功力的功能，則加之
  if (query("pill_skill") && query("force_point"))
    {
       // 內功型藥物增加內力，否則則增加精力
       if (query("pill_skill") == "force")
           {
           // 提供出信息
                           if( query("max_neili", me)<neili_limit
                            && query("pill_msg3"))
            tell_object(me, query("pill_msg3"));
          else if( query("max_neili", me) >= neili_limit
                && query("pill_msg4"))
            tell_object(me, query("pill_msg4"));
                                        //增加
          addn("max_neili", pot2+random(pot2), me);
          if( query("neili", me)<query("max_neili", me) )
              set("neili",query("max_neili",  me), me);
                } else
                {
                        // 提供出信息
                 if( query("max_jingli", me)<jingli_limit
                                             && query("pill_msg3"))
                         tell_object(me, query("pill_msg3"));
                 else if( query("max_jingli", me) >= jingli_limit
                           && query("pill_msg4"))
                   tell_object(me, query("pill_msg4"));
                                                //增加
                 addn("max_jingli", pot2+random(pot2), me);
          if( query("jingli", me)<query("max_jingli", me) )
                                                        set("jingli",query("max_jingli",  me), me);
                }
        }
        me->start_busy(random(3) + 3);

        destruct(this_object());

        return 1;
}