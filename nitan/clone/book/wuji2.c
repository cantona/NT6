// wuji2.c

inherit BOOK;

string* titles = ({
        "龍爪功法",
        "鷹爪功法",
        "拈花指法",
        "一指禪功",
        "慈悲刀法",
        "修羅刀法",
});

string* skills = ({
        "longzhua-gong",
        "yingzhua-gong",
        "nianhua-zhi",
        "yizhi-chan",
        "cibei-dao",
        "xiuluo-dao",
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
