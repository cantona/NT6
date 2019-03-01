// This program is a part of NT MudLIB
// itemd.c

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <command.h>

void do_enchase_attack(object item, object me, object victim, int damage);
void create() { seteuid(getuid()); }

int gift_point() { return 1; }
// 可以用來浸透的物品列表：必須是物品的base_name
string *imbue_list = ({
        "/d/shenlong/obj/hua4",
        "/clone/gift/puti-zi",
        "/clone/gift/xiandan",
        "/clone/gift/xisuidan",
        "/clone/gift/jiuzhuan",
        "/clone/gift/tianxiang",
        "/clone/gift/xuanhuang",
});

// 浸入的次數的隨機界限：如果每次IMBUE以後取0-IMBUE次數的隨機
// 數大于這個數值，則IMBUE最終成功。
#define RANDOM_IMBUE_OK         100

// 每次浸入需要聖化的次數
#define SAN_PER_IMBUE           5

// 殺了人以後的獎勵
void killer_reward(object me, object victim, object item)
{
        int exp;
        mapping o;
        string my_id;

        if (!me || !victim)
                return;

        if( !query("can_speak", victim) )
                // only human does effect
                return;

        // record for this weapon
        if (victim->is_not_bad())  addn("combat/WPK_NOTBAD", 1, item);
        if (victim->is_not_good()) addn("combat/WPK_NOTGOOD", 1, item);
        if (victim->is_good())     addn("combat/WPK_GOOD", 1, item);
        if (victim->is_bad())      addn("combat/WPK_BAD", 1, item);

        if (userp(victim))
                addn("combat/PKS", 1, item);
        else
                addn("combat/MKS", 1, item);

        exp=query("combat_exp", victim);
        if( exp<10000 || query("combat_exp", me)<exp*4/5 )
                return;

        exp /= 10000;
        if (exp > 250) exp = 100 + (exp - 250) / 16; else
        if (exp > 50) exp = 50 + (exp - 50) / 4;
        my_id=query("id", me);
        o=query("owner", item);
        if (!o) o = ([ ]);
        if (!undefinedp(o[my_id]) || sizeof(o) < 12)
                o[my_id] += exp;
        else
        {
                // Too much owner, I must remove one owner
                int i;
                int lowest;
                string *ks;

                lowest = 0;
                ks = keys(o);
                for (i = 1; i < sizeof(ks); i++)
                        if (o[ks[lowest]] > o[ks[i]])
                                lowest = i;
                map_delete(o, ks[lowest]);
                o += ([ my_id : exp ]);
        }
        set("owner", o, item);

        if (my_id == item->item_owner() && !random(10))
                addn("magic/blood", 1, item);
}

// 召喚物品
int receive_summon(object me, object item)
{
        object env;
        object temp;
        int type;

        if ((env = environment(item)) && env == me)
        {
                tell_object(me, item->name() + "不就在你身上"
                            "嘛？你召喚個什麼勁？\n");
                return 1;
        }

        if( query("jingli", me)<200 )
        {
                tell_object(me, "你試圖呼喚" + item->name() +
                            "，可是難以進入境界，看來是精力不濟。\n");
                return 0;
        }
        addn("jingli", -200, me);

        if( query("id", me) == "lonely" )
        {
              message_sort(HIM "\n只見四周金光散布，祥雲朵朵，遠處有鳳凰盤繞，麒麟逐戲。耳邊"
                           "傳來陣陣梵音。$N"HIM"一聲長嘯，"+query("name", item)+HIM
                           "破空而來 ……。\n\n" NOR, me);
        }
        else

              message_vision(HIW "$N" HIW "突然大喝一聲，伸出右手凌空"
                             "一抓，忽然烏雲密布，雷聲隱隱。\n\n" NOR, me);

        if (env == environment(me))
        {
                message_vision(HIW "只見地上的" + item->name() +
                               HIW "應聲而起，飛躍至$N" HIW
                               "的掌中！\n\n" NOR, me);
        } else
        {
                type = random(3);
                if (env)
                {
                        if (env->is_character() && environment(env))
                                        env = environment(env);

                        switch (type)
                        {
                        case 0:
                                message("vision", HIW "天空中傳來隱隱的雷聲"
                                        "，忽然電閃雷鳴，" + item->name() +
                                        HIW "騰空而起，"
                                        "消失不見！\n\n" NOR, env);
                                break;
                        case 1:
                                message("vision", HIC "一道神光從天而降"
                                        "，罩定了" + item->name() + HIC "，只見" +
                                        item->name() + HIC "化作長虹破空而"
                                        "走。\n\n" NOR, env);
                                break;
                        default:
                                message("vision", HIY "忽然間麝香遍地，氤氳彌漫，" +
                                        item->name() + HIY "叮呤呤的抖動數下，化作一"
                                        "道金光轉瞬不見！\n\n" NOR, env);
                                break;
                        }

                        if (interactive(env = environment(item)))
                        {
                                tell_object(env, HIM + item->name() +
                                                 HIM "忽然離你而去了！\n" NOR);
                        }
                }

                switch (type)
                {
                case 0:
                        message_vision(HIW "一聲" HIR "霹靂" HIW "，"
                                       "閃電劃破長空，" + item->name() + HIW
                                       "從天而降，飛入$N" HIW "的手中！\n\n" NOR, me);
                        break;
                case 1:
                        if( query("id", item) == "lonely")break;

                        message_vision(HIW "一道" HIY "長虹" HIW "掃過"
                                       "天空，只見" + item->name() + HIW
                                        "落入了$N" HIW "的掌中！\n\n" NOR, me);
                        break;
                default:
                        message_vision(HIW "只見" + item->name() + HIW "呤呤作響，大"
                                       "放異彩，挾雲帶霧，突現在$N"
                                       HIW "的掌中！\n\n" NOR, me);
                        break;
                }
        }

        // 取消no_get屬性
        delete_temp("stab_by", item);
        delete("no_get", item);

        item->move(me, 1);
        if (environment(item) != me)
                return 1;

        if( query("armor_type", item) )
        {
                // is armor
                temp = query_temp("armor/" + query("armor_type", item), me);
                if (temp) temp->unequip();
                WEAR_CMD->do_wear(me, item);
        } else
        if( query("skill_type", item) )
        {
                if( query("skill_type", item) == "throwing" )
                {
                        HAND_CMD->main(me,query("id", item));
                        return 1;
                }
                if( temp=query_temp("weapon", me) )
                        temp->unequip();
                if( temp=query_temp("secondary_weapon", me) )
                        temp->unequip();
                WIELD_CMD->do_wield(me, item);
        }

        return 1;
}

// 隱藏物品
int hide_anywhere(object me, object item)
{
        if( item->item_owner() != query("id", me) &&
            query("item_owner", item) != query("id", me) && query("owner", item) != query("id", me)) // 方便掉落物品擁有hide能力
                return 0;

        if( query("jingli", me)<100 )
        {
                tell_object(me, "你試圖令" + item->name() +
                            "遁去，可是精力不濟，難以發揮它的能力。\n");
                return 0;
        }
        addn("jingli", -100, me);

        message_vision(HIM "$N" HIM "輕輕一旋" + item->name() +
                       HIM "，已然了無蹤跡。\n", me);
        destruct(item);
        return 1;
}

// 追尋物品
int receive_miss(object me, object item)
{
        object env;

        env = environment(item);

        if (env == environment(me))
        {
                write("你瞪著" + item->name() + "，看啥？\n");
                return 0;
        }

        if (env == me)
        {
                write("你摸著" + item->name() + "，發了半天的呆。\n");
                return 0;
        }

        if (!objectp(env) || userp(env) || environment(env))
        {
                write("你試圖感應" + item->name() + "，但是感覺非常的渺茫。\n");
                return 0;
        }

        if( !wizardp(me) && (!query("outdoors", env) || query("no_magic", env) ||
            query("maze", env)) )
        {
                write("冥冥中你感應到" + item->name() + "，但是似乎難以到達那裡。\n");
                return 0;
        }

        message("vision", me->name() + "在凝神思索，不知道要做些什麼。\n",
                environment(me), ({ me }));
        if( query("jingli", me)<400 )
        {
                write("你覺得" + item->name() + "的感覺相當"
                      "飄忽，看來精力不濟，難以感應。\n");
                return 0;
        }

        // 消耗精力
        addn("jingli", -300-random(100), me);
        message_vision(HIM "$N" HIM "口中念念有詞，轉瞬天際一道長虹劃"
                       "過，$N" HIM "駕彩虹而走。\n" NOR, me);
        tell_object(me, "你追尋" + item->name() + "而去。\n");
        me->move(environment(item));
        message("vision", HIM "一道彩虹劃過天際，" + me->name() +
                HIM "飄然落下，有若神仙。\n" NOR, environment(me), ({ me }));
        tell_object(me, HIM "你追尋到了" + item->name() +
                    HIM "，落下遁光。\n" NOR);
        return 1;
}

// 插在地上
int do_stab(object me, object item)
{
        if( query("no_magic", environment(me)) )
                return notify_fail("在這裡亂弄什麼！\n");

        if (!item->is_weapon() && !item->is_unarmed_weapon())
                return notify_fail(item->name() + "也能插在地上？\n");

        if( !query("outdoors", environment(me)) &&
            !wizardp(me))
                return notify_fail("在這裡亂弄什麼！\n");

        set("no_get", bind((:call_other,__FILE__,"do_get_item",item:),item), item);
        set_temp("stab_by",query("id",  me), item);

        message_vision(WHT "\n$N" WHT "隨手將" + item->name() + NOR +
                       WHT "往地上一插，發出「嚓愣」一聲脆響。\n\n" NOR, me);
        item->move(environment(me));
        return 1;
}

