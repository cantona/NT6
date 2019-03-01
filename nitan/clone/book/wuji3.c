// wuji13.c

inherit BOOK;

string* titles = ({
        "韋陀棍法",
        "醉棍棍法",
        "無常杖法",
        "普渡杖法",
        "伏魔劍法",
        "達摩劍法",
});

string* skills = ({
        "weituo-gun",
        "zui-gun",
        "wuchang-zhang",
        "pudu-zhang",
        "fumo-jian",
        "damo-jian",
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
