// ultraquestd.c
// Written by Vin for Heros.cn 2002/08/16.
// Rewritten by Lonely@nitan.org

#include <ansi.h>
#include <quest.h>

inherit F_DBASE;

// 定義提供給外部調用的接口函數
public mixed accept_ask(object me, object who, string topic);
public mixed ask_information(object me, object who, string topic);
public void generate_information(object me, object who);
public void give_quest(object me, object who);
public void give_accede(object me, object who);
public void quest_guard(object me, object who);
public void quest_going(object me, object who);
public void give_gift(object me, object who);
void start_guard(object me, object who);
void check_guard(object me, object who, object killer);
void check_going(object me, object who);

#define QUEST           "/adm/etc/questlist/"
#define QUESTER "南賢"
#define LURCHER "北醜"

private void special_bonus(object me, object who)
{
        object ob;
        string un;

        // 給予隨機的物品作獎勵
        string *ob_list = ({
                "/clone/tessera/gem",
                "/clone/fam/item/bless_water",
                "/clone/fam/pill/dimai",
                "/clone/fam/pill/yulu",
                "/clone/fam/pill/renshen4",
                "/clone/fam/pill/lingzhi4",
                "/clone/fam/pill/xuelian4",
                "/clone/fam/pill/renshen3",
                "/clone/fam/pill/lingzhi3",
                "/clone/fam/pill/xuelian3",
                "/clone/fam/pill/linghui2",
                "/clone/fam/pill/neili2",
                "/clone/fam/pill/puti4",
                "/clone/fam/pill/sheli4",
                "/clone/fam/pill/sheli3",
                "/clone/fam/pill/puti3",
                "/clone/fam/pill/puti2",
                "/clone/fam/pill/sheli2",
        });

        ob = new(ob_list[random(sizeof(ob_list))]);

        // 查看物品的單位屬性
        if( query("base_unit", ob) )
                un=query("base_unit", ob);
        else
                un=query("unit", ob);

        // 保持與正常的 give 信息一致
        message_vision("$N說完拿出一" +
                       un+ob->name()+NOR"("+query("id", ob)+
                       ")給$n" NOR "。\n\n" NOR, me, who);

        ob->move(who, 1);
}

// 任務的起始程序，給予出最初任務和提供新線索
public mixed accept_ask(object me, object who, string topic)
{
        object item;
        string msg;
        string type;
        mapping q;

        if (topic == "任務" || topic == "quest")
        {
                message_vision("$n向$N打聽有關宗師任務的情況。\n", me, who);
                if (! ultrap(who))
                {
                        message_vision("$N瞪大眼睛看著$n，道：“你還沒有成為武學大宗師，還幫不了"
                                       "我什麼忙！”\n", me, who);
                        return 1;
                }

                q=query("ultraquest", who);
                if (mapp(q))
                {
                        switch (q["type"])
                        {
                        case "find":   // 尋物
                                message_vision(CYN "$N" CYN "一臉怒容對$n" CYN "道：我不是讓"
                                               "你把" NOR + HIR + q["name"] + "(" + q["id"] +
                                               ")" + NOR + CYN "給我找來嗎，現在這個東西呢？\n" NOR,
                                               me, who);
                                break;
                        case "send":   // 送物
                                message_vision(CYN "$N" CYN "一臉怒容對$n" CYN "道：我不是讓"
                                               "你把包裹送給" NOR + HIR + q["name"] + "(" + q["id"] +
                                               ")" + NOR + CYN "的嗎？現在回執呢？\n" NOR,
                                               me, who);
                                break;
                        case "rescue": // 救人
                                message_vision(CYN "$N" CYN "一臉怒容對$n" CYN "道：我不是讓"
                                               "你去把" NOR + HIR + q["name"] + "(" + q["id"] +
                                               ")" + NOR + CYN "解救出來嗎？他的信物呢？\n" NOR,
                                               me, who);
                                break;

                        case "kill":   // 殺人
                                message_vision(CYN "$N" CYN "一臉怒容對$n" CYN "道：我不是讓"
                                               "你去查掀起江湖腥風血雨的幕後主謀了嗎？現在他"
                                               "的人頭呢？\n" NOR, me, who);
                                break;

                        }
                        return 1;
                }

                if( query("combat_exp", who)<20000000 )
                {
                        message_vision(CYN "$N" CYN "嘆了一口氣，對$n" CYN "道：就你那點水平，"
                                       "我實在沒法給你派任務。\n" NOR, me, who);
                        return 1;
                }

                if( query("score", who)<200000 )
                {
                        message_vision(CYN "$N" CYN "嘆了一口氣，對$n" CYN "道：你這人閱歷太低，"
                                       "不通世道，幫不了我什麼忙。\n" NOR, me, who);
                        return 1;
                }

                if( query("weiwang", who)<200 )
                {
                        message_sort(CYN "$N" CYN "看了看$n" CYN "，嘆氣道：你在"
                                     "江湖上一點名頭都沒有，我沒法放心把任務交給"
                                     "你。\n" NOR, me, who);
                        tell_object(who, HIY "看來還是的加強自己的江湖威望才行。\n" NOR);
                        return 1;
                }
                /*
                if (who->is_bad() && me->is_good())
                {
                        message_sort(CYN "$N" CYN "大怒道：豈有此理！你居然已經誤"
                                     "入歧途，還敢來見我！\n" NOR, me, who);
                        return 1;
                }

                if (who->is_good() && me->is_bad())
                {
                        message_sort(CYN "$N" CYN "大怒道：豈有此理！才幾天不見，"
                                     "你居然也學起假仁假義來了，快給我滾！\n"
                                     NOR, me, who);
                        return 1;
                }
                */

                // 以下原先設計四種任務類型尋物救人等，現縮減為一種任務。
                switch (random(4))
                {
                case 0:
                        type = "kill";
                        message_sort(CYN "$N" CYN "凝視了$n" CYN "許久，方才點頭道：現在江"
                                     "湖正義不伸，邪道橫行，腥風血雨不斷，聽說這一切都是有"
                                     "人在操縱，你給我去查出這個主謀是誰，提他的頭顱來見我"
                                     "。\n" NOR, me, who);
                        break;
                case 1:
                        type = "kill";
                        message_sort(CYN "$N" CYN "對$n" CYN "道：最近江湖即將發生重大變故"
                                     "，即時將會腥風血雨，這背後肯定有人操縱，你給我去查出"
                                     "幕後主謀，提他的頭顱來見我。\n" NOR, me, who);
                        break;
                case 2:
                        type = "kill";
                        message_sort(CYN "$N" CYN "對$n" CYN "道：聽說有一股勢力正在策劃在"
                                     "江湖上掀起腥風血雨，妄圖顛覆武林，你給我去查出幕後主"
                                     "謀是誰，提他的人頭來見我。\n" NOR, me, who);

                        break;
                case 3:
                        type = "kill";
                        message_sort(CYN "$N" CYN "對$n" CYN "道：最近江湖掀起腥風血雨，我"
                                     "懷疑背後一定有主謀，你去給我查出背後主謀是誰，提他的"
                                     "頭顱來見我。\n" NOR, me, who);
                        break;
                }

                set("ultraquest/type", type, who);
                // 執行提供線索的程序，必須預先設定提供者
                set("ultraquest/id",query("id",  me), who);
                set("ultraquest/name",query("name",  me), who);

                generate_information(me, who);
                return 1;
        }

        if (topic == "線索" || topic == "clue")
        {
                if( !query("ultraquest/type", who) )
                        return "你要問什麼事？說話不明不白的。";

                if( query("ultraquest/finish", who) == 5 )
                        return "任務不是已經快完成了嗎？還需要什麼線索。";

                // 最多只能重新提供三次線索
                if( query("ultraquest/ask", who) >= 3 )
                        return "事不過三，剩下的事情你自己想辦法解決。\n"
                               "或者，你可以去找找北醜，他也許能幫你。";

                switch(query("ultraquest/ask", who) )
                {
                case 0:
                        msg = "你這次是第一次，希望不會再有下回。";
                        break;

                case 1:
                        msg = "我已經幫過你一次了，這次是第二次。";
                        break;

                default:
                        msg = "這已經是最後一次了，望君好自為之。";
                        break;
                }

                message_sort(WHT "\n$N" WHT "皺了皺眉，對$n" WHT "道：我所交給你的"
                             "任務其實是一個歷練的過程，很多地方必須經過磨練，憑借"
                             "自身的睿智與勇氣才能辦到。在這個過程中我最多可以幫你"
                             "三次。" + msg + "\n\n" NOR, me, who);

                // 取消以前的任務屬性
                delete("ultraquest/quest", who);//分支任務
                delete("ultraquest/gift", who);//分支任務獎勵
                delete("ultraquest/finish", who);//分支任務完成數
                delete("ultraquest/fail", who);//分支任務失敗的記錄
                delete("ultraquest/place", who);//提供線索人物的地點

                // 記錄重新詢問的次數
                addn("ultraquest/ask", 1, who);

                // 記錄提供線索的人物名稱
                set("ultraquest/id",query("id",  me), who);
                set("ultraquest/name",query("name",  me), who);

                // 重新提供線索
                generate_information(me, who);
                return 1;
        }

        if (topic == "取消" || topic == "cancel")
        {
                /*
                if( !query("ultraquest/type", who) )
                        return "我沒給你什麼任務啊？";
                */

                addn("weiwang", -50, who);
                if( query("weiwang", who)<0 )
                        set("weiwang", 0, who);

                addn("score", -100, who);
                if( query("score", who)<0 )
                        set("score", 0, who);

                delete("ultraquest", who);
                delete("ultra_count", who);
                message_vision(CYN "$N" CYN "嘆口氣，看了看$n" CYN "道：連這點小事都幹不了？算了吧。\n" NOR,
                               me, who);
                tell_object(who, HIR "你的江湖威望和江湖閱歷受到了損失。\n" NOR);
                return 1;
        }

}

