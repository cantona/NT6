 // story:labazhou 臘八粥
 // Plzw 2004-08-29

#include <ansi.h>

nosave string char_id;
nosave string char_name;
nosave string fam_name;
nosave string ann_name;
nosave string ann_id;

mixed give_pai();
int   rob_pai();
object   select_characters();

nosave mixed *story = ({
        "又是一年的冬天。",
        "夜晚，$N躺在牀上正要休息。",
        "忽聽門外一人朗聲説道：“俠客島賞善罰惡使者，前來拜見$F的$N！”",
        "$N衝出門去，只見院子裏並肩站着一胖一瘦兩個人。",
        "$N一見此一胖一瘦兩人，顫聲道：“尊駕二位便是俠客島的賞善罰惡使者麼？”",
        "張三道：“正是。閣下可是$F的$N？我們奉俠客島島主之命，手持銅牌前來，邀請閣下赴敝島相敍，喝一碗臘八粥。”",
        "$N沉默不語。",
        "...",
        "張三道：“閣下不説話，那就是了。”",
        "張三從懷中取出一塊銅牌，笑道：“既是如此，還望閣下準時赴約！",
        "$N知道這賞善罰惡使者的厲害，無奈之下，接過銅牌低聲道：“多謝貴島奉邀，定當於期前趕到。”",
        "張三和李四相視一笑，轉眼消失在夜幕中。",
        "...",
        (: give_pai :),
        "$AN大笑道：“你這膽小怕事之人，有膽去麼，不如將令牌讓我，我倒想去俠客島見識見識！”",
        "$N心想：居然天底下還有這種想死的人，自己反正也不會去，不如讓給他。”",
        "$N將銅牌遞上道：“既然兄台想去，拿去便是！”",
        "$AN接過銅牌哈哈大笑，身形一閃，已然消失在夜幕中。",
        (: rob_pai :),
});

void create()
{
        seteuid(getuid());

        if (! objectp(select_characters()))
        {
                STORY_D->remove_story("labazhou");
                destruct(this_object());
                return;
        }
}

string prompt() { return HIG "【武林奇遇】" NOR; }

object select_characters()
{
        object *obs;
        object ob;

        obs = filter_array(all_interactive(),
                           (: living($1) &&
                                  query("family", $1) && 
                              /*
                              query("weiwang", $1) >= 50000 && 
                              query("score", $1) >= 50000 && 
                              $1->query_skill("force", 1) >= 100 &&
                              $1->query_skill("dodge", 1) >= 100 &&
                              $1->query_skill("parry", 1) >= 100 &&
                              */
                              query("combat_exp", $1) >= 100000 && 
                              !wizardp($1) &&
                              !query("story/labazhou", $1):));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
        char_id=query("id", ob);
        char_name = ob->name(1);
        fam_name=query("family/family_name", ob);

                obs = filter_array(all_interactive(),
                                                        (: living($1) &&
                                                        query("weiwang", $1) >= 50000 && 
                                                        query("score", $1) >= 50000 && 
                                                        /*
                                                        $1->query_skill("force", 1) >= 150 &&
                                                        $1->query_skill("dodge", 1) >= 150 &&
                                                        $1->query_skill("parry", 1) >= 150 &&
                                                        */
                                                        query("combat_exp", $1) >= 100000 && 
                                                        !wizardp($1) &&
                                                        !query("story/labazhou", $1):));
        if (! sizeof (obs))
                return ob;
        ob = obs[random(sizeof(obs))];
        ann_id=query("id", ob);
        ann_name = ob->name(1);
        return ob;
}

mixed query_story_message(int step)
{
        mixed msg;

        if (step >= sizeof(story))
                return 0;

        if( !char_id || !ann_id ) return 0;
        msg = story[step];
        if (stringp(msg))
        {
                msg = replace_string(msg, "$N", char_name);
                msg = replace_string(msg, "$ID", char_id);
                msg = replace_string(msg, "$F", fam_name);
                msg = replace_string(msg, "$AN", ann_name);
                msg = replace_string(msg, "$AID", ann_id);
        }
        return msg;
}

mixed give_pai()
{
        object ob;
        object pai;

        ob = find_player(char_id);
        if (! ob) return 1;

                if (random(4) > 0)
                {

                set("story/labazhou", 1, ob);
                CHANNEL_D->do_channel(this_object(), "rumor", "聽説" + ob->name(1) +
                                      "收到龍、木二島主的邀請去俠客島喝臘八粥。");
                // 正神是賞善，負神是懲惡
                if( query("shen", ob) >= 0 )
                        pai = new("/d/xiakedao/obj/tongpai1");
                else
                        pai = new("/d/xiakedao/obj/tongpai2");

                set("own", query("id", ob), pai);
                pai->move(ob, 1);
                set("xkd/ling", 1, ob);
                set("xkd/time", time()+86400, ob);
                STORY_D->remove_story("labazhou");
                return 0;
            }
            // 25%的機率被搶
            if (ann_id != char_id)
                return "一道黑影掠過，一掌重重的擊在" + char_name + "的背心，" + char_name + "大叫一聲，吐出一口鮮血。";

}

int rob_pai()
{
        object ob, rob;
        object pai;

        ob = find_player(char_id);
        rob = find_player(ann_id);
        if ((! ob) || (! rob)) return 1;

        set("story/labazhou", 1, rob);
        CHANNEL_D->do_channel(this_object(), "rumor",
                              "聽説" + rob->name(1) + "從" + ob->name(1) + "手中奪走了"
                              "賞善罰惡令牌。");
        STORY_D->remove_story("labazhou");
        if (rob)
        {
                // 正神是賞善，負神是懲惡
                if( query("shen", rob) >= 0 )
                        pai = new("/d/xiakedao/obj/tongpai1");
                else
                        pai = new("/d/xiakedao/obj/tongpai2");
                if (pai) pai->move(rob, 1);
        }
        return 0;
}

