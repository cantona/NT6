// Code of ShenZhou
void dest_bug(object bug);
void setup_npc(object me, object ob);

void init()
{
        add_action("do_search", "search");
        add_action("do_search", "zhao");
}        

int do_search(string arg) {
                

        string* n= ({
                "/d/xingxiu/forest10",
                "/d/xingxiu/forest2",
                "/d/xingxiu/forest3",
                "/d/xingxiu/forest11",
                "/d/xingxiu/forest4",
                "/d/xingxiu/forest5",
                "/d/xingxiu/forest1",
                "/d/xingxiu/forest12",
                "/d/xingxiu/forest6",
                "/d/xingxiu/forest7",
                "/d/xingxiu/forest8",
                "/d/xingxiu/forest9",
        });

        object bug, me, fighter, room, gold, ob;

        int kar1, kar2, kar3, pot, max_pot, damage, find;        

        me=this_player();

        if( !arg || arg=="" ) return 0;
        
        if( arg=="bug" || arg=="chong"){

                if (!present("wa guan", me))
                        return notify_fail("你找到蟲子用什麼來盛呢？\n\n");
                        
               if( query("max_jingli", me)<100 )
                       return notify_fail("你的最大精力太少了。\n\n");
                if( query("jingli", me)<query("max_jingli", me)/5 )
                        return notify_fail("你先休息一下吧。\n\n");
                        
                if (me->is_busy()) return
                        notify_fail("你上一個動作還沒有完成。\n"); 
                        
                if (me->is_fighting()) return
                        notify_fail("您先吧敵人料理了在說吧。:)\n");
                        
                if( query_temp("found", me) == 1)return 
                        notify_fail("你最好先回去復命，別讓老仙等急了。\n");
                                       
                //if (me->query_temp("bug_out")==1)
                //        return notify_fail("毒蟲已經出來了，趕快抓吧！\n");
                
                if( query_temp("xx_job", me) != 1 )
                        return notify_fail("找來有什麼用？\n");
                
                addn("jingli", -10, me);
                addn("jing", -10, me);
                me->start_busy(random(1)+1);
                
                addn("find_bug", 1, me);
                addn_temp("xx/find", 1, me);

                message_vision("$N彎下了腰，伸手將殘枝敗葉撥開，仔細尋找毒蟲的蹤跡。\n",me);
                
                kar2=(query("int", me)+query("con", me)+query("str", me))*(random(2)+1);
                kar1=query("kar", me);

                if( query("find_bug", me)>random(20)){
                        set("find_bug", 0, me);
                                
                        room = load_object(n[random(sizeof(n))]);
                        
                        message_vision("$N又找了找，發現沒有絲毫毒蟲的蹤跡，只好離開這裡，到別的地方尋找。\n",me);
                        message_vision("$N急急忙忙地離開了。\n",me);
                        me->move(room);
                        message_vision("$N走了過來。\n",me);                        
                        return 1;
                }
                
                kar3=random(kar1*3);
                find=query_temp("xx/find", me);
                
                if (wizardp(me)) {
                                printf("my kar=%d  kar=%d  randkar=%d  time: %d\n", kar1, kar3, kar2, find);
                }
                
                if ((kar3>kar2 && find>10) || (find>=30)) {

                        message_vision(HIG"突然間一只小蟲子鑽了出來，迅速地爬動著。\n"NOR, me);
                        bug=new("/d/xingxiu/npc/duchong");
                        bug->move(environment(me));
                        set("playerid",query("id",  me), bug);
                        set_temp("bug_out", 1, me);
                        set_temp("xx/find", 0, me);
                        
                        if (wizardp(me)) {
                                printf("playerid:%s\n",query("playerid", bug));
                        }
                                                
                        return 1;
                        
                 }
                
                   if( query("combat_exp", random(50) <= 3 && count_ge(me),150000) && query_temp("xx_job", me)){

                        message_vision(HIR"突然間從樹後越出一個人，高喊一聲：“星宿姦人，拿命來！”\n"NOR,me);
                     fighter = new(CLASS_D("generate") + "/xxnpc.c");
                     NPC_D->set_from_me(fighter, me, 110 + random(20));
                     fighter->addn_temp("apply/attack",fighter->query_skill("force")*
                                             1/ 15);
                     fighter->addn_temp("apply/dodge",fighter->query_skill("force")*
                                             1/ 15);
                     fighter->addn_temp("apply/parry",fighter->query_skill("force")*
                                             1/ 15);
                     addn_temp("apply/damage", 5+1*7, fighter);
                     addn_temp("apply/unarmed_damage", 5+1*7, fighter);
                     addn_temp("apply/armor", 10+1*15, fighter);
                        set("player",query("id",  me), fighter);
                        fighter->move(environment(me));
                        fighter->kill_ob(me);
                        //fighter->set_busy(random(2));                        
                        return 1;
                }
                
                
                if (random(kar1*3)<1){
                        message_vision(HIW"$N眼前銀光一閃，哇，銀子！\n"NOR,me);
                        gold=new("/clone/money/silver");
                        gold->move(environment(me));
                        return 1;
                }
                
                if (random(kar1*2)<1){
                        message_vision(YEL"$N眼前銅光一閃，哇，銅錢 :(\n"NOR,me);
                        gold=new("/clone/money/coin");
                        gold->move(environment(me));
                        return 1;
                }
                
                if (random(kar1*4)<1){
                        message_vision(HIY"$N眼前金光一閃，哇，金子！\n"NOR,me);
                        message_vision(HIR"$N看見金子，心中一得意，手中瓦罐掉到地上打的粉碎。\n"NOR,me);
                        gold=new("/clone/money/gold");
                        gold->move(environment(me));
                        ob = present("wa guan", me);
                        if(ob)destruct(ob);
                        delete_temp("xx_job", me);
                        return 1;
                }
                
                if (random(20)<1){
                        message_vision(MAG"\n$N哎呀一聲，被地上的石頭絆了一交。\n"NOR,me);
                        me->start_busy(random(3)+2);
                        damage=me->query_skill("force",1);
                        me->receive_wound("qi", random(damage/10));
                }

                
                
        return 1;        
        } else if(arg=="dochong"){
                
                set_temp("fresh", 1, me);
                message_vision("$N彎下了腰，伸手將殘枝敗葉撥開，仔細尋找毒蟲的蹤跡。\n",me);
                
                if( query("find_bug", me)>random(20)){
                        set("find_bug", 0, me);
                                
                        room = load_object(n[random(sizeof(n))]);
                        
                        message_vision("$N又找了找，發現沒有絲毫毒蟲的蹤跡，只好離開這裡，到別的地方尋找。\n",me);
                        message_vision("$N急急忙忙地離開了。\n",me);
                        me->move(room);
                        message_vision("$N走了過來。\n",me);                        
                        return 1;
                }
                
                
                return 1;
        }        
        
}