// 詢問線索人物，需要在 /inherit/char/npc.c 增加對應程序
public mixed ask_information(object me, object who, string topic)
{
        string msg;
        string type, ob;

        if( stringp(type=query("ultraquest/quest/type", who)) &&
            stringp(ob=query("ultraquest/quest/name", who)) &&
            topic == ob)
        {
                // 提供任務人物對所提供出的任務信息的解答
                switch (type)
                {
                        case "kill" :
                                msg = "那賊廝鳥，我…我恨不得把他碎屍萬斷！";
                                break;

                        case "find" :
                                msg = "說起來那東西也不難找，你自己多留意吧。";
                                break;

                        case "send" :
                                msg = "其實那人我也不是很熟，你四處去問問吧。";
                                break;

                        case "give" :
                                msg = "我很久沒見到他了，也不清楚他現在怎樣。";
                                break;

                        case "going" :
                                msg = "我給你說得很清楚了啊，莫非你也不識路？";
                                break;
                }
                return msg;
        }

        if (topic == "線索" || topic == "clue")
        {
                // 如果以前的任務無法執行，則中斷
                if( query("ultraquest/fail", who) )
                        return "事情到了這一步，我也沒法再幫你了。";

                // 如果已經給予了任務，則返回
                if( query("ultraquest/quest/msg", who) )
                        return "我不是讓你" +
                               query("ultraquest/quest/msg", who)+
                               "嗎？還羅嗦什麼？";

                switch (random(4))
                {
                case 0:
                        msg = "你要找的線索，我確實知道一些，不過"
                              "首先得幫我個忙。";
                        break;

                case 1:
                        msg = "我這裡確實多多少少知道點眉目，不過"
                              "消息可不能白給。";
                        break;

                case 2:
                        msg = "我正為一件事發愁，如果你能幫我這個"
                              "忙，或許可以告訴你。";
                        break;

                default:
                        msg = "我自己的事情都忙不過來，哪裡還顧得"
                              "了你，不過…除非…";
                        break;
                }
                message_vision(CYN "$N" CYN "搖頭道：" + msg + "\n"
                               NOR, me, who);

                // 如果條件符合要求，執行技術需求的任務
                if( query("combat_exp", me) >= 100000
                     && query("age", me) >= 20
                     && !query_temp("need_accede", me )
                    && random(3) == 1)
                {
                        me->stop_move(); // 停止移動位置
                        give_accede(me, who);
                        return 1;
                }

                // 如果條件符合要求，執行保護或護送任務
                if( query("combat_exp", who)>query("combat_exp", me)*2/3
                     && !query("no_fight", environment(who) )
                     && !query_temp("start_guard", me )
                    && random(3) == 1)
                {
                        /*
                        if (random(2) == 1)
                        {
                                // 停止移動位置
                                me->stop_move();
                                // 執行護送的任務
                                quest_going(me, who);
                                return 1;
                        } else
                        {
                        */
                                // 停止移動位置
                                me->stop_move();
                                // 執行保護的任務
                                quest_guard(me, who);
                                return 1;
                        /*
                        }
                        */
                }

                // 給予系統預設任務
                give_quest(me, who);
                me->stop_move(); // 停止移動位置
                return 1;
        }
}

