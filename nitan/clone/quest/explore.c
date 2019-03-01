// 玩家任務：explore.c

#include <ansi.h>
#include <quest.h>
#include <command.h>

inherit QUEST_OB;

#define NPC_OB          my["npc"]       // 接收寶物的NPC對象
#define NPC_NAME        my["npc_name"]  // 接收寶物的NPC的名字
#define NPC_ID          my["npc_id"]    // 接收寶物的NPC的ID
#define ENV_OB          my["env_ob"]    // 寶物隱藏的地點
#define QOB             my["qob"]       // 接收寶物的文件名字
#define QOB_NAME        my["qob_name"]  // 接收寶物的名字
#define ZONE            my["zone"]      // 接收對象所處的區域

object search_qob(object me);
int    npc_accept_object(object me, object who, object ob);
void   npc_destructed();

// 任務對象創建
void create()
{
        seteuid(getuid());
        setup();
}

// 啟動一個任務
// 輸入一個物品進行尋找，自動生成兩個人物和兩個地點，其中殺
// 了第一個人即可獲得該物品，然後交給第二個人領取獎勵。
void init_quest(object npc_ob, string qob_name, string zone, string *files)
{
        mapping my;
        string room;
        object env;
        object qob;

        my = query_entire_dbase();

        // 生成任務的名字
        set_name(npc_ob->name() + "的事");

        if( query_temp("quest_ob", npc_ob) )
        {
                // 這個NPC已經用于其他任務，中止任務
                destruct(this_object());
                return;
        }

        if (objectp(qob = find_object(qob_name)))
        {
                if( objectp(query_temp("quest_ob", qob)) )
                {
                        // 該物品已經存在並用于其他任務，這個任務不能進行
                        destruct(this_object());
                        return;
                }
        } else
                // 生成任務物品
                qob = load_object(qob_name);

        // 記錄該物品的任務屬性
        set_temp("quest_ob", this_object(), qob);

        NPC_OB = npc_ob;
        NPC_NAME = npc_ob->name();
        NPC_ID=query("id", npc_ob);
        QOB    = qob;
        QOB_NAME = qob->name();
        ZONE = zone;

        // 隨機選擇一個地點
        for (;;)
        {
                call_other(room = zone + files[random(sizeof(files))], "???");
                if (! objectp(env = find_object(room)))
                {
                        // 無法取得這個房間
                        cancel_quest();
                        return;
                }

                if( mapp(query("exits", env)) )
                        // 找到了有出口的房間
                        break;
        }

        // 在房間中放置可搜索的對象，並去掉該房間可以找到的
        // 銀兩和銅板
        env->set_temp("no_search",(["/clone/money/coin":0,
                                      "/clone/money/silver" : 0, ]));
        set_temp("search_objects", ([(:search_qob:):10000]), env);
        set_temp("been/searched", -150, env);
        ENV_OB = env;

        // 設置NPC的對話信息
        set("inquiry/"+NPC_NAME, "正是區區在下！", npc_ob);
        set("inquiry/"+NPC_ID, "是我啊，你找對人了！", npc_ob);
        set("inquiry/"+QOB_NAME, "啊！你...你知道麼？快給我！", npc_ob);
        set_temp("quest_ob", this_object(), npc_ob);

        // 設置接收物品的信息：由于NPC存在的時候該任務對象必
        // 定會存在（因為任務析構的時候會清除NPC），所以可以
        // 讓NPC引用本地的"npc_accept_object"函數。
        set_temp("override/accept_object", (:npc_accept_object:), npc_ob);

        // 設置析構信息：NPC人物析構以後將自動解除任務
        set_temp("override/destruct", (:npc_destructed:), npc_ob);

        // 切換到正常狀態
        change_status(QUEST_READY);

        // 設置任務最長存活時間：30分鐘
        set("live_time", 1200);

        // 登記謠言消息
        register_information();
}

// 恢復NPC：任務結束的時候必須恢復正常的NPC
void restore_npc()
{
        mapping my = query_entire_dbase();
        object npc_ob;

        if (! objectp(npc_ob = NPC_OB))
                return;

        delete_temp("override/accept_object", npc_ob);
        delete_temp("override/destruct", npc_ob);
        delete("inquiry/"+NPC_NAME, npc_ob);
        delete("inquiry/"+NPC_ID, npc_ob);
        delete("inquiry/"+QOB_NAME, npc_ob);
        NPC_OB = 0;
}

