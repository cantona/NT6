// qianlong.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("乾隆皇帝", ({ "qianlong", "emperor"}) );
        set("title", "清高宗");
        set("gender", "男性");
        set("age", 43);
        set("per", 24);
        set("no_get", 1);
        set("long",
"乾隆皇帝姓愛新覺羅，名弘歷，是大清入關後第四位在位皇帝，生平
號稱有十大武功，自稱“十全老人”。\n");
        set("combat_exp", 500);
        set("attitude", "piece");
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 30);
}
void init()
{
        add_action("do_kneel", "kneel");
}

int do_kneel()
{
        int i;
        object *chen, me = this_player();

        if ( objectp(present("chen jialuo", environment(me))))
        {
              message_vision(
"$N正想給乾隆皇帝請安，卻被陳家洛一把攔住：韃子的鷹犬，
不要臉的奴才，納命來吧！\n\n", me);
              chen = all_inventory(environment(me));
              for(i=0; i<sizeof(chen); i++)
              {
                   if( query("id", chen[i]) == "chenjialuo" )
                       chen[i]->kill_ob(me);
              }
        }
        message_vision(
"$N恭恭敬敬地跪了下來，磕頭道：奴才"+query("name", me)+"救駕來遲，皇上恕奴才死罪！\n\n",me);
        if( query("combat_exp", me)<150000 )
        {
              message_vision(
"$n看著$N，哼了一聲：你膽敢欺君冒功！憑你這點能耐也想挑了紅花會？！\n\n", me, this_object() );
              message_vision(
"$n飛起一腳，踢得$N丫手丫腳滾下六和塔去了。\n\n", me, this_object() );
              me->move("/d/hangzhou/liuheta");
              tell_object(me, HIR"你從塔頂被一腳踢了下來，好疼！還受了傷。\n"NOR);
message("vision",HIR"只見"+query("name", me)+"從塔頂上撲通一聲跌了下來，躺在地上半天爬不起來！\n"NOR,environment(me),me);
              me->receive_wound("qi", 20);
              addn("combat_exp", 0-query("combat_exp", me)/100, me);
              return 1;
        }
        if( query("marks/qianlong", me) )
        {
              message_vision(
"$n看著$N，哼了一聲，沒理$N。\n\n", me, this_object() );
        }
        else
        {
              message_vision(
"$n看著$N說道：免了！看在你救駕有功，免你死罪，朕自有封賞。\n\n", me, this_object() );
              set("marks/qianlong", "1", me);
              addn("combat_exp", 10000, me);
        }
        return 1;
}
