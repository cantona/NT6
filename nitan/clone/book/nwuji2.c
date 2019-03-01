// Last Modified by winder on May. 29 2001
// wuji2.c

inherit ITEM;

string* titles = ({
        "龍爪功法",
        "寂滅爪法",
        "摩訶指法",
        "一指禪功",
        "修羅刀法",
});

string* skills = ({
        "dragon-claw",
        "jimie-claw",
        "mohe-finger",
        "one-finger",
        "xiuluo-blade",
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
                        "name":        skills[i],        // name of the skill
                        "exp_required":        10000,        // minimum combat experience required
                        "jing_cost": 15+random(30),// jing cost every time study this
                        "difficulty":        25,        // the base int to learn this skill
                        "max_skill":        99        // the maximum level you can learn
                      ]) );
}