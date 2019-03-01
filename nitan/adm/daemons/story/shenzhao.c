// story:shenzhao 凝血神爪

#include <ansi.h>

nosave string char_id;
nosave string char_name;
nosave string family_name;

int give_gift();
object select_character();

nosave mixed *story = ({
        "只聽那黑衣大漢大笑道：“顧炎武，黃宗羲，呂留良，看你們今天往哪裡逃？給我拿下了！”",
        "四名親兵立即應道：“是，謹遵瓜管帶吩咐。”",
        "瓜管帶道：“回京後見了鰲少保，人人不愁生官發財。”",
        "一名親兵笑道：“那都是瓜管帶提拔栽培，單憑我們四個，那有這等福分？”",
        "船頭忽然有人嘿嘿一笑，說道：“憑你們四人，原也沒這等福分。”",
        "船艙門呼的一聲，向兩旁飛開，只見一人負手背後，臉露微笑。",
        "瓜管帶道：“官老爺們在這裡辦案，你是誰？”",
        "那人微笑不答，邁步踏進船艙。頓時刀光閃動，四柄單刀分從四方劈落。",
        "那人手起手落，連出四掌，分別拍在四名親兵的胸口，咯咯聲響，四人肋骨齊斷。",
        "瓜管帶見勢不妙，連忙縱身一躍，從船艙缺口中跳了出去。",
        "那人奔到船頭，正欲追趕，卻見一書生提起竹篙，揮手擲出。",
        "竹篙猶似飛蛇，急射而前。但聽瓜管帶“啊“的一聲，斥革已插入他後心，將他釘在地上。",
        "兩人奔上岸邊，見瓜管帶已經死得透了，這才相互報以一笑。",
        "那人和那書生心中都暗自稱奇，心想：“這人是誰，武功如此之高，當真世所罕有。”",
        "兩人走進船艙，解開顧黃呂三人的穴道，又將四名親兵的屍體拋入運河，重點燈燭。",
        "顧黃呂三人不住道謝，問起兩人姓名。",
        "那書生道：“賤名適才承蒙黃先生齒及，在下姓陳，草字近南。敢問這位英雄大名？”",
        "那人微笑道：“無威無德，豈當‘英雄’二字，在下$F$N，承蒙陳總舵主見笑了。”",
        "陳近南道：“閣下武功高強，但閣下俠義熱血更為可貴，今日和閣下攜手一戰，暢快無比。”",
        "$N笑道：“陳總舵主名滿天下，今日一見，武功果然了得！”",
        "陳近南微笑道：“看閣下是武林中人，這套凝血神爪是集我畢生精力所創，今日便贈予閣下，多行俠事。”",
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

string prompt() { return HIR "【武林】" NOR; }

object select_character()
{
        object *obs;
        object ob;

        obs = filter_array(all_interactive(),
                           (: ultrap($1) &&
                              living($1) &&
                              $1->query_skill("ningxue-shenzhao", 1) < 1 &&
                              query("family/family_name", $1) && 
                              $1->query_dex() > 45 &&
                              query("shen", $1)>0 && 
                              ! wizardp($1) &&
                              !query("story/shenzhao", $1):));
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

        if (ob->query_skill("ningxue-shenzhao", 1) < 10)
                ob->set_skill("ningxue-shenzhao", 10);

        set("story/shenzhao", 1, ob);
        tell_object(ob, HIC "你從陳近南那裡學習到了凝血神爪。\n" NOR);
        CHANNEL_D->do_channel(this_object(), "rumor", "聽說" + ob->name(1) +
                              "從陳近南那裡學習到了凝血神爪。");
        STORY_D->remove_story("shenzhao");
        return 1;
}

