inherit NPC;

void create()
{
        set_name("老鴇婆", ({ "laobao po", "laobao", "po" }) );
        set("gender", "女性" );
         set("title", "怡紅院老板娘");
        set("age", 42);
        set("long", 
            "\n這老鴇婆雖是徐娘半老，但仍風韻尤存，只不過臉上的粉太厚了。\n");
        set("str", 25);
        set("dex", 25);
        set("con", 25);
        set("int", 25);
         set("no_get", 1);
        set("shen_type", -1);

        set("combat_exp", 25000);

        set("max_qi", 300);
        set("max_jing", 100);
        set("neili", 500);
        set("max_neili", 500);
        set("attitude", "friendly");

        setup();
        carry_object("/d/beijing/npc/obj/nvcloth")->wear();
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object me)
{
    command("look"+query("id", me));

    if( query("gender", me) == "無性"){
       command("say 你當老娘是爛婊子嗎？辣塊媽媽，老娘滿漢蒙藏回都接，就是不伺候太監！");
       command("kick"+query("id", me));
       message("vision", me->name() +"被老鴇婆一腳踢出門外。\n",
                environment(me), ({me}));
       me->move("/d/beijing/wang_8");
       message("vision", me->name() +"被人從怡紅院裡踢了出來，栽倒在地上，磕掉兩顆門牙。\n", 
                environment(me), ({me}));

    }
    else {
    if( query("class", me) == "bonze"){
       command("say 呦，" + RANK_D->query_respect(me) 
                +"也來光顧我們怡紅院啊。");
       command("say 想當年我接過一個西藏喇嘛，他上床前一定要念經，一面念經，眼珠子就骨溜溜的瞧著我。");
    }
    if( query("gender", me) == "女性"){
       command("say 哎呀，這年月大姑娘也逛窯子，成何體統。");
       command("sigh");
       command("say 可惜我兒子不在，不然讓他伺候你。");
    }
    command("say 樓上樓下的姑娘們，客人來了！");
    }
    return ;
}
