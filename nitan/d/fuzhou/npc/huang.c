// huang.c

#include <ansi.h>

inherit NPC;

int ask_diubiao();

void create()
{
        set_name("黃先生", ({ "huang xiansheng", "huang" }));
        set("title", HIR"福"HIC"威"YEL"鏢局"HIY"賬房"NOR);
        set("gender", "男性");
        set("age", 36);

        set("inquiry", ([
                "丟鏢" : (: ask_diubiao :),
                "失鏢" : (: ask_diubiao :),
                "失敗" : (: ask_diubiao :),
        ]) );

        set("combat_exp", 10000);
        set("shen_type", 1);

        set("eff_qi",800);
        set("qi",800);
        set("max_neili", 100);
        set("neili", 100);
        set("jiali", 10);


        setup();
        carry_object("/clone/misc/cloth")->wear();
}

int accept_object(object who, object ob)
{
        object myenv ;
        if( query_temp("fuwei_diubiao_ask", who) && (query("money_id", ob) && ob->value() >= 100000) )
    {
                message_vision(HIY"黃老先生對$N說：好吧！就再給你一次機會了！\n"NOR , who);
            delete_temp("fuwei_destm", who);
            delete_temp("fuwei_dest", who);
            delete_temp("fuwei_diubiao_ask", who);
            delete_temp("fuwei_ready", who);
            delete_temp("fuwei_prepare", who);
            return 1;
         }
        if( query_temp("fuwei_ready", who) )
        {
                message_vision(HIY"黃老先生對$N說：又給我錢？好！好！留著我喝老酒！\n"NOR , who);
                return 1;
        }
        if( !query_temp("fuwei_prepare", who) )
        {
                message_vision(HIY"黃老先生對$N說：要押鏢，該先去找總鏢頭！\n"NOR, who);
                return 1;
        }
        if( wizardp(who) || (query("money_id", ob) && ob->value() >= 200000) )
        {
                message_vision(HIY "黃老先生對$N說：鏢車準備好了，在院子裡呢。趕快接鏢(jiebiao)吧！\n丟了鏢押金就賠償給鏢主！\n"NOR , who);
                set_temp("fuwei_ready", 1, who);
                delete_temp("fuwei_prepare", who);
                return 1;
        }
        else
        {
                message_vision(HIR"黃老先生皺著眉對$N說：就這點？你還保什麼鏢？出去出去！\n"NOR, who);
                return 0;
        }
}

int ask_diubiao()
{
        object me = this_player();
        if( query_temp("fuwei_dest", me) )
        {
message_vision(HIR"黃老先生皺著眉對$N說：那上面可是有好幾萬鏢銀啊！你要還想繼續保鏢就先交十兩黃金來吧！\n"NOR, me);
        set_temp("fuwei_diubiao_ask", 1, me);
        return 1;
        }
        else
        {
          message_vision(HIR"黃先生皺眉道:你好象沒接過鏢吧？\n",me);
          return 1;
        }

}
