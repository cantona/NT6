// story:baguadao 紫金八卦刀

#include <ansi.h>

nosave string char_id;
nosave string char_name;
nosave string family_name;

int give_gift();
object select_character();

nosave mixed *story = ({
        "胡一刀大笑道：“商劍鳴，到了此時你還是束手就擒吧！”",
        "商劍鳴：“商某與閣下無冤無仇，今日苦苦相逼究是為何？”",
        "胡一刀：“苗家一家上下數十口性命，他們又和你有什麼仇？受死吧！”",
        "商劍鳴只見對方劍鋒一閃，暗道：“我命休矣！”",
        "——鏹——",
        "只見一柄長劍飛插上了橫樑。",
        "胡一刀虎目圓瞪，道：“你是誰？為何插手此事？”",
        "商劍鳴睜開雙眼，只見一人左手負後，右手提一柄單刀，面色沉着。",
        "那人談談的道：“閣下技勝一籌，何必又非要趕盡殺絕？”",
        "胡一刀：“他欠苗人鳳幾十條性命，今天此仇不能不報。”",
        "那人道：“苗人鳳是你朋友？”",
        "胡一刀：“不是，我也是他的仇人。”",
        "那人冷笑一聲道：“原來閣下是怕了苗人鳳，想拿商劍鳴的人頭來換你自己的人頭！”",
        "那人又接着道：“既然如此，我不插手好了！”",
        "胡一刀大怒道：“呸！我胡一刀豈是這種卑鄙下流之人！”",
        "那人冷冷的道：“原來你就是人稱‘遼東大俠’的胡一刀？”",
        "胡一刀：“正是在下！”",
        "那人又冷笑一聲，道：“我生平最恨的就是你們這些所謂的大俠，這事我管定了。”",
        "胡一刀怒極，拔出了腰間單刀，喝道：“好！我就領教你的高招！進招吧！”",
        "那人哼了一聲，身形一展，撲了上去。",
        "嗆！",
        "鏹！",
        "~嗤啦！~",
        "~~~啊！~~~",
        "…………",
        "那人道：“現在閣下還有什麼話説？”",
        "只見胡一刀右手血流不斷，看着地上的兩根斷指，一張黑臉漲得通紅，半天説不出話。",
        "胡一刀搖了搖頭，苦笑道：“胡某只得今日才知‘天外有天，人外有人’四字。”",
        "那人也不理睬，淡淡的道：“既然如此，那麼閣下請便吧。”",
        "…………",
        "商劍鳴：“請問恩人尊姓大名？今日之恩，商某今生難以回報！”",
        "那人道：“哼！你是什麼東西，也配我的姓名？今日是你運氣好而已，也別謝我。”",
        "那人頓了一頓，接着道：“告訴你也無妨，$F$N便是在下。”",
        "商劍鳴：“這套紫金八卦刀法乃我商家祖傳祕訣，絕不輸於他胡家刀法，恩人可以參詳一翻。”",
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

string prompt() { return HIR "【武林傳聞】" NOR; }

object select_character()
{
        object *obs;
        object ob;

        obs = filter_array(all_interactive(),
                           (: ultrap($1) &&
                              living($1) &&
                              $1->query_skill("zijinbagua-dao", 1) < 1 &&
                              $1->query_skill("blade", 1) > 120 &&
                              $1->query_skill("sword", 1) > 100 &&
                              query("family/family_name", $1) && 
                              query("family/family_name", $1) != "關外胡家" && 
                              query("born_family", $1) != "關外胡家" && 
                              query("shen", $1)<0 && 
                              ! wizardp($1) &&
                              !query("story/baguadao", $1):));
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

        if (ob->query_skill("zijinbagua-dao", 1) < 50)
                ob->set_skill("zijinbagua-dao", 50);

        set("story/baguadao", 1, ob);
        tell_object(ob, HIC "你從商劍鳴那裏學習到了紫金八卦刀。\n" NOR);
        CHANNEL_D->do_channel(this_object(), "rumor", "聽説" + ob->name(1) +
                              "從商劍鳴那裏學習到了紫金八卦刀。");
        STORY_D->remove_story("baguadao");
        return 1;
}