// 把取物品時檢查
mixed do_get_item(object item)
{
        object me;

        if (!objectp(me = this_player()))
                return 1;

        if( query("id", me) != query_temp("stab_by", item) &&
            query("id", me) != item->item_owner() )
                return "你試圖將" + item->name() + "拔起，卻"
                       "發現它仿佛是生長在這裡一般，無法撼動。\n";

        message_vision(HIW "\n$N" HIW "隨手拂過" + item->name() +
                       HIW "脊處，頓時只聽「嗤」的一聲，揚起一陣"
                       "塵土。\n\n" NOR, me);
        delete_temp("stab_by", item);
        delete("no_get", item);
        return 0;
}

// 發揮特殊功能
mixed do_touch(object me, object item)
{
        string msg;
        object ob;
        object *obs;
        mapping my;

        if( query("id", me) != item->item_owner() ||
            (me->query_condition("killer") &&
            (query("no_fight", environment(me)) ||
            query("room_owner_id", environment(me)))) )
        {
                message_vision(HIR "\n$N輕輕觸碰" + item->name() +
                               HIR "，突然間全身一震，連退數步，如"
                               "遭受電擊。\n" NOR, me);
                me->receive_damage("qi", 50 + random(50));
                return 1;
        }

        if( query("jingli", me)<100 )
        {
                set("jingli", 0, me);
                return notify_fail(CYN "\n你凝視" + item->name() +
                                   CYN "許久，悠悠一聲長嘆。\n" NOR);
        }

        addn("jingli", -80-random(20), me);
        switch (random(3))
        {
        case 0:
                msg = CYN "\n$N" CYN "輕輕一彈$n" CYN "，長吟"
                      "道：「別來無恙乎？」\n" NOR;
                break;
        case 1:
                msg = CYN "\n$N" CYN "輕輕撫過$n" CYN "，作古"
                      "風一首，$n" CYN "鈴鈴作響，似以和之。\n" NOR;
                break;
        default:
                msg = CYN "\n$N" CYN "悠然一聲長嘆，輕撫$n"
                      CYN "，沉思良久，不禁感慨萬千。\n" NOR;
                break;
        }

        switch (random(3))
        {
        case 0:
                msg += HIM "忽然只見$n" HIM "閃過一道光華，"
                       "飛躍而起，散作千百流離。\n" NOR;
                break;
        case 1:
                msg += HIM "頓聽$n" HIM "一聲龍吟，悠悠不絕"
                       "，直沁入到你的心肺中去。\n" NOR;
                break;
        default:
                msg += HIM "霎時間$n" HIM "光芒四射，如蘊琉"
                       "璃異彩，逼得你難以目視。\n" NOR;
                break;
        }

        msg = replace_string(msg, "$n", item->name());
        msg = replace_string(msg, "$N", "你");
        // message_vision(msg, me);
        tell_object(me, msg);

        if (random(1000) == 1 || wizardp(me))
        {
                obs = filter_array(all_inventory(environment(me)), (: userp :));
                foreach (ob in obs)
                {
                        my = ob->query_entire_dbase();
                        my["jing"]   = my["eff_jing"] = my["max_jing"];
                        my["qi"]     = my["eff_qi"]   = my["max_qi"];
                        my["neili"]  = my["max_neili"];
                        my["jingli"] = my["max_jingli"];
                        set_temp("nopoison", 1, ob);
                }
                tell_object(obs, HIC "你感到一股溫和的熱浪襲來，便似"
                                "獲得重生一般。\n" NOR);
        } else
        if( query("neili", me)<query("max_neili", me) )
        {
                set("neili",query("max_neili",  me), me);
                tell_object(me, HIC "你只覺一股熱氣至丹田冉冉升起，"
                                "說不出的舒服。\n" NOR);
        }
        if (me->is_fighting() && !me->is_busy())
                me->start_busy(10);
        return 1;
}

// 聖化物品
int do_san(object me, object item)
{
        string my_id;
        int count;
        int san;

        /*
        if( !query("skill_type", item) && query("armor_type", item) != "hands" )
        {
                // 是裝備類？
                return notify_fail("裝備現在還無法聖化...\n");
        }
        */

        // 武器類的聖化
        if( query("magic/power", item)>0 )
                return notify_fail("現在" + item->name() + "的威力"
                                   "已經得到了充分的發揮了。\n");

        if( query("magic/imbue_ok", item) )
                return notify_fail("現在" + item->name() + "的潛力"
                                   "已經充分挖掘了，現在只是需要最"
                                   "後一步融合。\n");

        my_id=query("id", me);

        count=sizeof(query("magic/do_san", item));
        if( query("magic/imbue_ob", item) )
                return notify_fail("現在" + item->name() + "已經被充分的聖"
                                   "化了，需要浸入神物以進一步磨練。\n");

        if( query("magic/do_san/"+my_id, item) )
                return notify_fail("你已經為" + item->name() + "聖化過了，"
                                   "非凡的能力還無法被它完全吸收。\n你"
                                   "有必要尋求他人幫助以繼續聖化。\n");

        if (item->item_owner() == my_id)
        {
                if (!count)
                        return notify_fail("你應該先尋求四位高手協助你先行聖化" +
                                           item->name() + "。\n");

                if (count < SAN_PER_IMBUE - 1)
                        return notify_fail("你應該再尋求" +
                                           chinese_number(SAN_PER_IMBUE - 1 - count) +
                                           "位高手先行聖化" + item->name() + "。\n");
        } else
        {
                if (count >= SAN_PER_IMBUE - 1)
                        return notify_fail("最後需要他的主人為它聖化，不勞你費心了。\n");
        }

        if( query("neili", me)<query("max_neili", me)*9/10 )
                return notify_fail("你現在內力並不充沛，怎敢貿然運用？\n");

        if( query("jingli", me)<query("max_jingli", me)*9/10 )
                return notify_fail("你現在精力不濟，怎敢貿然運用？\n");

        if (me->query_skillo("force", 1) < 300)
                return notify_fail("你的內功根基不夠紮實，不能貿然聖化。\n");

        if( query("max_neili", me)<8000 )
                return notify_fail("你嘗試運了一下內力，無法順"
                                   "利運足一個周天，難以施展你的能力。\n");

        if( query("max_jingli", me)<1000 )
                return notify_fail("你試圖凝神運用精力，但是感覺尚有欠缺。\n");

        message_sort(HIM "$N" HIM "輕輕撫過$n" HIM "，兩指點于其上，同"
                     "時運轉丹田內力，經由奇經\n八脈源源由體內流出，注"
                     "入$n" HIM "。\n忽的只見氤氳紫氣從$n" HIM
                     "上騰然升起，彌漫在四周。\n" NOR, me, item);

        if( query("max_neili", me)<me->query_neili_limit()-400 )
        {
                if (random(2) == 1)
                {
                        // 內力未滿警告
                        message_vision(HIR "$N" HIR "臉色忽然變了變。\n" NOR,
                                       me);
                        tell_object(me, HIC "你忽然覺得丹田氣息有些錯亂。\n" NOR);
                } else
                {
                        message_vision(HIR "$N" HIR "忽然悶哼一聲，臉"
                                       "上剎時大汗淋漓！\n" NOR, me);
                        tell_object(me, HIC "你感到可能是你的內力尚未鍛煉"
                                    "到極至，結果損傷了你的內功根基。\n" NOR);
                        tell_object(me, HIC "你的基本內功下降了。\n");
                        me->set_skill("force", me->query_skillo("force", 1) - 10 - random(5));
                        return 1;
                }
        }

        // 統計IMBUE過的次數，並用來計算本次MAX_NEILI/JINGLI的消耗
        san=query("magic/imbue", item);

        addn("max_neili", -(san+5), me);
        addn("neili", -(san*10+100), me);
        addn("max_jingli", -(san*5+50), me);
        addn("jingli", -(san*5+50), me);
        set("magic/do_san/"+my_id, me->name(1), item);
        me->start_busy(1);

        if (item->item_owner() == my_id ||
            sizeof(query("magic/do_san", item)) == SAN_PER_IMBUE )
        {
                tell_object(me, HIW "你凝神片刻，覺得" + item->name() +
                            HIW "似乎有了靈性，跳躍不休，不禁微微一笑。\n" NOR);
                message("vision", HIW + me->name() + HIW "忽然"
                        "微微一笑。\n" HIW, environment(me), ({ me }));

                if( !item->is_weapon() && !item->is_unarmed_weapon() && !query("magic/imbue", item) )
                {
                        set("magic/imbue_element", 1, item);
                        return 1;
                }

                // 選定一個需要imbue的物品
                set("magic/imbue_ob", imbue_list[random(sizeof(imbue_list))], item);
        }
        return 1;
}

