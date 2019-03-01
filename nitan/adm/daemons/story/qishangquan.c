// story:qishangquan 七傷拳

#include <ansi.h>

nosave string char_id;
nosave string char_name;
nosave string family_name;

int give_gift();
object select_character();

nosave mixed *story = ({
        "話說當日成昆讓一武林高手救之後：",
        "楊逍：教主，本教剛剛經過了一場大戰，我們應先回光明頂重整明教。",
        "張無忌：楊左使說得也沒錯，那麼我就和楊左使先回光明頂，義父你和韋一笑去追擊成昆吧。",
        "韋一笑：是，教主。",
        "謝遜：無忌，不必啦，光明頂重整需要人手，成昆我一個人去殺他就夠，韋一笑還是和你一起回明教吧。",
        "張無忌：也好！義父，那我們先走了。",
        "說罷，張無忌、楊逍、韋一笑等三人就轉身回明教去了。",
        "謝遜心想：雖然說我的武功足以殺成昆，但是......應該也會有一場惡戰！！不想了，追上去再說。",
        "不出半個時辰，謝遜已經追到了成昆.........",
        "謝遜喝道：成昆，你別想再跑！",
        "成昆嚇得出了一身冷汗，過了一會才慢慢的轉過身來，一見到只有謝遜一人才鬆了一口氣。",
        "成昆：我說我的徒兒，憑你也想殺你的師父麼？雖說你的功夫有很大的進步，但是我這幾年也不是白活啊！",
        "謝遜：廢話少說，來吧！！！",
        "謝遜說罷就向成昆揮出一拳，成昆嘿嘿一笑，身體輕輕一轉就避開了。",
        "謝遜心想：以現在的情況要殺死成昆確實不易，如果那天在光明頂答應幫我殺成昆的$N在這裡的話，那就一定沒問題",
        "話說曹操，曹操就到，$N路過這裡一見謝遜和成昆正打得火熱，就馬上施展輕功趕到謝遜身邊。",
        "$N對著謝遜說道：謝老前輩，今天可以實現我的諾言了！",
        "成昆望著$N在那裡惡心的表演心中有說不出的煩，鄙視的望著$N“呸”的一聲！",
        "$N馬上氣得火冒三丈，聚全身功力于一掌向成昆拍去！！！",
        "成昆見狀馬出掌相對！！！",
        "但是$N內功深厚，成昆被震得經脈盡斷，整個人向後倒飛了出去",
        "謝遜馬上提起屠龍趕到成昆的後面，然後對準他的臭冬瓜腦袋下面的脖子一刀砍下去！！！",
        "成昆連叫都來不及叫一聲就死了！！！！",
        "謝遜對天狂笑：哈哈哈！哈哈哈哈！！！哈哈！！！！！！",
        "過了良久......",
        "謝遜對著$N說到：我現在就按照當天的約定，把我的七傷拳傳授給你！",
        (: give_gift :),
});

void create()
{
        seteuid(getuid());

        if (! objectp(select_character()))
        {
                destruct(this_object());
                return;
        }
}

string prompt() { return HIY "【武林傳聞】" NOR; }

object select_character()
{
        object *obs;
        object ob;

        obs = filter_array(all_interactive(),
                           (: ultrap($1) &&
                              living($1) &&
                              $1->query_skill("qishang-quan", 1) < 1 &&
/*
                              query("combat_exp", $1) <= 30000000 && 
                              query("combat_exp", $1)>2500000 && 
*/
                              query("max_neili", $1)>5500 && 
                              SKILL_D("qishang-quan")->valid_learn($1) &&
                              ! wizardp($1) &&
                              !query("story/qishangquan", $1):));
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

        ob = find_player(char_id);
        if (! ob) return 1;

        if (ob->query_skill("qishang-quan", 1) < 10)
                ob->set_skill("qishang-quan", 10);

        set("story/qishangquan", 1, ob);
        tell_object(ob, HIC "你從謝遜那裡學習到了七傷拳。\n" NOR);
        CHANNEL_D->do_channel(this_object(), "rumor", "聽說" + ob->name(1) +
                              "從謝遜那裡學習到了七傷拳。");
        STORY_D->remove_story("qishangquan");
        return 1;
}
