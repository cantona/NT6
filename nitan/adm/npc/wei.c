// wei.c

#include <ansi.h>;

inherit NPC;

void create()
{
        set_name("韋小寶", ({ "wei xiaobao", "wei", "xiaobao" }));
        //set("title", HIC"大清國撫遠大將軍"HIY"一等鹿鼎公"NOR);
        set("gender", "男性");
        set("age", 18);
        set("str", 20);
        set("int", 30);
        set("con", 30);
        set("dex", 20);
        set("per", 28);
        set("long", 
"這位少年將軍頭戴紅頂子，身穿黃馬褂，眉花眼笑，賊忒兮
兮，左手輕搖羽扇，宛若諸葛之亮，右手倒拖大刀，儼然關
雲之長，正乃韋公小寶是也。見你看著他，“哈哈哈”，仰
天大笑三聲，學足了戲文中曹操的模樣，你頓時忍不住湊個
趣，問一句：“將軍為何發笑？”\n");
        set("combat_exp", 50000);
        set("shen_type", 1);
        set("attitude", "peaceful");
        set("max_qi", 2500);
        set("max_jing", 1000);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 50);

        set_skill("force", 20);
        set_skill("parry", 20);
        set_skill("hand", 20);
        set_skill("dodge", 20);
        set_skill("shenxing-baibian", 20);
        set_skill("yunlong-shengong", 20);
        set_skill("qianye-shou", 90);

        map_skill("force", "yunlong-shengong");
        map_skill("parry", "qianye-shou");
        map_skill("dodge", "shenxing-baibian");
        map_skill("hand", "qianye-shou");
        prepare_skill("hand", "qianye-shou");
        set("inquiry", ([
            "天地會"  : "別煩我！\n",
            "陳近南"  : "那是我師父！\n",
            "茅十八"  : "就是那十八個毛蟲啊？他還沒死吧！\n",
            "獨臂神尼": "那是我美貌尼姑師父！\n",
            "韋春芳"  : "我娘做婊子生意越來越差了，現在改行作老鴇了！\n",
            "康熙"    : "那是我皇帝師父！\n",
            "小玄子"  : "那是我皇帝師父！\n",
            "小桂子"  : "別提這個名字了，我怕怕！\n",
            "阿珂"    : "她是我明媒正娶的大老婆！\n",
            "雙兒"    : "你認識她？大功告成，親個嘴兒！\n",
            "曾柔"    : "我老婆你問那麼多幹嘛？皇上洪福齊天，我艷福齊天！\n",
            "方怡"    : "我老婆你問那麼多幹嘛？皇上洪福齊天，我艷福齊天！\n",
            "蘇荃"    : "我老婆你問那麼多幹嘛？皇上洪福齊天，我艷福齊天！\n",
            "沐劍屏"  : "我老婆你問那麼多幹嘛？皇上洪福齊天，我艷福齊天！\n",
            "建寧公主": "這個騷娘皮，親厚不及雙兒、美貌不及阿珂、武功不
及蘇荃、機巧不及方怡、天真純善不及沐劍屏、溫柔斯文不及曾柔，
差有一日之長者，不過橫蠻潑辣而已！\n",
        ]) );

        setup();
        carry_object("/d/city/obj/cloth")->wear();
        if (! clonep(this_object()))
        {
                move("/d/city/lichunyuan");
                message_vision("$N笑嘻嘻道：來了來了，我來了。\n", this_object());
                move("/d/city/lichunyuan");
        }
}

mixed accept_ask(object ob, string topic)
{
        object fob, *obs;

        if( topic == query("id", ob) )
        {
                command("laugh " + topic);
                return 1;
        }

        if (topic[0] > 160)
        {
                if( time()-query_temp("ask_wei_time", ob)<2 )
                {
                        tell_object(ob, HIY "韋小寶朝你一瞪眼睛：『別吵！問問題是吧？問那麼急幹嘛？』\n" NOR);
                        return 1;
                }
                
                set_temp("ask_wei_time", time(), ob);
                obs = livings();
                obs = filter_array(obs, (: filter_color($1->name(1)) == $2 && environment($1) :), topic);
                if (sizeof(obs) > 4)
                {
                        obs = 0;
                        message_vision(CYN "$N" CYN "憤聲暗罵，對$n"
                                CYN "瞪著眼睛道：『叫" + topic + "的人滿大街都是，"
                                "自己不會找？』\n" NOR, this_object(), ob);
                        return 1;
                } else
                if (sizeof(obs) > 0)
                {
                        obs = 0;
                        set_temp("pending/ask_wei", topic, ob);
                        /*
                        message_vision(CYN "$N" CYN "嘿嘿姦笑兩聲，對$n"
                                CYN "小聲道：『沒有問題，不過得要一兩黃"
                                "金，不二價！』\n" NOR, this_object(), ob);
                        */
                        tell_object(ob, CYN "韋小寶嘿嘿姦笑兩聲，對你"
                                        CYN "小聲道：『沒有問題，不過得要一兩黃"
                                        "金，不二價！』\n" NOR);
                        return 1;
                } else
                        return;
        }

        fob = find_player(topic);
        if (! fob || ! ob->visible(fob)) fob = find_living(topic);
        if (! fob || ! ob->visible(fob) || ! environment(fob))
                return;

        set_temp("pending/ask_wei", topic, ob);
        /*
        message_vision(CYN "$N" CYN "嘿嘿姦笑兩聲，對$n"
                       CYN "小聲道：“沒有問題，不過得要10兩"
                       "白銀，不二價！”\n" NOR, this_object(), ob);
        */
        tell_object(ob, CYN "韋小寶嘿嘿姦笑兩聲，對你"
                        CYN "小聲道：“沒有問題，不過得要10兩"
                        "白銀，不二價！”\n" NOR);
        return 1;
}

