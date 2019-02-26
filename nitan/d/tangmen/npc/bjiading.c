// bjiading

inherit NPC;

int do_giveto(object me, object obj);
int ask_tool();

void create()
{
        set_name("家丁", ({ "jia ding", "ding"}));
        set("long", 
"家丁xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx。\n");
        set("gender", "男性");
        set("age", 35);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 18);
        set("int", 25);
        set("con", 24);
        set("dex", 28);

        set("combat_exp", 30000);

        set_skill("force", 30);
        set_skill("dodge", 60);
        set_skill("parry", 40);
        set_skill("sword", 50);
        set_skill("blade", 40);
        set_skill("strike", 50);

        create_family("唐門世家", 4, "家丁");
        set("inquiry", ([
                "tool" : ( : ask_tool  : ),
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_give","give");
}

int do_give(string arg)
{
        object obj, obj2, me, *inv, who;
        string item;
        int amount, i;

        me = this_player();

        if(!arg) return notify_fail("你要給誰什麼東西？\n");

        if( sscanf(arg, "%s to ding", item) == 1 || sscanf(arg, "ding %s", item)==1 );
                else 
                        return notify_fail("你要給誰什麼東西？\n");

        if(!objectp(who = present("jia ding", environment(me))) || !living(who))
                return notify_fail("這裏沒有這個人。\n");

        if(sscanf(item, "%d %s", amount, item)==2)
        {
                if( !objectp(obj = present(item, me)) )        
                        return notify_fail("你身上沒有這樣東西。\n");
                if( !obj->query_amount() )        
                        return notify_fail( obj->name() + "不能被分開給人。\n");
                if( amount < 1 )
                        return notify_fail("東西的數量至少是一個。\n");
                if( amount > obj->query_amount() ) 
                        return notify_fail("你沒有那麼多的" + obj->name() + "。\n");
                else 
                        if( amount == (int)obj->query_amount() )
                                return do_giveto(me, obj2);
                        else
                        {
                                obj->set_amount( (int)obj->query_amount() - amount );
                                obj2 = new(base_name(obj));
                                obj2->set_amount(amount);
                                if (do_giveto(me, obj2))
                                        return 1;
                                else
                                {
                                        obj->set_amount((int)obj->query_amount() + amount);
                                        return 0;
                                }
                        }
        }

        if(arg=="all")
        {
                inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                {
                        do_giveto(me, inv[i]);
                }
                write("Ok.\n");
                return 1;
        }

        if(!objectp(obj = present(item, me)))
                return notify_fail("你身上沒有這樣東西。\n");
        return do_giveto(me, obj);
}

int do_giveto(object me, object obj)
{
        string tar, targ;
        int tarm;
        string *duwu = ({
                "","鐵礦石",
        });
        tar=query("name", obj);
        tarm=query_temp("biao", me);
        targ = (string)duwu[tarm];

        if( query("family/family_name", me) != "唐門世家" )
        {
                message_vision("$N將一"+query("unit", obj)+tar+"交給家丁。\n",me);
                message_vision("家丁對$N説道:“你是什麼人，為什麼會在這裏！”\n", me);
                message_vision("家丁不接受$N的東西。\n", me);
                return 1;
        }

        if( !environment() || base_name(environment()) != query("startroom") )
        {
                write("家丁説道：真是抱歉，請您等一下到儲料房來找我吧。\n");
                return 0;
        }

        if ( (tar == "鐵錘") && objectp(obj) && !userp(obj) && !obj->is_character() )
        {
                message_vision("家丁衝着$N一恭身，説道：“用完了就讓我收拾起來吧！”\n", me);
                message_vision("$N將一柄大鐵錘交給家丁。\n", me);
                message_vision("家丁接過鐵錘收在身後。\n", me);
                destruct(obj);
                delete("tangmen/gettool", me);
                return 1;
        }


        printf("1%s1 == 1%s1 == %d/%d\n",tar,targ,tarm,sizeof(duwu));

        if( !query_temp("biao", me) || !query_temp("tangmen", me) )
        {
                message_vision("家丁很怪異的看着$N，欠身説道：“您應該沒有做這裏的工作吧！”\n", me);
                return 0;
        }        

        if ( (tar == targ) && objectp(obj) )
        {
                message_vision("家丁衝着$N一恭身，説道：“辛苦您了，東西就交給我吧！”\n", me);
                delete_temp("tangmen", me);
                delete_temp("find", me);
                delete_temp("biao", me);
                addn("combat_exp", 150+random(150), me);
                return 1;
        }
        else
        {
                message_vision("家丁很為難的看着$N，欠身説道：“這不是你要給我的東西吧！”\n", me);
                return 0;
        }
}

int ask_tool()
{
        object me;
        me = this_player();

        if( query("family/family_name", me) != "唐門世家" )
        {
                message_vision("家丁對$N説道:“你是什麼人，為什麼會在這裏！”\n", me);
                return 1;
        }

        if( !environment() || base_name(environment()) != query("startroom") )
        {
                command("say “真是抱歉，請您等一下到儲料房來找我吧。”\n");
                return 1;
        }

        if( query("tangmen/gettool", me) )
        {
                command("say “你上次借的工具還沒還我呢，還想要？”\n");
                return 1;
        }


        if( query_temp("biao", me) )
        {
                command("say “哦，是唐鏢老爺子讓你來的吧！拿去吧！”");
                message_vision("家丁從身後取出一柄大鐵錘交給$N，説道:“用完了記得還回來！”\n", me);
                new("/d/tangmen/obj/tiechui")->move(me);
                set("tangmen/gettool", 1, me);
        }
        else
                command("say “恩？誰讓你來要工具的！”\n");
        return 1;
}