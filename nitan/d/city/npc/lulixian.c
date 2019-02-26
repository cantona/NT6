// npc: /d/city/npc/lulixian.c

#include <ansi.h>
inherit NPC;

int ask_riddle();

void create()
{
        set_name("陸麗仙", ({ "lu lixian", "lu", "lixian" }) );
        set("gender", "女性" );
        set("title", MAG"歌姬"NOR );
        set("nickname", YEL"金錠待系生"NOR);
        set("age", 18);
        set("long", 
"紅羞翠怯，嬌面含春，身穿時花繡襖，低束羅裙，貌如仙子，腰似小蠻，纖不盈握。\n");

        set("per", 28);
        set("int", 28);
        set("combat_exp", 5000);

        set("attitude", "peaceful");
        set("inquiry", ([
                "猜謎" : (: ask_riddle :),
                "謎語" : (: ask_riddle :),
        ]) );
        set("times", 100);
        setup();
        set("chat_chance", 10);
        set("chat_msg", ({
        }) );
        carry_object(CLOTH_DIR+"cloth/qi-dress")->wear();
        carry_object(CLOTH_DIR+"shoes")->wear();
}

void init()
{
        ::init();
        add_action("do_answer", "answer");
        add_action("do_enjoy",  "enjoy");
}

int ask_riddle()
{
        object me = this_player();

        if( query("trill_marks/guessing", me) )
        {
                write("陸麗仙笑了笑，説：你先把上個謎猜出來再説。\n");
                return 1;
        }
        else
        {
                switch(query("trill_marks/guess", me)){
                case 0:
                        message_vision("陸麗仙巧笑着對$N説：咱們猜個謎語吧：\n", me);
                        write("遙望山家正午炊 打《紅樓夢》人名一\n");
                        set("trill_marks/guessing", 1, me);
                        break;
                case 1:
                        message_vision("陸麗仙巧笑着對$N説：咱們猜個謎語吧：\n", me);
                        write("飛渡蓬萊我不懼 打《紅樓夢》詩句一\n");
                        set("trill_marks/guessing", 2, me);
                        break;
                case 2:
                        message_vision("陸麗仙巧笑着對$N説：咱們猜個謎語吧：\n", me);
                        write("潘金蓮嫌武大   打《詩經》詩句一\n");
                        set("trill_marks/guessing", 3, me);
                        break;
                default :
                        command("sigh");
                        message_vision("陸麗仙對$N説道：謎都被你猜光了，等我製出新的再説吧！\n", me);
                return 1;
        }
        write("想好了回答 (answer) 我。記住，不可泄露謎語或謎底。\n");
        message("vision", "陸麗仙對着"+me->name()+"嘀咕了幾句話。\n", environment(me), ({me}));
        return 1;
        }
}

int do_answer(string arg)
{
        object me;
        int soln,riddle;
        me = this_player();
        riddle=query("trill_marks/guessing", me);

        if (!riddle) {
                write("什麼？你想幹嗎？\n");
                return 1;
        }

        if( !arg || arg=="" ) {
                write("想好謎底再回答。\n");
                return 1;
        }
        message("vision", me->name() + "把嘴湊到陸麗仙的耳邊嘀嘀咕咕。\n", environment(me), ({me}) );

        switch (arg)
        {
        case "岫煙": soln=1; break;
        case "邢岫煙" : soln=1; break;
        case "任憑弱水三千" : soln=2; break;
        case "不如叔也" : soln=3; break;
        default :
                say("陸麗仙掩着嘴笑了起來，説道：不對，不對。\n"
                 + me->name() + "的臉唰的紅了起來。\n");
        return 1;
        }

        if ( riddle == soln )
        {
                set("trill_marks/guess", riddle, me);
                message_vision("陸麗仙愉快的對$N微笑着。\n", me);
                set("score",query("score",  me)+80, me);
                delete("trill_marks/guessing", me);
                write ("你的江湖閲歷增加了！\n");
        }
        else
                write ("不對，不對！！瞎猜可不好！\n");
        return 1;
}

int do_enjoy()
{
        object me;
        string msg, me_msg;
        int jin, e_jin, m_jin, bonus;

        if( query("times") < 0)
                return notify_fail("陸麗仙疲憊地笑了笑：“今兒我累了，你改天再來吧。”\n");
        addn("times", -1);
        me = this_player();
        me_msg="果然";
        if ( objectp( present( "zizhu xiao",me) ) )
                me_msg = "$N吹簫和之，聲調清亮，音韻悠然，\n果然";
        msg = "陸麗仙笑了一聲，徐將寶鴨添香，然後四弦入抱，半面遮羞，嘈嘈切切，錯雜彈來。\n"+me_msg+"吹彈的清風徐來，枝鳥徐啼，悄然曲盡而尚裊餘音。\n";
        message_vision(msg, me);
        jin=query("jing", me);
        e_jin=query("eff_jing", me);
        m_jin=query("max_jing", me);
        bonus = me->query_skill("literate",1) + me->query_per() - 60;
        if ( bonus < 0 ) bonus = 0;
        if ( bonus )
        {
                write("你聽完一曲，覺得神完氣足。\n");
                if ( jin < e_jin )
                {
                        if ( ( jin + bonus ) > e_jin ) jin = e_jin;
                        else jin += bonus;
                }
                set("jing", jin, me);
        }
        addn("lu_sing", 1, me);
        return 1;
}
