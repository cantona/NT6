//Cracked by Kafei
// yijing.c

inherit ITEM;

void create()
{
        set_name( "易經《系辭篇》", ({ "jing", "yi jing" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一冊易經。上面寫著：\n
　　天尊地卑，乾坤定矣。卑高以陳，貴賤位矣。 動靜有常，剛柔斷矣。
方以類聚，物以群分，吉兇生矣。 在天成象，在地成形，變化見矣。

　　鼓之以雷霆，潤之以風雨，日月運行，一寒一暑，乾道成男，坤道成
女。

　　乾知大始，坤作成物。

　　乾以易知，坤以簡能。

    易則易知，簡則易從。 易知則有親，易從則有功。 有親則可久，有
功則可大。 可久則賢人之德，可大則賢人之業。

    易簡，而天下矣之理矣；天下之理得，而成位乎其中矣。
\n");
                set("value", 200);
                set("material", "paper");
                set("skill", ([
                        "name":        "qimen-wuxing",        // name of the skill
                        "exp_required":        0,        // minimum combat experience required
                        "jing_cost": 25,         // jing cost every time study this
                        "difficulty":        30,        // the base int to learn this skill
                        "max_skill":        120,        // the maximum level you can learn
                ]) );
        }
}