// 浸透物品
int do_imbue(object me, object item, object imbue)
{
        if( query("magic/power", item)>0 )
                return notify_fail("現在" + item->name() + "的威力"
                                   "已經得到了充分的發揮了。\n");

        if( query("magic/imbue_ok", item) )
                return notify_fail("現在" + item->name() + "的潛力"
                                   "已經充分挖掘了，現在只是需要最"
                                   "後一步融合。\n");

        if( sizeof(query("magic/do_san", item))<SAN_PER_IMBUE )
                return notify_fail("你必須先對" + item->name() +
                                   "進行充分的聖化才行。\n");

        if( query("magic/imbue_element", item) )
        {
                if( !query("magic/element", imbue) )
                        return notify_fail(item->name() + "必須首先浸入具有五行屬性的物品。\n");
        }
        else
        {
                if( base_name(imbue) != query("magic/imbue_ob", item) )
                        return notify_fail(item->name() + "現在不需要用" +
                                           imbue->name() + "來浸入。\n");
        }

        message_sort(HIM "$N" HIM "深吸一口氣，面上籠罩了一層白霜，只手握住$n" +
                     imbue->name() +
                     HIM "，忽然間融化在掌心，晶瑩欲透！$N"
                     HIM "隨手一揮，將一汪清液洒在$n" HIM
                     "上，登時化做霧氣，須臾成五彩，奇光閃爍。\n" NOR,
                     me, item);

        tell_object(me, "你將" + imbue->name() + "的效力浸入了" +
                    item->name() + "。\n");
        delete("magic/do_san", item);
        delete("magic/imbue_ob", item);
        if( query("magic/imbue_element", item) )
                delete("magic/imbue_element", item);
        if( query("magic/element", imbue) )
                set("magic/type",query("magic/element",  imbue), item);
        if (imbue->query_amount())
                imbue->add_amount(-1);
        else
                destruct(imbue);
        me->start_busy(1);

        addn("magic/imbue", 1, item);
        if ((item->is_weapon() || item->is_unarmed_weapon())
         && (random(query("magic/imbue", item)) >= RANDOM_IMBUE_OK
         || query("magic/imbue", item) >= 150) )
        {
                        // 浸透完成
                tell_object(me, HIG "你忽然發現手中的" + item->name() +
                                HIG "有一種躍躍欲試的感覺，似乎期待著什麼。\n" NOR);
                set("magic/imbue_ok", 1, item);
        } else
        if (!item->is_weapon() && !item->is_unarmed_weapon()
         && (random(query("magic/imbue", item)) >= RANDOM_IMBUE_OK/5
         || query("magic/imbue", item) >= 30) )
        {
                tell_object(me, HIG "你忽然發現手中的" + item->name() +
                                HIG "有一種躍躍欲試的感覺，似乎期待著什麼。\n" NOR);
                set("magic/imbue_ok", 1, item);
        }

        return 1;
}

// 鑲嵌物品
int do_enchase(object me, object item, object tessera)
{
        mapping ins;
        mapping data, enchase_prop, temp;
        string  *apply;
        string  str;
        object  obj;
        int     i, n, level, wash, addsn;

        if( query("equipped", item) )
                return notify_fail("你先解除" + item->name() + "的裝備再說！\n");

        if( !query("enchase/flute", item) )
                return notify_fail(item->name() + "上並沒有凹槽可用來鑲嵌。\n");

        if( query("enchase/used", item) >= query("enchase/flute", item) )
                return notify_fail(item->name() + "上的凹槽已經鑲滿了。\n");

        /*
        if( query("magic/type", item) && query("can_be_enchased", tessera) )
                return notify_fail(item->name() + "上已經擁有靈力物品了。\n");

        if( !item->is_weapon() && !item->is_unarmed_weapon() && query("can_be_enchased", tessera) )
                return notify_fail(tessera->name() + "只能鑲嵌在兵器類裝備上。\n");
        */

        if( !tessera->is_tessera() || !mapp(query("enchase", tessera)) )
                return notify_fail(tessera->name() + "不能發揮魔力，沒有必要鑲嵌在" + item->name() + "上面。\n");

        if( query("magic/type", item) && query("magic/type", tessera) && query("magic/type", tessera) != query("magic/type", item) )
                return notify_fail(item->name() + "上已經擁有五行靈力屬性和鑲嵌物的五行靈力屬性不一致，無法鑲嵌融合。\n");

        if( (level = me->query_skill("certosina", 1)) < 200 )
                return notify_fail("你覺得你的鑲嵌技藝還不夠嫻熟，不敢貿然動手。\n");

        if( tessera->is_rune() && query("enchase/rune" + query("enchase/SN", tessera), item) )
                return notify_fail(item->name() + "上的凹槽裡已經鑲嵌此符文,再鑲嵌會產生魔性沖突。\n");

        if( !query("magic/type", item) && (item->is_weapon() || item->is_unarmed_weapon()))
        {
                if( !query("can_be_enchased", tessera) )
                if( query("enchase/used", item)+1 >= query("enchase/flute", item) )
                        return notify_fail(item->name() + "上的剩下的唯一的凹槽是用來鑲嵌具有靈力的物品。\n");
        }

        temp = query("enchase", tessera);
        if( undefinedp(temp["type"]) )
                return notify_fail(tessera->name() + "的魔力屬性不適合鑲嵌在" + item->name() + "上。\n");
        else
        {
                if (temp["type"] != "all" &&
                    temp["type"] != query("skill_type", item) &&
                    temp["type"] != query("armor_type", item) )
                        return notify_fail(tessera->name() + "的魔力屬性不適合鑲嵌在" + item->name() + "上。\n");
        }

        if( !tessera->is_rune() && !query("can_be_enchased", tessera) && temp["level"] != query("require/level", item) )
                return notify_fail(tessera->name() + "的等級不適合鑲嵌在" + item->name() + "上。\n");
        
        if( tessera->is_rune() && (query("armor_type", item) == "rings" || 
            query("armor_type", item) == "neck" || query("armor_type", item) == "charm") )
                return notify_fail("符文不適合鑲嵌在" + item->name() + "上。\n");
                
        if( level < 400 && random(level) < 180 && !(obj = present("enchase symbol", me)) )
        {
                message_vision(HIM "聽得“喀啦”一聲，只見" + tessera->name() + HIM "撞在$n" +
                               HIM "上，片片裂開。\n" NOR, me, item);
                tell_object(me, HIC "你鑲嵌" + tessera->name() + CYN "失敗了。\n" NOR);
                destruct(tessera);
                me->start_busy(1);
                return 1;
        }
        if( objectp(obj) ) destruct(obj);

        message_vision( HIM "聽得“喀啦”一聲，$N" HIM "將" + tessera->name() + NOR HIM"鑲嵌到了$n" HIM "上面，\n只間$n"
                        HIM "上隱隱的顯過了一道奇異的光芒，隨即變得平靜，說不出的平凡。\n\n" NOR, me, item);
        tell_object(me, HIC "你感受" + item->name() + HIC "發生了不可言喻的變化。\n" NOR);

        if( query("can_be_enchased", tessera) )
        {
                //CHANNEL_D->do_channel(this_object(), "rumor", "聽說神品" + item->name() + HIM + "來到了人間。");
                //set("magic/power",query("magic/power",  tessera), item);
                addn("magic/power",query("magic/power",  tessera), item);
                set("magic/type",query("magic/type",  tessera), item);
                set("magic/tessera", tessera->name(), item);
        }

        if( intp(query("enchase/wash", item)) )
                wash=query("enchase/wash", item);
        else
                wash = 0;

        addsn = 0;
        if (item->is_weapon() || item->is_unarmed_weapon())
        {
                if (wash >= 220) addsn = 4;
                else if (wash >= 180) addsn = 3;
                else if (wash >= 150) addsn = 2;
                else if (wash >= 50) addsn = 1;

                enchase_prop=query("enchase/weapon_prop", tessera);
        } else
        if( query("armor_type", item) == "rings" || query("armor_type", item) == "neck" || query("armor_type", item) == "charm" )
        {
                if (wash >= 100) addsn = 3;
                else if (wash >= 80) addsn = 2;
                else if (wash >= 30) addsn = 1;
                else if (wash < 15) addsn = -1;
                
                enchase_prop=query("enchase/rings_prop", tessera);
        } else
        {
                if (wash >= 100) addsn = 3;
                else if (wash >= 80) addsn = 2;
                else if (wash >= 30) addsn = 1;
                else if (wash < 15) addsn = -1;
                
                enchase_prop=query("enchase/armor_prop", tessera);
        }

        if (!mapp(enchase_prop)) enchase_prop = ([]);
        apply = keys(enchase_prop);
        /*
        if (tessera->is_rune())
                data=query("enchase/rune_prop", item);//符文的魔法能力單獨標記
        else
        */
                data=query("enchase/apply_prop", item);

        if (!mapp(data) ) data = ([]);

        for (i = 0; i<sizeof(apply); i++)
        {
                if ( undefinedp(data[apply[i]]) )
                        data[apply[i]] = enchase_prop[apply[i]];
                else
                        data[apply[i]] += enchase_prop[apply[i]];
        }

        set("enchase/apply_prop", data, item);

        n = sizeof(query("insert", item));
        ins = ([ "name" : query("name", tessera),
                 "id"   : query("id", tessera),
                 "SN"   : query("enchase/SN", tessera),
                 "apply_prop" : enchase_prop ]);

        set("insert/"+(n+1), ins, item);
        
        addn("enchase/used", 1, item);
        if( tessera->is_rune() ) {
                if( !query("enchase/rune", item) ){
                        addn("enchase/SN", query("enchase/SN", tessera), item);
                        set("enchase/rune", 1, item);
                }
                set("enchase/rune"+query("enchase/SN", tessera), 1, item);
        } else {
                /*
                if( query("can_be_enchased", tessera) )
                        //addn("enchase/SN", 5+random(5), item);
                        addn("enchase/SN",query("enchase/SN", tessera), item);
                else
                */
                {
                        addsn += random(query("enchase/SN", tessera))+1;
                        if (addsn > 9 ) addsn = 9;
                        if (addsn < 1 ) addsn = 1;

                        addn("enchase/SN", addsn, item);
                }
        }

        item->add_weight(tessera->query_weight());
        /* 取消洗裝備
        if( IDENTIFY_D->identify_ultimate_ob(item) )
                tell_object(me, BLINK HBMAG + tessera->name() + BLINK HBMAG "與" + item->name() +
                                BLINK HBMAG "的魔力充分融合相生使" + item->name() +
                                BLINK HBMAG "發生了不可思議的突變。\n\n" NOR);
        */
        item->save();
        destruct(tessera);
        if( !wizardp(me) )
                me->start_busy(1);
        return 1;
}

