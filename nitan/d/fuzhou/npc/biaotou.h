#define lay_exp 20
#define lay_pot 5
#define price_exp 220
#define price_pot 50
int ask_jiaobiao()
{
        object me = this_player();
        object cart,biaotou,money,ob = this_object();
        int i, give_exp, give_pot,give_score;

        if( query_temp("fuwei_destm", me) != query("id", ob) )
        {
                message_vision(HIR"$N問$n道：“搞錯了！搞錯了！你怎麼把給"+query_temp("fuwei_dest", me)+"分局的鏢車送到我這來呢？”\n"NOR,ob,me);
                return 1;
        }
        if (! objectp(cart = present("cart", environment(me))))
        {
                message_vision("$N問$n道：“鏢車呢？那上面可是有好幾萬鏢銀啊！”\n",ob,me);
                return 1;
        }
        if (! objectp(biaotou = present("biao tou", environment(me))))
        {
                message_vision("$N問$n道：“隨隊鏢頭呢？路上丟失人手，你還敢來見我！”\n",ob,me);
                return 1;
        }
        if( query("guarded", cart) != query("id", me) )
        {
                message_vision("$N看了看鏢車，對$n説道：“這鏢車不是你押的。你把鏢車丟哪去了？”\n",ob,me);
                return 1;
        }
        if( query("leader_name", biaotou) != query("id", me) )
        {
                message_vision("$N指着$n説道：“我不是和他一路的，我不認識他。”\n",biaotou, me);
                return 1;
        }
        tell_object(me,HIW+query("name", ob)+"笑道：恭喜你成功將鏢車送到目的地，完成了這項任務！\n\n"NOR);

        message("channel:chat",HIM"【謠言】聽説"+query("guardby", cart)+"成功將鏢車送到目的地了！\n"NOR,users());

        i = 0;
        give_exp=lay_exp*query("total_steps", biaotou);
        give_pot=lay_pot*query("total_steps", biaotou);
        while(i<query("combat_num", biaotou) )
        {
                give_exp += (price_exp/2 + random(price_exp/2));
                give_pot += (price_pot/2 + random(price_pot/2));
                i++;
        }

        message_vision(YEL"$N長出了一口氣道：“哎，終於到了。我可和夥計們喝酒去了。”\n"NOR,biaotou);
        message_vision(YEL"$N和"+query_temp("fuwei_dest", me)+"分局的趟子手們一陣粗言穢語、喊爹罵娘地勾肩搭背一擁出門去了。\n"NOR,biaotou);
        message_vision(HIC"鏢車給"+query_temp("fuwei_dest", me)+"分局的夥計們推進了庫房。\n\n"NOR,biaotou);
        destruct(biaotou);
        destruct(cart);

        if(give_exp > 5000) give_exp = 4000 + random(1000);
        if(give_pot > 1000 ) give_pot = 900 + random(100);
        give_score = 800 + random(400);
        money=new("/clone/money/gold");
        money->set_amount(40);
        money->move(me);

        tell_object(me,sprintf(HIR+query("name", ob)+"對"+query("name", me)+"稱許道：“你被獎勵了！得到%s點經驗和%s點潛能和%s點江湖閲歷。鏢局發給你四十兩黃金做你的薪金和補償你的押金。”\n"NOR,chinese_number(give_exp),chinese_number(give_pot),chinese_number(give_score))+NOR);
        message_vision("$N給$n一些"YEL"黃金"NOR"。\n"NOR, ob, me);
        log_file("mission/ms_biaoche",sprintf("%20s做運送鏢車任務，得到：%4i點EXP和%4i點潛能。\n",
       query("name", me)+"("+getuid(me)+")",give_exp,give_pot));
        addn("combat_exp", give_exp, me);
        addn("potential", give_pot, me);
        addn("score", give_score, me);
        addn("baobiao", 1, me);
        set_temp("prize_reason", "運鏢", ob);
        set_temp("can_give_prize", 1, ob);
        set_temp("prize_exp", give_exp, ob);
        set_temp("prize_pot", give_pot, ob);
        delete_temp("fuwei_destm", me);
        delete_temp("fuwei_dest", me);

        return 1;
}
