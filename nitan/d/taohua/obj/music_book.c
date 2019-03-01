//Cracked by Kafei
//music book

inherit ITEM;


string* names = ({
        "《樂府古題要解》",
        "《樂書要錄》",
        "《敦煌曲譜》",
        "《風雅十二詩譜》",
});
string* longs = ({
        "音樂著錄，唐代吳兢撰，記有許多樂曲的命名來由，對研究漢、魏、六朝的音樂\n相當有參考價值。\n",
        "唐代樂律學著作，對變聲的強調和左旋、右旋兩種旋宮之法的論述，頗有特點。\n",
        "敦煌石窟收藏的音樂文物抄錄，記有二十五首曲譜。所用譜字稱為「燕樂半字譜」，\n共計有二十多個，譜字旁有符號和文字表示音高和節奏。\n",
        "宋代詩歌譜集，歌詞出自詩經，配以雅樂風格的曲調。\n",
});


void create()
{
        int num = random(4);

        set_name( names[num], ({ "music book", "book" }));
                set("long", longs[num]);
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("value", 200);
                set("material", "paper");
                set("skill", ([
                        "name":        "music",        // name of the skill
                        "exp_required":        0,        // minimum combat experience required
                        "jing_cost": 10,         // jing cost every time study this
                        "difficulty":        24,        // the base int to learn this skill
                        "max_skill":        50,        // the maximum level you can learn
                ]) );
        }
}