// 用內力將鑲嵌物品溶化掉 melt
int do_wash(object me, object item)
{
        mapping enchase, insert, applied_prop;
        mapping mod_prop;
        string *apply, *ks;
        int i, j, f, n;

        if( query("neili", me)<query("max_neili", me)*9/10 )
                return notify_fail("你現在內力並不充沛，怎敢貿然運用？\n");

        if( query("jingli", me)<query("max_jingli", me)*9/10 )
                return notify_fail("你現在精力不濟，怎敢貿然運用？\n");

        if (me->query_skill("force") < 300)
                return notify_fail("你的內功根基不夠紮實，不能貿然運功。\n");

        if( query("max_neili", me)<8000 )
                return notify_fail("你嘗試運了一下內力，無法順"
                                   "利運足一個周天，難以施展你的能力。\n");

        if( query("max_jingli", me)<1000 )
                return notify_fail("你試圖凝神運用精力，但是感覺尚有欠缺。\n");

        message_vision(HIM "$N" HIM "將$n" HIM "握于掌中，默默運轉內力，注入$n" HIM "凹槽。\n只見$n" HIM
                       "白霧蒸騰，彌漫在四周。\n" NOR, me, item);


        message_vision(HIC"忽的卻見$n"HIC"上面"HIY+chinese_number(query("enchase/flute", item))+
                       HIC "個凹槽內物品嗤的化作一股青煙，\n$n"HIC "凹槽內已空無一物，猶如新出。\n" NOR,
                       me, item);

        if( query("enchase/rune30", item) || query("enchase/rune31", item) ||
            query("enchase/rune32", item) || query("enchase/rune33", item) )
        {
                if (item->is_weapon() || item->is_unarmed_weapon())
                {
                        if( query("enchase/used", item) >= 7 )
                                addn("enchase/wash", 1, item);
                }
                else
                {
                        if( query("enchase/used", item) >= 5 )
                                addn("enchase/wash", 1, item);
                }
        }

        f = query("enchase/flute", item);
        n = query("enchase/wash", item);
        applied_prop = copy(query("enchase/apply_prop", item));
        mod_prop = copy(query("enchase/mod_prop", item));
        /*
        insert = copy(query("insert", item));
        ks = keys(insert);
        for( i=0; i<sizeof(ks);i++ )
        {
                enchase = copy(insert[ks[i]]["apply_prop"]);
                apply = keys(enchase);
                for( j=0;j<sizeof(apply);j++ )
                {
                        applied_prop[apply[j]] -= enchase[apply[j]];
                        if( applied_prop[apply[j]] <= 0 )
                                map_delete(applied_prop, apply[j]);
                }
        }
        */
        delete("enchase", item);
        delete("insert", item);
        delete("magic/power", item);
        delete("magic/type", item);
        delete("magic/tessera", item);
        delete("ultimate/69", item);
        delete("ultimate/87", item);
        delete("ultimate/105", item);
        delete("ultimate/121", item);
        delete("ultimate/ob", item);
        delete("qianghua", item);
        set("enchase/flute", f, item);
        set("enchase/wash", n, item);
        //set("enchase/apply_prop", applied_prop, item);
        if( mapp(mod_prop) ) set("enchase/mod_prop", mod_prop, item);

        switch(query("material", item) )
        {
        case "tian jing":
                set("enchase/SN", 8, item);
                break;
        case "no name":
                set("enchase/SN", 16, item);
                break;
        default         :
                break;
        }

        item->save();
        if( !wizardp(me) )
                me->start_busy(1);
        return 1;
}

