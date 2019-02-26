// master.c

#include <ansi.h>
#include <login.h>

string *all_basic= ({
        "array",        "axe",                  "blade",        "claw",         "club",
        "cuff",         "dagger",               "dodge",        "finger",       "force",
        "hammer",       "hand",                 "hook",         "leg",          "magic",
        "parry",        "spear",                "staff",        "stick",        "strike",
        "sword",        "throwing",             "unarmed",      "whip",
});

int is_master() { return 1; }
int can_learn_from() { return 1; }
int query_auto_perform() { return 2; }

int prevent_learn(object me, string skill)
{
        mapping fam;

        if( !me->is_apprentice_of(this_object()) &&
            mapp(fam = query("family", me)) &&
            fam["family_name"] == query("family/family_name") &&
            fam["generation"] > query("family/generation") ) {
                command("say 雖然你是我門下的弟子，可是並非我的嫡傳弟"
                        "子... 還是去找你師父學吧。");
                return 1;
        }

        return 0;
}

void attempt_detach(object me)
{
        string *fams;

        if( !me->is_apprentice_of(this_object()) ) {
                 command("say 邊去，找你師傅。");
                return;
        }

        command("sigh");

        // 一轉後只可無損失脱離一次
        fams = query("reborn/fams", me);
        if( !arrayp(fams) || member_array(query("family/family_name", me), fams) == -1 )
        {
                command("say 走吧走吧！你走吧！把你學到的武功留下！");

                if( me->query_family() == "桃花島" )
                        set("combat_exp", query("combat_exp", me) / 3, me);
                me->skill_expell_penalty();
                me->unconcious();

                message_vision("$N將手掌粘在$n的背後，喃喃自語，"
                               "不知道在説些什麼。\n", this_object(), me);
                addn("detach/"+query("family/family_name", me), 1, me);
        }
        command("say 走吧走吧！你現在可以走吧！");
        delete("family", me);
        delete("quest", me);
        delete("quest_count", me);
        set("title", "普通百姓", me);
        me->save();
}


nomask void master_accept_kill(object me)
{
        object *inv;

        inv = all_inventory(environment());
        for(int i = 0; i < sizeof(inv); i++) {
                if( !inv[i]->is_character()
                ||  !living(inv[i])
                ||  inv[i] == this_object()
                ||  inv[i] == me
                ||  playerp(inv[i])
                ||  !inv[i]->query_family()
                ||  inv[i]->query_family() != this_object()->query_family() )
                        continue;
                else
                {
                        message_vision(sprintf("$N朝$n着喊道：“你%s，真是活的不耐煩了！！”\n\n",
                                (me->is_apprentice_of(this_object()))?
                                "膽敢欺師滅祖":((query("family/family_name", me) == query("family/family_name"))?
                                "連同門師傅都要殺":"敢動本門師傅" )),inv[i],me );
                        inv[i]->kill_ob(me);
                        me->kill_ob(inv[i]);
                }
        }
        return;
}

