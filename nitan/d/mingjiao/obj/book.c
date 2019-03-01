#include <ansi.h>

inherit ITEM;

void create()
{
        set_name( HIC "明教簡史" NOR, ({ "mingjiao jianshi", "jianshi", "book" }));
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
"\n                 『明教簡史』\n\n"
"明教源于波斯國，唐時傳至中土。當時稱為襖教。唐皇在各\n"
"處敕建大雲興明寺，為明教的寺院，明教教義是行善去惡，\n"
"眾生平等，若有金銀財物，須當救濟貧眾，不茹葷酒，崇拜\n"
"明尊。明尊即是火神，也即是善神。只因厲朝貪官污吏欺壓\n"
"明教，明教教眾不忿，往往起事，自北宋方臘方教主以來，\n"
"已不知有多少次了。在北宋期間的四大寇：方臘、宋江、王\n"
"慶、田虎，其中之一的方臘便是第一代教主。在南宋建炎年\n"
"間，王宗石教主在信州起事。紹定年間有余五婆教主在衢州\n"
"起事，理宗紹定年間有張三槍教主在江西、廣東一帶起事。\n"
"只因明教教素來和朝廷官府作對，朝廷官府便說明教是“魔\n"
"教”，嚴加禁止，明教在官府的逼迫之下為求生存，作事不\n"
"免隱秘詭怪，以避官府的耳目。正大門派和明教積怨成仇，\n"
"更是勢如水火。明教這麼大的一個教，教眾之中也不免偶有\n"
"不自檢點、為非作歹之徒，仗著武功了得，濫殺無辜者有之\n"
"姦淫擄掠者有之，所以明教的聲譽便如江河之目下。但自大\n"
"宋亡于蒙古韃子之手後，明教更成了朝廷之死敵，明教更把\n"
"驅除胡虜為已任，只可惜自陽頂天教主不明死因而亡後，明\n"
"群龍無守，教中諸高手為爭教主之位，鬧得自相開殘殺，四\n"
"五裂，終于有的洗手歸隱，有的另立門派，自任教主，教規\n"
"一墮之後，更與名門正派結的怨更深，之後才有六大門派圍\n"
"攻光明頂之事。現在在張無忌教主的帶領之下，由于對各大\n"
"有恩，與正派人等盡前嫌，成為一個正派的教。\n");
                set("value", 100);
                set("material", "paper");
        }
        setup();
}