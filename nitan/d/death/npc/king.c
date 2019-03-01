// king.c

#include <ansi.h>
inherit NPC;

string *answer_msg =({
"不錯，看在你平日的積德，加上你近日的磨練，就饒你這一次，你去見見判官吧。\n",
"嗯，你的罪孽已經差不多了，在過一段時間就可以了。\n",
"你心中積惡還未洗清，不能回家。",
"你罪孽深重，還是先等著吧。",
"哼，你孽似海深，還是老實點，多受些苦吧。",
"",//萬一有人是300，就是這行。
});
string ask_me();

void create()
{
        set_name(HIW "酆都冥府大帝" NOR, ({ "ming king","king" }) );
        set("long",HIW @LONG
岱泰山乃天帝之孫，群靈之府，主世界人民官職生死貴賤等事，定生死簿，轄天下眾
生，馭冥府群鬼。
LONG NOR);
        set("gender","男性");
        set("str",1000);
        set("nickname",HIR "閻羅冥王" NOR);
        set("title",GRN"天"RED"齊"YEL"仁"BLU"聖"CYN"大"MAG"生"WHT"敬"BLK"道"HIW"東岳大帝"NOR);            
        set("attitude", "peaceful");
        set("age", 102400000);
        set("combat_exp", 100000000);
        set("max_jing", 10000);
        set("max_qi", 10000);
        set("max_neili",100000);
        set("neili",100000);
        set("inquiry",([
                "回家":(:ask_me:),
        ]) );
        setup();
}

string ask_me()
{
        int rein_time, mud_age, i;
        object who;
        who=this_player();
        if( query("age", who) <= 15 )
                return "咦？你這麼小年紀，怎麼會跑到這裡來？";
        mud_age=query("mud_age", who);
        rein_time=(query("PKS", who)*20)+(query("MKS", who)/10);
        i=rein_time-mud_age;
        i=i>=0?i:0;
        i/=60;
        if(i>=4)
        {
                command("heng");
                i = 4;
        }
        else if(i<=0)
        {
                command("nod");
                i = 0; 
        }
        return answer_msg[i];
}