// story:zhuque 朱雀

#include <ansi.h>

int give_gift(string name);

nosave mixed *story = ({
        "火焰山，唐僧師徒 ……",
        "唐僧一臉愁容：這火焰山的火不熄滅，如何過得去啊！",
        "沙僧：不要着急師父，猴哥已經去牛魔王那裏借芭蕉扇了。",
        "豬八戒：算了吧，師傅，咱們就此散了吧，我回我的高老莊，沙師弟回他的流沙河，\n"
        "            猴哥就回花果山當他的美猴王 ……， 師父，沙師弟，你們説如何？",
        "唐僧開始認真考慮這個問題！",
        "沙僧開始認真考慮這個問題！",
        "…… …… ……",
        "孫悟空：師父——，我回來了，我從牛哥那裏借來了芭蕉扇！",
        "唐僧：阿們，總算借到了，悟空，開工~~！",
        "孫悟空雙手揮舞着芭蕉扇，剎那間狂風驟起，暴雨傾瀉而下 ……",
        "唐僧大聲嚷嚷道：“小心啦，打雷啦！下雨收衣服啦！”",
        "…… …… ……",
        "火焰山的火漸漸熄滅！",
        "…… …… ……",
        "剎那間，風止雨停，地動山搖，火焰山中傳出陣陣巨響。", 
        "突然，一隻巨大的渾身火紅的鳳凰伴隨着驚天動地般的叫聲衝出火焰山……",
        "孫悟空：妖怪？！",
        "豬八戒：⊙⊙ ！？",
        "沙僧：神獸？！",
        "唐僧：跑啊~~~~~~~ ！",
        "…… …… ……",
        "唐僧師徒四人瞬間消失得無影無蹤。",        
        "......",
        (: give_gift, "zhuque" :),
        "聽説朱雀(fire phoenix)從睡夢中驚醒，逃出了火焰山。",       
});

string prompt() { return HIM "【神話】" NOR; }

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

int give_gift(string name)
{
        object ob;

        ob = new(CLASS_D("misc/") + name);
        if (! objectp(ob))
                return 0;

        NPC_D->place_npc(ob);
        if (! objectp(environment(ob)))
        {
                destruct(ob);
                return 0;
        }

        CHANNEL_D->do_channel(find_object(STORY_D), "sys",
                              ob->name() + "出現在" + environment(ob)->short() +
                              "(" + base_name(environment(ob)) + ")。");
        return 1;
}
