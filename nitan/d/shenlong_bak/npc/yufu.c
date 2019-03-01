// yufu.c

#include <ansi.h>

#define YOU RANK_D->query_respect(this_object())
#define ME  RANK_D->query_respect(me)

inherit NPC;

mixed ask_shejing();

void create()
{
        set_name("神秘漁夫", ({"shenmi yufu"}));
        set("long",
                "這是一個附近島嶼上的漁夫，看樣子是遇到風浪到此暫時躲避的。\n"
        );

        set("gender", "男性");
        set("attitude", "peaceful");

        set("age", 50 + random(30));

        set("str", 25 + random(10));
        set("dex", 25 + random(10));
        set("max_qi", 20000);
        set("max_jing", 15000);
        set("neili", 20000);
        set("max_neili", 20000);
        set("jiaji", 50 + random(5));
        set("combat_exp", 10000000 + random(100000));

        set("inquiry", ([
                "蛇精" : (: ask_shejing :),
                "阿鼻道第三刀" : "如果你能証明你參與過對抗蛇精之戰，這第三刀的秘密我便告訴你。\n",
        ]));

        set_skill("force", 40);
        set_skill("dodge", 40);
        set_skill("unarmed", 40);
        set_skill("parry", 40);
        set_skill("sword", 50);
        set_skill("blade", 50);
        set("chat_chance", 5);
        set("chat_msg", ({
                "漁夫嘆道：聽說這神龍島上的蛇精又要出來害人了，孽障啊，孽障~~\n",
        }) );

        setup();

        carry_object("/clone/misc/cloth")->wear();
}

void start_dialog(object npc, object me, string *msg, int index)
{

        if (! objectp(npc) || ! objectp(me))return;
        
        if (environment(npc) != environment(me))return;
        
        // 對話結束，進行回調
        if (index >= sizeof(msg))
        {
                return;
        }
        
        if (index % 2 == 1)             
                tell_object(me, HIG + "=" + msg[index] + "\n" NOR);
        else
                tell_object(me, HIC + "=" + msg[index] + "\n" NOR);     

        index += 1;

        call_out("start_dialog", 1, npc, me, msg, index);

        return;
}

