// 玩家任務：defend.c

#include <ansi.h>
#include <quest.h>

inherit QUEST_OB;

#include <defend.h>

#define ENEMY_FAM             my["enemy_fam"]      // 攻擊者來自的門派
#define DEFEND_FAM            my["defend_fam"]     // 要保衛的門派
#define MASTER_ID             my["master_id"]
#define PLACE                 my["place"]
#define MIN_EXP               30000                // 最小 EXP 要求

nosave object dmaster = 0;

// 下面區分正派和邪派，就是為了防止出現一個門派自己攻擊
// 自己的荒唐情況（當然這也不難避免），一般而言，都是正
// 派攻擊邪派，或者邪派攻擊正派的（諸如“六大門派圍攻光
// 明頂”、“日月神教滅五岳劍派”什麼的），但是我們知道，
// 有些門派是很難說得清正邪的，比如桃花島，姑蘇慕容等等，
// 這樣我們就認為，同時不屬于以下兩個數組的門派，是“亦
// 正亦邪”或者說是“不正不邪”，也就是說，它在這場紛爭
// 中的態度是：既可能攻擊正派，也可能攻擊邪派，當然，也
// 可能攻擊亦正亦邪的門派。

// 正派列表
string *zps = ({
        "武當派", "華山氣宗", "全真教", "古墓派",
        "靈鷲宮", "桃花島", "關外胡家", "段氏皇族",
        "峨嵋派", "丐幫", "少林派", "逍遙派",
        "明教", "華山劍宗","唐門世家",
});

// 邪派列表
string *xps = ({
        "星宿派", "血刀門", "大輪寺", "歐陽世家",
        "神龍教", "慕容世家", "日月神教",
});

void die(object ob);
void npc_destructed();
void move_enemy(object enemy, string family);
void remove_enemy();
int  ask_defend(object ob, object me);
int  ask_finish(object ob, object me);

// 任務對象創建
void create()
{
        seteuid(getuid());
        setup();
}

// 啟動一個任務
// 輸入生成敵人的數量和被攻擊的門派名稱，已經向這個門
// 派的掌門要了任務的人可以去殺這些敵人，任務時間到了
// 就可以要獎勵。
void init_quest(int num, string family_name)
{
        int i;
        mapping my;
        object enemy;
        string *family;
        string enemy_fam;
        object env;

        my = query_entire_dbase();

        // 生成任務的名字
        set_name("圍攻" + family_name);

        // 隨機生成攻打者的門派
        family = keys(familys);
        if (member_array(family_name, xps) != -1)
        {
                family = family - xps - ({ family_name });
                enemy_fam = family[random(sizeof(family))];
        }
        // 否則就派正派上場
        else
        {
                family = family - zps - ({ family_name });
                enemy_fam = family[random(sizeof(family))];
        }

        // 記錄任務的數據信息
        ENEMY_FAM = enemy_fam;
        DEFEND_FAM = family_name;
        MASTER_ID = familys[family_name]["master_id"];
        PLACE = familys[family_name]["master_place"];

        env = get_object(PLACE);

        if (! objectp(dmaster = present(MASTER_ID, env)) ||
            query("startroom", dmaster) != base_name(env) )
        {
                destruct(this_object());
                return;
        }

        // 設置NPC的對話信息
        set("inquiry/"+name(), "你可以輸入指令defend來領取保衛門派任務。", dmaster);
        dmaster->set("inquiry/"+ENEMY_FAM,"這個"+ENEMY_FAM+"真是太可惡了，"
                                            "屢次來我們" + DEFEND_FAM +"挑舋。");
        dmaster->set("inquiry/"+DEFEND_FAM,"在下就是"+DEFEND_FAM+"的掌門呀，"
                                            "你願不願意助本門一臂之力，共御外敵？");
        set_temp("override/ask_defend", (:ask_defend:), dmaster);
        set_temp("override/ask_finish", (:ask_finish:), dmaster);

        // 按照指定位置送走敵人
        for (i = 0; i < num; i++)
        {
                enemy = new("/clone/npc/enemy");
                enemy->create_family(enemy_fam, familys[enemy_fam]["generation"]
                                                + (-1 + random(2)), "弟子" );
                enemy->setup_family(enemy_fam);
                set("is_attacking", family_name, enemy);
                set("long", "這人是前來攻打"+family_name+"的一名"+enemy_fam+"弟子。\n", enemy);

                // enemy->set_temp("override/die", (: die :));

                move_enemy(enemy, family_name);
        }

        CHANNEL_D->do_channel(dmaster, "family",
                        sprintf("聽說%s的一班弟子大舉殺上我派，我派形勢不妙。", enemy_fam));

        // 切換到正常狀態
        change_status(QUEST_READY);

        // 設置任務最長存活時間：5分鐘
        set("live_time", 300);

        // 登記謠言消息
        register_information();
}

