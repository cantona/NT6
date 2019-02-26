// /d/city/npc/wenqingqing.c
// by akuma 8:13 PM 5/30/2002

#include <ansi.h>
inherit NPC;
string ask_job(string arg);
string ask_gonglao(string arg);
void create()
{
        set_name("霍元甲", ({ "huo yuanjia", "huo", "yuanjia" }));
        set("long", @LONG
    精武門掌門，「迷蹤拳」的創始人。一心挑起抗擊東瀛流寇，堪稱當世民
族英雄。
LONG);
        set("gender", "男性");
        set("age", 40);
        set("attitude", "friendly");
        set("shen", 100000);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 5000);
        set("max_jing", 1200);
        set("neili", 4000);
        set("max_neili", 4000);
        set("max_jingli", 2000);
        set("jiali", 100);
        set("combat_exp", 1200000);
        set("no_quest_npc", 1);
        set("no_bark", 1);
        create_family("精武門", 1, "掌門");
        /*
        set_skill("force", 150);
        set_skill("yijin-jing", 150);
        set_skill("dodge", 150);
        set_skill("shaolin-shenfa", 150);
        set_skill("cuff", 150);
        set_skill("wenjia-daofa", 160);
        set_skill("parry", 150);
        set_skill("blade", 150);
        set_skill("wenjia-quan", 150);
        set_skill("literate", 110);
        map_skill("force", "yijin-jing");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "wenjia-quan");
        map_skill("parry", "wenjia-daofa");
        map_skill("blade", "wenjia-daofa");
        prepare_skill("cuff", "wenjia-quan");
        */
        set("inquiry", ([
                "抗日": (: ask_job :),
                "次數"  : (: ask_gonglao :),
        ]));
        setup();
        //carry_object(MISC_D("cloth"))->wear();
        //carry_object(MISC_D("qunzi"))->wear();
}

string ask_gonglao(object who)
{
        int i;
        object me = this_player();

        i=query("job/japan_job", me);

        if( !query("job/japan_job", me))return "「抗擊流寇為我輩中人的職責，"+RANK_D->query_respect(this_player())+"也要一起響應才是。」";

        command("massage"+query("id", me));
        return "「你已經抗擊了" + chinese_number(i) + "次東瀛人的侵犯。」";
}

int filldata(object obj)
{
        if ( wiz_level(obj) ) return 0;

        if ( !environment(obj) ) return 0;

        else return 1;
}