// 技術性任務的發布
public void give_accede(object me, object who)
{
        string msg, type, quest_msg;
        string skill;
        string ma, mb, wa, ac;
        int exp, lvl;

        // 把人稱及常用字符串作簡寫調用
        ma = RANK_D->query_self(me);
        mb = RANK_D->query_self_rude(me);
        wa = RANK_D->query_respect(who);
        ac = "(" HIY "accede" NOR + WHT ")";

        switch (random(6))
        {
        case 0:
                msg = random(2) ? "這位" + wa + "，" + ma + "近年來研究"
                                  HIW "算術" NOR + WHT "易經，頗有心得。"
                                  "你我二人便來比試" + ac + "一盤，倘若"
                                  "你能勝過我。那麼" + ma + "所知道的線"
                                  "索則無條件奉告":

                                  wa + "來得正好，" + mb + "正愁沒事做。"
                                  "來來來，你陪我比試" + ac + "一盤" HIW
                                  "算術" NOR + WHT "，倘若你能勝過我手中"
                                  "的竹簽與算盤，我把我知道的一切都告訴你";

                quest_msg = "跟我比試算術";
                type = "mathematics";
                break;

        case 1:
                msg = random(2) ? "這位" + wa + "，" + ma + "近年來研究"
                                  HIW "詩詞" NOR + WHT "歌賦，感觸頗深。"
                                  "你我二人便來吟詩" + ac + "作對，倘若"
                                  "你能對贏" + ma + "。那麼我所知道的線"
                                  "索則無條件奉告":

                                  "我看" + wa + "也無甚要事，既然你我二"
                                  "人都窮極無聊，不如來吟詩" + ac + "作"
                                  "對，共同探討探討" HIW "文學" NOR + WHT
                                  "知識。倘若你真能勝我，" + ma + "即將"
                                  "線索告之";

                quest_msg = "跟我吟詩對對";
                type = "literate";
                break;

        case 2:
                msg = random(2) ? "這位" + wa + "，" + ma + "近年來研究"
                                  HIW "弈棋" NOR + WHT "之道，頗有心得。"
                                  "你我二人便來對弈" + ac + "一局，倘若"
                                  "你能勝過我。那麼我所知道的線索則無條"
                                  "件奉告":

                                  wa + "你過來，我看你也沒甚要緊事做。幹"
                                  "脆來陪我殺" + ac + "一局" HIW "棋" NOR +
                                  WHT "，省得無聊。倘若你真能勝我幾子，我"
                                  "便把知道的全都告訴你也無妨";

                quest_msg = "陪我下一局棋";
                type = "chess";
                break;

        case 3:
                msg = random(2) ? "這位" + wa + "來得正好，" + ma + "正為"
                                  "一事發愁。今趟是我朋友的大壽，" + ma +
                                  "打算送他一幅對聯以表祝賀，可怎奈" HIW
                                  "書法" NOR + WHT "功夫欠佳，倘若你能幫" +
                                  ac + "我達成這個心願…" + ma + "感激不"
                                  "盡，線索也當無條件奉告":

                                  wa + "來得正是時候，" + ma + "正為一事"
                                  "發愁。唉…說起來…前日我一位摯友為姦賊"
                                  "所害，不幸慘死。今趟" + ma + "打算尋求"
                                  "一位" HIW "書法" NOR + WHT "名家為其書"
                                  "寫悼詞，卻不知" + wa + "能否幫" + ac +
                                  ma + "達成這個心願";

                quest_msg = "幫我寫一幅字";
                type = "calligraphy";
                break;

        case 4:
                msg = random(2) ? "這位" + wa + "來得正好，" + ma + "正為"
                                  "一事發愁。前日我朋友喜得貴子，" + ma +
                                  "打算送他一幅喜圖以表祝賀，可怎奈" HIW
                                  "丹青" NOR + WHT "造詣太差，倘若你能幫" +
                                  ac + "我達成這個心願…" + ma + "感激不"
                                  "盡，線索也當無條件奉告":

                                  "這個…" + ma + "有個不情之請，還請" + wa +
                                  "幫忙" + ac + "達成。" + ma + "有個多年"
                                  "不見的知己，乃是位" HIW "丹青" NOR + WHT
                                  "名手，今趟去拜訪…卻不知該如何備禮。倘"
                                  "若" + wa + "有此之長，能夠投其所好，當"
                                  "真感激不盡";

                quest_msg = "幫我畫一幅畫";
                type = "drawing";
                break;

        default:
                msg = random(2) ? "嗯…" + wa + "你過來，昨日" + ma + "跟"
                                  "人動手，不小心傷了筋骨，今日本想醫治…"
                                  "可怎奈附近找不到一位" HIW "醫術" NOR +
                                  WHT "好點的大夫，若你能幫忙" + ac + "治"
                                  "好此傷，" + ma + "感激不盡，線索也當無"
                                  "條件奉告":

                                  "不瞞你講，" + wa + "，前幾日" + ma +
                                  "與人過招，不慎受了點內傷，至盡尚未痊癒"
                                  "。唉…這病痛之苦委實難熬，倘若閣下通曉"
                                  HIW "醫理" NOR + WHT "，能夠減輕" + ac +
                                  ma + "病痛的話，" + ma + "當把知道的一切"
                                  "全部告之";

                quest_msg = "幫我醫治病痛";
                type = "medical";
                break;
        }

        // 提供出任務的描述信息
        msg = WHT "\n" + me->name() + WHT "沉思片刻，對你"
              "說道：" + msg + "。\n\n" NOR;

        message("vision", me->name() + "在" + who->name() +
                "耳邊小聲說了些什麼。\n",
                environment(who), ({ who }));

        tell_object(who, sort_msg(msg));

        // 技能要求的種類
        skill = type;

        // 為什麼乘十？是為了目標最大經驗等級的計算
        exp=query("combat_exp", me)*10;

        // 如果該人物有該項技能，則直接調用
        // 如果沒有，則取最大經驗支持等級作削減
        if (me->query_skill(skill))
                lvl = me->query_skill(skill, 1);
        else
                lvl = pow(exp, 1.0 / 3) - 50;

        // 等級太低則提高
        if (lvl < 80) lvl = 80;

        // 等級太高則削弱
        if (lvl > 300) lvl = 300;

        /*
        tell_object(who, HIC "【測試信息】" NOR + WHT + me->name() +
                         HIW " 經驗：" HIC + exp / 10 +
                         HIW " 類別：" HIC + to_chinese(skill) +
                         HIW " 等級：" HIC + lvl + "\n\n" NOR);
        */

        // 注冊任務屬性
        set("ultraquest/quest/type", type, who);
        set("ultraquest/quest/name",query("name",  me), who);
        set("ultraquest/quest/id",query("id",  me), who);
        set("ultraquest/quest/msg", quest_msg, who);

        // 人物注冊接受玩家
        set_temp("need_accede/user",query("id",  who), me);
        set_temp("need_accede/lvl", lvl, me);

        return;
}

// 系統預設任務的發布
public void give_quest(object me, object who)
{
        string quest, next_id, msg, id;
        string type, next_name, quest_msg, name, place;
        object item, ob;
        /*
        string *lines, file;
        string quest;
        object obj;

        // 根據系統預設的任務名單給出任務
        file = read_file(QUEST + "quest");
        file = replace_string(file, " ", "");
        lines = explode(file, "\n");

        quest = lines[random(sizeof(lines))];

        if (sscanf(quest, "%s/%s", type, obj) != 2)
                return;

        type = replace_string(type, "\r", "");
        type = replace_string(type, "\n", "");
        type = replace_string(type, " ", "");
        obj = replace_string(obj, "\r", "");
        obj = replace_string(obj, "\n", "");
        obj = replace_string(obj, " ", "");
        */

        id=query("ultraquest/id", who);
        name=query("ultraquest/name", who);

        // 沒有提供線索的人
        if (! id) return;

        //switch (type)
        switch (random(3))
        {
        case 0 :
                type = "kill";
                ob = new(CLASS_D("generate") + "/killer.c");
                NPC_D->place_npc(ob, ({ "大理一帶", "終南山", "關外", "長安城", "杭州城" }));
                NPC_D->set_from_me(ob, who, 120);
                addn_temp("apply/attack", ob->query_skill("force")*1/2, ob);
                addn_temp("apply/dodge", ob->query_skill("force")*1/2, ob);
                addn_temp("apply/parry", ob->query_skill("force")*1/2, ob);
                addn_temp("apply/damage", 500, ob);
                addn_temp("apply/unarmed_damage", 500, ob);
                addn_temp("apply/armor", 500, ob);
                set_temp("quester",query("id",  who), ob);

                NPC_D->random_move(ob);
                NPC_D->random_move(ob);

                next_id=query("id", ob);
                next_name=query("name", ob);
                place=query("place", ob);

                msg = random(2) ? "你幫我殺了" HIR + next_name + "(" + next_id + ")" + NOR +
                                  WHT "那廝，再提他的頭來見我。\n聽說他最近在" + place + "，你快去吧！":

                                  "你去把" HIR + next_name + "(" + next_id + ")" + NOR + WHT
                                  "給我做了，提他項上的頭來見我。\n聽說他最近在" + place + "，你快去吧！";

                quest_msg = "幫我殺了" + next_name + "(" + next_id + ")";
                break;
        /*
        case 1 :
                type = "find";
                msg = random(2) ? "我現在正急需" + next_name + "(" + next_id + ")" + NOR +
                                  WHT "，只好勞煩勞煩閣下了":

                                  "倘若你能幫我找到" + next_name + "(" + next_id + ")" + NOR
                                  + WHT "，或許我可以提供些線索";

                quest_msg = "幫我找到" + next_name + "(" + next_id + ")";
                break;
        */
        case 1 :
                type = "send";
                ob = new(CLASS_D("generate") + "/uq_receiver.c");
                NPC_D->place_npc(ob, ({ "大理一帶", "終南山", "關外", "長安城", "杭州城" }));
                NPC_D->set_from_me(ob, who, 100);

                NPC_D->random_move(ob);

                next_id=query("id", ob);
                next_name=query("name", ob);
                place=query("place", ob);

                msg = random(2) ? "你幫我把這封信送到" HIY + next_name + "(" + next_id + ")"
                                  + NOR + WHT "手中，然後拿" HIW
                                  "回執" NOR + WHT "來見我。\n聽說他最近在" + place + "，你快去吧！":

                                  "我有封信要立刻送到" HIY + next_name + "(" + next_id + ")"
                                  + NOR + WHT "處，這件事你幫我"
                                  "辦辦吧。\n聽說他最近在" + place + "，你快去吧！";

                quest_msg = "幫我把信送到" + next_name + "(" + next_id + ")" + "處";
                item = new("/clone/misc/letter");
                break;

        case 2 :
                type = "give";
                ob = new(CLASS_D("generate") + "/uq_receiver.c");
                NPC_D->place_npc(ob, ({ "大理一帶", "終南山", "關外", "長安城", "杭州城" }));
                NPC_D->set_from_me(ob, who, 100);

                NPC_D->random_move(ob);

                next_id=query("id", ob);
                next_name=query("name", ob);
                place=query("place", ob);

                msg = random(2) ? "你幫我把這個包裹送到" HIY +
                                  next_name + "(" + next_id + ")" + NOR + WHT "那裡，看看他"
                                  "有什麼反應。\n聽說他最近在" + place + "，你快去吧！":

                                  "勞煩將此包裹轉交給" HIY + next_name + "(" + next_id + ")"
                                  + NOR + WHT "，中途切莫私自打"
                                  "開。\n聽說他最近在" + place + "，你快去吧！";

                quest_msg = "幫我把包裹轉交給" + next_name + "(" + next_id + ")";
                item = new("/clone/misc/baoguo");
                break;
        }

        // 提供出線索信息
        message("vision", me->name() + "悄悄在" + who->name() + "耳"
                          "邊說了些什麼。\n", environment(who),
                          ({ me, who }));

        tell_object(who, WHT + me->name() + WHT "悄悄對你說道：" +
                        msg + "。\n" NOR);

        // 注冊任務屬性
        set("ultraquest/quest/type", type, who);
        //set("ultra_quest/quest/obj", obj, me);
        set("ultraquest/quest/name", next_name, who);
        set("ultraquest/quest/id", next_id, who);
        set("ultraquest/quest/msg", quest_msg, who);

        // 如果存在任務道具，則注冊物件屬性
        if (objectp(item))
        {
                set("send/from", name, item);
                set("send/send", next_name, item);
                set("send/user", who->name(), item);
                set("long",WHT"這是一"+query("unit", item)+
                                  name + "準備轉交給" + next_name + "的" +
                                  item->name() + "。\n" NOR, item);

                // 提供出物件轉移的信息
                message_vision("$N"NOR"拿出一"+query("unit", item)+
                               item->name()+NOR"("+query("id", item)+
                               ")給$n" NOR "。\n" NOR, me, who);
                item->move(who, 1);
        }
        return;
}