void send_enemy(int num, string family_name)
{
        object enemy;
        string enemy_fam;
        string *family;
        int i;

        family = keys(familys);
        if (member_array(family_name, xps) != -1)
        {
                family = family - xps - ({ family_name });
                enemy_fam = family[random(sizeof(family))];
        }
        // 否則就派正派上場
        else
        {
                family = family - zps - ({ family_name });
                enemy_fam = family[random(sizeof(family))];
        }

        for (i = 0; i < num; i++)
        {
                enemy = new("/clone/npc/enemy");
                enemy->create_family(enemy_fam, familys[enemy_fam]["generation"]
                                                + (-1 + random(2)), "弟子" );
                enemy->setup_family(enemy_fam);
                set("is_attacking", family_name, enemy);
                set("long", "這人是前來攻打"+family_name+"的一名"+enemy_fam+"弟子。\n", enemy);

                set_temp("override/die", (:die:), enemy);

                move_enemy(enemy, family_name);
        }

        return;
}

// 送走敵人（在 ENEMY 的 chat_msg 中也有呼叫）
void move_enemy(object enemy, string family)
{
        string *places = familys[family]["place"];
        string place = places[random(sizeof(places))];
        object room;

        if (objectp(room = environment(enemy)))
        {
                tell_room(room, enemy->name() + "一閃身就不見了。\n");
        }
#ifdef DEBUG
        CHANNEL_D->do_channel(this_object(), "sys",
                sprintf("%s : %O", enemy->short(), place));
#endif
        enemy->move(place);
        tell_room(place,"只見一名"+query("family/family_name", enemy)+"弟子不知什麼時候鑽了出來。\n");

        return;
}

// 恢復NPC：任務結束的時候必須恢復正常的NPC
void restore_npc()
{
        mapping my = query_entire_dbase();
        object npc_ob;

        if (! objectp(npc_ob = dmaster))
                return;

        delete_temp("override/ask_defend", npc_ob);
        delete_temp("override/ask_finish", npc_ob);
        delete("inquiry/"+name(), npc_ob);
        delete("inquiry/"+ENEMY_FAM, npc_ob);
        delete("inquiry/"+DEFEND_FAM, npc_ob);
        dmaster = 0;
}

// 結束任務
void cancel_quest()
{
        remove_enemy();
        restore_npc();
        ::cancel_quest();
}

// 到時間了，送走敵人
void remove_enemy()
{
        object *enemys;
        int i;
        mapping my = query_entire_dbase();

        enemys = children("/clone/npc/enemy");
        enemys=filter_array(enemys,(:query("is_attacking", $1) == $(DEFEND_FAM )
                                       && query("family/family_name", $1) == $(ENEMY_FAM):));

        if (sizeof(enemys) > 0)
        {
                for (i = 0; i < sizeof(enemys); i++)
                {
                        if (enemys[i]->is_fighting())
                        {
                                enemys[i]->remove_all_killer();
                                tell_room(environment(enemys[i]), HIW "只見" + enemys[i]->name()
                                        + "突然面色一變，迅速攻出幾招，跳出戰圈轉身逃了。\n");
                        }
                        else {
                                tell_room(environment(enemys[i]), HIW "只見" + enemys[i]->name()
                                        + "掐值一算，突然臉色大變，急急忙忙地逃走了。\n");
                        }
                        destruct(enemys[i]);
                }
        }
        return;
}

