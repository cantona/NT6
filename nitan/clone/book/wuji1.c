// wuji1.c

inherit BOOK;

string* titles = ({
        "風雲手手法",
        "如來千葉手手法",
        "大金剛拳法",
        "羅漢拳法",
        "般若掌法",
        "散花掌法",
        "醉拳",
});

string* skills = ({
        "fengyun-shou",
        "qianye-shou",
        "jingang-quan",
        "luohan-quan",
        "banruo-zhang",
        "sanhua-zhang",
        "zui-quan",
});

void create()
{
        int i = random(sizeof(titles));

        set_name(titles[i], ({ "shaolin wuji", "wuji" }));
        set_weight(200);
        set("unit", "冊");
        set("long", "這是一冊" + titles[i] + "\n");
        set("value", 500);
        set("material", "paper");
        set("skill", ([
                "name": skills[i],      // name of the skill
                "exp_required": 10000,  // minimum combat experience required
                "jing_cost": 15+random(30),// jing cost every time study this
                "difficulty":   25,     // the base int to learn this skill
                "max_skill":    99      // the maximum level you can learn
        ]) );
}