// 保護任務的發布
public void quest_guard(object me, object who)
{
        string msg;

        message("vision", me->name() + "在" + who->name() +
                          "耳邊小聲說了些什麼。\n",
                          environment(who), ({ who }));

        switch (random(3))
        {
        case 0:
                msg = "我的仇家今日要殺上門來";
                break;

        case 1:
                msg = "昨日有個家伙放言要做了我";
                break;

        default:
                msg = "我聽說有人準備對我不利";
                break;
        }

        tell_object(who, WHT + me->name() + WHT "悄悄對你"
                         "說道：" + msg + "，你" HIW "留在"
                         "這裡" NOR + WHT "保護我一下。\n" NOR);

        // 為了防止任務沖突，目標設置被保護屬性
        set_temp("start_guard", 1, me);

        // 注冊保護任務屬性
        set("ultraquest/quest/type", "guard", who);
        set("ultraquest/quest/name",query("name",  me), who);
        set("ultraquest/quest/id",query("id",  me), who);
        set("ultraquest/quest/msg", "留在這裡保護我", who);
        who->start_call_out((: call_other, __FILE__, "start_guard",
                            me, who :), 5);
        return;
}

// 護送任務的發布
public void quest_going(object me, object who)
{
        string *lines;
        string file;
        string where, area, place;

        // 調用系統預設的地點名稱
        file = read_file(QUEST + "place");
        lines = explode(file, "\n");
        where = lines[random(sizeof(lines))];

        if (sscanf(where, "%s/%s", area, place) != 2)
                return;

        // 如果系統調用的地名與起始地重復，則直接執行
        // 系統預設的任務程序

        if( place == query("short", environment(me)) )
        {
                generate_information(me, who);
                return;
        }

        message("vision", me->name() + "在" + who->name() +
                          "耳邊小聲說了些什麼。\n",
                          environment(who), ({ who }));

        tell_object(who, WHT + me->name() + WHT "悄悄對你"
                         "說道：我現在有點事要到" + HIW +
                         area + NOR + WHT "的" HIW + place +
                         NOR + WHT "處理，勞駕你送我過去。"
                         "\n" NOR);

        // 目標開始跟隨行動
        me->set_leader(who);
        message_vision("$N決定開始跟隨$n一起行動。\n", me, who);

        // 為了防止任務沖突，目標設置被保護屬性
        set_temp("start_guard", 1, me);

        // 注冊護送任務屬性
        set("ultraquest/quest/type", "going", who);
        set("ultraquest/quest/obj", place, who);
        set("ultraquest/quest/name",query("name",  me), who);
        set("ultraquest/quest/msg", "送我到"+area+"的"+place, who);

        // 開始定時掃描所到達的地點
        who->start_call_out((: call_other, __FILE__, "check_going",
                            me, who :), 1);
        return;
}

// 執行保護任務的程序
void start_guard(object me, object who)
{
        object killer;

        if (! objectp(me) || ! objectp(who)
            || environment(me) != environment(who))
                return;

        if (random(5) == 1)
        {
                message_vision(CYN "\n$N" CYN "撓了撓頭，頗為"
                               "尷尬的說道：咦？難道傳聞有錯？"
                               "\n" NOR, me);

                if (random(3) == 1)
                {
                        message_vision(CYN "$N" CYN "幹笑了兩"
                                       "聲，對$n" CYN "道：看"
                                       "樣子沒人來了，你也算辛"
                                       "苦了一場，我就告訴你吧"
                                       "。\n" NOR, me, who);

                        // 目標取消被保護的屬性
                        delete_temp("start_guard", me);

                        // 任務完成，注冊獎勵屬性
                        // set("ultraquest/name1", me->name(), who);
                        set("ultraquest/gift/point", 120, who);
                        set("ultraquest/gift/msg","你通過保護"+
                                 query("ultraquest/quest/name", who)+"的過程", who);

                        // 系統給予該次任務的獎勵
                        give_gift(me, who);
                } else
                {
                        message_vision(CYN "$N" CYN "嘆了口氣"
                                       "，對$n" CYN "道：看樣"
                                       "子沒人來了，我還是重新"
                                       "給你個事情做做吧。\n"
                                       NOR, me, who);

                        // 目標取消被保護的屬性
                        delete_temp("start_guard", me);

                        // 任務中斷，系統重新分配的任務
                        give_quest(me, who);
                }
                return;
        }
        message_vision(CYN "\n突然間$N" CYN "對$n" CYN "顫聲說道"
                       "：來了，殺我的人來了。\n\n" NOR, me, who);

        killer = new(CLASS_D("generate") + "/killer");
        NPC_D->set_from_me(killer, who, 120);
        killer->move(environment(me));

        message_vision(HIW "$n" HIW "走了過來，對$N" HIW "獰笑"
                       "道：原來你躲在這裡，受死吧！\n" NOR, me,
                       killer);

        killer->set_leader(me);
        killer->kill_ob(me);

        // 檢查保護狀態
        who->start_call_out((: call_other, __FILE__, "check_guard",
                             me, who, killer :), 3);
}