// 要到任務才能去殺人（去掉非要本門的限制）
int ask_defend(object ob, object me)
{
        string *places, place;

        string *msg_now =
        ({
                "最近本門常有人來挑舋", "最近本門似乎不太平安",
                "最近本門時有敵人進攻", "最近本門似乎很不安穩",
                "聽說就快要有敵人進攻", "常有人對本門虎視眈眈",
        });
        string *msg_do =
        ({
                "趕快到四處巡查巡查", "注意四周都要去查查",
                "山上山下都仔細看看", "在本門要道好好守著",
                "在險要地方做好防衛", "得防止敵人攻上山來",
        });
        string *msg_place =
        ({
                "雖然說不上山明水秀，但是", "也是一個險要位置，所以",
                "好歹也是個重要關卡，因此", "畢竟算個本門要地，那麼",
                "常常有敵人來此攻打，所以", "就怕敵人攻到這裡，因此",
        });

        if( !query("family/family_name", me) )
        {
                ob->command("haha"+query("id", me));
                message_sort(HIC "$N" HIC "對$n" HIC "道：“" + RANK_D->query_respect(me)
                                +"無門無派，問我要什麼任務呢？”\n" NOR, ob, me);
                tell_object(me, HIW "你還是先拜個師父再要任務吧。\n" NOR);
                return 1;
        }

        if( query("family/family_name", ob) != query("family/family_name", me) )
        {
                ob->command("?"+query("id", me));
                message_sort(HIC "$N" HIC "皺著眉頭對$n" HIC "道：“這位"
                        +query("family/family_name", me)+"的"+RANK_D->query_respect(me)+
                        "，你怕是找錯人了吧？”\n" NOR, ob, me);
                tell_object(me, HIW "這不是你自己的門派，你不應該問這位師傅要任務呀。\n" NOR);
                return 1;
        }

        if( query("combat_exp", me)<MIN_EXP )
        {
                ob->command("sigh");
                message_sort(HIC "$N" HIC "對$n" HIC "道：“唉，你還是等水平高些"
                                "再來做這個任務不遲。”\n" NOR, ob, me);
                tell_object(me, HIW "這個任務得有 " +MIN_EXP+" 點經驗值才能做。\n" NOR);
                return 1;
        }

        if( query_temp("defend_quest", me) && !wizardp(me) )
        {
                ob->command("yi");
                message_sort(HIC "$N" HIC "疑惑地對$n" HIC "道：“你不是已經在做"
                                "這個任務了麼？\n怎麼還來找我？”\n" NOR, ob, me);
                tell_object(me, HIW "快去做好準備，保衛你的門派吧。\n" NOR);
                return 1;
        }

        else
        {
                places = familys[query("family/family_name", me)]["place"];
                place = places[random(sizeof(places))];
                place=query("short", get_object(place));

                send_enemy(10,query("family/family_name", me));

                command("nod"+query("id", me));
                message_sort(HIC "$N" HIC "讚許地對$n" HIC "道：“好吧，"
                        + msg_now[random(sizeof(msg_now))] +"，你要注意\n"
                        + msg_do[random(sizeof(msg_do))] + "。”\n" NOR, ob, me);

                tell_object(me, HIW + ob->name() + HIW "悄悄告訴你：“"
                        + place + HIW"這個地方" + msg_place[random(sizeof(msg_place))]
                        +"\n你最好多注意注意。”\n" NOR);

                set_temp("defend_quest/start", 1, me);
                me->apply_condition("swjob", 30 + random(30));
                return 1;
        }
}