int accept_object(object me, object ob)
{
        string wid;

        if (clonep(this_object()))
        {
                command("hehe");
                command("say 我是真韋小寶，如假包換啊！");
                return 1;
        }

        if( !stringp(query("money_id", ob)) )
        {
                switch(query_temp("wei_refused", me) )
                {
                case 0:
                        command("heihei");
                        command("say 這種破爛你留著吧。");
                        set_temp("wei_refused", 1, me);
                        return 0;

                case 1:
                        message_vision("$N飛起一腳，把$n踢了出去，罵道：搗什麼亂？\n",
                                       this_object(), me);
                        break;

                case 2:
                        message_vision("$N飛起一腳，狠狠的把$n踢了出去，罵道：還來搗亂？\n",
                                       this_object(), me);
                        me->receive_damage("qi", 100);
                        me->receive_wound("qi", 10);
                        break;

                default:
                        message_vision("$N大怒，一招萬佛朝宗，就見$n像紙片一樣飛了出去。\n",
                                       this_object(), me);
                        command("chat*heng"+query("id", me));
                        me->unconcious();
                        break;
                }

                addn_temp("wei_refused", 1, me);
                me->move("/d/city/nandajie2");
                message_vision("只聽“啪”的一聲，$N狠狠的摔在了地上。\n", me);
                return -1;
        }

        if (ob->value() < 500)
        {
                message_vision("$N接過$n遞過去的" + ob->name() +
                               "，皺了皺眉，道：就這點錢？算了，你不要就給我吧！\n",
                               this_object(), me);
                destruct(ob);
                return 1;
        }

        delete_temp("wei_refused", me);
        if( stringp(wid=query_temp("pending/ask_wei", me)) )
        {
                int    i;
                string msg;
                object fob, *obs;

                if (ob->value() < 1000 ||
                    (ob->value() < 10000 && wid[0] > 160))
                {
                        message_vision("$N冷笑一聲道：“就這點錢？"
                                       "你還是打發魯有腳還差不多。”\n",
                                       this_object());
                        return 0;
                }

                delete_temp("pending/ask_wei", me);

                if (wid[0] > 160)
                {
                        obs = livings();
                        obs = filter_array(obs, (: filter_color($1->name(1)) == $2 && environment($1) :) ,wid);
                        if (! sizeof(obs))
                        {
                                message_vision("$N撓撓頭對$n道：“怪事... 剛"
                                               "才我還有他的消息呢，怎麼這麼一會兒...”\n",
                                               this_object(), me);
                                return 0;
                        }
                        msg = " \n據可靠消息，叫" + wid + "的一共有" + 
                              chinese_number(sizeof(obs)) + "個人！\n";                     
                        for (i = 0; i < sizeof(obs); i++)
                                msg+=obs[i]->name(1)+"("+query("id", obs[i])+")"+
                                       "剛才在" + environment(obs[i])->short() + "。\n";
                        destruct(ob);
                        obs = 0;
                        command("whisper"+query("id", me)+msg);
                        return 1;
                }
                                
                fob = find_player(wid);
                if (! fob || ! me->visible(fob)) fob = find_living(wid);
                if (! fob || ! me->visible(fob) || ! environment(fob))
                {
                        message_vision("$N撓撓頭對$n道：“怪事... 剛"
                                       "才我還有他的消息呢，怎麼這麼一會兒...”\n",
                                       this_object(), me);
                        return 0;
                }

                destruct(ob);
                command("whisper"+query("id", me)+
                        " 據可靠消息，這個人剛才在" +
                        environment(fob)->short() + "。");
                return 1;
        }

        message_vision("$N樂得合不攏嘴，連忙接過" + ob->name() + 
                       "，點頭哈腰的對$n道：好！好！\n", this_object(), me); 

        destruct(ob);
        return 1;
}