// 鍛造裝備升級
int do_forging(object me, object item, object ob)
{
        mapping temp;
        int n, rate, level;

        if( (int)me->query_skill("forging", 1) < 200 )
                return notify_fail("你對鍛造技藝掌握不夠。\n");

        if( query("level", me)/10*10 <= query("require/level", item) )
                return notify_fail("你目前的能力無法再繼續鍛造你的裝備。\n");

        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("你的內功修為不足。\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("你現在的氣太少了。\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("你現在的精太少了。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你覺得內力頗有不足。\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("你現在的內力太少了。\n");

        if( (query("potential", me)-query("learned_points", me)) < 20 )
                return notify_fail("你的潛能不夠，無法鍛煉兵器！\n");

        message_sort(HIM "$N" HIM "手握" +ob->name()+ HIM "，一股內力絲絲的傳了進去，" +ob->name()+
                     HIM "忽然間融化在掌心，晶瑩欲透！$N"
                     HIM "隨手一揮，將一汪清液洒在$n"
                     HIM "上，" HIM "$n" HIM "猶如烈火中重生一般，散發出絢目的光彩！\n" NOR,
                     me, item);

        addn("max_neili", -10, me);
        set("neili", query("max_neili", me), me);
        addn("qi", -50, me);
        addn("eff_qi", -30, me);
        addn("eff_jing", -30, me);
        addn("potential", -20, me);

        temp = query("require", item);
        level = temp["level"];
        temp["ilvl"] += 1;
        n = temp["ilvl"];

        if( n >= level+10 )
        {
                temp["level"] += 10;
                level = temp["level"];
                rate = random(100);
                if( rate < 40 ) temp["str"] = level*2 + random(level);
                else if( rate < 60 ) temp["con"] = level*2 + random(level);
                else if( rate < 80 ) temp["dex"] = level*2 + random(level);
                else temp["int"] = level*2 + random(level);
                temp["ilvl"] = 0;

                message_vision(HIY +item->name()+ HIY "忽的一亮，一道金光隱入$N" HIY "的" +item->name()+ HIY "，不見了！\n" NOR +
                               HIG "$N" HIG "的" +item->name()+ HIG "的等級提高了！\n" NOR, me);

                //set("enchase/steady", 0, item);   // 強化次數恢復0
                //set("enchase/increase", 0, item); // 改造次數恢復0
        }

        set("require", temp, item);
        item->save();
        destruct(ob);
        message_vision(RED "$N" RED "的" +item->name()+ RED "的質地改善了!\n" NOR, me);
        if( !wizardp(me) )
                me->start_busy(1);
        return 1;
}

// 改裝備屬性要求
int do_require(object me, object ob)
{
        mapping temp;
        int level;
        int rate;

        if( (int)me->query_skill("smelting", 1) < 200 )
                return notify_fail("你對冶煉技藝掌握不夠。\n");

        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("你的內功修為不足。\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("你現在的氣太少了。\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("你現在的精太少了。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你覺得內力頗有不足。\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("你現在的內力太少了。\n");

        temp = query("require", ob);
        level = temp["level"];

        rate = random(100);
        if( rate < 40 ) temp["str"] = level*2 + random(level);
        else if( rate < 60 ) temp["con"] = level*2 + random(level);
        else if( rate < 80 ) temp["dex"] = level*2 + random(level);
        else temp["int"] = level*2 + random(level);
        set("require", temp, ob);
        message_vision(HIY +ob->name()+ HIY "隱隱的顯過了一道奇異的光芒，隨即變得平靜。\n" NOR, me);
        ob->save();
}

// 10級兵器攻擊對手
mixed weapon10lv_hit_ob(object me, object victim, object weapon, int damage_bonus)
{
        mapping magic;
        int jingjia;
        int power, resistance;
        int damage;
        int add, reduce;
        string msg;

        // 計算魔法效果
        magic=query("magic", weapon);
        if( !mapp(magic) ) return;
        power = magic["power"];
        damage = 0;
        resistance = 0;
        //jingjia = me->query("jiajing");
        jingjia=query("jiali", me)/3;

        switch (magic["type"])
        {
        case "lighting":
                // 閃電攻擊：傷害內力++和氣+
                resistance=query_temp("apply/resistance/lighting", victim);
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=query_temp("apply/add_lighting", me);
                reduce=query_temp("apply/reduce_lighting", victim);
                damage += damage * random(add + 1) / 100;
                damage -= damage * random(reduce + 1) / 100;

                if (damage < 0) return;

                switch (random(6))
                {
                case 0:
                        msg = HIY + weapon->name() + HIY "迸發出幾道明亮的閃光，茲茲作響，讓$n"
                              HIY "不由為之酥麻。\n" NOR;
                        break;
                case 1:
                        msg = HIY "一道電光閃過，" + weapon->name() + HIY
                              "變得耀眼奪目，令$n" HIY "無法正視，心神俱廢。\n" NOR;
                        break;
                case 2:
                        msg=HIY+query("name", weapon)+HIY"噴出一團熾白的光球，直奔$n"
                              HIY "而去，$n" HIY "被打了個正著，受傷不輕。\n" NOR;
                        break;
                case 3:
                        msg = HIY "一圈熾白的光環圍繞" + weapon->name() + HIY
                             "不斷擴散開來，所到之處亮如白晝，$n" HIY "立刻魂飛魄散。\n" NOR;
                        break;
                case 4:
                        msg=HIY+query("name", weapon)+HIY"暴出漫天夾雜響雷的閃電直擊而來，$n"
                              HIY "被閃電悉數直穿身體而過，頓時軟弱無力。\n" NOR;
                        break;
                default:
                        msg = HIY "天際隱隱響起幾聲悶雷，緊接著一道霹靂直下，" +
                              weapon->name() + HIY "忽明忽暗，五彩繽紛，震得$n"
                              HIY "酸軟無力。\n" NOR;
                        break;
                }

                if( query("neili", victim)>damage )
                        addn("neili", -damage, victim);
                else
                        set("neili", 0, victim);

                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 2);
                break;

        case "water":
                // 冷凍攻擊：傷害精++和氣+
                resistance=query_temp("apply/resistance/water", victim);
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=query_temp("apply/add_water", me);
                reduce=query_temp("apply/reduce_water", victim);
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 3);
                victim->receive_wound("jing", damage / 6);
                victim->receive_damage("qi", damage / 2);
                victim->receive_wound("qi", damage / 4);
                switch (random(6))
                {
                case 0:
                        msg = HIB + weapon->name() + HIB "閃過一道冷澀的藍光，讓$n"
                              HIB "不寒而栗。\n" NOR;
                        break;
                case 1:
                        msg = HIB "忽然間" + weapon->name() + HIB
                              "變得透體通藍，一道道冰冷的寒光迸發出來，$n"
                              HIB "渾身只是一冷。\n" NOR;
                        break;
                case 2:
                        msg = HIB "一圈晶瑩的冰光環圍繞" + weapon->name() + HIB
                              "不斷擴散開來，所到之處萬物皆凝。$n" HIB
                              "只覺自己氣血凝滯。\n" NOR;
                        break;
                case 3:
                        msg=HIB+query("name", weapon)+HIB"暴出漫天冰錐直射而來，$n"
                              HIB "轉眼間已然成了蜂窩。\n" NOR;
                        break;
                case 4:
                        msg = HIB "忽然間" + weapon->name() + HIB
                              "變得透體通藍，周圍空氣忽然急速凝結，一面淡藍的冰牆把$n"
                              HIB "冰封在了裡面。\n" NOR;
                        break;
                default:
                        msg = HIB "一道光圈由" + weapon->name() + HIB "射出，"
                              "森然盤旋在$n" HIB "四周，悄然無息。\n" NOR;
                        break;
                }
                break;

        case "fire":
                // 火燄攻擊：傷害精+和氣++
                resistance=query_temp("apply/resistance/fire", victim);
                damage = (power + jingjia) * 300 / (100 + resistance);
                add=query_temp("apply/add_fire", me);
                reduce=query_temp("apply/reduce_fire", victim);
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 5);
                victim->receive_wound("jing", damage / 8);
                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 2);
                switch (random(6))
                {
                case 0:
                        msg = HIR + weapon->name() + HIR "驀的騰起一串火燄，將$n"
                              HIR "接連逼退了數步，慘叫連連。\n" NOR;
                        break;
                case 1:
                        msg = HIR "一道火光從" + weapon->name() + HIR
                              "上迸出，迅捷無倫的擊中$n" HIR "，令人避無可避！\n" NOR;
                        break;
                case 2:
                        msg = HIR "一圈通紅的火光從" + weapon->name() + HIR
                              "上迸出擴散開來，所到之處萬物皆灰，將$n"
                              HIR "身體燒出了一個焦黑的窟窿。\n" NOR;
                        break;
                case 3:
                        msg=HIR+query("name", weapon)+HIB"暴出漫天通紅的火球直擊而來，$n"
                              HIR "被置身一片火海，慘叫連連。\n" NOR;
                        break;
                case 4:
                        msg = HIR "忽然間" + weapon->name() + HIR
                              "變得透體通紅，周圍空氣忽然異常幹燥，$n"
                              HIR "眨眼功夫周身竟然被熊熊烈火團團圍住，被燒的體無完膚。\n" NOR;
                        break;
                default:
                        msg = HIR "一串串火燄從" + weapon->name() + HIR "上飛濺射出，"
                              "四下散開，接連擊中$n" HIR "！\n" NOR;
                        break;
                }
                break;
                
        case "metal":
                // 冷凍攻擊：傷害精++和氣+
                resistance=query_temp("apply/resistance/metal", victim);
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=query_temp("apply/add_metal", me);
                reduce=query_temp("apply/reduce_metal", victim);
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 3);
                victim->receive_wound("jing", damage / 6);
                victim->receive_damage("qi", damage / 2);
                victim->receive_wound("qi", damage / 4);
                switch (random(4))
                {
                case 0:
                        msg = HIY + weapon->name()+HIY"頓時金光四射，縱橫交錯，布滿了整個空間，$n"HIY"已難以醒目。\n"NOR;
                        break;
                case 1:
                        msg = HIY + weapon->name()+HIY"一飛沖天，片刻時間化作無數的"HIY + weapon->name()+HIY"金錢撒地般的射向$n。\n"NOR;
                        break;
                default:
                        msg = HIY + weapon->name()+HIY"通體變的金黃耀目，伴鳴響天地的撕裂聲直擊$n"HIY"要害之處。\n"NOR;
                        break;
                }
                break;

        case "wood":
                // 冷凍攻擊：傷害精++和氣+
                resistance=query_temp("apply/resistance/wood", victim);
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=query_temp("apply/add_wood", me);
                reduce=query_temp("apply/reduce_wood", victim);
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 3);
                victim->receive_wound("jing", damage / 6);
                victim->receive_damage("qi", damage / 2);
                victim->receive_wound("qi", damage / 4);
                switch (random(4))
                {
                case 0:
                        msg =  HIG"霎時間"HIG + weapon->name()+HIG"之影暴長 ，似乎變幻出無數枝幹，將$N緊緊抓住。\n" NOR;
                        break;
                case 1:
                        msg =  HIG + weapon->name()+HIG"在$n"HIG"周身盤旋，將$n"HIG"帶入翡翠夢境，令$n迷失不已。\n" NOR;
                        break;
                default:
                        msg =  HIG  + weapon->name()+HIG"閃出無數條亮影，如枯木回春般蔓延了$n"HIG"全身。\n" NOR;
                        break;
                }
                break;
                
        case "earth":
                // 冷凍攻擊：傷害精++和氣+
                resistance=query_temp("apply/resistance/earth", victim);
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=query_temp("apply/add_earth", me);
                reduce=query_temp("apply/reduce_earth", victim);
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 3);
                victim->receive_wound("jing", damage / 6);
                victim->receive_damage("qi", damage / 2);
                victim->receive_wound("qi", damage / 4);
                switch (random(4))
                {
                case 0: 
                        msg = YEL + weapon->name()+ YEL"突然顫抖，音聲低沉凝重，引山搖地動之式，$n"YEL"以不能自已！\n" NOR;
                        break;
                case 1:
                        msg = YEL + weapon->name()+ YEL"急速的劃過土石之緣，帶動山石之雨，咆哮著令人心膽俱裂的震天怒響擊向$n。 \n"NOR;
                        break;
                default:
                        msg = YEL + weapon->name()+ YEL"汲取天地萬物之靈氣發起攻擊，剎那間天地蒼蒼，飛沙走石。\n" NOR;  
                        break;
                }
                break;     
                
        case "poison":
                // 毒系魔法：打內力或者忙亂
                resistance=query_temp("apply/resistance/poison", victim);
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=query_temp("apply/add_poison", me);
                reduce=query_temp("apply/reduce_poison", victim);
                damage += damage * random(add + 1) / 100;
                damage -= damage * random(reduce + 1) / 100;

                if (damage < 0) return;

                if( query("neili", victim)>damage )
                        addn("neili", -damage, victim);
                else
                        set("neili", 0, victim);

                if (!victim->is_busy())
                        victim->start_busy(2 + random(3));

                switch (random(6))
                {
                case 0:
                        msg = HIG + weapon->name() + HIG "驀的冒出絲絲白煙擴散開來，$n"
                              HIG "頓時渾身慢慢酸軟起來。\n" NOR;
                        break;
                case 1:
                        msg=HIG+query("name", weapon)+HIG"噴出股股黃煙快速圍繞過來，$n"
                              HIG "頓時感覺頭重腳輕，竟然險些拿不動兵器。\n" NOR;
                        break;
                case 2:
                        msg=HIG+query("name", weapon)+HIG"噴出漫天五彩迷霧撲面而來，$n"
                              HIG "周身被五彩迷霧圍在其中，手無敷雞之力。\n" NOR;
                        break;
                case 3:
                        msg = HIG + weapon->name() + HIG "驀的冒出幾絲略帶清香的白煙飄然而過，$n"
                              HIG "頓時全身無力。\n" NOR;
                        break;
                case 4:
                        msg = HIG + weapon->name() + HIG "驀的一圈略帶幽香的黃色煙霧不斷擴散開來，所到之處萬物皆枯，$n"
                              HIG "只覺自己飄飄欲仙，全身使不出力量來。\n" NOR;
                        break;
                default:
                        msg=HIG+query("name", weapon)+HIG"噴出漫天濃香的五彩霧氣，$n"
                              HIG "只覺醉生夢死，全身使不出力量來。\n" NOR;
                        break;
                }
                break;

        case "wind":
                // 風系魔法：打法力或者加命中
                resistance=query_temp("apply/resistance/wind", victim);
                damage = (power + jingjia) * 300 / (100 + resistance);
                add=query_temp("apply/add_wind", me);
                reduce=query_temp("apply/reduce_wind", victim);
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 5);
                victim->receive_wound("jing", damage / 8);
                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 2);

                switch (random(6))
                {
                case 0:
                        msg = HIW + weapon->name() + HIW "吹出一陣強風，直吹的$n"
                              HIW "東倒西歪連站穩住都有些困難。\n" NOR;
                        break;
                case 1:
                        msg = HIW + weapon->name() + HIW "刮出一陣旋風，夾雜黃沙的旋風如萬把風刀向$n"
                              HIW "襲來，吹的$n" HIW "天旋地轉，竟然險些拿不動兵器。\n" NOR;
                        break;
                case 2:
                        msg = HIW + weapon->name() + HIW "周圍空氣忽然急速旋轉，$n"
                              HIW "躲閃不及眨眼功夫周身竟然被強烈的龍卷風圍在其中，被折騰的手無敷雞之力。\n" NOR;
                        break;
                case 3:
                        msg = HIW + weapon->name() + HIW "刮出強風破，一陣狂風舖面過後，$n"
                              HIW "似乎失去了些許防備能力。\n" NOR;
                        break;
                case 4:
                        msg = HIW + weapon->name() + HIW "刮出一股氣流迅速旋轉並不斷擴散開來，所到之處萬物皆損，$n"
                              HIW "只覺自己天旋地轉，受傷不輕。\n" NOR;
                        break;
                default:
                        msg = HIW + weapon->name() + HIW "刮出強大的龍卷風夾雜黃沙其中從各處向$n"+HIG+"迅速襲來，$n"
                              HIW "身體向短線風箏在旋風中旋轉，全身體無完膚。\n" NOR;
                        break;
                }
                break;

        case "magic":
                // 魔法攻擊：吸取氣+
                resistance=query_temp("apply/resistance/magic", victim);
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=query_temp("apply/add_magic", me);
                reduce=query_temp("apply/reduce_magic", victim);
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 2);

                if( query("neili", victim)>damage )
                        addn("neili", -damage, victim);
                else
                        set("neili", 0, victim);

                switch (random(3))
                {
                case 0:
                        msg = HIM + weapon->name() + HIM "響起一陣奇異的聲音，猶如龍吟，令$n"
                              HIM "心神不定，神情恍惚。\n" NOR;
                        break;
                case 1:
                        msg = HIM "“啵”的一聲，" + weapon->name() + HIM
                              "如擊敗革，卻見$n" HIM "悶哼一聲，搖晃不定！\n" NOR;
                        break;
                default:
                        msg = HIM + weapon->name() + HIM "上旋出一道道五彩繽紛的"
                              "光圈，籠罩了$n" HIM "，四下飛舞。\n" NOR;
                        break;
                }
                break;

        default:
                msg = "";
                break;
        }

        // 使用perform
        if( random(2) && random(query("magic/blood", weapon)) < 2100 ) return msg;
        damage = power + jingjia;

        switch (random(6))
        {
        case 0:
                victim->receive_wound("jing", damage / 6 + random(damage / 6), me);
                return msg + HIM "$N" HIM "嘿然冷笑，抖動" + weapon->name() +
                       HIM "，數道光華一起射出，將$n" HIM "困在當中，無法自拔。\n" NOR;

        case 1:
                victim->receive_wound("jing", damage / 5 + random(damage / 5), me);
                return msg + HIC "$N" HIC "手中的" + weapon->name() + HIC "射出各種光芒，"
                       "眩目奪人，一道道神採映射得天地盡情失色，讓$n"
                       HIC "目瞪口呆！\n" NOR;
        case 2:
                victim->receive_wound("qi", damage / 4 + random(damage / 4), me);
                return msg + HIY "$N" HIY "舉起" + weapon->name() +
                       HIY "，只見天空一道亮光閃過，$n" HIY "連吐幾口鮮血！\n" NOR;

        case 3:
                victim->receive_wound("qi", damage / 3 + random(damage / 3), me);
                return msg + HIG "$N" HIG "隨手劃動" + weapon->name() + HIG "，一圈圈碧芒"
                       "圍向$n" HIG "，震得$n吐血連連！\n" NOR;

        case 4:
                victim->receive_wound("qi", damage / 2 + random(damage / 2), me);
                return msg + HIW "$N" HIW "一聲長嘆，" + weapon->name() + HIW "輕輕遞出，"
                       "霎時萬籟俱靜，$n" HIW "只覺得整個人都跌進了地獄中去！\n" NOR;

        default:

                return msg;
                if( query_temp("weapon_performing", me) )
                        break;
                me->start_call_out(bind((: call_other, __FILE__, "continue_attack",
                                           me, victim, weapon, 10 + random(4) :), me), 0);
        }
}

