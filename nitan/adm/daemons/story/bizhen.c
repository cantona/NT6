// story:bizhen 玄鐵令——學習碧針清掌

#include <ansi.h>

nosave string char_id;
nosave string char_name;

int give_gift();
object select_character();

nosave mixed *story = ({
        "只聽那那黑衣高個兒怒喝：“吳道通，你是決計不交出來的啦？”",
        "吳道通哼了一聲，雙手分執鐵鉗兩股，竟將鐵鉗拆了開來，變成了一對判官筆。",
        "吳道通大喝一聲，衝如人羣。雙筆使開，招招取人穴道，以一敵三，仍然佔到了上風。",
        "西北角屋面上站着一名矮瘦老者，雙手叉在腰間，冷冷的瞧着三人相鬥。",
        "片刻之後………",
        "只聽喀喇喇的一聲響，那高個雙掌紮紮實實的擊在吳道通胸口，也不知斷了多少根肋骨。",
        "矮瘦老者見狀陡的飛身上前，抓起吳道通的身子，見他已停了呼吸。",
        "矮瘦老者眉頭微皺，喝道：“剝了他衣服，細細搜查。”",
        "四名下屬應道：“是！”立即剝去吳道通的衣衫。只見他背上長衣之下負着一個包裹。",
        "兩名黑衣漢子迅速打開包裹，但見包中有包，矮瘦老者挾手攫過，捏了一捏，面色陡變。",
        "矮瘦老者怒道：“他奶奶的！騙人的玩意，不用看了！快到屋裏搜去。”",
        "十餘名黑衣漢子又進了燒餅店，只聽嗆啷嗆啷，店裏的碗碟、桌椅、全部給摔了出來。",
        "幾個時辰之後，眾人將燒餅店牆壁、灶頭也都拆了。",
        "這時眾人已將燒餅鋪中搜了個天翻地覆，連地下的磚也已一塊塊挖起來查過。",
        "矮瘦老者見再也查不到什麼，喝道：“收隊！” ",
        "唿哨聲連作，跟着馬蹄聲響起，幾十個漢子片刻間走了個乾乾淨淨。",
        "…………",
        "暮靄蒼茫中，$N漫步而至，看到四周一片狼籍，心中微感詫異。",
        "$N突然發現吳道通的屍體橫卧街中，右手單手作爪狀，似乎在死前想要抓取什麼。",
        "順着吳道通右手的方向瞧去，$N只見他右手三尺之外有一塊燒餅。",
        "$N揀起那塊燒餅，輕輕一拉，發現其中藏着黑黝黝的一塊鐵片。",
        "$N頓時想起一事，隨手拔起地下一柄長劍，順手往鐵片上斫去，叮的一聲，長劍斷為兩截。",
        "$N心中狂喜，心道：“想來這便是江湖中傳聞的玄鐵令，想不到今日竟讓我得到。”",
        "相傳持此玄鐵令者，只要親手將令交在摩天居士謝煙客手中，便可讓他幫你做任何事情。",
        "$N心道：“此地不宜久留，我這就找謝煙客去。”説罷，悄然飄失在夜幕中。",
        (: give_gift :),
});

void create()
{
        seteuid(getuid());

        if (! objectp(select_character()))
        {
                STORY_D->remove_story("bizhen");
                destruct(this_object());
                return;
        }
}

string prompt() { return HIR "【武林傳聞】" NOR; }

object select_character()
{
        object *obs;
        object ob;

        obs = filter_array(all_interactive(),
                           (: living($1) &&
                              $1->query_skill("bizhen-qingzhang", 1) < 1 &&
                              query("combat_exp", $1) >= 1000000 && 
                              ! wizardp($1) &&
                              !query("story/bizhen", $1):));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
        char_id=query("id", ob);
        char_name = ob->name(1);
        return ob;
}

mixed query_story_message(int step)
{
        mixed msg;

        if (step >= sizeof(story))
                return 0;

        msg = story[step];
        if (stringp(msg))
        {
                msg = replace_string(msg, "$N", char_name);
                msg = replace_string(msg, "$ID", char_id);
        }
        return msg;
}

int give_gift()
{
        object ob;
        object book;

        ob = find_player(char_id);
        if (! ob) return 1;

        set("story/bizhen", 1, ob);
        tell_object(ob, HIC "你得到了玄鐵令。\n" NOR);
        CHANNEL_D->do_channel(this_object(), "rumor", "聽説玄鐵令落在了" + ob->name(1) +
                              "的手裏。");
        book = new("/d/tulong/tulong/obj/xuantie-ling");
        book->move(ob, 1);
        STORY_D->remove_story("bizhen");
        return 1;
}

