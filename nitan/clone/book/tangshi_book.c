// tangshi_book.c

inherit ITEM;

void create()
{
        set_name( "唐詩劍譜",({ "tangshi jianpu","book"}));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long","這是一本唐詩選輯。經過水浸泡後一些字顯得格外醒目：

    “江陵城南偏西天寧寺大殿佛像向之虔誠膜拜通靈祝告如來賜福往生極樂”。

\n");
                set("value", 1500);
                set("material", "paper");
                set("skill", ([
                        "name":         "tangshi-jian",      //name of the skill
                        "exp_required": 1 ,           //minimum combat experience required
                        "jing_cost":    10+random(10),// jing cost every time study this
                        "difficulty":        10,           // the base int to learn this skill
                        "min_skill":        0,            // the minimum level you can learn
                        "max_skill":        49            // the maximum level you can learn
                ]) );
        }
}