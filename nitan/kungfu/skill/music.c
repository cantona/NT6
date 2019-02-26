// music.c 五音十二律

// 樂律十二律，是為黃鐘、大呂、太簇、夾鍾、姑洗、中呂、蕤賓、林鐘、夷則、
// 南呂、無射、應鐘。此是自古已有，據説當年黃帝命伶倫為律，聞鳳凰之鳴而制十二律。
// 瑤琴七絃，具宮、商、角、微、羽五音，一弦為黃鐘，三絃為宮調。五調為慢角、清商、
// 宮調、慢宮、及蕤賓調。

inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me) 
{
        int lvl, lvl2;
        
        lvl = (int)me->query_skill("music", 1);

        if ( lvl > 100 && me->query_int()-15 < lvl/10 )
                return notify_fail("你悟性有限，難以領會音律中更高的意境。\n");

        return 1;
}

int practice_skill(object me)
{       
        return notify_fail("基本音律只能靠學(learn)來提高。\n");
}
