#include <ansi.h>
inherit NPC;

string *degree_desc = ({
       HIR "總督" NOR,
       MAG "兵部侍郎" NOR,
       MAG "兵部尚書" NOR,
       HIB "鎮北節度使" NOR,
       HIB "征討大將軍" NOR,
       HIW "兵馬大元帥" NOR,
});
string clear_degree(string arg);
string ask_chubing(object me);
int ask_degree();
int add_degree(object ob, int lv);

void create()
{
        set_name("劉公公", ({"liu gonggong", "liu"}));
        set("gender", "無性");
        set("age", random(20) + 20);

        set("long", "這是一個京城皇宮中的一名太監，負責為皇帝傳送奏本。\n");
        set("combat_exp", 800000);
        set("attitude", "peaceful");
        set("max_qi", 3000);
        set("max_jing", 2000);
        set("max_neili", 2000);
        set("neili", 1000);
        set("no_get", 1);
        set("inquiry", ([
                 "策封" :   (: ask_degree :),
                 "出兵" :   (: ask_chubing :),
        ]));

        setup();
        carry_object("clone/cloth/cloth")->wear();
}

int ask_degree()
{
        int lv;
        object ob = this_player();

        if( query_temp("degree_jungong", ob) )
        {
                command("say 大人稍安勿躁，"
                        + "咱家已經啟奏聖上了，還是先耐心恭候聖上旨意吧！\n");
                return 1;
        }

        if( query("guo_shoucheng/reward", ob)>
                (100*(1+query("degree_jungong", ob))*(1+query("degree_jungong", ob))) )
        lv=query("degree_jungong", ob)+1;

        if (lv > (sizeof(degree_desc) + 8))
        {
                command("say 大人已經官居極品，位高權重，該多考慮些"
                        + "為國家社稷出力才是！\n");
                return 1;
        }

        if( lv <= query("degree_jungong", ob) || query("degree_jungong", ob)<8 )
        {
                command("say 要獲得更高的策封，大人所立軍功好像不夠啊！\n");
                return 1;
        }

        command("say 大人請稍候，咱家這就立刻稟報聖上，為大人請封！\n");

        //  remove_call_out("add_degree");
        call_out("add_degree", 10, ob, lv);
        set_temp("degree_jungong", 1, ob);
        return 1;
}

int add_degree(object ob, int lv)
{
        string degree, old_degree;
        degree = degree_desc[lv - 9];

        if (! ob) return;

        if( query("degree", ob))old_degree=query("degree", ob);
        else old_degree = "";

        message("channel:rumor", MAG"【大宋京城】"NOR + YEL
                + CHINESE_D->chinese_date((time() - 14 * 365 * 24 * 60 * 60))
                + "......\n"NOR,
                users());

        message("channel:rumor", MAG"【大宋京城】"HIY"奉天承命，皇帝詔曰："
                +"策封"+old_degree+""+HIW+query("name", ob )
                + HIY" 為大宋 "NOR + degree + HIY"，欽此！\n"NOR,
                users());
        delete_temp("degree_jungong", ob);

        if( query("degree", ob) )
        {
                if( query("degree_ask", ob) )
                        degree=HIM " ☆ " NOR+clear_degree(query("degree", ob) )
                               + HIM " ☆ " NOR + degree + HIM " ☆ "NOR;
                else
                        degree=HIM " ☆ " NOR+clear_degree(query("degree", ob) )
                               + degree + HIM " ☆ " NOR;
        } else
                degree = HIM " ☆ " NOR + degree
                       + HIM " ☆ " NOR;

        set("degree_jungong", lv, ob);
        set("degree", degree, ob);
        addn("weiwang", lv*200, ob);
        return 1;
}

string clear_degree(string arg)
{
        if ((strsrch(arg, HIR "提督" NOR) >= 0)
        ||  (strsrch(arg, HIR "總督" NOR) >= 0)
        ||  (strsrch(arg, MAG "兵部侍郎" NOR) >= 0)
        ||  (strsrch(arg, MAG "兵部尚書" NOR) >= 0)
        ||  (strsrch(arg, HIB "鎮北節度使" NOR) >= 0)
        ||  (strsrch(arg, HIB "征討大將軍" NOR) >= 0)
        ||  (strsrch(arg, HIW "兵馬大元帥" NOR) >= 0)
        ||  (strsrch(arg, HIM " ☆ " NOR) >= 0))
        {
                arg = replace_string(arg, HIR "總督" NOR, "");
                arg = replace_string(arg, MAG "兵部侍郎" NOR, "");
                arg = replace_string(arg, MAG "兵部尚書" NOR, "");
                arg = replace_string(arg, HIB "鎮北節度使" NOR, "");
                arg = replace_string(arg, HIB "征討大將軍" NOR, "");
                arg = replace_string(arg, HIW "兵馬大元帥" NOR, "");
                arg = replace_string(arg, HIR "提督" NOR, "");
                arg = replace_string(arg, HIM " ☆ " NOR, "");
                arg = replace_string(arg, HIM "☆" NOR, "");
        }
        return arg;
}

string ask_chubing(string arg)
{
        object me;

        me = this_player();
        return WAR_D->ask_kingwar(me);
}
