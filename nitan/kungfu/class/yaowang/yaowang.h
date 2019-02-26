// yaowang.h
#include <ansi.h>
int permit_recruit(object ob)
{
        if( query("detach/藥王谷", ob) || 
            query("betrayer/藥王谷", ob) )
        {
                command("say 你既然已經離開了藥王谷，幹嘛又要回來？");
                return 0;
        }

        if( query("betrayer/times", ob) )
        {
                command("say 閣下不忠不信，我們藥王谷雖小，但卻不收棄師之徒。");
                return 0;
        }

        if( query("family/family_name", ob) && 
            query("family/family_name", ob) != "藥王谷" )
        {
                command("say 你既有了名師指點，就要勤下苦功，勿要三心二意！");
                return 0;
        }

        return 1;
}



/*
void kill_ob(object ob)
{
        set_temp("my_killer",ob);
        remove_call_out("check");
        call_out("check",1);
        ::kill_ob(ob);
}
*/

int accept_fight(object ob)
{
        command("say 我沒有興趣陪你打架。");
        return 0;
}

int accept_hit(object ob)
{
        command("heng");
        command("command 你要找死麼？");
        remove_call_out("check");
        call_out("check",1);
        return 1;
}

int accept_kill(object ob)
{
        command("haha");
        command("say 來的好！我就要你死個痛快！");
        remove_call_out("check");
        call_out("check",1);
        return 1;
}

void check()
{
        object ob=this_object();
//        object me=query_temp("my_killer");
        object me=this_player();
        if(! present(me,environment()) )
        {
                remove_call_out("check");
                return;
        }
        if( me->is_ghost() )
        {
        remove_call_out("check");
        return;
        }
      
        switch(random(4))
        {        
        case 0:
        {
        message_vision(HIR"$N雙手一揮，一支斷腸花直衝$n而去！\n",ob,me);

        if(random(2))
        
                {
                message_vision(HIR"$N只覺一股淡香襲來,頓時腦中一陣麻木！\n"NOR,me,ob);
                me->receive_damage("jing",query("jing", me)/15);
                me->receive_wound("jing",query("jing", me)/20);
                me->receive_damage("qi",query("qi", me)/15);
                me->receive_wound("qi",query("qi", me)/20);
                me->apply_condition("flower_poison", 30 +
                                    (int)me->query_condition("flower_poison"));
                remove_call_out("check");
                }
        else
                {
                message_vision(HIR"$N輕而易舉的躲過了$n的斷腸花！\n"NOR,me,ob);
                call_out("check",2+random(3));
                }
        }
        break;

        case 1:
        {

        message_vision(HIR"$N雙手一搓，空氣中水珠化作冰塊向$n去！\n",ob,me);

        if(random(2))

                {
                message_vision(HIR"只見冰塊自空中直衝而下，鑽入$N體中不見了！\n"NOR,me);
                me->receive_damage("jing",query("jing", me)/15);
                me->receive_wound("jing",query("jing", me)/20);
                me->receive_damage("qi",query("qi", me)/15);
                me->receive_wound("qi",query("qi", me)/20);
                me->apply_condition("iceshock", 30 +
                                    (int)me->query_condition("iceshock"));
                remove_call_out("check");
                }
        else
                {
                message_vision(HIR"$N迎着冰塊而去，用內力將冰塊擊得粉碎!\n"NOR,me);
                call_out("check",2+random(3));
                
                }
        }
        break;

        case 2:
        {

        message_vision(HIR"$N把手中養生丹向$n遞去\n",ob,me);

        if(random(2))

                {
                message_vision(HIR"$N接過養生丹，吃了下去！\n"NOR,me);
                message_vision(HIR"$N只覺肚子「咕咕咕」叫個不停，隨後放了個奇臭"
                                "無比的屁！\n"NOR,me);
                me->receive_damage("jing",query("jing", me)/15);
                me->receive_wound("jing",query("jing", me)/20);
                me->receive_damage("qi",query("qi", me)/15);
                me->receive_wound("qi",query("qi", me)/20);
                set("food", 0, me);
                set("water", 0, me);
                me->apply_condition("hunger", 5 +
                                    (int)me->query_condition("hunger"));
                remove_call_out("check");
                message_vision(HIR"$N餓得快死了。\n"NOR,me);
                message_vision(HIR"$N渴得要虛脱了。\n"NOR,me);
                }
        else
                {
                message_vision(HIR"$N接過養生丹，吃了下去！\n"NOR,me);
                message_vision(HIR"$N只感疲勞一掃而空，再也不覺得飢餓。\n"NOR,me);
                if( query("food", me)<400 )
                        set("food", 400, me);

                if( query("water", me)<400 )
                        set("water", 400, me);
                call_out("check",2+random(3));
                }
        }
        break;
        
        case 3:
        {

        message_vision(HIR"$N右手一甩，一支透骨針直向$n飛去！\n",ob,me);

        if(random(2))

                {
                message_vision(HIR"$N頓時血流如注，頃刻染紅了全身！\n"NOR,me);
                me->receive_damage("jing",query("jing", me)/15);
                me->receive_wound("jing",query("jing", me)/20);
                me->receive_damage("qi",query("qi", me)/15);
                me->receive_wound("qi",query("qi", me)/20);
                me->apply_condition("tougu_zhen", 30 +
                                    (int)me->query_condition("tougu_zhen"));
                remove_call_out("check");
                }
        else
                {
                message_vision(HIR"$N順着透骨針的方向，縱身躍起，躲過這致命一擊！\n"NOR,me);
                call_out("check",2+random(3));
                
                }
        }
        break;

        }
/*
        if( random(10) == 9 )
//      這個地方留待中七星海棠毒，但條件NPC必須是無嗔、石萬嗔。        
*/

}