int ask_finish(object ob, object me)
{
        int killed, exp, pot, gongxian;

        if( !query("family/family_name", me) )
        {
                ob->command("haha"+query("id", me));
                message_vision(HIC "$N" HIC "對$n" HIC "道：“" + RANK_D->query_respect(me)
                                +"無門無派，問我要什麼任務呢？”\n\n" NOR,ob,me);
                tell_object(me, HIW "你還是先拜個師父再要任務吧。\n" NOR);
                return 1;
        }

        if( query("family/family_name", ob) != query("family/family_name", me) )
        {
                ob->command("?"+query("id", me));
                message_vision(HIC "$N" HIC "皺著眉頭對$n" HIC "道：“這位" +
                               query("family/family_name", me)+"的"+RANK_D->query_respect(me)+
                               "，你怕是找錯人了吧？”\n" NOR,ob,me);
                tell_object(me, HIW "這不是你自己的門派，你不應該問這位師傅要任務呀。\n" NOR);
                return 1;
        }

        if( !query_temp("defend_quest/start", me) )
        {
                ob->command("sigh");
                message_vision(HIC "$N" HIC "疑惑地對$n" HIC "道：“你都不是在做這個任務，就想要獎勵？”\n" NOR, ob, me);
                tell_object(me, HIW "你總得先要個任務吧。\n" NOR);
                return 1;
        }

        if( !query_temp("defend_quest/finish", me) )
        {
                ob->command("sigh");
                message_vision(HIC "$N" HIC "疑惑地對$n" HIC "道：“你的任務還沒有完呢，現在就想要獎勵？”\n" NOR, ob, me);
                tell_object(me, HIW "你等做完了再要獎勵吧。\n" NOR);
                return 1;
        } else
        {
                if( !query_temp("defend_quest/killed", me) )
                {
                        ob->command("hmm");
                        message_vision(HIC "$N" HIC "點點頭對$n" HIC "道：“好吧，這次任務你存功未立，就不給你獎勵了。”\n" NOR, ob, me);
                        delete_temp("defend_quest", me);
                        return 1;
                } else
                {
                        killed=query_temp("defend_quest/killed", me);
                        ob->command("nod");

                        exp = killed * 40 + random(200);
                        exp = exp / 2 + random(exp / 2);
                        pot = exp / 3 + random(2);
                        gongxian = killed * 3;

                        message_vision(HIC "$N" HIC "點點頭對$n" HIC "道：“好！這次任務你成功截殺了" +
                                       chinese_number(killed) + "個敵人，這裡是給你的一點獎勵。”\n" NOR, ob, me);
                        /*
                        tell_object(me, HIW "這次任務你得到了" + chinese_number(exp) + "點經驗值和" +
                                       chinese_number(pot) + "點潛能值的獎勵，你的門派貢獻提高了。\n" NOR);
                        */
                        delete_temp("defend_quest", me);

                        QUEST_D->bonus(me, ([ "exp" : exp, "pot" : pot, "gongxian" : gongxian ]), 1);

                        return 1;
                }
        }
}