// 9級兵器攻擊對手
mixed weapon_hit_ob(object me, object victim, object weapon, int damage_bonus)
{
        int ap;
        int dp;
        int damage;
        string msg;

        if (random(2)) return;

        msg = "";

        // 計算damage：不論是空手武器還是普通兵器，統一計算
        if (weapon->is_weapon())
                damage=query_temp("apply/damage", me);
        else
                damage=query_temp("apply/unarmed_damage", me);

        if (damage < 1) return;
        switch (random(8))
        {
        case 0:
                victim->receive_wound("jing", damage / 5 + random(damage / 5), me);
                msg += HIY "$N" HIY "抖動手中的" + weapon->name() + HIY
                       "，幻化成夜空流星，數道" HIM "紫芒" HIY "劃破星"
                       "空襲向$n" HIY "。\n" NOR;
                break;
        case 1:
                victim->receive_wound("qi", damage / 3 + random(damage / 3), me);
                msg += HIR "$N" HIR "大喝一聲，手中" + weapon->name() +
                       HIR "遙指$n" HIR "，一道殺氣登時將$n" HIR "震退"
                       "數步。\n" NOR;
                break;
        case 2:
                victim->receive_wound("qi", damage / 6 + random(damage / 6), me);
                victim->receive_wound("jing", damage / 10 + random(damage / 10), me);
                msg += HIG "$N" HIG "驀地回轉" + weapon->name() + HIG
                       "，漾起層層碧波，宛若" NOR + HIB "星河" HIG "氣"
                       "旋，將$n" HIG "圈裹其中。\n" NOR;
                break;
        case 3:
        case 4:
        case 5:
        case 6:
                break;

        default:
                return msg;
                if( query_temp("weapon_performing", me) )
                        break;
                me->start_call_out(bind((: call_other, __FILE__, "continue_attack",
                                           me, victim, weapon, 5 + random(4) :), me), 0);
        }
        return msg;
}

// 絕招：12連環攻擊
void continue_attack(object me, object victim, object weapon, int times)
{
        int i;
        string msg;
        int ap, dp;

        if (!me || !victim || !weapon || !me->is_fighting(victim) ||
            environment(me) != environment(victim))
                return;

        if (!living(me) || !living(victim) )
                return;
        
        /*
        msg  = HIC "\n$N" HIC "一聲冷笑，人與" + weapon->name() +
               HIC "合而為一，飛也似的撲向$n" HIC "！\n" NOR;
        */
        msg  = HIW "霎時只聽$N" HIW "縱聲長嘯，人與" + weapon->name() +
               HIW "融為一體，霎時間寒芒飛散，向$n" HIW "射去。\n" NOR;

        ap = me->query_skill("martial-cognize");
        dp = victim->query_skill("parry");

        if (ap / 2 + random(ap) > dp / 2)
                /*
                msg += HIR "$n" HIR "大駭之下慌忙後退，卻哪裡躲避得開？一時不禁破綻迭出！\n"
                       HIY "$N" HIY "抓住$n" HIY "露出的破綻，急揮手中的" +
                       weapon->name() + HIY "，連續" + chinese_number(times) +
                       "招全部指向$n" HIY "的要害！\n" NOR;
                */
                msg += HIR "$n" HIR "大駭之下連忙後退，可已然不及閃避，慌亂"
                       "中不禁破綻迭出。\n" HIW "$N" HIW "盯住$n" HIW "招中"
                       "破綻，疾速旋轉手中" + weapon->name() + HIW "，電光火"
                       "石間已朝$n" HIW "攻出" + chinese_number(times) + HIW
                       "招！\n" NOR;
        else
        {
                /*
                msg += HIC "$n" HIC "冥神抵擋，將$N" HIC "這必殺一擊的所有變化全然封住！\n" NOR;
                */
                msg += CYN "可是$n" CYN "冥神抵擋，將$N"
                       CYN "此招的所有變化全然封住。\n" NOR;
                message_combatd(msg, me, victim);
                return;
        }
        message_combatd(msg, me, victim);

        set_temp("weapon_performing", 1, me);
        i = times;
        while (i--)
        {
                if (!me->is_fighting(victim))
                        break;

                if (!victim->is_busy() && random(2))
                        victim->start_busy(1);

                COMBAT_D->do_attack(me,victim,query_temp("weapon", me),0);
        }
        delete_temp("weapon_performing", me);
}

