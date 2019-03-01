// suanming.c
#include <ansi.h>
inherit NPC;
string ask_where();
string ask_chance();

void create()
{
        set_name("李半仙", ({ "li banxian", "li", "banxian", "xiansheng" }) );
        set("nickname", "算命先生" );
        set("gender", "男性" );
        set("age", 92);
        set("long", "這位算命先生坐在那裡，一副神秘莫測的樣子。\n");
        set("combat_exp", 10000);
        set("attitude", "friendly");
        set("no_get", 1);
        set("inquiry", ([
                "name" : "在下姓李，因為算命算得準，所以大家都尊稱我為李半仙。",
                "rumors" : "要想知道你今生的禍福榮辱，那就問我來算命吧。",
                "行蹤": (: ask_where :),
                "where": (: ask_where :),
                "機會" : (: ask_chance :),
                "算命" : "我的價錢最公道，不多不少，只要一兩黃金。"
        ]) );
        set("chat_chance", 10);
        set("chat_msg", ({
                "李半仙吆喝道：鐵嘴神算，價錢公道，相資一兩黃金。\n",
                "李半仙吆喝道：命運機緣，欲知詳情，相資十兩黃金。\n",
                (: random_move :),
                "李半仙對你說道：客倌請留步，卜個吉兇如何？\n",
        }) );
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

string ask_chance()
{
    object me = this_player();
    me->set_temp("ask_chance",1);
    return "機會是吧？待老夫掐指算來......恩，如此這般，看來此事頗為不易啊！"NOR;
}

string ask_where()
{
    object me;
    string name;
    mapping quest;
    me=this_player();

    if ( !mapp(quest = me->query_temp("quest")))
        return "你這人真是的，沒事問別人的行蹤幹嘛？";

    if (!me->query_temp("suanming_paid"))
        return "什麼？你說什麼？我聽不見呢。\n";

    if (!stringp(name = me->query_temp("quest/name")))
        return "這，你要問誰啊？\n";

    if (!stringp(name = me->query_temp("quest/place")))
        return "唉喲，這人可不知道在哪呢。\n";

    me->delete_temp("suanming_paid");
    return me->query_temp("quest/name")+CYN"是吧？聽說有人看見他曾經出現在"+name+CYN"一帶。"NOR;
}


int accept_object(object who, object ob)
{
        int kar, per, max_age;
        int tc , temp;

        if (!who->query_temp("ask_chance") && ob->query("money_id") && ob->value() >= 5000)
        {
                message_vision("算命先生對著$N端詳了一陣。\n", who);
                who->set_temp("suanming_paid", 1);
                per = who->query("per");
                if (random(2)) per += random(10);
                  else per -= random(7);
                kar = who->query("kar");
                if (random(2)) kar += random(10);
                  else kar -= random(7);
                max_age = 67 + random(7) + who->query("con") - who->query("kar") - who->query("per")
                             + who->query("pur") + who->query("shen")/1000000;

                if (per > 25) {
                        write("算命先生景仰地說：“看" + RANK_D->query_respect(who) + "相貌堂堂，天庭飽滿，地廓方圓，");
                        if (random (kar) > 25) write("真乃富貴之象也！”\n");
                        else if (random (kar) >= 20) write("一生運勢平平，也算過得去了。”\n");
                        else if (random (kar) >= 15) write("可惜沖撞了小人。”\n");
                        else write("不過你霉運當頭，行事可要小心了！”\n");
                }
                else if (per >= 20) {
                        write("算命先生清了清嗓子，說：“看" + RANK_D->query_respect(who) + "相貌屬中上之資，");
                        if (random (kar) > 25) write("一生大富大貴，子孫多多。”\n");
                        else if (random (kar) >= 20) write("一生運勢平平，也算過得去了。”\n");
                        else if (random (kar) >= 15) write("就可惜沖撞了小人。”\n");
                        else write("不過你霉運當頭，行事可要小心了！”\n");
                }
                else if (per >= 15) {
                        write("算命先生有點勉強地說：“看" + RANK_D->query_respect(who) + "相貌平平，倒也還能算是中人之資，");
                        if (random (kar) > 25) write("前生一定行了善事，一生大富大貴，子孫多多。”\n");
                        else if (random (kar) >= 20) write("一生也就運勢平平，只能算過得去。”\n");
                        else if (random (kar) >= 15) write("就可惜沖撞了小人。”\n");
                        else write("你最近霉運當頭，行事可要小心了！”\n");
                }
                else {
                        write("算命先生很厭惡地說：“看" + RANK_D->query_respect(who) + "五官挪位，印堂發暗，");
                        if (random (kar) > 25) write("不過你前生一定行了善事，一生大富大貴，子孫多多。”\n");
                        else if (random (kar) >= 20) write("倒還有些運氣，也算過得去了。”\n");
                        else if (random (kar) >= 15) write("所以你就一生坎坷，多遇小人。”\n");
                        else write("活該倒霉，當有血光之災！”\n");
                }
                write("算命先生掐指一算，道：“" + RANK_D->query_respect(who) + "今生估計壽至" + chinese_number(max_age) + "歲。”\n");
                return 1;
        } else {
                if (who->query_temp("ask_chance") && ob->query("money_id") && ob->value() >= 100000) {
                        write("算命先生當即說道：“好說，好說，一切都好說。”\n");

                        tc = who->query("combat_exp")/1000000;
                        write("算命先生說道：“看" + RANK_D->query_respect(who) + "的命相，當前每個謎題總共可有" + chinese_number(tc) + "次機會。”\n");

                        if (!who->query("quest/jiuyin1/pass")) {
                                temp = tc - who->query("quest/jiuyin1/fail");
                                if (temp < 0) temp = 0;
                                write("算命先生說道：“" + RANK_D->query_respect(who) + "還有" + chinese_number(temp) + "次機會，解開九陰真經上冊。”\n");
                        }

                        if (!who->query("quest/jiuyin2/pass")) {
                              	tc = who->query("combat_exp")/500000;
                                temp = tc - who->query("quest/jiuyin2/fail");
                                if (temp < 0) temp = 0;
                                write("算命先生說道：“" + RANK_D->query_respect(who) + "還有" + chinese_number(temp) + "次機會，解開九陰真經下卷。”\n");
                        }

                        if (!who->query("jiuyin/emeipass") && (who->query("family/family_name") == "峨嵋派")) {
                                temp = tc - who->query("jiuyin/emeifail");
                                if (temp < 0) temp = 0;
                                write("算命先生說道：“" + RANK_D->query_respect(who) + "還有" + chinese_number(temp) + "次機會，解開峨嵋九陰真經。”\n");
                        }
                        if (!who->query("quest/qianzhu/pass") && (who->query("gender") == "女性" )) {
                        	      tc = who->query("combat_exp")/500000;
                                temp = tc - who->query("quest/qianzhu/fail");
                                if (temp < 0) temp = 0;
                                write("算命先生說道：“" + RANK_D->query_respect(who) + "還有" + chinese_number(temp) + "次機會，解開千蛛萬毒手。”\n");
                        }
                        
                        if (!who->query("quest/jiuyingm/pass") && (who->query("family/family_name") == "古墓派")) {
                                tc = who->query("combat_exp")/500000;
                                temp = tc - who->query("jiuyin/jiuyingm/fail");
                                if (temp < 0) temp = 0;
                                write("算命先生說道：“" + RANK_D->query_respect(who) + "還有" + chinese_number(temp) + "次機會，解開古墓九陰真經。”\n");
                        }

                        if (!who->query("quest/jiebai/pass")
                            && who->query("class") !="bonze"
                            && who->query("class") != "huanxi"
                            && (who->query("gender") == "男性" || who->query("gender") == "女性")
                            && (int)who->query("shen") >= 0
                            && (int)who->query("combat_exp") >= 1000000) {
                                temp = tc - who->query("quest/jiebai/fail");
                                if (temp < 0) temp = 0;
                                write("算命先生說道：“" + RANK_D->query_respect(who) + "還有" + chinese_number(temp) + "次機會，和老頑童結拜。”\n");

                                temp = tc - who->query("quest/hubo/fail");
                                tc = who->query("combat_exp")/500000;
                                if (temp < 0) temp = 0;
                                write("算命先生說道：“" + RANK_D->query_respect(who) + "還有" + chinese_number(temp) + "次機會，學會雙手左右互搏。”\n");
                        }

                        if (who->query("quest/jiebai/pass") && !who->query("double_attack")) {
                                tc = who->query("combat_exp")/500000;
                                temp = tc - who->query("quest/hubo/fail");
                                if (temp < 0) temp = 0;
                                write("算命先生說道：“" + RANK_D->query_respect(who) + "還有" + chinese_number(temp) + "次機會，學會雙手左右互搏。”\n");
                        }

/*                       if (!who->query("lbwb/lbwb1pass") && !who->query("lbwb/lbwb2pass")) {
                                temp = tc - who->query("lbwb/lbwb1fail");
                                if (temp < 0) temp = 0;
                                write("算命先生說道：“" + RANK_D->query_respect(who) + "還有" + chinese_number(temp) + "次機會，在無量玉洞學到凌波微步。”\n");

                                temp = tc - who->query("lbwb/lbwb2fail");
                                if (temp < 0) temp = 0;
                                write("算命先生說道：“" + RANK_D->query_respect(who) + "還有" + chinese_number(temp) + "次機會，從段譽處學到凌波微步。”\n");
                        }
*/
                        if (who->query("combat_exp")<1000000) {
                                tc=0;
                        }
                        else
                        {
                                tc = who->query("combat_exp")/1000000;
                        }
                        temp = who->query("user_weapon_imbued");
                        write("算命先生說道：“" + RANK_D->query_respect(who) + "有" + chinese_number(tc) + "次打造機會，已經用了" + chinese_number(temp) +"次了。”\n");

                        who->delete_temp("ask_chance");
                        return 1;
                }
        }
        return 0;
}

