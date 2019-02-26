//Cracked by Kafei
// qingzhu-ling.c 青竹令

#include <ansi.h>;

inherit ITEM;

void create()
{
        set_name("青竹令", ({"qingzhu ling", "bamboo", "ling"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "面");
                set("long","這是一面青竹削制的令牌，正面青光發亮，燒蝕着「丐幫」兩個大字。\n");
                set("material", "bamboo");
        }
}

void init()
{
        add_action("do_bihua", "bihua");
        add_action("do_bihua", "bi");
        add_action("do_halt", "halt");
        add_action("do_halt", "h");
        add_action("do_look", "look");
        add_action("do_look", "l");
}

int do_bihua(string arg)
{     
        object ob1, ob2, old_target;
        string family;

        ob1 = this_player();
        
        if( !arg || arg=="" ) 
        return notify_fail("你想跟誰比劃？\n");  

        if( query_temp("busy", this_object()) )
        return notify_fail("每次只能有兩人蔘加比武。\n");

        if( !objectp( ob2 = present(arg, environment(ob1)) ) ) 
        return notify_fail("你想跟誰比劃？\n");

        if( query_temp("owner", this_object()) != query("name", ob1) )
        return notify_fail("你不是這快青竹令的主人！\n");

        if( !stringp(family=query("family/family_name", ob1)) )
        return notify_fail("你不是丐幫弟子，不能使用青竹令跟人比劃武功！\n");

        if( !stringp(family=query("family/family_name", ob2)) )
        return notify_fail("對方不是丐幫弟子，你不能使用青竹令與之比劃武功！\n");

        if( query("rank", ob2) != query("rank", ob1) )
        return notify_fail("對方在幫中的等級與你不同，不能互相較藝！\n");

        if( !objectp( present("qingzhu ling", ob2) ) ) 
        return notify_fail("對方沒有青竹令，你們不能互相較藝！\n");

        if( query_temp("gaibang_winner", ob1) )
        return notify_fail("你已經技壓同門，趕快找大師兄比試吧 ！\n");

        if( query_temp("loser", this_object()) == query("name", ob2) )
        return notify_fail("對方是你的手下敗將，你不能與之比劃武藝！\n");

        if( ob1 == ob2)    
        return notify_fail("你不能攻擊自己。\n");

        if( query_temp("win_times", this_object()) >= 1 )
        return notify_fail("你已經戰勝同門一次，不必繼續比試武藝。\n");

        if( userp(ob2) && query_temp("pending/fight", ob2) != ob1){
                message_vision("\n$N對着$n説道：" 
                        + RANK_D->query_self(ob1) 
                        + ob1->name() + "領教師兄的高招！\n\n", ob1, ob2);
                if( objectp(old_target=query_temp("pending/fight", ob1)) )
                        tell_object(old_target, YEL + ob1->name() + "取消了和你比試的念頭。\n" NOR);
                set_temp("pending/fight", ob2, ob1);
                tell_object(ob2,YEL"如果你願意和對方進行比試，請你也對"+ob1->name()+"("+query("id", ob1)+")"+"下一次bihua指令。\n"NOR);

                write(YEL "由於對方是由玩家控制的人物，你必須等對方同意才能進行比試。\n" NOR);
                return 1;
        }
            
        delete_temp("halted", ob1);
        delete_temp("halted", ob2);

        remove_call_out("fighting");
        call_out("fighting", 2, ob1, ob2);

        return 1;
}

void fighting(object ob1, object ob2)
{
        message_vision("\n" + ob1->name() + "與" + ob2->name() + "開始比武！\n\n", ob1);

        remove_call_out("checking");
        call_out("checking", 0, ob1, ob2);

        this_object()->set_temp("busy");

        ob1->fight_ob(ob2);
        ob2->fight_ob(ob1);
}

int checking(object ob1, object ob2)
{
        object ob; 
        
        if(ob1->is_fighting()) 
        {
                call_out("checking", 1, ob1, ob2);
                return 1;
        }

        delete_temp("pending/fight", ob1);
        delete_temp("pending/fight", ob2);

        if ( !present(ob1, environment(ob2)) ) return 1;

        if ( !present(ob2, environment(ob1)) ) return 1;
           
        if( query_temp("halted", ob1) )
        {
                delete_temp("halted", ob1);
                return 1;
        }

        if( query_temp("halted", ob2) )
        {
                delete_temp("halted", ob2);
                return 1;
        }

        if( query("qi", ob1)*2>query("max_qi", ob1) )
        {
                if( query("qi", ob2)*2>query("max_qi", ob2)){
                        message_vision( ob1->name() + "與" + ob2->name() + 
                        "比武不分勝負！\n", ob1);
                        return 1;
                }
                message_vision( ob2->name() + "向" + ob1->name() + 
                        "拱了拱手，在青竹令上劃了一道記號，並簽上自己的名字。\n", ob1);

                ob = present("qingzhu ling", ob1);
                addn_temp("win_times", 1, ob);
                set_temp("loser",query("name",  ob2), ob);
                set_temp("gaibang_winner", 1, ob1);
        } 
        else 
        {
                message_vision( ob1->name() + "向" + ob2->name() + 
                        "拱了拱手，在青竹令上劃了一道記號，並簽上自己的名字。\n", ob1);

                ob = present("qingzhu ling", ob2);
                addn_temp("win_times", 1, ob);
                set_temp("loser",query("name",  ob1), ob);
                set_temp("gaibang_winner", 1, ob2);
        }

        delete_temp("busy", this_object());

        return 1;

}

int do_halt()
{
        object me = this_player();

        if (me->is_fighting())
        set_temp("halted", 1, me);
        return 0;
}

int do_look(string arg)
{
        object ob = this_object();

        if( !arg || arg == "" ) return 0;

        if( present(arg, this_player()) != ob ) return 0;

        if( query_temp("win_times", ob)){
                tell_object( this_player(), 
                "這是一面青竹削制的令牌，正面青光發亮，燒蝕着「丐幫」兩個大字，\n" +
                "青竹令的背面刻著一道表示勝利的記號。反面是"+query_temp("loser", ob)+
                "的簽名。\n");

                tell_object(this_player(),"\n這塊青竹令由簡長老簽發，屬於"+query_temp("owner", ob)+"。\n");
        }
        else         tell_object( this_player(), 
                "這是一面青竹削制的令牌，正面青光發亮，燒蝕着「丐幫」兩個大字。\n" );

        return 1;
}