// 待擴充效果
int qianghua_effect(object item, string type)
{
        int level;
        
        level = query("qianghua/level", item);
        level *= 2;

        if( type == "weapon" )
                return level;
        
        return level;
}

// 降低耐久度
void reduce_consistence(object item, object me, object victim, int damage)
{
        int st;
        int con;

        // 調用鑲嵌物品攻擊特效 
        if( !objectp(item) ) return;
        
        do_enchase_attack(item, me, victim, damage);
                        
        st=query("stable", item);

        if (st < 2)
                return;

        con=query("consistence", item);

        // 寰宇天晶煉制的武器永不磨損
        if( query("material", item) == "tian jing" )
                return;

        if( query("material", item) == "no name" )
                return;

        if (random(st) > (100 - con) / 12)
                return;

        if( addn("consistence",-1, item)>0 )
                return;

        set("consistence", 0, item);

        if (environment(item))
                tell_object(environment(item), HIG "你的" +
                            item->name() + HIG "已經徹底損壞了。\n");

        item->unequip();
}

// 構造物品缺省的耐久度信息
void equip_setup(object item)
{
        int stable;
        mapping dbase;
        int max_consistence;

        dbase = item->query_entire_dbase();
        if (!undefinedp(dbase["max_consistence"]))
                max_consistence = dbase["max_consistence"];
        else
                max_consistence = 100;
        if (undefinedp(dbase["consistence"]))
               dbase["consistence"] = max_consistence;

        if( undefinedp(query("stable", item)) )
        {
                switch(query("material", item) )
                {
                case "cloth":
                        // 永遠不會損壞
                        stable = 0;
                        break;

                case "paper":
                        stable = 3;
                        set("no_repair", "這東西我可沒法修理。\n", item);
                        break;

                case "bone":
                        stable = 8;
                        set("no_repear", "修理這個？可別拿我尋開心。\n", item);
                        break;

                case "bamboo":
                case "wood":
                        stable = 10;
                        set("no_repair", "這東西我咋修理？\n", item);
                        break;

                case "stone":
                        stable = 20;
//                        item->set("no_repair", "這個壞了就壞了，可修不了。\n");
                        break;

                case "copper":
                        stable = 40;
                        break;

                case "silver":
                        stable = 40;
                        break;

                case "iron":
                        stable = 45;
                        break;

                case "gold":
                        stable = 50;
                        break;

                case "steel":
                        stable = 75;
                        break;

                default:
                        stable = 100;
                        break;
                }

                if (!item->is_item_make())
                        stable /= 2;

                set("stable", stable, item);
        }
}

// 兵器鑲嵌的寶石攻擊
void do_enchase_attack(object item, object me, object victim, int damage)
{
        mapping enchase;
        string *apply;
        string msg;
        object *inv;
        object shenlong;
        int a1, a2, a3, a4;
        int extra, avoid, i, j, n;
        int dam;

        if( !me || !victim ) return;
                
        // 發揮項鏈的特殊攻擊技能

        //if( !item->is_item_make() ) return;

        if( !query("skill_type", item) && query("armor_type", item) != "hands" &&
             query("armor_type", item) != "finger" ) return;

        // 沒有鑲嵌則返回
        enchase = query("enchase/apply_prop", item);

        if( !mapp(enchase) || sizeof(enchase) < 1 ) 
                return;
        
        message_combatd(HIG + "$N" HIG "的「" + item->name() + HIG "」發出一道奇異的光芒！\n" NOR, me);
        
        apply = keys(enchase);
        n = sizeof(apply);   
        for( i=0;i<n;i++ )
        {
                // 發出特效
                switch( apply[i] )
                {
                case "suck_qi":
                        extra = enchase[apply[i]]; // 偷取生命%
                        if( random(100) > extra ) break;
                        extra = damage*10/100;
                        if( query("qi", victim) < extra ) break;
                        victim->receive_damage("qi", extra, me);
                        me->receive_heal("qi", extra);
                        msg = HIR +victim->name()+ HIR "感到自己的氣血被" + item->name() + HIR "吸幹了似的。\n" NOR;
                        tell_object(victim, msg);
                        msg = HIY "「" + item->name() + HIY "」吸取「" + victim->name() + HIY + "」氣血：" + sprintf("%d", extra) + "點\n" NOR;
                        tell_object(me, msg);
                        break;
                        
                case "suck_neili":
                        extra = enchase[apply[i]]; // 偷取內力%
                        if( random(100) > extra ) break;
                        extra = damage*10/100;
                        if( query("neili", victim) < extra ) break;
                        addn("neili", -extra, victim);
                        addn("neili", extra, me);
                        if( query("neili", me) > query("max_neili", me))
                                set("neili", query("max_neili", me), me);                        
                        msg = HIG +victim->name()+ HIG "感到自己的內力被" + item->name() + HIG "吸幹了似的。\n" NOR;
                        tell_object(victim, msg);
                        msg = HIY "「" + item->name() + HIY "」吸取「" + victim->name() + HIY + "」內力：" + sprintf("%d", extra) + "點\n" NOR;
                        tell_object(me, msg);
                        break;
                
                case "add_blind":
                        extra = enchase[apply[i]]; // 致盲
                        if( random(100) > extra ) break;
                        avoid = query_temp("apply/avoid_blind", victim);
                        if( random(100) < avoid ) break;
                        
                        msg = HIR "$n" HIR "只覺雙目一陣劇痛，眼前一黑，就什麼也看不見了，頓時長聲痛極而呼。\n" NOR;
                        message_combatd(msg, me, victim);
                        set_temp("block_msg/all", 1, victim);
                        victim->start_call_out((: call_other, __FILE__, "remove_effect", victim, "致盲" :), 5);
                        break;
                
                case "add_freeze":
                        extra = enchase[apply[i]]; // 冰凍
                        if( random(100) > extra ) break;
                        avoid = query_temp("apply/avoid_freeze", victim);
                        if( random(100) < avoid ) break;
                        
                        msg = HIB "$n" HIB "只覺四肢僵硬，身體開始凝凍，行動遲緩，動作困難，像一個冰人似的。\n" NOR;
                        message_combatd(msg, me, victim);
                        set_temp("freeze", 1, victim); // combatd和perform中調用
                        victim->start_call_out((: call_other, __FILE__, "remove_effect", victim, "冰凍" :), 5);
                        break;
                
                case "add_burning":
                        extra = enchase[apply[i]]; // 灼傷
                        if( random(100) > extra ) break;
                        avoid = query_temp("apply/avoid_burning", victim);
                        if( random(100) < avoid ) break;
                        
                        msg = HIR "$n" HIR "只覺自己被置于火山之中，身體開始自燃，氣血和內力開始不停的下降。\n" NOR;
                        message_combatd(msg, me, victim);
                        victim->apply_condition("add_burning", 50);
                        break;

                case "add_dizziness":
                        if( query("env/no_dizziness", me) ) break;
                        if( query("fight_room", environment(me)) ) break;
                        extra = enchase[apply[i]]; // 眩暈
                        if( random(100) > extra ) break;
                        avoid = query_temp("apply/avoid_dizziness", victim);
                        if( random(100) < avoid ) break;
                        
                        msg = HIY "$n" HIY "只覺頭腦昏昏沉沉，昏然欲睡，精神不振，迷迷糊糊，處于眩暈狀態中。\n" NOR;
                        message_combatd(msg, me, victim);
                        victim->remove_all_killer();
                        all_inventory(environment(victim))->remove_killer(victim);
                        set_temp("dizziness", 1, victim);
                        set_temp("override/receive_damage", (: call_other, __FILE__, "receive_damage" :), victim); // damage調用恢復
                        victim->start_call_out((: call_other, __FILE__, "remove_effect", victim, "眩暈" :), 5);
                        break;
 
                 case "add_forget":
                        extra = enchase[apply[i]]; // 遺忘
                        if( random(100) > extra ) break;
                        avoid = query_temp("apply/avoid_forget", victim);
                        if( random(100) < avoid ) break;
                        
                        msg = HIR "$n" HIR "突然心中一亂，大腦一片空白，頓時遺忘了絕招如何使用。\n" NOR;
                        message_combatd(msg, me, victim);
                        set_temp("forget", 1, victim); 
                        victim->start_call_out((: call_other, __FILE__, "remove_effect", victim, "遺忘" :), 5);
                        break;
                /*
                case "add_weak":
                        extra = enchase[apply[i]]; // 虛弱
                        if( random(100) > extra ) break;
                        avoid = query_temp("apply/avoid_weak", victim);
                        if( random(100) < avoid ) break;
                        
                        msg = HIR "$n" HIR "頓時只覺得身體非常的虛弱，每個動作都非常困難，一點力氣也使不出來了。。。\n" NOR;
                        message_combatd(msg, me, victim);
                        victim->set_weak(5);
                        break;

                case "add_busy":
                        extra = enchase[apply[i]]; // 忙亂
                        if( random(100) > extra ) break;
                        avoid = query_temp("apply/avoid_busy", victim);
                        if( random(100) < avoid ) break;
                        
                        msg = HIR "「" + item->name() + HIR "」追加「" + victim->name() + HIY + "」忙亂效果：" + sprintf("%d", 5) + "秒\n" NOR;
                        tell_object(me, msg);
                        if( !victim->is_busy() ) victim->start_busy(5);
                        break;
                                                             
                case "add_damage":
                        extra = enchase[apply[i]];
                        extra = damage * extra/100;
                        msg = HIR "「" + item->name() + HIR "」追加「" + victim->name() + HIY + "」傷害：" + sprintf("%d", extra) + "點\n" NOR;
                        tell_object(me, msg);
                        victim->receive_damage("qi", extra, me);
                        break;

                case "no_exert":
                        extra = enchase[apply[i]];                       
                        msg = HIR "「" + item->name() + HIR "」追加「" + victim->name() + HIY + "」內息紊亂：" + sprintf("%d", extra) + "秒\n" NOR;
                        tell_object(me, msg);
                        if( !query_temp("no_exert", victim) ) 
                                set_temp("no_exert", 1, victim);
                        tell_object(victim, HIM "你被" + me->name() + HIM "的" + HIY + item->name() + HIM "打中，頓覺內息紊亂！\n" NOR);

                        // 消除效果
                        call_out("remove_effect", extra, victim, "內息紊亂");
                        break;

                case "no_perform":
                        extra = enchase[apply[i]]; 
                        msg = HIR "「" + item->name() + HIR "」追加「" + victim->name() + HIY + "」力道渙散：" + sprintf("%d", extra) + "秒\n" NOR;
                        tell_object(me, msg);
                        if( !query_temp("no_perform", victim) ) 
                                set_temp("no_perform", 1, victim);
                        tell_object(victim, HIM "你被" + me->name() + HIM "的" + HIY + item->name() + HIM "打中，頓覺力道渙散！\n" NOR);

                        // 消除效果
                        call_out("remove_effect", extra, "力道渙散");
                        break;
                */
                case "clear_force":
                        extra = enchase[apply[i]]; 
                        if( random(100) > extra ) break;
                        if( query("neili", victim) < 100 ) break;
                        msg = HIR "「" + item->name() + HIR "」追加「" + victim->name() + HIY + "」破除氣海要穴。\n" NOR;
                        tell_object(me, msg);
                        set("neili", 0, victim);
                        tell_object(victim, HIM "你被" + me->name() + HIM "的" + HIY + item->name() + HIM "打中氣海要穴，頓覺內力渙散！\n" NOR);
                        break;

                // 削弱戰力
                case "reduce_combat":
                        extra = enchase[apply[i]]; 
                        if( random(100) > extra ) break;
                        if( query_temp("reduce_combat", victim) ) break;

                        msg = HIR "「" + item->name() + HIR "」追加「$n" + HIR "」削弱戰力：削弱攻、防、回避、命中各30%。\n" NOR;
                        message_combatd(msg, me, victim);
                        set_temp("reduce_combat", 1, victim);
                        a1 = query_temp("apply/damage", victim) / 10 * 3;
                        a2 = query_temp("apply/unarmed_damage", victim) / 10 * 3;
                        a3 = query_temp("apply/defense", victim) / 10 * 3;
                        a4 = query_temp("apply/attack", victim) / 10 * 3;
                        addn_temp("apply/damage", -a1, victim);
                        addn_temp("apply/unarmed_damage", -a2, victim);
                        addn_temp("apply/defense", -a3, victim);
                        addn_temp("apply/attack", -a4, victim);
                        victim->start_call_out((: call_other, __FILE__, "remove_effect", victim, "消弱戰力", a1, a2, a3, a4 :), 15);
                        break;

                // 致命一擊
                case "fatal_blow":
                        extra = enchase[apply[i]]; 
                        if( random(100) > 20 ) break;
                        extra = query("qi", victim) * extra/100;
                        
                        msg = HIR "「" + item->name() + HIR "」追加「$n" + HIY + "」致命一擊！傷害：" + sprintf("%d", extra) + "點\n" NOR;
                        message_combatd(msg, me, victim);
                        victim->receive_damage("qi", extra, me);
                        victim->receive_wound("qi", extra/2, me);
                        break;

                // 天魔附體
                case "absorb_blood":
                        extra = enchase[apply[i]]; 
                        if( random(100) > extra ) break;
                        if( query_temp("absorb_blood", me) ) break;
                        msg = HIG "「" + item->name() + HIG "」光芒萬丈，天魔伴隨著光芒從天而降對$N" + HIG "進行附體。\n" NOR;
                        message_combatd(msg, me);
                        set_temp("absorb_blood", 1, me);
                        a1 = query_temp("apply/damage", me) / 10 * 3;
                        a2 = query_temp("apply/unarmed_damage", me) / 10 * 3;
                        a3 = query_temp("apply/defense", me) / 10 * 3;
                        a4 = query_temp("apply/attack", me) / 10 * 3;
                        addn_temp("apply/damage", a1, me);
                        addn_temp("apply/unarmed_damage", a2, me);
                        addn_temp("apply/defense", a3, me);
                        addn_temp("apply/attack", a4, me);
                        me->start_call_out((: call_other, __FILE__, "remove_effect", me, "天魔附體", a1, a2, a3, a4 :), 15);
                        break;
                
                // 殺戮
                case "slaughter":
                        extra = enchase[apply[i]]; 
                        if( random(100) > extra ) break;
                        dam = query("magic/power", item) + query("jiali", me);
                        msg = HIR "「" + item->name() + HIR "」殺氣漫天，一條條殺氣伴隨著閃電從天而降。\n" NOR;
                        message_combatd(msg, me);
                        inv = all_inventory(environment(me));
                        for( j=sizeof(inv)-1; j>=0; j--)
                        {
                                if( inv[j] == me ) continue;
                                if( !inv[j]->is_killing(query("id", me)) ) continue;
                                inv[j]->receive_damage("qi", dam, me);
                                inv[j]->receive_wound("qi", dam/2, me);
                        }
                        break;
                        
                // 召喚神龍
                case "summon_shenlong":
                        extra = enchase[apply[i]]; 
                        if( random(100) > extra ) break;
                        if( time() - query_temp("last_summon_shenlong", me) < 180 ) break;

                        msg = HIG "「" + item->name() + HIG "」光芒萬丈，一條神龍伴隨著光芒從天而降。\n" NOR;
                        message_combatd(msg, me);
                        
                        shenlong = new("/kungfu/class/misc/shenlong");
                        
                        if( !objectp(shenlong) ) break;
                                                
                        set_temp("last_summon_shenlong", time(), me);

                        shenlong->move(environment(me));
                        set("long", HIC + me->name() + HIC "的寶物龍女﹒碧海神龍的力量所召喚的神龍，威風無比。\n" NOR, shenlong);
                        shenlong->kill_ob(victim);
                        shenlong->force_me("guard " + query("id", me) );
                        break;
                default :
                        break;
                }
        }       
        return;
}

