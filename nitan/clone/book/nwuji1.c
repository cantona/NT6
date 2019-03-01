// Last Modified by winder on May. 29 2001
// nwuji1.c

inherit ITEM;

string* titles = ({
        "風雲手手法",
        "散花掌法",
        "如來千葉手手法",
        "大金剛拳法",
        "羅漢拳法",
        "般若掌法",
        "韋陀掌法",
});

string* skills = ({
        "fengyun-hand",
        "sanhua-strike",
        "qianye-hand",
        "jingang-cuff",
        "luohan-cuff",
        "boruo-strike",
        "weituo-strike",
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
                "name":        skills[i],
                "exp_required":        10000,
                "jing_cost": 15+random(30),
                "difficulty":        25,
                "max_skill":        99
        ]) );
}