public mixed teach_perform(object me, object master, mapping args)
{
        string family,name,perform,msg,msg1,msg2;
        string sk1, sk2, sk3, sk4       ;
        int lv1, lv2, lv3, lv4          ;
        int i,free,gongxian,shen,force,neili;

        // 至少要三個參數：武功名、絕招中文名、絕招英文名
        if( !stringp(name = args["name"])
        ||  !stringp(perform = args["perform"])
        ||  !stringp(sk1 = args["sk1"])
          )
                return 0;

        // 判斷所屬門派，如為公共傳授，應添加 free 參數
        if( !intp(free = args["free"]) || free <= 0 ) {
                family = query("family/family_name", master);

                if( query("family/family_name", me) != family )
                        return RANK_D->query_respect(me) + "與我" +
                               family + "素無淵源，不知此話從何説起。";
        }

        // 如果已經學會，則返回
        if( query("can_perform/"+sk1+"/"+perform, me) )
                return "這招你不是已經會了麼，還來問我做什麼？";

        //判斷神
        if( intp(shen = args["shen"]) ) {
                if( shen < 0 && query("shen", me) > shen )
                        return "哼！像你這樣的心慈手軟之輩，又能幹成什麼大事？";
                if( shen > 0 && query("shen", me) < shen )
                        return "你目前所做的俠義正事不夠，這招暫時還不能傳你。";
        }

        // 判斷門派貢獻的要求
        if( intp(gongxian = args["gongxian"])
        &&  query("family/gongji", me) < gongxian)
                return "你還是多為本門作一些貢獻再來吧。";

        // 判斷特定的武功需求，其中 sk1 應為主 skills
        if( !me->query_skill(sk1, 1) )
                return "你連" + to_chinese(sk1) + "都沒學過，還問什麼絕招？";

        if( intp(lv1= args["lv1"]) && me->query_skill(sk1, 1) < lv1 )
                return "你的" + to_chinese(sk1) + "還沒學到家，去練好了再來吧。";

        if( stringp(sk2 = args["sk2"]) && intp(lv2 = args["lv2"]) && me->query_skill(sk2,1) < lv2 )
                return "你的" + to_chinese(sk2) + "還沒有到家，去練好了再來吧。";

        if( stringp(sk3 = args["sk3"]) && intp(lv3 = args["lv3"]) && me->query_skill(sk3,1) < lv3 )
                return "你的" + to_chinese(sk3) + "還沒到家，去練好了再來吧。";

        if( stringp(sk2 = args["sk4"]) && intp(lv2 = args["lv4"]) && me->query_skill(sk4,1) < lv4 )
                return "你的" + to_chinese(sk4) + "還沒到家，去練好了再來吧。";

        // 判斷絕招對內功的要求
        if( intp(force = args["force"]) && me->query_skill("force") < force )
                return "你的基本內功火候還不夠，等練好了再來吧。";

        // 判斷絕招對內力上限的要求
        if( intp(neili = args["neili"]) && query("max_neili", me) < neili )
                return "你的內力修為還不夠，學不了這招！";

        // 給予學習絕招的描述信息
        if( stringp(msg1 = args["msg1"]) ) {
                msg = msg1;
        } else {
                switch (random(4))
                {
                case 0 :
                        msg = "$N微微點了點頭，伸手將$n" HIY "招"
                              "至身前，低聲在$n" HIY "耳畔講述了"
                              "半天，還不時伸手比劃演示着什麼，所"
                              "講全是" + to_chinese(sk1) + "的精"
                              "微要詣。$n" HIY "聽後會心一笑，看"
                              "來對$N的教導大有所悟。";
                        break;

                case 1 :
                        msg = "$N凝視了$n" HIY "許久，方才微微點"
                              "了點頭，説道：“我給你演示一遍，可"
                              "看清楚了。”$N話音剛落，隨即起身而"
                              "立拉開架勢，慢慢的演示開" +
                              to_chinese(sk1) + "的招式。$n" HIY
                              "只覺$N招式精奇，神妙非凡，實乃前所"
                              "未聞，頓時大有感悟。";
                        break;

                case 2 :
                        msg = "$N看了看$n" HIY "，頗為讚許的説道"
                              "：“想不到你的" + to_chinese(sk1) +
                              "進展如此神速，已達此般境界。不易，"
                              "不易。今日我便傳你這招，可記清楚了"
                              "。”説完$N便將$n" HIY "招至跟前，"
                              "耐心講述" + name + "的諸多精要，$n"
                              HIY "一邊聽一邊不住的點頭。";
                        break;

                default :
                        msg = "$N哈哈一笑，對$n" HIY "讚道：“不"
                              "錯，不錯。依照你現在" +
                              to_chinese(sk1) + "的造詣，我便傳授"
                              "你" + name + "又有何妨？”説完便只"
                              "見$N從懷中摸出一本頗為古舊的小冊子"
                              "，指着其中一段對$n" HIY "仔細講解"
                              "。$n" HIY "聽後沉思良久，若有所悟。";
                        break;
                }
        }
        message_vision(HIY "\n" + msg + "\n\n" NOR, master, me);

        // 學會該項絕招
        addn("can_perform/"+sk1+"/"+perform, 1, me);

        // 給予提示信息
        tell_object(me, HIC "你學會了「" HIW + name +
                         HIC "」。\n" NOR);

        // 提升相對應的武功技能
        if( stringp(sk1) ) me->improve_skill(sk1, 500000);
        if( stringp(sk2) ) me->improve_skill(sk2, 500000);
        if( stringp(sk3) ) me->improve_skill(sk3, 500000);
        if( stringp(sk4) ) me->improve_skill(sk4, 500000);


        // 提升主 skill 的基本技能
        for (i = 0; i < sizeof(all_basic); i++) {
                if( SKILL_D(sk1)->valid_enable(all_basic[i]) )
                        me->improve_skill(all_basic[i], 500000);
        }

        // 消耗門派貢獻值
        if( intp(gongxian) && gongxian > 0 )
                addn("family/gongji", -gongxian, me);
        // 最後的回答信息
        if( stringp(msg2 = args["msg2"]) ) {
                msg = msg2;
        } else {
                // 最後的回答信息
                switch (random(5))
                {
                case 0 :
                        msg = "剛才的招式，你明白了多少？";
                        break;
                case 1 :
                        msg = "招式便是如此，你自己下去領悟吧。";
                        break;
                case 2 :
                        msg = "剛才我所傳授的全是該招的精意，可記牢了。";
                        break;
                case 3 :
                        msg = "這招你下去後需勤加練習，方能運用自如。";
                        break;
                default :
                        msg = "這招其實並不複雜，你自己下去練習吧。";
                        break;
                }
        }
        return msg;
}
/* 例子
string ask_skill2(object me,string arg)
{
        return teach_perform(this_player(),this_object(),([
                                "perform"       : "fugu",               //pfm的代碼必需參數
                                "name"          : "附骨纏身",           //pfm的名稱
                                "sk1"           : "jinshe-zhang",       //主要的武功的id
                                "lv1"           : 100,                  //主要的武功的等級
                                "sk2"           : "strike",             //需要武功sk2的id
                                "lv2"           : 100,                  //需要武功sk2 的等級
//                              "sk3"           : "throwing",           //武功sk3
//                              "lv3"           : 100,
//                              "sk4"           : "throwing",           //武功sk4
//                              "lv4"           : 100,
                                "neili"         : 300,                  //需要內力多少
                                "free"          : 1,                    //free=1不需要同一門派
//                              "shen"          : 100,                  //需要的shen
//                              "msg1"          : "教的描述",
//                              "msg2"          : "教完的描述",

                                                                                                                                ]));
}
*/
