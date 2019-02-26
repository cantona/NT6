// whip.c

inherit ITEM;

void create()
{
        set_name("鞭法總訣", ({"shu", "book" }));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "冊");
                set("long","這是一冊修習鞭法的武經\n裏面記載着全真派掌教丹陽子多年的練功心得，畫冊中人物姿勢如玉龍盤柱、如金鳳飛舞。\n");
                set("value", 500);
                set("material", "book");
                set("skill", ([
                        "name":        "whip",        // name of the skill
                        "exp_required":        0,        // minimum combat experience required
                        "jing_cost":        15,        // jing cost every time study this
                        "difficulty":        20,        // the base int to learn this skill
                        "max_skill":        100        // the maximum level you can learn
                ]) );
        }
}