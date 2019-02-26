// masterd.c
// Written by Vin for Heros.cn 2002/07/13.

#include <ansi.h>
inherit F_DBASE;

// 定義提供給外部調用的接口函數
public mixed teach_pfm(object who, object ob, mapping b);
public mixed give_item(object who, object ob, mapping b);

// 對應下面的提升 skills 的可激發技能
string *valid_types = ({
        "force",
        "dodge",
        "unarmed",
        "cuff",
        "strike",
        "finger",
        "hand",
        "claw",
        "sword",
        "blade",
        "staff",
        "hammer",
        "club",
        "whip",
        "dagger",
        "throwing",
        "parry",
        "magic",
        "medical",
        "poison",
        "chuixiao-jifa",
        "tanqin-jifa",
        "guzheng-jifa",
        "cooking",
});

// 傳授武功絕招
public mixed teach_pfm(object who, object ob, mapping b)
{
        string name, perform;           // 絕招名稱及絕招進程記錄
        int i;                          // 導入主要技能升級的循環符
        string msg;                     // 對於某些返回信息的描述
        string msg1, msg2;              // 顯示出的信息及回答信息
        string sk1, sk2, sk3, sk4, sk5; // 所需要的武功名稱
        int lv1, lv2, lv3, lv4, lv5;    // 所對應的武功等級
        int reborn;                     // 轉世幾次要求
        int free;                       // 與下面的門派所對應，如果設置該參數，則
                                        // 無須考慮傳授者與被傳授者的門派是否一致
        string family;                  // 傳授者的門派，如果不設置公共參數，則要
                                        // 傳授雙方的門派為同一門派
        int gongxian, shen;             // 需求的貢獻及神
        int force, dodge;               // 需求的內功等級與輕功等級
        int neili, jingli;              // 需求的最大內力與最大精力
        string temp1, temp2, temp3;     // 要求的進程記錄
        string tmsg1, tmsg2, tmsg3;     // 要求的進程記錄的回答信息
        string *fams;

        // 如果沒有指明對象，則返回
        if (! stringp(name = b["name"])
           || ! stringp(perform = b["perform"]))
                return 0;

        // 判斷所屬門派，如為公共傳授，應添加 free 參數
        if (! intp(free = b["free"]) || free <= 0)
        {
                family=query("family/family_name", ob);
                fams = query("reborn/fams", who);

                if( query("family/family_name", who) != family &&
                    (!arrayp(fams) || member_array(family, fams) == -1) )
                        return RANK_D->query_respect(who) + "與我" +
                               family + "素無淵源，不知此話從何説起。";
        }

        // 如果已經學會，則返回
        if( query(perform, who) )
        {
                switch (random(4))
                {
                case 0 :
                        msg = "自己下去練，還來羅嗦什麼。";
                        break;

                case 1 :
                        msg = "我不是已經教過你了麼？自己下去練。";
                        break;

                case 2 :
                        msg = "我能教的都教給你了，剩下的你自己領悟吧。";
                        break;

                default :
                        msg = "這招你不是已經會了麼，還纏着我做甚？";
                        break;
                }
                return msg;
        }

        if( intp(reborn = b["reborn"]) )
        {
                if( query("reborn/times", who) < reborn )
                        return "你目前經歷的轉世體驗不夠，這招"
                               "暫時還不能傳你。";
        }

        // 判斷正神或負神的要求
        if (intp(shen = b["shen"]))
        {
                // 如果要求為負神，則作出大於判斷
                if( shen<0 && query("shen", who)>shen )
                        return "哼！像你這樣的心慈手軟之輩，又"
                               "能幹成什麼大事？";

                // 如果要求為正神，則作出小於判斷
                if( shen>0 && query("shen", who)<shen )
                        return "你目前所做的俠義正事不夠，這招"
                               "暫時還不能傳你。";
        }

        // 判斷門派貢獻的要求
        if (intp(gongxian = b["gongxian"])
            && query("family/gongji", who)<gongxian )
                return "你為"+query("family/family_name", who)+
                       "作出的貢獻不夠，這招暫時還不能傳你。";

        // 判斷特定的進程記錄要求
        if( stringp(temp1=b["temp1"]) && !query(temp1, who) )
        {
                if (stringp(tmsg1 = b["tmsg1"]))
                        return tmsg1;
                else
                        return "現在某些機緣未到，這招我暫時還"
                               "不能傳給你。";
        }

        if( stringp(temp2=b["temp2"]) && !query(temp2, who) )
        {
                if (stringp(tmsg2 = b["tmsg2"]))
                        return tmsg2;
                else
                        return "現在某些機緣未到，這招我暫時還"
                               "不能傳給你。";
        }

        if( stringp(temp3=b["temp3"]) && !query(temp3, who) )
        {
                if (stringp(tmsg3 = b["tmsg3"]))
                        return tmsg3;
                else
                        return "現在某些機緣未到，這招我暫時還"
                               "不能傳給你。";
        }

        // 判斷特定的武功需求，其中 sk1 應為主 skills
        if (stringp(sk1 = b["sk1"]) && intp(lv1 = b["lv1"]))
        {
                if (who->query_skill(sk1, 1) <= 0)
                        return "你連" + to_chinese(sk1) + "都"
                               "未曾學過，何談絕招可言？";

                if (who->query_skill(sk1, 1) < lv1)
                        return "你對" + to_chinese(sk1) + "的"
                               "瞭解還不夠，尚且無法領悟此招。";
        }

        if (stringp(sk2 = b["sk2"]) && intp(lv2 = b["lv2"])
           && who->query_skill(sk2, 1) < lv2)
                return "你對" + to_chinese(sk2) + "的瞭解還不"
                       "夠，尚且無法領悟此招。";

        if (stringp(sk3 = b["sk3"]) && intp(lv3 = b["lv3"])
           && who->query_skill(sk3, 1) < lv3)
                return "你對" + to_chinese(sk3) + "的瞭解還不"
                       "夠，尚且無法領悟此招。";

        if (stringp(sk4 = b["sk4"]) && intp(lv4 = b["lv4"])
           && who->query_skill(sk4, 1) < lv4)
                return "你對" + to_chinese(sk4) + "的瞭解還不"
                       "夠，尚且無法領悟此招。";

        if (stringp(sk5 = b["sk5"]) && intp(lv5 = b["lv5"])
           && who->query_skill(sk5, 1) < lv5)
                return "你對" + to_chinese(sk5) + "的瞭解還不"
                       "夠，尚且無法領悟此招。";

        // 判斷絕招對內功的要求
        if (intp(force = b["force"])
           && force > 0
           && who->query_skill("force") < force)
                return "你目前的內功火候不足，下去練練再來吧。";

        // 判斷絕招對輕功的要求
        if (intp(dodge = b["dodge"])
           && dodge > 0
           && who->query_skill("dodge") < dodge)
                return "你目前的輕功火候不足，下去練練再來吧。";

        // 判斷絕招對內力上限的要求
        if (intp(neili = b["neili"])
           && neili > 0
            && query("max_neili", who)<neili )
                return "你現在的內力修為不足，修煉高點再來吧。";

        // 判斷絕招對精力上限的要求
        if (intp(jingli = b["jingli"])
           && jingli > 0
            && query("max_jingli", who)<jingli )
                return "你現在的精力修為不足，修煉高點再來吧。";

        // 給予學習絕招的描述信息
        if (stringp(msg1 = b["msg1"]))
        {
                msg = msg1;
        } else
        {
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
        message_sort(HIY "\n" + msg + "\n\n" NOR, ob, who);

        // 學會該項絕招
        addn(perform, 1, who);

        // 給予提示信息
        tell_object(who, HIC "你學會了「" HIW + name +
                         HIC "」。\n" NOR);

        // 提升相對應的武功技能
        if (stringp(sk1) && who->can_improve_skill(sk1))
                who->improve_skill(sk1, 1500000);

        if (stringp(sk2) && who->can_improve_skill(sk2))
                who->improve_skill(sk2, 1500000);

        if (stringp(sk3) && who->can_improve_skill(sk3))
                who->improve_skill(sk3, 1500000);

        if (stringp(sk4) && who->can_improve_skill(sk4))
                who->improve_skill(sk4, 1500000);

        if (stringp(sk5) && who->can_improve_skill(sk5))
                who->improve_skill(sk5, 1500000);

        // 提升主 skill 的基本技能
        for (i = 0; i < sizeof(valid_types); i++)
        {
                if (SKILL_D(sk1)->valid_enable(valid_types[i])
                   && who->can_improve_skill(valid_types[i]))
                        who->improve_skill(valid_types[i], 1500000);
        }

        // 提升武學修養等級
        who->improve_skill("martial-cognize", 3500000);

        // 消耗門派貢獻值
        if (intp(gongxian) && gongxian > 0)
                addn("family/gongji", -gongxian, who);

        tell_object(who, "\n");

        // 最後的回答信息
        if (stringp(msg2 = b["msg2"]))
        {
                msg = msg2;
        } else
        {
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

// 物件的發放
public mixed give_item(object who, object ob, mapping b)
{
        object obj, owner;              // 給予的物品及擁有者
        string item;                    // 給予物品的 base_name
        string msg;                     // 對於某些返回信息的描述
        string sk1, sk2, sk3;           // 所需要的武功名稱
        int lv1, lv2, lv3;              // 所對應的武功等級
        int free;                       // 是否為公共物品派送
        int master;                     // 是否只有直屬弟子才能領取
        int generation;                 // 門派中的輩份要求
        string family;                  // 給予物品者的門派
        int gongxian, shen;             // 需求的貢獻及神
        string temp1, temp2, temp3;     // 要求的進程記錄
        string tmsg1, tmsg2, tmsg3;     // 要求的進程記錄的回答信息

        // 如果沒有指明對象，則返回
        if (! stringp(item = b["item"]))
                return 0;

        // 判斷所屬門派，如為公共應添加 free 參數
        //if (! intp(free = b["free"]) || free <= 0)
        //{
                family=query("family/family_name", ob);

                if( query("family/family_name", who) != family )
                        return RANK_D->query_respect(who) + "與我" +
                               family + "素無淵源，不知此話從何説起。";
        //}

        // 查找對應的 base_name 呼出物件
        obj = find_object(item);

        if (! obj)
                obj = load_object(item);

        if (! obj)
                return "那東西出了點問題，你最好找巫師商量商量。";

        // 判斷師承，如添加 master 參數，則只有直屬弟子才能領取
        if (intp(master = b["master"])
           && master > 0
            && query("family/master_id", who) != query("id", ob) )
                return "只有我的弟子才配使用" + obj->name() + CYN
                       "，你還是走吧。" NOR;

        // 判斷門派輩份，如果添加 master 參數，則應作缺省
        if (intp(generation = b["gen"])
           && generation > 0
            && query("family/generation", who)>generation )
                return "憑你在"+query("family/family_name", who)+
                       "中的地位，還不足以讓我將" + obj->name() + CYN
                       "交予你。" NOR;

        // 判斷正神或負神的要求
        if (intp(shen = b["shen"]))
        {
                // 如果要求為負神，則作出大於判斷
                if( shen<0 && query("shen", who)>shen )
                        return "哼！像你這樣的心慈手軟之輩，就"
                               "算拿着" + obj->name() + CYN "也"
                               "是無用。" NOR;

                // 如果要求為正神，則作出小於判斷
                if( shen>0 && query("shen", who)<shen )
                        return "你目前所做的俠義正事不夠，這" +
                               obj->name() + CYN "暫時還不能交"
                               "給你。" NOR;
        }

        // 判斷特定的進程記錄要求
        if( stringp(temp1=b["temp1"]) && !query(temp1, who) )
        {
                if (stringp(tmsg1 = b["tmsg1"]))
                        return tmsg1;
                else
                        return "現在某些機緣未到，這" + obj->name() +
                               CYN "暫時還不能交給你。" NOR;
        }

        if( stringp(temp2=b["temp2"]) && !query(temp2, who) )
        {
                if (stringp(tmsg2 = b["tmsg2"]))
                        return tmsg2;
                else
                        return "現在某些機緣未到，這" + obj->name() +
                               CYN "暫時還不能交給你。" NOR;
        }

        if( stringp(temp3=b["temp3"]) && !query(temp3, who) )
        {
                if (stringp(tmsg3 = b["tmsg3"]))
                        return tmsg3;
                else
                        return "現在某些機緣未到，這" + obj->name() +
                               CYN "暫時還不能交給你。" NOR;
        }

        // 判斷特定的武功需求
        if (stringp(sk1 = b["sk1"]) && intp(lv1 = b["lv1"]))
        {
                if (who->query_skill(sk1, 1) <= 0)
                        return "你連" + to_chinese(sk1) + "都未曾"
                               "學過，拿" + obj->name() + CYN "又"
                               "有何用？" NOR;

                if (who->query_skill(sk1, 1) < lv1)
                        return "你的" + to_chinese(sk1) + "火候未"
                               "到，就算拿着" + obj->name() + CYN
                               "也沒用。" NOR;
        }

        if (stringp(sk2 = b["sk2"]) && intp(lv2 = b["lv2"]))
        {
                if (who->query_skill(sk2, 1) <= 0)
                        return "你連" + to_chinese(sk2) + "都未曾"
                               "學過，拿" + obj->name() + CYN "又"
                               "有何用？" NOR;

                if (who->query_skill(sk2, 1) < lv2)
                        return "你的" + to_chinese(sk2) + "火候未"
                               "到，就算拿着" + obj->name() + CYN
                               "也沒用。" NOR;
        }

        if (stringp(sk3 = b["sk3"]) && intp(lv3 = b["lv3"]))
        {
                if (who->query_skill(sk3, 1) <= 0)
                        return "你連" + to_chinese(sk3) + "都未曾"
                               "學過，拿" + obj->name() + CYN "又"
                               "有何用？" NOR;

                if (who->query_skill(sk3, 1) < lv3)
                        return "你的" + to_chinese(sk3) + "火候未"
                               "到，就算拿着" + obj->name() + CYN
                               "也沒用。" NOR;
        }

        // 尋找該物件的所有者
        owner = environment(obj);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;

                owner = environment(owner);
        }

        if (owner == who)
                return "那"+query("unit", obj)+obj->name()+
                       CYN "不就是你拿着在用麼，怎麼反倒找我"
                       "來了？" NOR;

        if (objectp(owner) && owner != ob)
        {
                if (! owner->is_character())
                        return "那"+query("unit", obj)+obj->name()+
                               CYN "我已經借出去了，你還是隔段時間再"
                               "來吧。" NOR;

                if( query("family/family_name", owner) == family )
                        return "那"+query("unit", obj)+obj->name()+
                               CYN "現在是我派的" + owner->name() +
                               "在用，你若需要就去找他吧。" NOR;
                else
                if( query("family/family_name", owner) == query("family/family_name", who) )
                        return "那"+query("unit", obj)+obj->name()+
                               CYN "現在是你派的" + owner->name() +
                               "在用，你自己去問他要吧。" NOR;
                else
                        return "那"+query("unit", obj)+obj->name()+
                               CYN "現在落在了" + owner->name() +
                               "手中，你去把它取回來吧。" NOR;
        }

        // 判斷門派貢獻的要求
        if (intp(gongxian = b["gongxian"]) && gongxian > 0)
                if (query("family/first", who)) gongxian /= 2;

        if (gongxian && query("family/gongji", who)<gongxian )
                return "你為"+query("family/family_name", who)+
                       "作出的貢獻不夠，這" + obj->name() + CYN
                       "暫時還不能交給你。" NOR;

        // 物件轉移，給予出提示信息
        message_vision("$N拿出" + obj->name() + "(" +
                       query("id", obj)+")給$n。\n"NOR,ob,who);
        obj->move(who, 1);
        obj->start_borrowing();

        // 消耗門派貢獻值
        if (intp(gongxian) && gongxian > 0)
                addn("family/gongji", -gongxian, who);

        // 最後的回答提示信息
        if (! stringp(msg = b["msg"]))
                msg="既然這樣，那這"+query("unit", obj)+
                      obj->name() + CYN "你就暫時拿去吧。" NOR;

        return msg;
}