// 恢復ENV：任務結束的時候必須恢復正常的環境
void restore_env()
{
        mapping my = query_entire_dbase();
        object env;

        if (! objectp(env = ENV_OB))
                return;

        // 去掉臨時搜索的物品信息
        delete_temp("search_objects", env);
        delete_temp("no_search", env);
        set_temp("been/searched", 30, env);
        ENV_OB = 0;
}

// 結束任務
void cancel_quest()
{
        mapping my = query_entire_dbase();

        // 恢復NPC，然後結束任務
        restore_npc();
        restore_env();

        if (objectp(QOB) && ! environment(QOB))
                destruct(QOB);

        ::cancel_quest();
}

// 任務NPC消亡
void npc_destructed()
{
        call_out("cancel_quest", 0);
}

// 在房屋種找物品
object search_qob(object me)
{
        mapping my = query_entire_dbase();
        mapping dq;
        int i, exp2, pot2, exc2;      // 強迫freequest所獲得的額外獎勵
        object ob, gift;
        string msg;

        if( query("score", me)<2000 )
                // 必須有2000的江湖閱歷才能夠找到
                return 0;

        if (! objectp(QOB))
                // 這個物品已經沒有了，無法找了
                return 0;

        if (objectp(environment(QOB)))
                // 該物品已經現世，無法找了
                return 0;

        if( !query("no_fight", environment(me)) && random(100)<10 )
        {
                // 找到殺手一名？
                ob = new("/clone/npc/killer");
                ob->move(environment(me));
                message_vision(HIW "\n突然竄出一個黑影，惡狠狠的對$N"
                               HIW "罵道：" + RANK_D->query_rude(me)
                               + "！你在這兒幹啥？\n" NOR, me);
                ob->kill_ob(me);
                return 0;
        }

        if( mapp(dq=query_temp("freequest", me)) && 
            dq[this_object()])
        {
                // 如果我詢問過這個任務，此時就可以獲得獎勵
                map_delete(dq, this_object());

                GIFT_D->delay_bonus(me, ([ "exp"   : 100 + random(20),
                                           "pot"   : 30 + random(20),
                                           "score" : 5 + random(4),
                                           "prompt": "在你尋找" + QOB_NAME +
                                                     HIC "的過程中" ]));

                // 被列為門派中斷的自由任務
                if( query("quest/freequest", me)>0 )
                        GIFT_D->delay_freequest_bonus(me);
        }
        return QOB;
}

// 詢問NPC - 需要提供物品的人
string ask_npc(object knower, object me)
{
        mapping my = query_entire_dbase();

        if (! objectp(NPC_OB))
                return CYN "哦，據說" HIY + NPC_NAME + NOR CYN
                       "不知道去哪兒去了，神秘的失蹤了。" NOR;

        return "你說" + NPC_NAME + "啊？我還想向你打聽呢！";
}

// 詢問QOB - 提供的物品的信息
string ask_qob(object knower, object me)
{
        mapping my = query_entire_dbase();
        mapping dq;
        object env;
        string exits;
        string *str;

        if (! objectp(QOB) || ! objectp(env = ENV_OB) && ! environment(QOB))
                return CYN "據可靠的消息說，" + QOB_NAME + CYN "是"
                       "再也找不著了，再怎麼也是白忙活了。" NOR;

        if (environment(QOB))
                return CYN "好像說是有人已經找到" + QOB_NAME +
                       CYN "了，嘖嘖，怎麼就不是我呢？" NOR;

        if( query("score", me) >= 2000 )
        {
                if( !mapp(query("exits", env)) )
                        exits = "沒有出口";
                else
                {
                        str=keys(query("exits", env));
                        str = map_array(str, (: GO_CMD->query_chinese_dir($1) :));
                        str -= ({ 0 });
                        exits = "大概具有" + implode(str, "、") + "出口";
                }

                message("vision", WHT + knower->name() + "看了看四周，鬼鬼祟祟"
                                  "的在" + me->name() + WHT "耳邊說了些什麼。\n"
                                  NOR, environment(me), ({ me }));

                tell_object(me, sort_msg(knower->name() + "看了看四"
                            "周，鬼鬼祟祟的在你耳邊說道：“你可千萬"
                            "別告訴別人呀！這可是我聽到的秘密情報，"
                            "今天我不要錢就告訴你了：據說那個東西在一個" +
                            exits + "的地方，離咱們這裡也不算太遠呢。你"
                            "到那裡仔細找找沒準會有發現呢！”\n"));

                if( !mapp(dq=query_temp("freequest", me)) )
                        dq = ([ this_object() : 1 ]);
                else
                        dq[this_object()] = 1;

                set_temp("freequest", dq, me);
        } else
                message_vision(CYN "$N" CYN "上上下下的打量了$n" CYN "一番，嘴"
                               "角露出一絲不屑的神態。\n" NOR, knower, me);

        return CYN "其實你說這" HIY + QOB_NAME + NOR CYN
               "東西有啥用呢？能比得上雞腿和酒袋麼？" NOR;
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

        return CYN "據說" + HIY + NPC_NAME + NOR CYN "正在托人尋找" +
               HIY + QOB_NAME + NOR CYN "，嘖嘖，可惜我要看店。" NOR;
}

