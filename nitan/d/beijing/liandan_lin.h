void init()
{
        add_action("do_cai","cai");
}

int do_cai(string arg)
{
        object me=this_player();
        object ob;
        object ob1;
        if( query_temp("caiyao", me)<1 )
                return notify_fail("別在這浪費時間了，快走吧。\n");

        if (!arg || arg != "yao")
                return notify_fail("你要採什麼。\n");

        if ( me->is_busy() )
                return notify_fail("慢慢找，先別急。\n");
       
        if( query("jing", me)<40 )
                return notify_fail("你太累了，休息下吧。\n");

        if( query("qi", me)<40 )
                return notify_fail("你太累了，休息下吧。\n");

        if( query_temp("caiyao", me) == 2 )
                return notify_fail("東西到手，快去交了吧。\n"); 

        message_vision("$N趴在地上，瞪大了眼睛在草叢中找尋著藥草，生怕漏掉了目標。\n",me); 

        me->start_call_out((: call_other, __FILE__, "cai", me :), 3); 
        me->start_busy(4); 
        return 1;
}
 
int cai(object me)
{ 
        object ob;
        object ob1;        
        if (random(10)<7)
        {
        me->receive_damage("jing",10+random(20));
        me->receive_damage("qi",10+random(20));   
        message_vision(CYN"一翻摸索後，草叢中似乎沒有$N要找的東西，$N失望的嘆了口氣。\n"NOR,me);
        }

        if (random(20) ==1 && ! present("du she", environment(me))) 
        {         
        tell_room(environment(me),HIR"草叢中一陣晃動，突然鑽出一條毒蛇。\n"NOR );
        ob=new("/d/beijing/npc/liandan_dushe");
        ob->move(environment(me));
        }

   else if(random(20)==1 && ! present("du langzhong", environment(me))) 
        {         
        tell_room(environment(me),HIR"林子後面突然跳出一個兇神惡剎的男子，手提一把短刀向你撲來！\n"NOR );
        ob=new("/d/beijing/npc/liandan_langzhong");
        ob->move(environment(me));
        }
   else
        { 
        ob1 = new("/d/beijing/npc/dan/caoyao");
        ob1->move(me);
        me->receive_damage("jing",10+random(20));
        me->receive_damage("qi",10+random(20));
        addn_temp("caiyao", 1, me);
        message_vision(HIG"$N找了半天，終于發現其中一株草苗與其它的草略有不同，
小心翼翼地掘了出來。\n"NOR,me); 
        }
        me->stop_busy();
        return 1;
       
}