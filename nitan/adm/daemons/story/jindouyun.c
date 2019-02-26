// story:donghai 東海龍傳説

#include <ansi.h>

int give_gift(string name);

nosave mixed *story = ({
        "赤腳大仙：鬥戰勝佛！",
        "孫悟空：哦？你這老頭啊？對了，上次託你送的洗髓丹你可送到了？",
        "赤腳大仙：那個自然，自然！小仙怎敢耽誤大聖的差使？",
        "孫悟空：噢，那好，那好，我還怕被你給吞沒了呢。",
        "赤腳大仙：哪裏...哪裏...",
        "孫悟空：南極仙翁那老頭怎麼説？",
        "赤腳大仙：...... 很好，很好... 對了，南極仙翁託小仙告訴大聖您準備赴本屆的蟠桃盛會呢！",
        "孫悟空：嗯，看來這禮沒有白送。想那蟠桃的滋味老孫我可是很久沒有品嚐了。",
        "赤腳大仙賠笑道：這隻怪那蟠桃熟的太慢，耽誤了大聖的口福了。",
        "孫悟空惱道：就是，熟個桃子還磨磨唧唧的，乾脆放到鍋了煮熟算了！",
        "赤腳大仙一嚇，道：這個不可，萬萬不可。",
        "孫悟空笑道：老孫我隨口説説你還當真了？桃子熟了只怕沒什麼味道。",
        "赤腳大仙抹抹冷汗，道：我口信送到，就不耽誤大聖您的工夫了，先走了，蟠桃會上再見！",
        "孫悟空：好，你去吧！",
        "......",
        "孫悟空暗想：現在離那蟠桃盛會還有一段時間，左右無事，何不下凡看看？卻不知我那羣猴娃們如何了。",
        (: give_gift, "sun" :),
        "聽説鬥戰勝佛孫悟空(sun wukong)凡心思動，來到人間。",
});

string prompt() { return HIM "【神話】" NOR; }

// 每天一次
int interval() { return 24 * 60 * 60; }

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