// 檢查被保護任務的狀態
void check_guard(object me, object who, object killer)
{
        if (! objectp(me) && ! objectp(killer))
                return;

        // 正在戰鬥？則延遲檢查
        if (objectp(killer) && objectp(me)
            && (me->is_fighting(killer)
            || who->is_fighting(killer)))
        {
                who->start_call_out((: call_other, __FILE__, "check_guard",
                                    me, who, killer :), 1);
                return;
        }

        // 被保護的人消失，任務中斷
        if (! objectp(me)
            && objectp(killer))
        {
                tell_object(who,HIG"你眼見"+query("ultraquest/quest/name", who)+
                                 HIG "被殺，心中連連叫糟。\n" NOR);

                // 記錄下失敗記錄
                set("ultraquest/fail", 1, who);
                return;
        }

        // 殺手消失且被保護人存在，任務結束
        if (! objectp(killer)
            && objectp(me))
        {
                // 如果被保護人昏迷，則先轉醒
                if (! living(me))
                        me->revive();

                message_vision(CYN "$N" CYN "擦了擦汗，對$n" CYN "道：天幸"
                               "今天有你幫忙，感激不盡。\n$N" CYN "接著道："
                               "救命之恩難以回報，我一定把我知道的都告訴你"
                               "。\n" NOR, me, who);

                // 目標取消被保護的屬性
                delete_temp("start_guard", me);

                // 任務完成，注冊獎勵屬性
                // set("ultraquest/name1", me->name(), who);
                set("ultraquest/gift/point", 250, who);
                set("ultraquest/gift/msg","你通過保護"+
                        query("ultraquest/quest/name", who)+"的過程", who);

                // 系統給予該次任務的獎勵
                give_gift(me, who);
                return;
        }
        message_vision(CYN "$N" CYN "看了看四周，大叫道：巫"
                       "師！BUG，BUG！\n" NOR, who);
        return;
}

// 檢查護送任務的狀態
void check_going(object me, object who)
{
        string msg, place;

        // 若任務已經失敗，則取消掉屬性並且中斷任務
        if( query("ultraquest/fail", who) )
        {
                delete_temp("dest_npc", who);
                destruct(me); // 銷毀線索人物
                return;
        }

        // 特殊情況下護送的人物跟丟了，執行以下程序
        if (! objectp(me) || ! objectp(who)) return;

        // 調用出護送的目的地
        place=query("ultraquest/quest/obj", who);

        if (environment(me) != environment(who))
        {
                switch(query_temp("dest_npc", who) )
                {
                case 0:
                        msg = "你回頭張望間，卻發現那" + me->name()
                              + "竟不知何時不見了蹤影。\n你心中暗道"
                              "：可千萬別讓線索斷掉了，得趕緊將他找"
                              "回來。";
                        break;

                case 1:
                        msg = "你心中頗為焦急：咦？" + me->name()
                              + "那家伙到底上哪去了。";
                        break;

                case 2:
                        msg = "你心底直罵：什麼時候了，那該死的" +
                              me->name() + "怎麼還不滾出來。";
                        break;

                default:
                        msg = "你心中連連嘆息：唉…到底還是把人給"
                              "跟丟了。這線索…唉…";

                        // 記錄下失敗記錄
                        set("ultraquest/fail", 1, who);
                        break;
                }

                // 設置人物丟失的時間段，超過三則任務中斷
                addn_temp("dest_npc", 1, who);

                // 等一個時間段再重新做掃描
                who->start_call_out((: call_other, __FILE__, "check_going",
                                    me, who :), 5);

                tell_object(who, HIG "\n" + msg + "\n\n" NOR);
                return;
        }

        // 清除等候護送人物的時間段
        if( query_temp("dest_npc", who) )
                delete_temp("dest_npc", who);


        // 查看當前位置，如為目的地，則任務完成
        if( query("short", environment(me)) == query("ultraquest/quest/obj", who) )
        {
                // 如果被保護人昏迷，則先轉醒
                if (! living(me))
                        me->revive();

                message_vision(CYN "$N" CYN "擦了擦汗，對$n" CYN "道：謝謝"
                               "你將我送到" + place + "，路上真是麻煩你了。"
                               "\n$N" CYN "接著道：看在你這番辛苦的份上，我"
                               "就告訴你一些線索吧。\n" NOR, me, who);

                // 目標取消被保護的屬性
                delete_temp("start_guard", me);

                // 目標不再跟隨
                me->set_leader(0);

                // 任務完成，注冊獎勵屬性
                // set("ultraquest/name1", me->name(), who);
                set("ultraquest/gift/point", 220, who);
                set("ultraquest/gift/msg","你通過護送"+
                                                 query("ultraquest/quest/name", who)+"抵達"+
                                                 place + "的過程", who);

                // 系統給予該次任務的獎勵
                give_gift(me, who);
                return;
        } else
        {
                string last_place;

                // 隨機事件使經驗較低的護送目標停留
                if( stringp(last_place=query_temp("last_place", me) )
                     && last_place != query("short", environment(me) )
                    && ! me->is_busy()
                     && query("combat_exp", me)<2000000
                    && random(50) == 1)
                {
                        switch (random(5))
                        {
                        case 0:
                                msg = "突然間$N" HIW "跑得急了，一個筋鬥"
                                      "栽到路邊，咿咿呀呀叫個不停。";
                                break;

                        case 1:
                                msg = "只聽$N" HIW "喘息道：" + who->name()
                                      + HIW "，走慢點…走慢…累死我了。";
                                break;

                        case 2:
                                msg = "$N" HIW "「咦」了一聲，似乎發現了"
                                      "什麼新鮮事物，腳步頓時緩了下來。";
                                break;

                        case 3:
                                msg = "$N" HIW "忽然臉色慘白，道：" +
                                      who->name() + HIW "，勞煩停…停一"
                                      "會，我走岔氣了。";
                                break;

                        default:
                                msg = "卻見$N" HIW "不留神間，踢到了路邊"
                                      "凸起的一塊大石，直痛得躬下腰去。";
                                break;
                        }
                        message_vision(HIW "\n" + msg + "\n\n" NOR, me, who);
                        me->start_busy(2 + random(2));
                }

                // 設定上一次所到達的地點，如果與當前地點不同，則
                // 執行上面的隨機停留的程序
                set_temp("last_place",query("short",  environment(me)), me);

                // 未到達目的地，定時重新做掃描
                who->start_call_out((: call_other, __FILE__, "check_going",
                                    me, who :), 1);
                return;
        }
        return;
}