// 任務提示
string query_prompt()
{
        switch (random(3))
        {
        case 0:
                return CYN "最近聽來往的客人談起過『" HIY + name() +
                       NOR CYN "』來。";
        case 1:
                return "噢！樓上住店的那幾個客人剛才說什麼『" HIY + name() +
                       NOR CYN "』呢。";
        default:
                return "前兩天來過幾個江湖人士，一看就是高手，"
                       "他們還說起過『" HIY + name() + NOR CYN "』呢。";
        }
}

void do_say(object knower)
{
        if (! objectp(knower) || ! living(knower))
                return 0;

        message_vision(CYN "$N" CYN "聳聳肩道：“這年頭，露財不是好事。"
                       "你看，這不出事了吧？”\n" NOR, knower);
}

int npc_accept_object(object me, object who, object ob)
{
        mapping my = query_entire_dbase();
        mapping b;
        object reward;

        int exp;
        int pot;
        int score;
        int weiwang;

        if (ob->is_character() || ob->is_item_make())
                // 不接受人物和自造的兵器
                return 0;

        if (ob != QOB)
                return 0;

        if (me->is_fighting())
                return 0;

        if( base_name(environment(me)) != query("startroom", me) )
        {
                message_vision("$N望著$n，一副白痴模樣。\n", me, who);
                return -1;
        }

        message_sort(HIY "\n$N" HIY "接過" + ob->name() + HIY "，翻來覆去看"
                     "了看，喜不自勝，一時間是激動萬分。半晌才對$n" HIY "道"
                     "：這位" + RANK_D->query_respect(who) + "，實在是感激"
                     "不盡，這點小意思，務必笑納！\n" NOR, me, who);

        message_vision(HIC "$N" HIC "交給$n" HIC "一些" NOR + YEL "黃金"
                       HIC "作為報酬。\n" NOR, me, who);

        reward = new("/clone/money/gold");
        reward->set_amount(1);
        reward->move(who, 1);

        // 獎勵
        exp = 200 + random(200);
        pot = 150 + random(150);
        score = 15 + random(15);
        weiwang = 5 + random(5);

        b = ([ "exp"     : exp,
               "pot"     : pot,
               "score"   : score,
               "weiwang" : weiwang,
               "prompt"  : "在尋找" + QOB_NAME + HIC
                           "的過程中，經過鍛煉" ]);
        GIFT_D->delay_bonus(who, b);

/*
        CHANNEL_D->do_channel(this_object(), "rumor",
                              "聽說" + who->name(1) +
                              "("+query("id", who)+
                              ")替" + me->name() + HIM +
                              "找到了" + QOB_NAME + HIM
                              "，領到了賞銀。" NOR);
*/

        destruct(ob);
        call_out("cancel_quest", 0);
        return -1;
}

// 登記該任務的消息
void register_information()
{
        mapping my = query_entire_dbase();

        if (! clonep() || ! mapp(my))
                // 不是任務，所以不登記
                return;

        set_information(NPC_NAME, (: ask_npc :));
        set_information(NPC_ID,   (: ask_npc :));
        set_information(QOB_NAME, (: ask_qob :));
}

// 這個任務可以被某人散布嗎？
int can_know_by(object knower)
{
        mapping my = query_entire_dbase();
        string fname;

        fname = file_name(environment(knower));
        if (! stringp(ZONE) || strlen(ZONE) < 1 ||
            ZONE == fname[0..strlen(ZONE) - 1])
                // 和小二在同一個區域
                return 1;

        return 0;
}