string ask_job(string arg)
{
        int count, i, maxexp, maxpot, minexp, k_qi, k_neili, k_jing, k_jiali, total;
        object me = this_player(), ob = this_object(), obj, target;
        object *ob_list, *team;

        ob_list = users();
        ob_list = filter_array(ob_list, (: filldata :));

        if( count_lt(query("combat_exp", me),200000))return "「東瀛人很強悍，你還是不要去冒險了。」";

        if( query("job_done", me) == "japan")return "「東瀛人剛被擊退，一時還不會來。」";

        if ( me->query_condition("killer") ) {
                command("fule"+query("id", me));
                return "「先管好自己吧，你這個殺人犯!";
        }
        if( query("job_done", me) == "japan_job")return "「你不是剛剛幫我偷過一次嗎？」";

        if ( me->query_condition("job_busy" ) ) return "「哇，你比我還忙着，先做完你自己的任務吧。」";

        if ( me->query_condition("gb_busy" ) ) return "「你不是在幫丐幫做任務嗎？」";

        if ( me->query_condition("xx_task" ) ) return "「你不是在幫星宿丁老賊做任務嗎？」";

        if ( me->query_condition("guanfu_task" ) ) return "「你已經投靠官府這棵大樹，還來我在幫助我偷官府的東西？」";

        if ( me->query_condition("niao_job" ) ) return "「你正在幫青鳥送請帖。」";

        if( query_temp("japan/job", me)){
                command("knock"+query("id", me));
                return "「不叫你去做了嗎？怎麼還在這裏？為國抗敵是要作出實際行動來的。」";
        }
        for ( i = 0; i < sizeof(ob_list); i++ ) {
                if( query_temp("japan/job", ob_list[i]))return "「現在東瀛人已經進城，無法在潛入那裏了。」";

                if ( (int)ob_list[i]->query_condition("japan_job") >= 1 ) return "「現在東瀛人已經進城，無法在潛入那裏了。」";
        }
        team = me->query_team();
        count = sizeof(team);

        if ( count <= 1 ) {
                count = 1;
                team = ({ me });
        }
        for ( i = 0; i < count; i++ ) {
                if ( team[i] == 0 ) return "「你的隊伍中現在有人不在。」";

                if( query_temp("japan/job", team[i]))return "「"+query("name", team[i])+"不是已經去了嗎？你還站這裏幹嗎？」";

                if( (uptime()-query("time", ob))<300)return "「剛剛有人進城殺敵去了。」";

                if( query("combat_exp", team[i])<200000)return "「東瀛人很強悍，我不能讓還"+query("name", team[i])+"去冒險了。」";

                if( query("job_done", team[i]) == "japan")return "「東瀛人剛被擊退，一時還不會來。」";
        }
        if ( count > 3 ) return "「人太多了就會被敵人發現。」";

        delete("player", ob);
        minexp=query("combat_exp", me);
        set("player/minname", me->name(), me);
        set("player/max", me, me);
        maxexp = minexp;
        for ( i = 0; i < count; i++ ) {
                if ( team[i] != 0 ) {
                        if( query("combat_exp", team[i])<minexp){
                                minexp=query("combat_exp", team[i]);
                                set("player/minname", team[i]->name(), me);
                        }
                        if( query("combat_exp", team[i])>maxexp){
                                maxexp=query("combat_exp", team[i]);
                                set("player/max", team[i], me);
                                set("player/maxname", team[i]->name(), me);
                        }
                }
        }
        if( (maxexp-minexp)>800000)return "「"+query("player/minname", me)+"和"+query("player/maxname", me)+"的武功差太遠了。」";

        ob=query("player/max", me);
        maxexp=query("combat_exp", ob);

        for ( i = 0; i < count; i++ ) {
                set_temp("japan/job", 1, team[i]);
                team[i]->apply_condition("japan_job", 12);
        }
        count = ( count + 1 ) * 3 + random(count * 3) + random(count + 1);
        if ( count < 2 ) count = 2;

        k_jiali = (int)ob->query_skill("force") / 2;
        k_jiali -= random(40);
        if ( k_jiali < 1 ) k_jiali = 1;

        for ( i = 0; i < count; i++ ) {
                target = new("/job/japan/killer1");
                set("combat_exp", (maxexp*4/5+random(maxexp/5)), target);
                maxpot=query("max_pot", ob)-90-random(10);
                if ( maxpot < 1 ) maxpot = 1;
                set("max", maxpot, target);

                k_qi=query("max_qi", ob);
                k_qi = k_qi * 4 / 5 + random(k_qi / 5);
                k_jing=query("max_jing", ob);
                k_jing = k_jing * 4 / 5 + random(k_jing / 5);
                k_neili=query("max_neili", ob);
                k_neili = k_neili * 4 / 5 + random(k_neili / 5);

                set("max_qi", k_qi, target);
                set("eff_qi", k_qi, target);
                set("qi", k_qi, target);
                set("max_jing", k_jing, target);
                set("eff_jing", k_jing, target);
                set("jing", k_jing, target);
                set("max_neili", k_neili, target);
                set("neili", k_neili, target);
                set("jiali", k_jiali, target);
                target->do_clone();
                target->move("/d/tianjin/town" + random(4) + random(10));
        }
        if ( maxexp > 2000000 ) total = 4;
        else total = 1;

        for ( i = 0; i <= total; i++ ) {
                target = new("/job/japan/killer2");
                set("combat_exp", (maxexp*4/5+random(maxexp*2/5)), target);
                maxpot=query("max_pot", ob)-100-random(20)+random(30);
                if ( maxpot < 1 ) maxpot = 1;
                set("max", maxpot, target);

                k_qi=query("max_qi", ob);
                k_qi = k_qi * 4 / 5 + random(k_qi * 2 / 5);
                k_jing=query("max_jing", ob);
                k_jing = k_jing * 4 / 5 + random(k_jing * 2 / 5);
                k_neili=query("max_neili", ob);
                k_neili = k_neili * 4 / 5 + random(k_neili * 2 / 5);

                set("max_qi", k_qi, target);
                set("eff_qi", k_qi, target);
                set("qi", k_qi, target);
                set("max_jing", k_jing, target);
                set("eff_jing", k_jing, target);
                set("max_jingli", k_neili, target);
                set("jing", k_jing, target);
                set("max_neili", k_neili, target);
                set("neili", k_neili, target);
                set("jiali", k_jiali, target);
                target->do_clone();
                target->move("/d/tianjin/town" + random(4) + random(10));
        }
        set("time", uptime(), ob);
        return "「據息東瀛人又要來天津城燒殺，就去好好地為國殺敵吧。」";
}