// 針對任務人物提出的技術性任務給予答復
int need_accede(object me, object who)
{
        string skill, ma, wa;
        string suc_msg, fai_msg, msg;
        int lvl;

        // 準備比較的技能屬性
        skill=query("ultraquest/quest/type", who);
       lvl=query_temp("need_accede/lvl", me);

        // 把人稱做簡單化
        ma = RANK_D->query_self(me);
        wa = RANK_D->query_respect(who);

        switch (skill)
        {
        case "mathematics" :
                suc_msg = me->name() + "點了點頭，隨即蹲下身來，在地面畫"
                          "了些橫直符號與圓圈接著又寫下「太、天元、地元、"
                          "人元、物元」等字。你在一旁默默細觀，掐指間便已"
                          "將幾道算題的答案算出，隨口告之" + me->name() +
                          "。" + me->name() + "聽後一驚，嘆道：我原以為…"
                          "唉…罷了，罷了。";

                fai_msg = me->name() + "點了點頭，隨即蹲下身來，在地面畫"
                          "了些橫直符號與圓圈接著又寫下「太、天元、地元、"
                          "人元、物元」等字。你在一旁看得不知所雲，全然不"
                          "知該如何下手。" + me->name() + "等了半天，見你"
                          "毫無動靜，不由得滿意的一笑。";
                break;

        case "literate" :
                suc_msg = me->name() + "點了點頭，清了清嗓子道：我出一個"
                          "上聯，你給我對出下聯。這上聯是「炎黃英雄史」。"
                          "你微微一笑，隨口對道：「網絡傻瓜墓」。" +
                          me->name() + "聽後一震，讚道：絕妙，真乃絕妙。";

                fai_msg = me->name() + "點了點頭，清了清嗓子道：我出一個"
                          "上聯，你給我對出下聯。我這上聯是「泥潭英雄史」"
                          "。你聽後一愣，苦想了半天才道：「暗…暗黑破壞神"
                          "」。" + me->name() + "聽後大怒，罵道：我呸，這"
                          "算什麼對子。你就知道黃對黑麼？";
                break;

        case "chess" :
                suc_msg = "你當即走上前去，與" + me->name() + "擺開棋局"
                          "對弈起來。不過多時，卻見" + me->name() + "已"
                          "是大汗淋漓。緊接著你又落下一子，" + me->name() +
                          "頓時臉色鐵青，頹然道：不下了，不下了。我認輸"
                          "便是。";

                fai_msg = "你當即走上前去，與" + me->name() + "擺開棋局"
                          "對弈起來。不過多時，你已被" + me->name() +
                          "逼得節節敗退，險象橫生。" + me->name() + "見"
                          "你臉色鐵青，大笑道：怎麼？就你這水平，還不認"
                          "輸麼？";
                break;

        case "calligraphy" :
                suc_msg = "你微微一笑，當即走上前去，接過毛筆便開始書寫"
                          "起來。霎時只見你隨意揮洒手中筆墨，騰蛟起鳳，"
                          "洋洋洒洒；字跡宛若行雲流水，當真將書法的意境"
                          "發揮得淋漓盡致。" + me->name() + "在一旁看得"
                          "目瞪口呆，連聲稱讚。";

                fai_msg = "你當即走上前去，接過毛筆飽沾墨水，便開始書寫"
                          "起來。正當你寫到意氣風發之處，抬頭間卻發現" +
                           me->name() + "顏色甚為難看，不由得微微一愣。" +
                           me->name() + "搖了搖頭，失望道：倘若我將這樣的"
                           "字拿出手，豈非惹人恥笑？原本還…唉…";
                break;

        case "drawing" :
                suc_msg = "你微微一笑，當即接過畫筆，隨意揮洒筆墨。但見"
                          "你墨意淋漓，筆力雄健，雖只寥寥數筆，氣勢可著"
                          "實不凡。" + me->name() + "在一旁越看越是心喜"
                          "，連聲稱讚。";

                fai_msg = "你當即走上前去，接過畫筆作起畫來。正當你畫得"
                          "意氣風發之時，抬頭間卻發現" + me->name() + "顏"
                          "色甚為難看，不由得微微一愣。" + me->name() +
                          "搖了搖頭，失望道：算了，算了。就你這水平，還"
                          "沒我自己動手畫妥當。";
                break;

        default:
                suc_msg = "你點了點頭，伸出兩指搭在" + me->name() + "的"
                          "脈上，不出片刻便已發現其病根所在。當下也不耽"
                          "擱，急急配出了藥方。" + me->name() + "見後大"
                          "喜道：天幸今日碰上了" + wa + "，此番恩情真是"
                          "難以回報。";

                fai_msg = "你愣了愣，走上前去給" + me->name() + "搭脈，"
                          "探了半天，卻發現" + me->name() + "脈象異常絮"
                          "亂，遠超自己所識。" + me->name() + "見你愁眉"
                          "不展，不由得長嘆道：唉…我這傷本非一般庸醫能"
                          "治，也不難為你了。";
                break;
        }

        message("vision", "只見" + who->name() + "走上前去，在" +
                          me->name() + "耳邊嘀咕了幾句。\n",
                          environment(who), ({ who }));

        // 注銷掉人物的任務對象屬性
        delete_temp("need_accede", me);

        if (who->query_skill(skill, 1) >= lvl)
        {
                // 提交成功的描述信息
                tell_object(who, sort_msg(WHT + suc_msg + "\n\n" NOR));

                // 任務完成，注冊獎勵屬性
                // set("ultraquest/name1", me->name(), who);
                set("ultraquest/gift/point", 350, who);
                set("ultraquest/gift/msg","你通過此番幫助"+
                                                 me->name() + "的經歷", who);

                if (! who->is_busy())
                        who->start_busy(3);

                // 隨機給予獎勵物品
                if (random(5) == 1)
                {
                        message_vision(CYN "$N" CYN "道：" + wa + "的為人"
                                       "實令" + ma + "折服不已。一點薄禮，"
                                       "不成敬意。\n" NOR, me);

                        set("ultraquest/gift/item", 1, who);
                }

                // 系統給予該次任務的獎勵
                give_gift(me, who);
        } else
        {
                // 提交失敗的描述信息
                tell_object(who, sort_msg(WHT + fai_msg + "\n\n" NOR));

                message_vision(CYN "$N" CYN "搖了搖頭，對$n"
                               CYN "道：也罷，我還是重新交代"
                               "個事情讓你做吧。\n" NOR, me, who);

                // 任務中斷，系統重新分配的任務
                give_quest(me, who);
        }

        return 1;
}