mixed ask_shejing()
{
        string *msg;

        object me;

        me = this_player();

        msg = ({
                "漁夫打量了一下你說道：這位" + ME + "恐怕是剛來這神龍島的吧，呵呵~~",
                "你說道：正是！",
                "漁夫點了點頭又道：老朽是這島附近的一個漁夫，在這附近打漁已經40多年了，還從未見過這蛇精呢。",
                "你疑惑到：哦？那" + YOU + "剛才口中所說的蛇精是怎麼回事？難道這島上真有蛇精不成？",
                "漁夫道：聽祖輩們說過，這島原不叫神龍島，而叫蛇島，這島上有著成千上萬種怪蛇，這些蛇兇猛無比，任何踏足\n"
                "島上的人它們都會主動攻擊，據說，進入蛇島深處的人至今還無一人生還　……",
                "你說道：既然如此，那為什麼那些人又要上蛇島呢，難道這島上有寶貝不成？",
                "漁夫搖了搖頭道：" + ME + "有所不知：這蛇島地處交通要地，凡是出去捕漁的漁夫都會經過此地，每逢遇到風浪，附近\n"
                "捕漁的漁夫都會上島躲避風浪，但是，一旦踏足這蛇島就再無人生還，哎～",
                "你說道：那為什麼附近的漁民不自己組織一批身強力壯之士來將這些蛇全部殺掉，這不就可以永絕後患了嗎？",
                "漁夫嘆了口氣道：聽我的祖輩們說，他們先後組織了四批勇士前來島上，這四批勇士每個都是身懷絕跡，並且都帶著\n"
                "火把、硫磺，裝備著各種兵器、鎧甲，起初進入蛇島，一切都還順利，將蛇殺得幾乎一條不留，但是到後來……",
                "你急切道：後來，後來怎麼了？難道是？",
                "漁夫點了點頭繼續道：但是後來，他們卻發現這島上的射就猶如江河水一般，源源不斷，始終殺不完，而且越殺越多，\n"
                "到最後這些勇士一個個都是耗盡精力被群射纏食而死。",
                "你迫不及待地追問道：這難道是蛇精在作祟？",
                "漁夫稍有懼色道：蛇精，蛇精！誰有沒見過，當時這四批公認最厲害的勇士全軍覆沒後，也再沒人敢提這件事了，從此附近\n"
                "漁民外出捕漁都是繞過此島，即使是遇到風浪也不再踏足此島。後來，這事就漸漸被人遺忘。",
                "你說道：那後來呢？沒人見過蛇精怎麼會有人知道是蛇精在作祟呢？",
                "後來有一位遊方道人到此小住，見漁民出外捕漁都是避蛇島而遠之，便覺奇怪，後來多放打探才知道原委。這位道人為報答\n"
                "漁民盛情，事後，開壇做法，欲除去這島上之害，但是，這位道人道行有限，一系列法事後，他告訴附近村民說，經他開壇\n"
                "做法雖不能解除蛇島之患，但他算出這蛇島上的毒蛇並非原本就有，而是來自與這蛇島上的千年蛇精，只要這只蛇精不\n"
                "除，蛇島之患便永久無法解除。",
                "你連忙問道：那這位道人有沒有說怎麼才能殺掉這兩只蛇精呢？",
                "漁夫搖頭道：這我就不是很清楚了，剛才我所說的也是聽我父輩口述，只知道後來蛇精被壓在這蛇島底，這島也改名叫神龍島，\n"
                "至于其中來龍去脈我就不得而知了，但是，據說，最後有一位叫賽神龍的勇士降伏了蛇精",
                "你說道：哦？賽神龍，何許人也？",
                "漁夫道：我聽我祖輩說，賽神龍乃人中龍鳳，武藝超群，當年，由他帶頭降伏了蛇精，並終身駐守神龍島，以防蛇精重出人間。",
                "你說道：那怎麼才能找到賽神龍？",
                "漁夫道：聽說他就駐守在此島的蛇精洞內，但是，千百年來也無人再敢進入 ……",
                "你說道：多謝！",

        });

        start_dialog(this_object(), me, msg, 0);

        return 1;

}

int accept_object(object me, object ob)
{
        if (! objectp(me) || ! objectp(ob))return 0;

        if( query("id", ob) != "shejing linpian" )
        {
                return 0;
        }

        command("yi");

        if( !query("can_perform/badao/san-2", me) )
        {
                command("say 這不是從九頭蛇精身上掉下鱗片嗎！閣下勇氣超群，老夫佩服，佩服！");
                command("tan");
                command("say 可惜你還未掌握阿鼻道第二刀的精髓，等你學會阿鼻道第二刀再來吧！");
                return 0;
        }

        if( query("can_perform/badao/san", me) )
        {
                command("bow "+query("id", me));
                command("say 閣下定會揚名江湖！！");
                return 0;
        }

        if (me->query_skill("badao", 1) < 1000)
        {
                command("say 這不是從九頭蛇精身上掉下鱗片嗎！閣下勇氣超群，老夫佩服，佩服！");
                command("tan");
                command("say 可惜你霸刀火候還不夠，這第三刀恐怕不能傳你！");
                return 0;
        }

        if( query("reborn/times", me) < 3 )
        {
                command("say 這不是從九頭蛇精身上掉下鱗片嗎！閣下勇氣超群，老夫佩服，佩服！");
                command("tan");
                command("say 可惜你機緣不夠，這第三刀恐怕不能傳你！");
                return 0;
        }

        command("say 這不是從九頭蛇精身上掉下鱗片嗎！閣下勇氣超群，老夫佩服，佩服！");
        command("nod");
        command("say 閣下如此勇氣，日後定當揚名江湖，老夫便將這失傳已久的阿鼻道第三刀傳你，你可聽好了 ...");

        tell_object(me, HIG "恭喜你，領悟了阿鼻道第三刀！\n" NOR);
        tell_object(me, HIR "恭喜你，已經領悟了阿鼻道三刀的所有招式，阿鼻道三刀已經練成！\n" NOR);
        set("can_perform/badao/san", 1, me);

        me->save();

        destruct(ob);

        return 1;
}
