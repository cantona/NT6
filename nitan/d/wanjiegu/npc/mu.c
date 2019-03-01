// mu.c
inherit NPC;

void create()
{
        set_name("木婉清", ({ "mu wanqing","mu" }) );
        set("gender", "女性" );
        set("age", 17);
        set("str", 26);
        set("con", 24);
        set("dex", 21);
        set("per", 28);
        set("int", 27);
        set("long",
        "一張臉秀麗絕俗，如新月清暉，如花樹堆雪。\n"
        "看上去楚楚可憐，嬌柔婉轉。只是長時間面幕\n"
        "臉之故，臉色蒼白，沒半點血色，兩片薄薄的\n"
        "嘴唇，也是血色極淡。\n");

        set("attitude", "friendly");

        set("inquiry", ([
                "段譽" : "段哥哥呢？他在哪兒？說完，木婉清的臉上現出一絲紅暈。",
                "鐘靈" : "鐘靈這死丫頭，哼！",
                "木婉清" : "我就是木婉清。",
        ]));

        set("max_neili", 600);
        set("neili", 200);
        set("force_factor" , 50);
        set("combat_exp", 550000);

        set_skill("finger", 100);
        set_skill("parry", 100);
        set_skill("dodge", 100);
        set_skill("sword", 100);
        set_skill("force", 100);
        set_skill("sun-finger",100);
        set_skill("yizhi-chan",100);

        map_skill("finger", "sun-finger");
        map_skill("parry", "sun-finger");

        setup();

       carry_object("/d/wanjiegu/npc/obj/dress")->wear();
        carry_object("/d/wanjiegu/npc/obj/shoes")->wear();
}

int accept_object(object who, object ob)
{
        if (ob->name() == "絕情花") {
                if (userp(ob) || ob->is_item_make() || ob->query_save_file())
                {
                      who->get_into_prison(this_object(), 0, 30);
                      return 1;
                }
           message_vision("$N拿出一朵絕情花給木婉清。\n",who);
           call_out("do_give", 1, who );
           return 1;
        }
        return 0;
}

void do_give(object me)
{
        object room = find_object(__DIR__"backyard");
        object who;
        object obj;

        message_vision("木婉清將絕情花吃了下去，她中的「陰陽合和散」的藥性解除了！\n",me);
        command("say 太謝謝了，我這就要離開這是非之地，後會有期！");
        message_vision("木婉清取出一根彩菱往外一拋，身影如風一般飛了出去。\n",me);
        message_vision("只聽外面腳步聲漸漸遠去，又有人追了過去。\n", me);
        obj = new("/d/item/obj/xuantie");
        if (! obj->move(me)) obj->move(environment());
        addn("combat_exp", random(60)+20, me);
        addn("potential", random(30)+20, me);

        destruct( this_object() );
}