// 接受任務需求的物品
int accept_object(object me, object who, object ob)
{
        string msg;
        string type;
        int ultra_count;
        int exp;                // 獲得的經驗
        int pot;                // 獲得的潛能
        int mar;                // 獲得的實戰體會
        int weiwang;            // 獲得的威望
        int score;              // 獲得的江湖閱歷
        int lvl;                // 人物的等級
        mixed special = 0;      // 是否有特殊獎勵
        object ob1, rob;

        // 如果沒有領取任務
        if( !mapp(query("ultraquest", who)) )
                return 0;

        if( query("name", me) == QUESTER )
        {
                if( query("ultraquest/finish", who) < 5 )
                        return 0;
                
                switch(query("ultraquest/type", who) )
                {
                case "find":
                        if( query("id", ob) != query("ultraquest/id", who) )
                                return 0;

                        message_vision(CYN "$N" CYN "看了看" + ob->name()
                                       + NOR + CYN "，微微的點了點頭。\n" NOR, me);
                        // destruct(ob);
                        break;

                case "give":
                case "rescue":
                        if (! ob->is_receipt())
                                return 0;

                        if( query("reply_to", ob) != query("name", me )
                         || query("reply_by", ob) != query("ultraquest/id", who )
                         || query("receive_from_name", ob) != who->name(1) )
                        {
                                message_vision("$N皺眉道：“給我這玩藝幹什麼？”\n", me);
                                return 0;
                        }

                        message_vision(CYN "$N" CYN "接過" + ob->name() + NOR + CYN
                                       "，仔細看了看，滿意的說：很好。\n" NOR, me);
                        // destruct(ob);
                        break;

                case "kill":
                        if(! ob->is_corpse() && ! ob->is_head())
                                return 0;

                        if( !stringp(query("owner_id", ob)) )
                        {
                                message_vision(CYN "$N" CYN "捂著鼻子看了看" + ob->name()
                                               + NOR + CYN "，道：什麼臭烘烘的？快給我"
                                               "拿走。\n" NOR, me);
                                return 0;
                        }

                        if( query("killed_by", ob) != query("id", who) )
                                return 0;

                        if( query("victim_name", ob) != query("ultraquest/name", who) )
                                return 0;

                        // message_vision(CYN "$N" CYN "看了看" + ob->name()
                        //                + NOR + CYN "，微微的點了點頭。\n" NOR, me);
                        // destruct(ob);
                        break;
                }

                msg = CYN "$N" CYN "接過" + ob->name() + NOR + CYN"，仔細看了"
                      "看，滿意的說：很好。\n" NOR;

                // 這裡要定義完成任務獎勵
                addn("ultra_count", 1, who);

                ultra_count=query("ultra_count", who);

                lvl = NPC_D->check_level(who);
                exp = 6000 + random(1000) + lvl * 10;
                pot = 1200 + random(200) + lvl * 10;
                mar = 120 + random(50);
                weiwang = 20 + random(30);
                score = 20 + random(30);

                // 根據任務完成的次數修正獎勵
                if (ultra_count >= 100)
                {
                        // 連續完成了超過100次的任務
                        exp += 800 + random(ultra_count + 1);
                        pot += 450 + random(ultra_count + 1);
                        mar += 50 + random(20);
                        weiwang += 8 + random(20);
                        score += 4 + random(15);
                } else
                if (ultra_count >= 50)
                {
                        // 連續完成了超過50次的任務
                        exp += 700 + random(ultra_count + 1);
                        pot += 400 + random(ultra_count + 1);
                        mar += 40 + random(10);
                        weiwang += 5 + random(15);
                        score += 3 + random(10);
                } else
                if (ultra_count >= 25)
                {
                        // 連續完成了超過25次的任務
                        exp += 500 + random(ultra_count + 1);
                        pot += 300 + random(ultra_count + 1);
                        mar += 30 + random(5);
                        weiwang += 3 + random(10);
                        score += 2 + random(10);
                } else
                if (ultra_count >= 10)
                {
                        // 連續完成了超過10次的任務
                        exp += 450 + random(ultra_count + 1);
                        pot += 250 + random(ultra_count + 1);
                        weiwang += 1 + random(5);
                        score += 1 + random(5);
                }

                if (ultra_count == 10)
                {
                        msg += CYN "$N" CYN "哈哈大笑兩聲道：“真有你的，連著上十"
                               "次任務都完成的漂漂亮亮，很好，很好。”\n" NOR;
                        special = 1;
                } else
                if (ultra_count == 25)
                {
                        msg += CYN "$N" CYN "大喜道：“不錯不錯，真實不錯，二十五"
                               "次任務幹得很好。”\n NOR";
                        special = "/clone/gift/jiuzhuan";
                } else
                if (ultra_count == 50)
                {
                        msg += CYN "$N" CYN "嘆道：“真是長江後浪推前浪，想不到你接連五十"
                               "次任務都無一疏漏，不易，不易！”\n" NOR;
                        special = "/clone/gift/tianxiang";
                } else
                if (ultra_count >= 100)
                {
                        msg += CYN "$N" CYN "深深嘆了口氣，道：“想不到你連著上百次"
                               "任務無一失手，看來我們泥潭真是後繼有人啊！”\n" NOR;
                        special = "/clone/gift/xuanhuang";
                        ultra_count = 0;
                } else
                if ((ultra_count % 10) == 0)
                {
                        msg += CYN "$N" CYN "喜道：“真是不賴，居然連著" +
                               chinese_number(ultra_count) +
                               "次都沒有失手，幹的好！”\n" NOR ;
                }

                if (stringp(special))
                {
                        ob1 = new(special);
                        ob1->move(who, 1);
                        tell_object(who,HIM"你獲得了一"+query("unit", ob1)+ob1->name()+
                                         HIM "。\n" NOR);
                }

                message_vision(msg, me, who);
                if ((ultra_count >= 10 && random(200) == 1) || special)
                        special_bonus(me, who);

                // 帝王符圖編號15-21
                if( query("quest_tuteng/start", who) )
                {
                        int n_tt;
                        object ob_tt;

                        if (random(3000) == 1)
                        {
                                n_tt = 15 + random(7);
                                ob_tt = new("/clone/tuteng/diwang-suipian" + sprintf("%d", n_tt));
                                if (ob_tt)
                                {
                                        ob_tt->move(who, 1);
                                        tell_object(who, HIG "你獲得了一張帝王符圖碎片。\n" NOR);
                                }
                        }
                }

                set("ultra_count", ultra_count, who);
                delete("ultraquest", who);

                GIFT_D->delay_bonus(who, ([ "exp" : exp*3/2, "pot" : pot, "mar" : mar,
                                            "weiwang" : weiwang, "score" : score ]), 1);
                destruct(ob);
                return 1;
        }

        // 只有殺人、尋物、送信/包裹的任務才執行物品接受
        if( !stringp(type=query("ultraquest/quest/type", who) )
            || (type != "kill" && type != "find"
            && type != "give" && type != "send"))
                return 0;

        // 如果對象為接受信件或包裹的NPC
        if( query("id", me) == query("ultraquest/quest/id", who) )
        {
                switch (type)
                {
                case "send" :
                        if (! ob->is_letter())
                                return 0;

                        if( query("send/send", ob) != me->name() )
                        {
                                message_vision(CYN "$N" CYN "皺眉道：你會認人麼？這"
                                               "封信又不是寫給我的。\n" NOR, me);
                                return 0;
                        }

                        if( query("send/user", ob) != who->name() )
                        {
                                message_vision(CYN "$N" CYN "皺眉道：這信是誰讓你送"
                                               "的？我怎麼不認識。\n" NOR, me);
                                return 0;
                        }

                        message_vision(CYN "$N" CYN "看了看" + ob->name()
                                       + NOR + CYN "，不置可否的點了點頭。\n" NOR, me);

                        rob = new("/clone/misc/receipt");
                        set("reply_by",query("name",  me), rob);
                        set("reply_to",query("send/from",  ob), rob);
                        set("receive_from",query("id",  who), rob);
                        set("long", "這是一封由"+me->name()+"收到的來信寫的回執。\n", rob);
                        rob->move(who, 1);
                        message_vision("$N交給$n一張回執。\n", me, who);
                        destruct(ob);

                        break;

                case "give" :
                        if (! ob->is_bag())
                                return 0;

                        if( query("send/send", ob) != me->name() )
                        {
                                message_vision(CYN "$N" CYN "皺眉道：你會認人麼？這"
                                               "包裹又不是拿給我的。\n" NOR, me);
                                return 0;
                        }

                        if( query("send/user", ob) != who->name() )
                        {
                                message_vision(CYN "$N" CYN "皺眉道：這包裹是誰給你"
                                               "的？還是你自己留著吧。\n" NOR, me);
                                return 0;
                        }

                        message_vision(CYN "$N" CYN "看了看" + ob->name()
                                       + NOR + CYN "，不置可否的點了點頭。\n" NOR, me);
                        rob = new("/clone/misc/receipt");
                        set("reply_by",query("name",  me), rob);
                        set("reply_to",query("send/from",  ob), rob);
                        set("receive_from",query("id",  who), rob);
                        set("long", "這是一封由"+me->name()+"收到的包裹寫的回執。\n", rob);
                        rob->move(who, 1);
                        message_vision("$N交給$n一張回執。\n", me, who);
                        destruct(ob);
                        break;
                }

                me->destruct_me(); // 銷毀接受物品任務NPC
                return 1;
        }

        // 如果對象為發布任務的NPC
        if( query("id", me) == query("ultraquest/id", who) )
        {
                switch (type)
                {
                case "kill":
                        if(! ob->is_corpse() && ! ob->is_head())
                                return 0;

                        if( !stringp(query("owner_id", ob)) )
                        {
                                message_vision(CYN "$N" CYN "捂著鼻子看了看" + ob->name()
                                               + NOR + CYN "，道：什麼臭烘烘的？快給我"
                                               "拿走。\n" NOR, me);
                                return 0;
                        }

                        if( query("killed_by", ob) != query("id", who) )
                                return 0;

                        if( query("victim_name", ob) != query("ultraquest/quest/name", who) )
                                return 0;

                        message_vision(CYN "$N" CYN "看了看" + ob->name()
                                       + NOR + CYN "，不置可否的點了點頭。\n" NOR, me);
                        // destruct(ob);
                        break;

                case "find" :
                        if( query("id", ob) != query("ultraquest/quest/id", who) )
                                return 0;

                        message_vision(CYN "$N" CYN "看了看" + ob->name()
                                       + NOR + CYN "，不置可否的點了點頭。\n" NOR, me);
                        // destruct(ob);
                        break;

                case "send" :
                        if (! ob->is_receipt())  return 0;
                        message_vision(CYN "$N" CYN "看了看" + ob->name()
                                       + NOR + CYN "，不置可否的點了點頭。\n" NOR, me);

                        if (ob->is_receipt())
                        {
                                if( query("reply_to", ob) != query("name", me) )
                                {
                                        message_vision("$N皺眉道：“給我這玩藝幹什麼？”\n", me);
                                        return 0;
                                }

                                if( query("receive_from", ob) != query("id", who) ||
                                    query("reply_by", ob) != query("ultraquest/quest/name", who) )
                                {
                                        message_vision("$N皺眉道：“這是你幫我送的嗎？”\n", me);
                                        return 0;
                                }
                                // destruct(ob);
                        }

                        break;

                case "give" :
                        if (! ob->is_receipt())  return 0;
                        message_vision(CYN "$N" CYN "看了看" + ob->name()
                                       + NOR + CYN "，不置可否的點了點頭。\n" NOR, me);
                        if (ob->is_receipt())
                        {
                                if( query("reply_to", ob) != query("name", me) )
                                {
                                        message_vision("$N皺眉道：“給我這玩藝幹什麼？”\n", me);
                                        return 0;
                                }

                                if( query("receive_from", ob) != query("id", who) ||
                                    query("reply_by", ob) != query("ultraquest/quest/name", who) )
                                {
                                        message_vision("$N皺眉道：“這是你幫我送的嗎？”\n", me);
                                        return 0;
                                }
                                // destruct(ob);
                        }
                        break;
                }

                destruct(ob);
                set("ultraquest/gift/point", 600, who);
                set("ultraquest/gift/msg","你通過此番幫助"+
                                                 me->name() + "的經歷", who);
                give_gift(me, who);

                return 1;
        }
}

