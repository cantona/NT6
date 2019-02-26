// story:sanfenjian 三分劍術

#include <ansi.h>

nosave string char_id;
nosave string char_name;
nosave string family_name;

int give_gift();
object select_character();

nosave mixed *story = ({
        "只聽“鏹鐺”一聲，閻世章五行雙輪一招「指天劃地」，擋開了霍青桐的長劍。",
        "閻世章退出一步，叫道：“且慢，我有話説。”",
        "眾回人逼上前去，兵刃耀眼，眼見就要將他亂刀分屍。",
        "閻世章右手一扯，將背上的紅布包袱拿在手中，雙輪高舉，叫道：“且慢！”",
        "眾回人俱都大驚，退了幾步。",
        "閻世章暗道：這次身入重圍，難以逃脱，看來只有憑一身藝業以圖僥倖。",
        "閻世章奸笑一聲，説道：“如果你們要倚多取勝，我先將這包裹砍爛了。”",
        "霍青桐道：“好，就我和你單挑，接你五行輪的高招。”",
        "霍青桐説罷劍走偏鋒，斜刺左肩。閻世章的雙輪遮鎖封攔，招數嚴密。兩人轉瞬拆了七八招。",
        "只聽一聲驚叫，閻世章右腕中劍，右輪飛上半空，眾人不約而同，齊聲喝彩。",
        "閻世章縱身飛出丈餘，説道：“我認輸了，經書給你！”反手去解背上紅布包袱。",
        "霍青桐歡容滿臉，搶上幾步，還劍入鞘，雙手去接這部他們族人奉為聖物的《可蘭經》。",
        "閻世章臉色一沉，喝道：“拿去！”右手一揚，突然三把飛錐向她當胸疾飛而來。",
        "這一下變起倉卒，霍青桐難以避讓，仰面一個「鐵板橋」，全身筆直向後彎倒，躲了開去。",
        "閻世章一不做，二不休，三把飛錐剛脱手，緊接着又是三把連珠擲出。",
        "霍青桐雙眼向天，不見大難已然臨身。旁視眾人盡皆驚怒，齊齊搶出。",
        "霍青桐剛挺腰立起，只聽得叮、叮、叮三聲，三柄飛錐被暗器打落地下，跌在腳邊。",
        "霍青桐暗道：若非有人相救，三把飛錐已盡數打中自己要害。",
        "閻世章和身撲上，勢若瘋虎，五行輪對準霍青桐當頭砸下。",
        "只見閻世章的五行輪漸漸壓向霍青桐頭上，輪周利刃已碰及她帽上翠羽。",
        "眾人正要上前援手，忽然間青光一閃，霍青桐左手短劍撲的一聲，插入閻世章胸腹之間。",
        "閻世章大叫一聲，向後便倒。眾人又是轟天價喝一聲彩。",
        "霍青桐拔出短劍，看閻世章早已斷氣，鬆了口氣，忽見$N向她微微一笑。",
        "霍青桐心想：剛才打落這奸賊暗器，救了我性命的原來是他。",
        "霍青桐道：“承恩人相救小女性命，感激萬分，請問恩人尊姓大名？”",
        "$N輕輕一笑，説道：“在下$F的$N，女英雄有禮了。”",
        "$N又道：“久聞天山雙鷹兩位前輩三分劍術冠絕當時，今日得見姑娘神技，真乃名下無虛。”",
        "霍青桐道：“今天承蒙想救，無以為贈，這套三分劍術如閣下如果有意，也可參詳一番。”",
        "霍青桐又道：“若你我有緣，他日可上天山找我，將此套劍法的絕招傳授予你。”",
        (: give_gift :),
});

void create()
{
        seteuid(getuid());

        if (! objectp(select_character()))
        {
                STORY_D->remove_story("sanfenjian");
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
                           (: ultrap($1) &&
                              living($1) &&
                              query("combat_exp", $1) >= 2500000 && 
                              $1->query_skill("sword", 1) > 100 &&
                              $1->query_skill("sanfen-jianshu", 1) < 1 &&
                              query("family/family_name", $1) && 
                              ! wizardp($1) &&
                              !query("story/sanfenjian", $1):));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
        char_id=query("id", ob);
        char_name = ob->name(1);
        family_name=query("family/family_name", ob);
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
                msg = replace_string(msg, "$F", family_name);
                msg = replace_string(msg, "$ID", char_id);
        }
        return msg;
}

int give_gift()
{
        object ob;

        ob = find_player(char_id);
        if (! ob) return 1;

        if (ob->query_skill("sanfen-jianshu", 1) < 50)
                ob->set_skill("sanfen-jianshu", 50);

        set("story/sanfenjian", 1, ob);
        tell_object(ob, HIC "你從霍青桐那裏學習到了三分劍術。\n" NOR);
        CHANNEL_D->do_channel(this_object(), "rumor", "聽説" + ob->name(1) +
                              "從霍青桐那裏學習到了三分劍術。");
        STORY_D->remove_story("sanfenjian");
        return 1;
}

