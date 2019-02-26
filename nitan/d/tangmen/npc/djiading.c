// bguanli

inherit NPC;

int do_giveto(object me, object obj);

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
                "","蜈蚣","毒蠍子","竹葉青","金環蛇","蝮蛇","千年毒王",
        });
        tar=query("name", obj);
        tarm=query_temp("duyao", me);
        targ = (string)duwu[tarm];

        if( !environment() || base_name(environment()) != query("startroom") )
        {
                write("家丁説道：真是抱歉，請您等一下到儲料房來找我吧。\n");
                return 0;
        }

//      printf("1%s1 == 1%s1 == %d/%d\n",tar,targ,tarm,sizeof(duwu));

        if( !query_temp("duyao", me) || !query_temp("tangmen", me) )
        {
                message_vision("家丁很怪異的看着$N，欠身説道：“您應該沒有做這裏的工作吧！”\n", me);
                return 0;
        }        

        if ( (tar == targ) && objectp(obj) && !userp(obj) && !obj->is_character())
        {
                message_vision("家丁衝着$N一恭身，説道：“辛苦您了，東西就交給我吧！”\n", me);
                destruct(obj);
                delete_temp("tangmen", me);
                delete_temp("duyao", me);
                addn("combat_exp", 150+random(150), me);
                addn("potential", 80+random(30), me);
                return 1;
        }
        else
        {
                message_vision("家丁很為難的看着$N，欠身説道：“這不是你應該找到的東西吧！”\n", me);
                return 0;
        }
}