// 完成任務的獎勵
public void give_gift(object me, object who)
{
        int gift;

        // 如果沒有注冊獎勵參數，則中斷
        if( !query("ultraquest/gift/msg", who )
                 || !query("ultraquest/gift/point", who) )
                return;

        // 設置連續完成的數量
        addn("ultraquest/finish", 1, who);

        // 給予物品獎勵
        if( query("ultraquest/gift/item", who) )
                special_bonus(me, who);

        // 獎勵的底數
        gift=query("ultraquest/gift/point", who)+
                query("ultraquest/finish", who);

        GIFT_D->delay_bonus(who,(["prompt":query("ultraquest/gift/msg", who),
                                         "exp"     : gift,
                                         "pot"     : gift / 5,
                                         "mar"     : gift / 30,
                                         "score"   : gift / 40,
                                         "weiwang" : gift / 50, ]));

        // 取消掉原來的任務屬性
        delete("ultraquest/gift", who);
        delete("ultraquest/quest", who);

        // 提供新的線索，以便任務連貫
        generate_information(me, who);
        return;
}

// 人物所提供的線索信息
public void generate_information(object me, object who)
{
        object ob;
        string where, id, name, place;
        string msg, ma, next_name;
        int finish;

        // 沒有上一個提供線索的人
        if (! objectp(me)) return;

        // 完成了五個線索後載入本次任務的對象
        if( query("ultraquest/finish", who) == 5 )
        {
                switch(query("ultraquest/type", who) )
                {
                case "kill":
                        ob = new(CLASS_D("generate") + "/killer.c");
                        NPC_D->place_npc(ob, ({ "大理一帶", "終南山", "關外", "長安城", "杭州城", "西域" }));
                        NPC_D->set_from_me(ob, me, 150);
                        addn_temp("apply/attack", ob->query_skill("force")*1/2, ob);
                        addn_temp("apply/dodge", ob->query_skill("force")*1/2, ob);
                        addn_temp("apply/parry", ob->query_skill("force")*1/2, ob);
                        addn_temp("apply/damage", 1000, ob);
                        addn_temp("apply/unarmed_damage", 1000, ob);
                        addn_temp("apply/armor", 1000, ob);
                        set_temp("quester",query("id",  who), ob);

                        set("ultraquest/id",query("id",  ob), who);
                        set("ultraquest/name",query("name",  ob), who);

                        NPC_D->random_move(ob);
                        NPC_D->random_move(ob);
                        NPC_D->random_move(ob);

                        place=query("place", ob);

                        tell_object(who, CYN + me->name() + CYN "小聲對你說道："
                                        NOR+HIR+ob->name()+"("+query("id", ob)+")"+NOR+CYN
                                        "就是幕後主人，可千萬不要說是我說。\n聽說他最近在" + place + "，你快去吧！\n" NOR);
                        break;
                case "send":  // 該任務暫時沒有開放
                        break;
                case "rescue":
                        break;
                case "find":
                        break;
                }
                me->destruct_me(); // 銷毀上次線索人物
                return;
        }

        ob = new(CLASS_D("generate") + "/cluenpc.c");
        NPC_D->place_npc(ob, ({ "大理一帶", "終南山", "關外", "長安城", "杭州城" }));
        NPC_D->set_from_me(ob, me, 100);
        addn_temp("apply/attack", ob->query_skill("force")*1/2, ob);
        addn_temp("apply/dodge", ob->query_skill("force")*1/2, ob);
        addn_temp("apply/parry", ob->query_skill("force")*1/2, ob);
        addn_temp("apply/damage", 500, ob);
        addn_temp("apply/unarmed_damage", 500, ob);
        addn_temp("apply/armor", 500, ob);
        set_temp("quester",query("id",  who), ob);

        NPC_D->random_move(ob);

        id=query("id", ob);
        name=query("name", ob);
        place=query("place", ob);

        // 記錄下下一個線索人物及出現地
        set("ultraquest/id", id, who);
        set("ultraquest/name", name, who);
        set("ultraquest/place", place, who);

        // 清除上次的線索信息
        delete("ultraquest/quest", who);

        // 添加醒目的顏色
        next_name = HIY + name + "(" + id + ")" + NOR + WHT;

        // 把人稱做簡單化
        ma = RANK_D->query_respect(me);

        // 這裡增加情節描述
        finish=query("ultraquest/finish", who);
        switch (finish)
        {
        case 1:
                msg = "聽說，這個幕後黑手曾遺失過一個重要物品，通過這個物品可以知"
                      "道他是誰。\n好象" + place + "的" + next_name + "就知道這"
                      "個物品的下落。\n" + ma + "可去找他問問，但也不知是真是假";
                break;

        case 2:
                msg = "那物品我到是聽說點線索，" + ma + "知道" + place + "嗎？\n"
                      "那裡有個" + next_name + "，傳聞你要找的那東西就在他身上";
                break;

        case 3:
                msg = "不知" + ma + "認識" + place + "的" + next_name + "嗎？\n"
                      "你來的真不巧，那個東西我上個月送給他了，你可以找他試試";
                break;

        case 4:
                msg = "很遺憾，你要的東西我前幾天搞丟了，不清楚" + ma + "是否認識"
                      + place + "的" + next_name + "。\n他見過此東西，而且好象知"
                      "道那個物品的主人是誰";
                break;

        default:
                msg = "我想想…" + ma + "去找" + place +
                      "的" + next_name + "問問看吧。\n去年我聽"
                      "他說起過這件事";
                break;
        }

        // 起始任務的主控人物，可以刷新線索
        if (me->name() == QUESTER)
        {
                if( query("ultraquest/ask", who) )
                        msg = "…嗯…你去" + place +
                              "問問" + next_name + "看，他那兒"
                              "似乎又有些線索";
                else
                        msg = "你可以去" + place +
                              "找" + next_name + "打聽打聽，他"
                              "那似乎有些線索";
        }

        // 北醜，只要有錢就好說話
        if (me->name() == LURCHER)
        {
                switch (random(3))
                {
                case 0:
                        msg = "…嘿嘿…你去" + place +
                              "逛逛，那兒有個" + next_name +
                              "，你問他啥都知道";
                        break;

                case 1:
                        msg = "…這樣吧…你去找" + next_name +
                              "問問看，那家伙就在" + place +
                              "，可別走丟了";
                        break;

                default:
                        msg = "你到" + place + "瞅瞅，如"
                              "果碰到" + next_name + "那廝，說"
                              "不定…嘿嘿…能有啥收獲";
                        break;
                }
        }

        // 提供出線索信息
        message("vision", me->name() + "悄悄在" + who->name() + "耳"
                "邊說了些什麼。\n", environment(who),
                ({ me, who }));

        // 提供出任務的描述信息
        msg = WHT + me->name() + WHT "悄悄對你說道：" + msg + "。\n" NOR;

        // tell_object(who, sort_msg(msg));
        tell_object(who, msg);
        if (me->name() != QUESTER && me->name() != LURCHER)
                me->destruct_me(); // 銷毀上次線索人物

        return;
}