void die(object ob)
{
        int percent;
        object me;
        string *pills, pill;
        int amount = 300 + random(300);
        string *condition = ({
                "氣喘吁吁，就要不支", "頭重腳輕，馬上就倒",
                "嘔血成升，眼冒金星", "傷痕累累，無力招架",
        });

        if (objectp(me = ob->query_last_damage_from())
        &&  environment(ob) == environment(me)
         && query_temp("defend_quest/start", me )
         && !query_temp("defend_quest/finish", me )
         && !query_temp("defend_quest/waiting", me) )
        {
                switch (random(15))
                {
                        case 1: {
                                message_sort(HIR "眼見$N" HIR + condition[random(sizeof(condition))]
                                                +"，突然$N大喝一聲，急退幾步，\n“撲通”給$n跪了下來。"
                                                "\n" NOR, ob, me);
                                tell_object(me, HIW + ob->name()+"突然從懷裡掏出一堆白花花的銀子，小聲"
                                                "對你道：“這位" + RANK_D->query_respect(me) + "，\n你"
                                                "就網開一面（nod）如何，這" + chinese_number(amount) +
                                                "兩白銀就歸你了！”\n" NOR);
                                ob->clean_up_enemy();
                                ob->remove_all_enemy(0);
                                ob->clear_condition(0);
                                set("jing", 1, ob);
                                set("qi", 1, ob);
                                set_temp("defend_quest/waiting", amount, me);
                                return;
                        }
                        default: {
                                // 獎勵
                                if( query("family/family_name", me) == query("is_attacking", ob) )
                                        addn_temp("defend_quest/killed", 1, me);

                                set_temp("die", 1, ob);

                                QUEST_D->bonus(me, ([ "exp" : 10 + random(30),
                                                      "pot" : 3 + random(20),
                                                      "score" : 3 + random(20) ]));
                                ob->die(me);
                        }
                }
                return;
        }
        if( objectp(me) && query("family/family_name", me) == query("is_attacking", ob) )
        {
                addn_temp("defend_quest/killed", 1, me);

                QUEST_D->bonus(me, ([ "exp" : 10 + random(30),
                                      "pot" : 3 + random(20),
                                      "score" : 3 + random(20) ]));
        }
        ob->die();
}

// 詢問DEFENDER - 正在被攻打的門派
string ask_defender(object knower, object me)
{
        mapping my = query_entire_dbase();

        return CYN "這個" HIY + DEFEND_FAM + NOR CYN
               "聽說名聲倒是很大，不會這次就會給" HIY
               + DEFEND_FAM + NOR CYN "滅了吧。";
}

// 詢問ENEMY - 攻打者的門派
string ask_enemy(object knower, object me)
{
        mapping my = query_entire_dbase();

        return CYN "這個" HIY + ENEMY_FAM + NOR CYN
               "的弟子一向兇霸霸的，一看就不是什麼好東西。" NOR;
}

// 任務介紹
string query_introduce(object knower)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC))
        {
                remove_call_out("do_say");
                call_out("do_say", 1);
        }

        return CYN "據說那個" + HIY + ENEMY_FAM + NOR CYN "的弟子們正在攻打" +
               HIY + DEFEND_FAM + NOR CYN "呢，也不知道結下了什麼樑子。" NOR;
}

void do_say(object knower)
{
        if (! objectp(knower) || ! living(knower))
                return 0;

        message_sort("$N嘟囔道：“我跟你都說了，這些門派呀，沒一個好"
                       "東西，這不？打起來了吧？”\n", knower);
}

// 任務提示
string query_prompt()
{
        switch (random(3))
        {
        case 0:
                return CYN "倒是最近聽有些客人說起" HIY + name() +
                       NOR CYN "來。";
        case 1:
                return "也沒什麼大事，只是聽說過" HIY + name() +
                       NOR CYN "罷了。";
        default:
                return "前兩天還聽人家說過" HIY + name() +
                       NOR CYN "呢。";
        }
}

// 登記該任務的消息
void register_information()
{
        mapping my = query_entire_dbase();

        if (! clonep() || ! mapp(my))
                // 不是任務，所以不登記
                return;

        set_information(ENEMY_FAM, (: ask_enemy :));
        set_information(DEFEND_FAM,(: ask_defender :));
}

// 這個任務可以被某人知曉嗎？
int can_know_by(object knower)
{
        return 1;
}

void check_all_place()
{
        int i, j;
        string *the_place;
        string *family;
        object env;

        family = keys(familys);
        for (i = 0;i < sizeof(family);i++)
        {
                the_place = familys[family[i]]["place"];
                for (j = 0;j<sizeof(the_place);j++)
                        if (!objectp(env = get_object(the_place[j])))
                                log_file("static/defend_quest",sprintf("門派任務錯誤記錄：%s\n",the_place[j]));
        }
}