// 消除特效
varargs void remove_effect(object victim, string eff, int a1, int a2, int a3, int a4)
{
        if( !objectp(victim) ) return;

        switch( eff )
        {
                case "致盲":
                        if( !query_temp("block_msg/all", victim) ) return;
                        delete_temp("block_msg/all", victim);
                        tell_object(victim, HIR "你終于抹掉了眼前的鮮血，能看見了。\n" NOR);
                        return;
                case "冰凍":
                        if( !query_temp("freeze", victim) ) return;
                        delete_temp("freeze", victim); 
                        tell_object(victim, HIR "你終于全身開始解凍，恢復了正常。\n" NOR);
                        return;
                case "眩暈":
                        if( !query_temp("dizziness", victim) ) return;
                        delete_temp("dizziness", victim);
                        tell_object(victim, HIR "你眩暈狀態解除，恢復了正常。\n" NOR);
                        return;
                case "遺忘":
                        if( !query_temp("forget", victim) ) return;
                        delete_temp("forget", victim); 
                        tell_object(victim, HIR "你終于想起了所有的記憶，恢復了正常。\n" NOR);
                        return;
                case "內息紊亂":
                        if( !query_temp("no_exert", victim) ) return;
                        delete_temp("no_exert", victim);
                        tell_object(victim, HIR "你內息紊亂狀況消除，恢復了正常。\n" NOR);
                        return;
                case "力道渙散":
                        if( !query_temp("no_perform", victim) ) return;
                        delete_temp("no_perform", victim);
                        tell_object(victim, HIR "你力道渙散狀況消除，恢復了正常。\n" NOR);
                        return;
                case "天魔附體":
                        if( !query_temp("absorb_blood", victim) ) return;
                        delete_temp("absorb_blood", victim);
                        addn_temp("apply/damage", -a1, victim);
                        addn_temp("apply/unarmed_damage", -a2, victim);
                        addn_temp("apply/defense", -a3, victim);
                        addn_temp("apply/attack", -a4, victim);
                        return;
                case "消弱戰力":
                        if( !query_temp("reduce_combat", victim) ) return;
                        delete_temp("reduce_combat", victim);
                        addn_temp("apply/damage", a1, victim);
                        addn_temp("apply/unarmed_damage", a2, victim);
                        addn_temp("apply/defense", a3, victim);
                        addn_temp("apply/attack", a4, victim);
                        return;
        }
        return;
}

varargs int receive_damage(object me, string type, int damage, object who)
{
        delete_temp("override/receive_damage", me);
        if( !query_temp("dizziness", me) ) return 0;
        delete_temp("dizziness", me);
        tell_object(me, HIR "由于受到攻擊，你眩暈狀態解除，恢復了正常。\n" NOR);
        return 0;
}
