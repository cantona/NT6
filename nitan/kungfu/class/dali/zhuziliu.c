// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

inherit NPC;

void create()
{
        set_name("朱子柳", ({ "zhu ziliu", "ziliu", "zhu" }) );
        set("gender", "男性" );
        set("age", 48);
        set("long",
                "這是一箇中年書生，手裏拿了一本舊書，正讀得搖頭晃腦的。 \n");
        set("str", 25);
        set("dex", 20);
        set("con", 17);
        set("int", 15);
        set("shen_type", 1);
        set_skill("unarmed", 70);
        set_skill("dodge", 65);
        set_skill("hammer",70);
        set("combat_exp", 550000);


        set("attitude", "peaceful");
        set("inquiry", ([
                "段皇爺" : "他以經死了。",
                "讓路" :  "路我是不讓的，你要敢跳，我就戳你一指。",
                ]) );

        setup();

        set("chat_chance", 20);
        set("chat_msg", ({
                "朱子柳問道：是樵夫放你們上來的麼？他有什麼信物給你們帶上來？\n",
        }) );
}

void init()
{
        ::init();
        add_action("do_answer","answer");
}

int accept_object(object who, object ob)
{
        object me=this_object();

        if( query("name", ob) == "鏽鐵斧"
                 && query("material", ob) == "steel"){

                remove_call_out("destroying");
                call_out("destroying", 1, ob);

                if( query("visited", me)>3){
                        write("朱子柳搖頭道：對不住，我師傅今天和師叔出去遊山了，閣下改天再來吧。\n");
                        return 1;
                }
                addn("visited", 1, me);

                if( query_temp("marks/子柳", who)){
                        write("朱子柳笑眯眯的説：答不出來就好好去讀讀書嘛。\n");
                        return 1;
                }
                else {
                        write("朱子柳抬頭看了你一眼："+"這位"+RANK_D->query_respect(who) + "也懂詩詞？\n");
                        write("朱子柳搖頭晃腦的吟道：\n");
                        switch(random(7)) {
                        case 0:
                                write("抽刀斷水水更流，舉杯銷愁愁更愁。\n");
                                write("人生在世不稱意，明朝散發弄□□。\n");
                                set_temp("marks/子柳", 1, who);
                                break;
                        case 1:
                                write("鄭公粉繪隨長夜，曹霸丹青已白頭。\n");
                                write("天下何曾有山水，人間不解重□□。 \n");
                                set_temp("marks/子柳", 2, who);
                                break;
                        case 2:
                                write("錦瑟無端五十弦，一弦一柱思華年。\n");
                                write("莊生曉夢迷蝴蝶，望帝春心託杜鵑。\n");
                                write("滄海明珠應有淚，藍天日暖玉生煙。\n");
                                write("此情可待成追憶，□□□□□□□。\n");
                                set_temp("marks/子柳", 3, who);
                                break;
                        case 3:
                                write("白骨露於野，千里無雞鳴。 \n");
                                write("生民百遺一，念之斷□□。  \n");
                                set_temp("marks/子柳", 4, who);
                                break;
                        case 4:
                                write("梳洗罷，獨倚望江樓。過盡千帆皆不是，\n");
                                write("斜暉脈脈水□□，腸斷白蘋洲！ \n");
                                set_temp("marks/子柳", 5, who);
                                break;
                        case 5:
                                write("牆裏鞦韆牆外道，牆外行人，牆裏佳人笑。 \n");
                                write("笑漸不聞聲漸悄，□□□□□□□ \n");
                                set_temp("marks/子柳", 6, who);
                                break;
                        case 6:
                                write("恨春去，不與人期，弄月色， \n");
                                write("空遺滿地□□□  \n");
                                set_temp("marks/子柳", 7, who);
                                break;
                        case 7:
                                write("前不見古人，後不見來者， \n");
                                write("□□□□□□□□□□□□ \n");
                                set_temp("marks/子柳", 8, who);
                                break;
                        }
                        message_vision("朱子柳笑眯眯的問道：我不記得了，你能告訴我麼？\n", who);
                        return 1;
                }
        }
        return 0;
}

void destroying(object obj)
{
        destruct(obj);
        return;
}

int do_answer(string arg)
{
        int soln,riddle;
    object me = this_player();
    riddle=query_temp("marks/子柳", this_player());

    if (!riddle) {
                write("我又不是你師傅，你用不着回答我。\n");
                return 1;
        }
    if( !arg || arg=="" ) {
                write("想好謎底再回答。\n");
                return 1;
        }

    message("vision", me->name() + "朗聲回答。\n", environment(me), ({me}) );
        switch (arg) {
        case "扁舟": soln=1; break;
        case "驊騮" : soln=2; break;
        case "只是當時已枉然" : soln=3; break;
        case "人腸" : soln=4; break;
        case "悠悠" : soln=5; break;
        case "多情卻被無情惱" : soln=6; break;
        case "梨花雪": soln=7; break;
        case "念天地之悠悠獨傖然而涕下" : soln=8; break;
        default :
                say("朱子柳冷笑道，你掃過盲了麼。\n"+me->name()+"急忙退下山去。\n");
                me->move("/d/heizhao/shanlu9");
                return 1;
        }

        if (riddle==soln) {
                delete_temp("marks/子柳", this_player());
                say ("朱子柳一鞠到地，對" + me->name() + "説道：高明，高明。佩服，佩服\n");
                write ("朱子柳移開三尺，你從他身邊一躍而過，上山而去。 \n");
                me->move("/d/heizhao/yideng8");
        }
        else write (" 不對！！\n");
        return 1;
}
